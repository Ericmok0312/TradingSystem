#include <Interface/datastructure.h>
#include <Interface/IMessenger.h>
#include <Interface/IEngine.h>
#include <Helper/logger.h>
#include <futu/FTAPI.h>
#include <futu/FTSPI.h>

using namespace Futu;

namespace ts
{
    

    class FutuEngine: public IEngine, public Futu::FTSPI_Qot, public Futu::FTSPI_Trd, public Futu::FTSPI_Conn {
        protected:
            Futu::FTAPI_Qot* futuQotApi_;
            Futu::FTAPI_Trd* futuTrdApi_;
            static std::mutex getIns_mutex;
            static shared_ptr<FutuEngine> instance_;
        public:
            FutuEngine();
            virtual ~FutuEngine();


            static std::shared_ptr<FutuEngine> getInstance();


            virtual void init();
            virtual void start();
            virtual void stop(); 
            virtual void setTradeMode(){};
            virtual void lockTXN(){};
            virtual void unlockTXN(){};
            virtual void subscribe(const char* code, int32_t subtype);
            //virtual void subscribe(Json::Value&& param);
            virtual void getFund(int id, int32_t market, int32_t mode);
            //virtual void getFund(Json::Value&& param);
            virtual void getAccessList();


            virtual void regCallBack(const char* code, int32_t subtype);
            // overriding Futu's pure virtual functions

            virtual void OnInitConnect(Futu::FTAPI_Conn* pConnect, Futu::i64_t nErrCode, const char* strDesc){};
            virtual void OnDisConnect(FTAPI_Conn* pConn, Futu::i64_t nErrCode){}


            virtual void OnReply_GetGlobalState(Futu::u32_t nSerialNo, const GetGlobalState::Response &stRsp){}
            virtual void OnReply_Sub(Futu::u32_t nSerialNo, const Qot_Sub::Response &stRsp);
            virtual void OnReply_RegQotPush(Futu::u32_t nSerialNo, const Qot_RegQotPush::Response &stRsp){}
            virtual void OnReply_GetSubInfo(Futu::u32_t nSerialNo, const Qot_GetSubInfo::Response &stRsp){}
            virtual void OnReply_GetTicker(Futu::u32_t nSerialNo, const Qot_GetTicker::Response &stRsp){}
            virtual void OnReply_GetBasicQot(Futu::u32_t nSerialNo, const Qot_GetBasicQot::Response &stRsp){};
            virtual void OnReply_GetOrderBook(Futu::u32_t nSerialNo, const Qot_GetOrderBook::Response &stRsp){}
            virtual void OnReply_GetKL(Futu::u32_t nSerialNo, const Qot_GetKL::Response &stRsp) {};
            virtual void OnReply_GetRT(Futu::u32_t nSerialNo, const Qot_GetRT::Response &stRsp){}
            virtual void OnReply_GetBroker(Futu::u32_t nSerialNo, const Qot_GetBroker::Response &stRsp){}
            virtual void OnReply_RequestRehab(Futu::u32_t nSerialNo, const Qot_RequestRehab::Response &stRsp){}
            virtual void OnReply_RequestHistoryKL(Futu::u32_t nSerialNo, const Qot_RequestHistoryKL::Response &stRsp){}
            virtual void OnReply_RequestHistoryKLQuota(Futu::u32_t nSerialNo, const Qot_RequestHistoryKLQuota::Response &stRsp){}
            virtual void OnReply_GetTradeDate(Futu::u32_t nSerialNo, const Qot_GetTradeDate::Response &stRsp){}
            virtual void OnReply_GetStaticInfo(Futu::u32_t nSerialNo, const Qot_GetStaticInfo::Response &stRsp){}
            virtual void OnReply_GetSecuritySnapshot(Futu::u32_t nSerialNo, const Qot_GetSecuritySnapshot::Response &stRsp) {};
            virtual void OnReply_GetPlateSet(Futu::u32_t nSerialNo, const Qot_GetPlateSet::Response &stRsp){}
            virtual void OnReply_GetPlateSecurity(Futu::u32_t nSerialNo, const Qot_GetPlateSecurity::Response &stRsp){}
            virtual void OnReply_GetReference(Futu::u32_t nSerialNo, const Qot_GetReference::Response &stRsp){}
            virtual void OnReply_GetOwnerPlate(Futu::u32_t nSerialNo, const Qot_GetOwnerPlate::Response &stRsp){}
            virtual void OnReply_GetHoldingChangeList(Futu::u32_t nSerialNo, const Qot_GetHoldingChangeList::Response &stRsp){}
            virtual void OnReply_GetOptionChain(Futu::u32_t nSerialNo, const Qot_GetOptionChain::Response &stRsp){}
            virtual void OnReply_GetWarrant(Futu::u32_t nSerialNo, const Qot_GetWarrant::Response &stRsp){}
            virtual void OnReply_GetCapitalFlow(Futu::u32_t nSerialNo, const Qot_GetCapitalFlow::Response &stRsp){}
            virtual void OnReply_GetCapitalDistribution(Futu::u32_t nSerialNo, const Qot_GetCapitalDistribution::Response &stRsp){}
            virtual void OnReply_GetUserSecurity(Futu::u32_t nSerialNo, const Qot_GetUserSecurity::Response &stRsp){}
            virtual void OnReply_ModifyUserSecurity(Futu::u32_t nSerialNo, const Qot_ModifyUserSecurity::Response &stRsp){}
            virtual void OnReply_StockFilter(Futu::u32_t nSerialNo, const Qot_StockFilter::Response &stRsp){}
            virtual void OnReply_GetCodeChange(Futu::u32_t nSerialNo, const Qot_GetCodeChange::Response &stRsp){}
            virtual void OnReply_GetIpoList(Futu::u32_t nSerialNo, const Qot_GetIpoList::Response &stRsp){}
            virtual void OnReply_GetFutureInfo(Futu::u32_t nSerialNo, const Qot_GetFutureInfo::Response &stRsp){}
            virtual void OnReply_RequestTradeDate(Futu::u32_t nSerialNo, const Qot_RequestTradeDate::Response &stRsp){}
            virtual void OnReply_SetPriceReminder(Futu::u32_t nSerialNo, const Qot_SetPriceReminder::Response &stRsp){}
            virtual void OnReply_GetPriceReminder(Futu::u32_t nSerialNo, const Qot_GetPriceReminder::Response &stRsp){}
            virtual void OnReply_GetUserSecurityGroup(Futu::u32_t nSerialNo, const Qot_GetUserSecurityGroup::Response &stRsp){}
            virtual void OnReply_GetMarketState(Futu::u32_t nSerialNo, const Qot_GetMarketState::Response &stRsp){}
            virtual void OnReply_GetOptionExpirationDate(Futu::u32_t nSerialNo, const Qot_GetOptionExpirationDate::Response &stRsp){}

            virtual void OnPush_Notify(const Notify::Response &stRsp){}
            virtual void OnPush_UpdateBasicQot(const Qot_UpdateBasicQot::Response &stRsp);
            virtual void OnPush_UpdateOrderBook(const Qot_UpdateOrderBook::Response &stRsp){}
            virtual void OnPush_UpdateTicker(const Qot_UpdateTicker::Response &stRsp);
            virtual void OnPush_UpdateKL(const Qot_UpdateKL::Response &stRsp){}
            virtual void OnPush_UpdateRT(const Qot_UpdateRT::Response &stRsp){}
            virtual void OnPush_UpdateBroker(const Qot_UpdateBroker::Response &stRsp){}
            virtual void OnPush_UpdatePriceReminder(const Qot_UpdatePriceReminder::Response &stRsp){}

            virtual void OnReply_GetAccList(Futu::u32_t nSerialNo, const Trd_GetAccList::Response &stRsp);
            virtual void OnReply_UnlockTrade(Futu::u32_t nSerialNo, const Trd_UnlockTrade::Response &stRsp){};
            virtual void OnReply_SubAccPush(Futu::u32_t nSerialNo, const Trd_SubAccPush::Response &stRsp){};
            virtual void OnReply_GetFunds(Futu::u32_t nSerialNo, const Trd_GetFunds::Response &stRsp);
            virtual void OnReply_GetPositionList(Futu::u32_t nSerialNo, const Trd_GetPositionList::Response &stRsp){}
            virtual void OnReply_GetMaxTrdQtys(Futu::u32_t nSerialNo, const Trd_GetMaxTrdQtys::Response &stRsp){}
            virtual void OnReply_GetOrderList(Futu::u32_t nSerialNo, const Trd_GetOrderList::Response &stRsp){}
            virtual void OnReply_PlaceOrder(Futu::u32_t nSerialNo, const Trd_PlaceOrder::Response &stRsp){}
            virtual void OnReply_ModifyOrder(Futu::u32_t nSerialNo, const Trd_ModifyOrder::Response &stRsp){}
            virtual void OnReply_GetOrderFillList(Futu::u32_t nSerialNo, const Trd_GetOrderFillList::Response &stRsp){}
            virtual void OnReply_GetHistoryOrderList(Futu::u32_t nSerialNo, const Trd_GetHistoryOrderList::Response &stRsp){}
            virtual void OnReply_GetHistoryOrderFillList(Futu::u32_t nSerialNo, const Trd_GetHistoryOrderFillList::Response &stRsp){}
            virtual void OnReply_GetMarginRatio(Futu::u32_t nSerialNo, const Trd_GetMarginRatio::Response &stRsp){}
            virtual void OnReply_GetOrderFee(Futu::u32_t nSerialNo, const Trd_GetOrderFee::Response& stRsp){}

            virtual void OnPush_UpdateOrder(const Trd_UpdateOrder::Response &stRsp){}
            virtual void OnPush_UpdateOrderFill(const Trd_UpdateOrderFill::Response &stRsp){}

    };


} // namespace ts
