#pragma once
#include "../../../../HttpServer/include/router/RouterHandler.h"
#include "../TestServer.h"

class TestHandler : public http::router::RouterHandler {
   public:
    explicit TestHandler(TestServer* server) : server_(server) {}
    void handle(const http::HttpRequest& req, http::HttpResponse* resp) override;

   private:
    TestServer* server_;
};