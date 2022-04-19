/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Core/WebServer/WebServer.hpp"

using namespace CodeSmithy::ContentPlatform;

WebServer::WebServer(Ishiko::Logger& logger)
    : m_app(std::make_shared<Nemu::SingleConnectionWebServer>(Ishiko::TCPServerSocket::AllInterfaces, Ishiko::Port::http, logger),
        logger)
{
   m_app.routes().append(Nemu::Route("/*",
        std::make_shared<Nemu::FileSystemWebRequestHandler>("D:\\www")));
}

void WebServer::run()
{
    m_app.run();
}

void WebServer::stop()
{
    m_app.stop();
}
