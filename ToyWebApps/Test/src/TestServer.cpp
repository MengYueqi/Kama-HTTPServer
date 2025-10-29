#include "../include/TestServer.h"

#include "../include/handlers/TestHandler.h"

TestServer::TestServer(int port, const std::string& name, muduo::net::TcpServer::Option option)
    : httpServer_(port, name, option) {
    initialize();
}

TestServer::~TestServer() {}

void TestServer::initialize() {
    initializeRouter();  // 初始化路由
};

// 初始化路由
void TestServer::initializeRouter() {
    httpServer_.Get("/test", std::make_shared<TestHandler>(this));
};

// 启动服务器
void TestServer::start() {
    httpServer_.start();
}