/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Core/WebServer/WebServer.hpp"

using namespace CodeSmithy::ContentPlatform;

WebServer::WebServer(const std::string& contentRootDir, Ishiko::Logger& logger)
    : m_app(
        std::make_shared<Nemu::SingleConnectionWebServer>(Ishiko::TCPServerSocket::AllInterfaces, Ishiko::Port::http,
            logger),
        logger)
{
    // Set the mustache engine as the default template engine
    // TODO: get from config
    const std::string templatesRootDir = "${CODESMITHYIDE}/content-platform-themes/default/templates";
    const std::string layoutsRootDir = "${CODESMITHYIDE}/content-platform-themes/default/layout";
    m_app.views().add(
        std::make_shared<Nemu::MustacheTemplateEngine>(
            Nemu::MustacheTemplateEngine::Options(templatesRootDir, layoutsRootDir)));

    m_app.routes().append(
        Nemu::Route("/*",
            std::make_shared<Nemu::FunctionWebRequestHandler>(
                [](const Nemu::WebRequest& request, Nemu::WebResponseBuilder& response, void* handlerData,
                    Ishiko::Logger& logger)
                {
                    Nemu::ViewContext context;
                    // TODO: get project from config
                    context["codesmithy_page_title"] = "My Project";
                    std::string templatePath = request.url().path();
                    if (templatePath == "/")
                    {
                        templatePath = "index.html";
                    }
                    response.view(templatePath, context, "page.html");
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
