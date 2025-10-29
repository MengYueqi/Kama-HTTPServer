#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <iostream>
#include <string>

#include "../include/TestServer.h"

int main() {
    std::cout << "Hello, Test Start!" << std::endl;
    LOG_INFO << "pid = " << getpid();

    std::string serverName = "TestHttpServer";
    int port = 8080;

    TestServer server(port, serverName, muduo::net::TcpServer::kReusePort);
    server.start();
}