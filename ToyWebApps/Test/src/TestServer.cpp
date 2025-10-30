#include "../include/TestServer.h"

#include "../include/handlers/TestHandler.h"

TestServer::TestServer(int port, const std::string& name, muduo::net::TcpServer::Option option)
    : httpServer_(port, name, option) {
    initialize();
}

TestServer::~TestServer() {}

void TestServer::initialize() {
    http::MysqlUtil::init("tcp://127.0.0.1:3306", "root", "123456", "Gomoku", 10);
    std::cout << mysqlUtil_.executeQuery("SHOW TABLES") << std::endl;
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