/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Content/PageContentScheme.hpp"
#include <Ishiko/Text.hpp>
#include <memory>

using namespace CodeSmithy::ContentPlatform;

PageContentScheme::PageContentScheme()
    : m_name("page"),
    m_callbacks("page", "page.html", Nemu::ViewWebRequestHandler::DeclarativeCallbacks::PrefixMapping("", ""))
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
    std::string page = configuration.value("path").asString();

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
    // TODO: I think I'm close to make this handler shared by every page since it contains nothing unique now
    std::shared_ptr<Nemu::ViewWebRequestHandler> handler = std::make_shared<Nemu::ViewWebRequestHandler>(m_callbacks);
    handler->context().map()["codesmithy"] = Nemu::ViewContext::Value::Map();
    handler->context().map()["codesmithy"].asValueMap()["page"] = Nemu::ViewContext::Value::Map();
    handler->context().map()["codesmithy"].asValueMap()["page"].asValueMap()["title"] = configuration.value("title").asString();
    routes.emplace_back(routePattern, handler);

    return routes;
}
