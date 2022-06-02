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
    // TODO: --presentation as mandatory option without default
    addNamedOption("log-level", { Ishiko::CommandLineSpecification::OptionType::toggle, "info" });
    addNamedOption("port", { Ishiko::CommandLineSpecification::OptionType::singleValue, "80" });
}

WebServer::Configuration::Configuration(const Ishiko::Configuration& configuration)
    : m_port(configuration.value("port")), m_logLevel(Ishiko::LogLevel::FromString(configuration.value("log-level"))),
    m_presentation(configuration.value("presentation")), m_content(configuration.value("content"))
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

const boost::filesystem::path& WebServer::Configuration::presentation() const
{
    return m_presentation;
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
    initialize(presentation, content);
}

void WebServer::run()
{
    m_app.run();
}

void WebServer::stop()
{
    m_app.stop();
}

const Nemu::Routes& WebServer::routes() const noexcept
{
    return m_app.routes();
}

Nemu::Routes& WebServer::routes() noexcept
{
    return m_app.routes();
}

void WebServer::initialize(const Presentation& presentation, const Content& content)
{
    // Set the mustache engine as the default template engine
    // TODO: we set up 2 profiles that are equivalent to this default configuration but ideally this should be
    // configurable (as part of the presentation layer? As in not the content one)
    /*
    * "schemes" : [
        {
            "doxygen": {
                "template-engine": {
                    "name": "mustache",
                    "options": {
                        "templates-root-dir": "templates/docs/api"
                    }
                }
            }
        },
        {
            "pages": {
                "template-engine": {
                    "name": "mustache",
                    "options": {
                        "templates-root-dir": "pages"
                    }
                }
            }
        },
    ],
    */
    m_app.views().set("pages",
        std::make_shared<Nemu::MustacheTemplateEngineProfile>(
            Nemu::MustacheTemplateEngineProfile::Options(presentation.templatesRootDir(), &presentation.layoutsRootDir())));

#if 0 // This has now been replaced by logic inside the schemes and content. Do these comments still apply?
    // TODO: what is the cost of creating all these lambda functions? Surely it would be better to have 1 handler and
    // deduce the file to use from the URI. How do I achieve that from the content.json config though?
    // TODO: also this doesn't work because the scheme itself needs to provide the handler. So ContentPages kind of
    // gives the list of all pages that are valid and a handler for each of them. That handler can then be the same for
    // multiple pages. OK that works better, at least for things like Doxygen.
    for (const std::string& page : content.getPages())
    {
        // TODO: remove prefix in a more configurable way
        // TODO: 6 because "pages"
        std::string pattern = page.substr(5);

        // TODO: better way to put the path together
        m_app.routes().add(
            // TODO: what if abolsute path etc.
            Nemu::Route(pattern,
                std::make_shared<Nemu::FunctionWebRequestHandler>(
                    // TODO: view takes the path in relation to the templates root dir which we set as "pages" in our
                    // case so we take substr(6). This is all brittle so improve.
                    [page = page.substr(6), &content](const Nemu::WebRequest& request,
                        Nemu::WebResponseBuilder& response, void* handlerData, Ishiko::Logger& logger)
                    {
                        Nemu::ViewContext context;
                        context["codesmithy_page_title"] = content.getTitle();
                        response.view(page, context, "page.html");
                    })));
    }
#endif
    std::vector<Nemu::Route> routes = content.getRoutes();
    m_app.routes().add(routes);

    m_app.routes().add(
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
                        // TODO: this should use "homepage" setting from Content
                        templatePath = "index.html";
                    }
                    response.view("pages", templatePath, context, "page.html");
                })));
}
