#ifndef SRC_FUTU_FUTUPARSER_H
#define SRC_FUTU_FUTUPARSER_H

#include <string>
#include <Interface/datastructure.h>
#include <Helper/util.h>
#include <rapidjson/document.h>
#include <rapidjson/rapidjson.h>


using namespace std;
namespace ts{



    inline void FutuQot2TsQot(const std::string& src, std::vector<shared_ptr<BaseData>>& des){
        rapidjson::Document doc;
        String2Json(src, doc);
        const rapidjson::Value& list = doc["s2c"]["basicQotList"];

        for(rapidjson::SizeType i = 0; i<list.Size(); i++){
            std::unique_ptr<ts::Quote> temp = make_unique<ts::Quote>();
            strcpy(temp->code_, list[i]["security"]["code"].GetString());
            strcpy(temp->time_, list[i]["updateTime"].GetString());
            strcpy(temp->exg_, "FUTU");

            temp->hPrice_ = list[i]["highPrice"].GetDouble();
            temp->oPrice_ = list[i]["openPrice"].GetDouble();
            temp->lPrice_ = list[i]["lowPrice"].GetDouble();
            temp->cPrice_ = list[i]["curPrice"].GetDouble();
            temp->lcPrice_ = list[i]["lastClosePrice"].GetDouble();
            temp->pSpread_ = list[i]["priceSpread"].GetDouble();
            temp->volume_ = list[i]["volume"].GetInt64();
            temp->turnover_ = list[i]["turnover"].GetDouble();
            temp->turnoverRate_ = list[i]["turnoverRate"].GetDouble();
            temp->amplitude_ = list[i]["amplitude"].GetDouble();
            temp->timestamp_ = list[i]["updateTimestamp"].GetDouble();

            temp->sPrice_ = list[i]["optionExData"]["strikePrice"].GetDouble();
            temp->conSize_ = list[i]["optionExData"]["contractSize"].GetDouble();
            temp->opInterest_ = list[i]["optionExData"]["openInterest"].GetInt64();
            temp->impVolatility_ = list[i]["optionExData"]["impliedVolatility"].GetDouble();
            temp->premium_ = list[i]["optionExData"]["premium"].GetDouble();
            temp->delta_ = list[i]["optionExData"]["delta"].GetDouble();
            temp->gamma_ = list[i]["optionExData"]["gamma"].GetDouble();
            temp->vega_ = list[i]["optionExData"]["vega"].GetDouble();
            temp->theta_ = list[i]["optionExData"]["theta"].GetDouble();
            temp->rho_ = list[i]["optionExData"]["rho"].GetDouble();


            temp->lsprice_ = list[i]["futureExData"]["lastSettlePrice"].GetDouble();
            temp->position_ = list[i]["futureExData"]["position"].GetInt64();
            temp->pChange_ = list[i]["futureExData"]["positionChange"].GetInt64();

            des.push_back(move(temp));
        }
    }
}



#endif