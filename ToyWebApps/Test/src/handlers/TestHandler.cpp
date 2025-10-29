#include "../../include/handlers/TestHandler.h"

void TestHandler::handle(const http::HttpRequest& req, http::HttpResponse* resp) {
    // 简单响应测试
    std::string responseBody = "Hello from TestHandler!";
    resp->setStatusLine(req.getVersion(), http::HttpResponse::k200Ok, "OK");
    resp->setContentType("text/plain");
    resp->setBody(responseBody);
    resp->setContentLength(responseBody.size());
    resp->setCloseConnection(false);
}