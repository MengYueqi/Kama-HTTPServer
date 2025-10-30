#pragma once

#include <string>

#include "../../../HttpServer/include/http/HttpServer.h"
#include "../../../HttpServer/include/utils/JsonUtil.h"
#include "../../../HttpServer/include/utils/MysqlUtil.h"

class TestHandler;

class TestServer {
   private:
    http::HttpServer httpServer_;
    void initializeRouter();
    http::MysqlUtil mysqlUtil_;

   private:
    friend TestHandler;

   public:
    TestServer(int port, const std::string& name,
               muduo::net::TcpServer::Option option = muduo::net::TcpServer::kNoReusePort);
    ~TestServer();
    void initialize();
    void start();
};
