/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Content/PageContentScheme.hpp"

using namespace CodeSmithy::ContentPlatform;

PageContentScheme::PageContentScheme()
    : m_name("page")
{
}

const std::string& PageContentScheme::name() const noexcept
{
    return m_name;
}

std::vector<Nemu::Route> PageContentScheme::instantiate(const Ishiko::Configuration& configuration)
{
    std::vector<Nemu::Route> routes;

    // TODO: remove prefix in a more configurable way
    // TODO: 5 because "pages"
    std::string page = configuration.value("path"); // TODO: handle invalid configuration where there is no path
    std::string pattern = page.substr(5);

    // TODO: when I have proper support for schemes I definitely need to try to reuse the handlers
    // TODO: better way to put the path together
    routes.emplace_back(pattern,
        // TODO: can this use the ViewWebRequestHandler, if not then ViewWebRequestHandler is probably not fit for
        // purpose
        std::make_shared<Nemu::FunctionWebRequestHandler>(
            // TODO: view takes the path in relation to the templates root dir which we set as "pages" in our
            // case so we take substr(6). This is all brittle so improve.
            // TODO: risk here that title appears after content in json file. FIX
            [page = page.substr(6), title = configuration.value("title")](const Nemu::WebRequest& request,
                Nemu::WebResponseBuilder& response, void* handlerData, Ishiko::Logger& logger)
            {
                Nemu::ViewContext context;
                context["codesmithy_page_title"] = title;
                response.view("pages", page, context, "page.html");
            }));

    return routes;
}
