/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Content/DoxygenContentScheme.hpp"
#include <boost/filesystem.hpp>
#include <CodeSmithy/Doxygen/Core.hpp>
#include <Ishiko/Text.hpp>
#include <vector>

using namespace CodeSmithy::ContentPlatform;

namespace
{

void AddIndexRoute(const Ishiko::Configuration& configuration, const CodeSmithy::DoxygenXMLIndex& doxygenIndex,
    Nemu::ViewWebRequestHandler::Callbacks& callbacks, std::vector<Nemu::Route>& routes)
{
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

    std::shared_ptr<Nemu::ViewWebRequestHandler> handler = std::make_shared<Nemu::ViewWebRequestHandler>(callbacks);
    handler->context().map()["codesmithy"] = Nemu::ViewContext::Value::Map();
    handler->context().map()["codesmithy"].asValueMap()["page"] = Nemu::ViewContext::Value::Map();
    handler->context().map()["codesmithy"].asValueMap()["page"].asValueMap()["title"] = configuration.value("title").asString();
    handler->context().map()["codesmithy"].asValueMap()["doc"] = Nemu::ViewContext::Value::Map();
    handler->context().map()["codesmithy"].asValueMap()["doc"].asValueMap()["api"] = Nemu::ViewContext::Value::Map();
    handler->context().map()["codesmithy"].asValueMap()["doc"].asValueMap()["api"].asValueMap()["classes"] = Nemu::ViewContext::Value::Array();

    const std::vector<CodeSmithy::DoxygenXMLIndex::ClassInfo>& doxygenClasses = doxygenIndex.classes();
    Nemu::ViewContext::Value::Array& documentedClasses = handler->context().map()["codesmithy"].asValueMap()["doc"].asValueMap()["api"].asValueMap()["classes"].asValueArray();
    for (const CodeSmithy::DoxygenXMLIndex::ClassInfo& classInfo : doxygenClasses)
    {
        documentedClasses.push_back(classInfo.name);
    }
    routes.emplace_back(routePattern, handler);
}

void AddClassRoute(const Ishiko::Configuration& configuration,
    const CodeSmithy::DoxygenXMLClassDocumentation& classDocumentation,
    Nemu::ViewWebRequestHandler::Callbacks& callbacks, std::vector<Nemu::Route>& routes)
{
    // TODO: do the mapping in a more configurable way
    // TODO: we know it's an API we want to publish so we will display the index at /docs/api/index.html
    // TODO: do not reuse Doxygen scheme, come up with our own and ensure it works universally
    std::string routePattern = "/docs/api/class/" + classDocumentation.id() + ".html";

    std::string view = "docs/api/class.html";
    // TODO: Check view validity

    std::shared_ptr<Nemu::ViewWebRequestHandler> handler = std::make_shared<Nemu::ViewWebRequestHandler>(callbacks);
    handler->context().map()["codesmithy"] = Nemu::ViewContext::Value::Map();
    handler->context().map()["codesmithy"].asValueMap()["page"] = Nemu::ViewContext::Value::Map();
    handler->context().map()["codesmithy"].asValueMap()["page"].asValueMap()["title"] = configuration.value("title").asString();
    handler->context().map()["codesmithy"].asValueMap()["doc"] = Nemu::ViewContext::Value::Map();
    handler->context().map()["codesmithy"].asValueMap()["doc"].asValueMap()["api"] = Nemu::ViewContext::Value::Map();
    handler->context().map()["codesmithy"].asValueMap()["doc"].asValueMap()["api"].asValueMap()["class"] = Nemu::ViewContext::Value::Map();
    Nemu::ViewContext::Value::Map& documentedClass = handler->context().map()["codesmithy"].asValueMap()["doc"].asValueMap()["api"].asValueMap()["class"].asValueMap();

    documentedClass["name"] = classDocumentation.name();

    routes.emplace_back(routePattern, handler);
}

}

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

    // TODO: handle invalid configuration where there is no index
    boost::filesystem::path doxygenIndexPath = configuration.value("index").asString();

    // TODO: handle file doesn't exist
    DoxygenXMLIndex doxygenIndex = DoxygenXMLIndex::FromFile(doxygenIndexPath);

    AddIndexRoute(configuration, doxygenIndex, m_callbacks, routes);

    for (const DoxygenXMLIndex::ClassInfo& classInfo : doxygenIndex.classes())
    {
        boost::filesystem::path classDocumentationFilePath =
            doxygenIndexPath.parent_path() / (classInfo.refId + ".xml");
        CodeSmithy::DoxygenXMLClassDocumentation classDocumentation =
            CodeSmithy::DoxygenXMLClassDocumentation::FromFile(classDocumentationFilePath);

        AddClassRoute(configuration, classDocumentation, m_callbacks, routes);
    }

    return routes;
}
