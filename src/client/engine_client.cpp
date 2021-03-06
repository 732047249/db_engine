/***************************************************************************
 *
 * Copyright (c) 2014 aishuyu, Inc. All Rights Reserved
 *
 **************************************************************************/



/**
 * @file engine_client.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2014/12/10 17:24:45
 * @brief
 *
 **/

#include "engine_client.h"

#include "common/common.h"

namespace db_engine {

using namespace libevrpc;

EngineClient::EngineClient() : serveice_stub_ptr_(NULL) {
    ClientInit();
}

EngineClient::~EngineClient() {
    if (NULL != serveice_stub_ptr_) {
        delete serveice_stub_ptr_;
    }
}

bool EngineClient::ClientInit() {
    const char* addr = DB_SYS_CONF.IniGetString("host:addr");
    const char* port = DB_SYS_CONF.IniGetString("host:port");
    InitClient(addr, port);
    serveice_stub_ptr_ = new EngineService::Stub(GetRpcChannel());

    return true;
}

bool EngineClient::Put(const char* key, const char* value) {
    DBRequest db_request;
    db_request.set_db_key(key);
    db_request.set_db_value(value);

    DBResponse db_reponse;
    serveice_stub_ptr_->Put(NULL, &db_request, &db_reponse, NULL);
    if (ERR == db_reponse.code()) {
        DB_LOG(ERROR, "put failed! engine rpc server error");
        return false;
    }
    return true;
}

bool EngineClient::Get(const char* key, std::string& value) {
    DBRequest db_request;
    db_request.set_db_key(key);

    DBResponse db_reponse;
    serveice_stub_ptr_->Get(NULL, &db_request, &db_reponse, NULL);
    if (ERR == db_reponse.code()) {
        DB_LOG(ERROR, "get failed! engine rpc server error");
        return false;
    }
    value = db_reponse.db_res();
    return true;
}

bool EngineClient::Delete(const char* key) {
    DBRequest db_request;
    db_request.set_db_key(key);

    DBResponse db_reponse;
    serveice_stub_ptr_->Delete(NULL, &db_request, &db_reponse, NULL);
    if (ERR == db_reponse.code()) {
        DB_LOG(ERROR, "del failed! engine rpc server error");
        return false;
    }

    return true;
}


}  // end of namespace db_engine





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
