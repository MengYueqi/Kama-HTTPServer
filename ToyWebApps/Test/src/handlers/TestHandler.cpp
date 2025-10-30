#include "../../include/handlers/TestHandler.h"

void TestHandler::handle(const http::HttpRequest& req, http::HttpResponse* resp) {
    // json requestJson;
    // 简单响应测试
    std::string responseBody = R"({"message": "Hello from TestHandler!", "name": ")" +
                               req.getQueryParameters("name") + R"("})";
    resp->setStatusLine(req.getVersion(), http::HttpResponse::k200Ok, "OK");
    resp->setContentType("application/json");
    resp->setBody(responseBody);
    resp->setContentLength(responseBody.size());
    resp->setCloseConnection(false);
}