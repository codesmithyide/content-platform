/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Content/PageContentScheme.hpp"
#include <Ishiko/Text.hpp>

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
    const std::string templatesRoot = "pages";

    // TODO: handle invalid configuration where there is no path
    std::string page = configuration.value("path");

    // The actual location of the pages on disk is mapped to a URL by removing the templates root directory from the
    // path.
    std::string routePattern = page;
    bool prefixRemoved = Ishiko::ASCII::RemovePrefix(templatesRoot, routePattern);
    if (!prefixRemoved)
    {
        // TODO: what do we do here?
        // An error because this not allowed, security risk
    }
    // TODO: Check routePattern validity, the first char should be '/'

    std::string view = routePattern;
    prefixRemoved = Ishiko::ASCII::RemovePrefix("/", view);
    if (!prefixRemoved)
    {
        // TODO: this should be an error as it means the path was not valid
    }
    // TODO: Check view validity

    // TODO: when I have proper support for schemes I definitely need to try to reuse the handlers
    // TODO: better way to put the path together
    routes.emplace_back(routePattern,
        // TODO: can this use the ViewWebRequestHandler, if not then ViewWebRequestHandler is probably not fit for
        // purpose
        std::make_shared<Nemu::FunctionWebRequestHandler>(
            // TODO: view takes the path in relation to the templates root dir which we set as "pages" in our
            // case so we take substr(6). This is all brittle so improve.
            // TODO: risk here that title appears after content in json file. FIX
            [view, title = configuration.value("title")](const Nemu::WebRequest& request,
                Nemu::WebResponseBuilder& response, void* handlerData, Ishiko::Logger& logger)
            {
                Nemu::ViewContext context;
                context["codesmithy_page_title"] = title;
                response.view("pages", view, context, "page.html");
            }));

    return routes;
}
