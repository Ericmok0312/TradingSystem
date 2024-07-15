#ifndef SRC_DATAMANAGER_LMDBKEYS_H
#define SRC_DATAMANAGER_LMDBKEYS_H

#include <Interface/datastructure.h>
#include <sstream>


static uint32_t reverseEndian(uint32_t src)
{
	uint32_t x = (src & 0x000000FF) << 24;
	uint32_t y = (src & 0x0000FF00) << 8;
	uint32_t z = (src & 0x00FF0000) >> 8;
	uint32_t w = (src & 0xFF000000) >> 24;
	return x + y + z + w;
}


typedef struct _LMDBKey{
    char    exg_[MAX_EXG_SIZE];
    char    code_[MAX_SYMBOL_SIZE];
    char    date_[MAX_TIME_SIZE];
    char    time_[MAX_TIME_SIZE];

    _LMDBKey(const char* exg, const char* code, const char* date, const char* time){
        memset(this, 0, sizeof(_LMDBKey));
        strcpy(exg_, exg);
        strcpy(code_, code);
        strcpy(date_, date);
        strcpy(time_, time);

    }

    inline string getString(){
        stringstream ss;
        ss<<exg_<<"/"<<code_<<"/"<<date_<<"/"<<time_;
        return move(ss.str());
    }
}LMDBKey;




#endif