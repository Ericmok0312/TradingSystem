#ifndef SRC_DATAMANAGER_TSLMDB_HPP
#define SRC_DATAMANAGER_TSLMDB_HPP

#include <liblmdb/lmdb.h>
#include <unistd.h>
#include <sys/stat.h>
#include <algorithm>
#include <vector>
#include <string>
#include <functional>
#include <Helper/util.h>

namespace ts{

    typedef std::vector<std::string> ValueArray;
    typedef std::function<void(const ValueArray&, const ValueArray&)> LMDBCB;


    class TsLMDB{
        public:
            TsLMDB(bool bReadOnly = false):env_(nullptr), dbi_(0), errno_(0), readonly_(bReadOnly){}


            ~TsLMDB(){
                if(dbi_ != 0){
                    mdb_dbi_close(env_, dbi_);
                }
                if(env_ != nullptr){
                    mdb_env_close(env_);
                }
            } 

            inline MDB_env* env(){return env_;}

            inline MDB_dbi dbi(){return dbi_;}

            
            inline MDB_dbi update_dbi(MDB_txn* txn){
                if(dbi_ != 0){
                    return dbi_; // if dbi_ is created alr, no need to open again
                }
                //open dbi with txn, dbi is 0 is not created
                errno_ = mdb_dbi_open(txn, nullptr, MDB_DUPSORT, &dbi_);
                return dbi_;
            }

            inline bool open(const char* path, long long mapsize = 1099511627776){
                int ret = access(path, 0);

                if(ret!=0){ //does not exist
                    mkdir(path, 777); // create file with all permission to all users
                }


                errno_ = mdb_env_create(&env_); // create an lmdb env handler
                if(errno_ != MDB_SUCCESS){
                    return false; //error occur when create the env
                }

                errno_ = mdb_env_open(env_, path, 0, 0664);
                if(errno_ != MDB_SUCCESS){
                    return false; //error occur when open the file
                }

                errno_ = mdb_env_set_mapsize(env_, mapsize); // set map size

                return true;


            }

            inline int errmsg(){ return errno_;}

            inline bool is_readonly() {return readonly_;}

            inline void update_errorno(int err){errno_ = err;}

        private:
            MDB_env* env_;
            MDB_dbi dbi_;
            int errno_;
            bool readonly_;
    };



    /// @brief Class for read-write operation on an opened 
    class TSQryLMDB{
        public:
            TSQryLMDB(TsLMDB& db): txn_(NULL), commited_(false), db_(db){
                readonly_ = db.is_readonly();
                //Setting up txn with db's env
                db_.update_errorno(mdb_txn_begin(db_.env(), NULL, (readonly_ ? MDB_RDONLY : 0), &txn_));
                dbi_ = db_.update_dbi(txn_);
            }

            ~TSQryLMDB(){
                if(readonly_){
                    mdb_txn_abort(txn_); //if readonly directly abort txn
                }
                else if(!commited_){
                    db_.update_errorno(mdb_txn_commit(txn_)); // commit the txn if not commited
                }
            }

            inline void rollback(){
                if(commited_) return;

                mdb_txn_abort(txn_); // abort the txn_ for redo
                commited_ = true; // doesn't need to commit when destructed
            }

            inline void commit(){
                if(commited_ || readonly_){
                    return; // cannot commit if is the above 2 cases
                }

                db_.update_errorno(mdb_txn_commit(txn_)); // commit the txn
                commited_ = true; // no need to commit in destructor
            }


            inline bool put(const std::string& key, const std::string& val){
                return Put((void*)key.data(), key.size(), (void*)val.data(), val.size());
            }

    
            inline bool Put(void* key, std::size_t klen, void* val, std::size_t vlen){
                MDB_val mKey, mData;
                //setting key
                mKey.mv_data = key;
                mKey.mv_size = klen;

                //setting value
                mData.mv_data = val;
                mData.mv_size = vlen;

                int error  = mdb_put(txn_, dbi_, &mKey, &mData, MDB_NODUPDATA); // update to database
                db_.update_errorno(error); // update error in database
                return error == MDB_SUCCESS;
            }


            inline bool put_and_commit(const std::string key, const std::string val){
                return Put_And_Commit((void*)key.data(), key.size(), (void*)val.data(), val.size());
            }

            inline bool Put_And_Commit(void* key, std::size_t klen, void* val, std::size_t vlen){
                uint64_t init = GetTimeStamp();
                MDB_val mKey, mData;
                //setting key
                mKey.mv_data = key;
                mKey.mv_size = klen;

                //setting value
                mData.mv_data = val;
                mData.mv_size = vlen;

                int error  = mdb_put(txn_, dbi_, &mKey, &mData, 0); // update to database
                db_.update_errorno(error); // update error in database
                if (error != MDB_SUCCESS){
                    return false;
                } 

                error = mdb_txn_commit(txn_);
                db_.update_errorno(error);
                commited_ = true;

                val = nullptr;
                return error == MDB_SUCCESS;
                
            }

            std::string get(const std::string& key){
                return Get((void*)key.data(), key.size());
            }

            //reading database with given key
            std::string Get(void* key, std::size_t klen){
                MDB_cursor* cursor;
                int error = mdb_cursor_open(txn_, dbi_, &cursor);
                db_.update_errorno(error);

                if(error != MDB_SUCCESS){
                    return std::move(std::string()); // return empty string by move
                }

                MDB_val mKey, mData;
                mKey.mv_data = key;
                mKey.mv_size = klen;

                error = mdb_cursor_get(cursor, &mKey, &mData, MDB_NEXT); // get the data
                db_.update_errorno(error);
                if(error != MDB_SUCCESS){
                    return std::move(std::string());
                }

                std::string ret = std::string((char*)mData.mv_data, mData.mv_size);
                mdb_cursor_close(cursor);
                return std::move(ret);

            }

            int get_range(const std::string& lower_key, const std::string& upper_key, LMDBCB callback){
                MDB_cursor* cursor;
                int error = mdb_cursor_open(txn_, dbi_, &cursor);
                db_.update_errorno(error);
                if (error != MDB_SUCCESS)
                    return 0;

                MDB_val lKey, rKey, mData;
                lKey.mv_data = (void*)lower_key.data();
                lKey.mv_size = lower_key.size();

                rKey.mv_data = (void*)upper_key.data();
                rKey.mv_size = upper_key.size();

                int cnt = 0;

                MDB_cursor_op op = MDB_SET_RANGE; // define cursor operations to be set range
                ValueArray Keys, Vals;

                for(; (error = mdb_cursor_get(cursor, &lKey, &mData, op)) == MDB_SUCCESS;){
                    db_.update_errorno(error);
                    if(error == MDB_NOTFOUND){
                        break;
                    }

                    if (memcmp(lKey.mv_data, rKey.mv_data, lKey.mv_size) > 0){
                        break; //out of range;
                    }
                    Keys.emplace_back(std::string((char*)lKey.mv_data, lKey.mv_size));
                    Vals.emplace_back(std::string((char*)mData.mv_data, mData.mv_size));
                    cnt++;
                    op = MDB_NEXT; //lKey move to next element
                }
                callback(Keys, Vals); //calling callback to handle retrieved data;
                mdb_cursor_close(cursor);
                return cnt;
            }


            int get_lowers(const std::string& lower_key, const std::string& upper_key, int count, LMDBCB callback){
                MDB_cursor* cursor;
                int error = mdb_cursor_open(txn_, dbi_, &cursor);
                db_.update_errorno(error);
                if(error!=MDB_SUCCESS) return 0;


                MDB_val rKey, mData;
                rKey.mv_data = (void*) upper_key.data();
                rKey.mv_size = upper_key.size();


                int cnt = 0;
                ValueArray Keys, Vals;
                error = mdb_cursor_get(cursor, &rKey, &mData, MDB_SET_RANGE);
                db_.update_errorno(error);


                if(error == MDB_NOTFOUND){
                    error = mdb_cursor_get(cursor, &rKey, &mData, MDB_LAST);
                    db_.update_errorno(error);
                }

                for(; error != MDB_NOTFOUND;){
                    if(memcmp(rKey.mv_data, upper_key.data(), upper_key.size())>0){ // not reaching the upperbound, continue to shift
                        error = mdb_cursor_get(cursor, &rKey, &mData, MDB_PREV);
                        db_.update_errorno(error);
                        continue;
                    }

                    if(memcmp(rKey.mv_data, lower_key.data(), lower_key.size())<0){
                        break;
                    }

                    Keys.emplace_back(std::string((char*)rKey.mv_data, rKey.mv_size));
                    Vals.emplace_back(std::string((char*)mData.mv_data, mData.mv_size));
                    cnt++;

                    if (cnt==count) break;

                    error = mdb_cursor_get(cursor, &rKey, &mData, MDB_PREV);
                    db_.update_errorno(error);
      
		            reverse(Keys.begin(), Keys.end());
		            reverse(Vals.begin(), Vals.end());
		            callback(Keys, Vals);
		            mdb_cursor_close(cursor);
                    return cnt;
                }
            }

            int get_all(LMDBCB callback){ //pure callback as input will lead to compilation error
                MDB_cursor* cursor;
                int errorno_ = mdb_cursor_open(txn_, dbi_, &cursor);
                if (errorno_ != MDB_SUCCESS) return 0;
                MDB_val rKey, mData;
                std::vector<std::string> Keys, Vals;

                for (; errorno_ != MDB_NOTFOUND;){
                    errorno_ = mdb_cursor_get(cursor, &rKey, &mData, MDB_NEXT);
                    db_.update_errorno(errorno_);

                    Keys.emplace_back(std::string((char*)rKey.mv_data, rKey.mv_size));
                    Vals.emplace_back(std::string((char*)mData.mv_data, mData.mv_size));
                }
                callback(Keys, Vals);
                return (int)Vals.size();
            }


        private:
            TsLMDB& db_;
            MDB_txn* txn_;
            MDB_dbi dbi_;
            bool readonly_;
            bool commited_;
    };

}




#endif