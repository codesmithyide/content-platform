/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Core/WebServer/WebServer.hpp"

using namespace CodeSmithy::ContentPlatform;

WebServer::WebServer(Ishiko::Logger& logger)
    : m_app(std::make_shared<Nemu::SingleConnectionWebServer>(Ishiko::TCPServerSocket::AllInterfaces, Ishiko::Port::http),
        logger)
{
    /*Route::ptr route = std::make_shared<Route>(
            "/",
            std::make_shared<FileSystemRequestHandler>("../../Data/")
            );*/

    m_app.routes().append(Nemu::Route("/",
        std::make_shared<Nemu::FunctionWebRequestHandler>(
            [](const Nemu::WebRequest& request, Nemu::WebResponseBuilder& response, void* handlerData, Ishiko::Logger& logger)
            {
                // TODO: this doesn't work as the user would be left with specifying all the right headers. Do I assume some default?
                response.setStatus(Ishiko::HTTPStatusCode::ok);
                response.body() = "Hello nemu.wf";
            })));
}

void WebServer::run()
{
    m_app.run();
}

void WebServer::stop()
{
    m_app.stop();
}
