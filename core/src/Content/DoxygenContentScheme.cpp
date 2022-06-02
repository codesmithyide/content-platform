/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Content/DoxygenContentScheme.hpp"

using namespace CodeSmithy::ContentPlatform;

DoxygenContentScheme::DoxygenContentScheme()
    : m_name("doxygen")
{
}

const std::string& DoxygenContentScheme::name() const noexcept
{
    return m_name;
}

std::vector<Nemu::Route> DoxygenContentScheme::instantiate(const Ishiko::Configuration& configuration)
{
    std::vector<Nemu::Route> routes;

    // TODO: we don't do anything with this right now, it needs to be used to build the view context with the
    // appropriate variables
    std::string index = configuration.value("index"); // TODO: handle invalid configuration where there is no index

    // TODO: do the mapping in a more configurable way
    // TODO: we know it's an API we want to publish so we will display the index at /docs/api/index.html
    std::string pattern = "/docs/api/index.html";

    // TODO: better way to put the path together
    routes.emplace_back(pattern,
        std::make_shared<Nemu::FunctionWebRequestHandler>(
            // TODO: view takes the path in relation to the templates root dir which we set as "pages" so this won't
            // work. I need to map this one to "templates"
            // TODO: risk here that title appears after content in json file. FIX
            [page = "templates/docs/api/index.html", title = configuration.value("title")](const Nemu::WebRequest& request,
                Nemu::WebResponseBuilder& response, void* handlerData, Ishiko::Logger& logger)
            {
                Nemu::ViewContext context;
                context["codesmithy_page_title"] = title;
                response.view("doxygen", page, context, "page.html");
            }));

    return routes;
}
