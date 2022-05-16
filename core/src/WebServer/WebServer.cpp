/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "WebServer/WebServer.hpp"
#include <Ishiko/Text.hpp>

using namespace CodeSmithy::ContentPlatform;

WebServer::CommandLineSpecification::CommandLineSpecification()
{
    // TODO: --content as mandatory option without default
    addNamedOption("log-level", { Ishiko::CommandLineSpecification::OptionType::toggle, "info" });
    addNamedOption("port", { Ishiko::CommandLineSpecification::OptionType::singleValue, "80" });
}

WebServer::Configuration::Configuration(const Ishiko::Configuration& configuration)
    : m_port(configuration.value("port")), m_logLevel(Ishiko::LogLevel::FromString(configuration.value("log-level"))),
    m_content(configuration.value("content"))
{
}

Ishiko::Port WebServer::Configuration::port() const
{
    return m_port;
}

Ishiko::LogLevel WebServer::Configuration::logLevel() const
{
    return m_logLevel;
}

const boost::filesystem::path& WebServer::Configuration::content() const
{
    return m_content;
}

WebServer::WebServer(const Configuration& configuration, const Content& content, const Presentation& presentation,
    Ishiko::Logger& logger)
    : m_app(
        std::make_shared<Nemu::SingleConnectionWebServer>(Ishiko::TCPServerSocket::AllInterfaces, configuration.port(),
            logger),
        logger)
{
    // Set the mustache engine as the default template engine
    m_app.views().add(
        std::make_shared<Nemu::MustacheTemplateEngine>(
            Nemu::MustacheTemplateEngine::Options(presentation.templatesRootDir(), presentation.layoutsRootDir())));

    m_app.routes().append(
        Nemu::Route("/*",
            std::make_shared<Nemu::FunctionWebRequestHandler>(
                [&content](const Nemu::WebRequest& request, Nemu::WebResponseBuilder& response, void* handlerData,
                    Ishiko::Logger& logger)
                {
                    Nemu::ViewContext context;
                    context["codesmithy_page_title"] = content.getTitle();
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
