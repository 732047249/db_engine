/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file libev_connector.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/01/27 15:35:38
 * @brief 
 *  
 **/


#include "libev_connector.h"

#include <string>

#include "socket_util.h"
#include "rpc_server.h"
#include "../log/db_log.h"

namespace db_engine {

using std::string;

LibevConnector::LibevConnector() : epoller_(NULL) {
}

LibevConnector::~LibevConnector() {
    if (NULL != epoller_) {
        ev_loop_destroy(epoller_);
    }
}

bool LibevConnector::Initialize(const char *host, const char *port) {
    int32_t listenfd = TcpListen(host, port);
    if (listenfd < 0) {
        DB_LOG(ERROR, "rpc server listen failed!")
        return false;
    }
    
    epoller_ = ev_loop_new(EVBACKEND_EPOLL | EVFLAG_NOENV);
    
    // set callback AcceptCb, Note the function AcceptCb must be static function
    ev_io_init(&socket_watcher_, LibevConnector::AcceptCb, listenfd, EV_READ);
    ev_io_start(epoller_, &socket_watcher_);

    return true;
}

void LibevConnector::LibevLoop() {
    if (NULL == epoller_) {
        DB_LOG(ERROR, "It is not Initialize!");
        return;
    }
    
    while (true) {
        ev_loop(epoller_, 0);
    }
}

void LibevConnector::AcceptCb(struct ev_loop *loop, struct ev_io *watcher, int revents) {
    if (EV_ERROR & revents) {
        DB_LOG(ERROR, "ERROR event in accept callback! exit!");
        return;
    }
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    int32_t cfd = Accept(watcher->fd, client_addr, len);
    if (cfd < 0) {
        return;
    }

    DB_LOG(INFO, "NEW connection coming!!");
    struct ev_io *client_eio = (struct ev_io*)malloc(sizeof(struct ev_io));
    ev_io_init(client_eio, LibevConnector::ProcessCb, cfd, EV_READ);
    ev_io_start(loop, client_eio);
}

void LibevConnector::ProcessCb(struct ev_loop *loop, struct ev_io *watcher, int revents) {
    if (EV_ERROR & revents) {
        DB_LOG(ERROR, "ERROR event in process callback! exit!");
        free(watcher);
        return;
    }

    RpcServer& rpc_server = RpcServer::GetInstance();
    rpc_server.RpcCall(watcher->fd);
    ev_io_stop(loop, watcher);
    free(watcher);
}

}  // end namespace db_engine


/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
