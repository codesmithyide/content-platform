/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Content/DoxygenContentScheme.hpp"
#include <CodeSmithy/Doxygen/Core.hpp>
#include <Ishiko/Text.hpp>

using namespace CodeSmithy::ContentPlatform;

DoxygenContentScheme::DoxygenContentScheme()
    : m_name("doxygen"), m_callbacks("doxygen", "page.html", "", "")
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
    std::string doxygenIndexPath = configuration.value("index"); // TODO: handle invalid configuration where there is no index

    // TODO: handle file doesn't exist
    DoxygenXMLIndex doxygenIndex = DoxygenXMLIndex::FromFile(doxygenIndexPath);

    // TODO: do the mapping in a more configurable way
    // TODO: we know it's an API we want to publish so we will display the index at /docs/api/index.html
    std::string routePattern = "/docs/api/index.html";

    std::string view = routePattern;
    bool prefixRemoved = Ishiko::ASCII::RemovePrefix("/", view);
    if (!prefixRemoved)
    {
        // TODO: this should be an error as it means the path was not valid
    }
    // TODO: Check view validity

    std::shared_ptr<Nemu::ViewWebRequestHandler> handler = std::make_shared<Nemu::ViewWebRequestHandler>(m_callbacks);
    handler->context().map()["codesmithy_page_title"] = configuration.value("title");
    routes.emplace_back(routePattern, handler);

    return routes;
}
