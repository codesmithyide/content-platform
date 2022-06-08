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

void InitiateContext(const Ishiko::Configuration& configuration, Nemu::MapViewContext& context)
{
    std::map<std::string, Nemu::ViewContext::Value>& map = context.map();

    auto codesmithyNode = map.insert({ "codesmithy", Nemu::ViewContext::Value::Map() });

    auto pageNode = codesmithyNode.first->second.asValueMap().insert({ "page", Nemu::ViewContext::Value::Map() });
    pageNode.first->second.asValueMap().insert({ "title", configuration.value("title").asString() });

    auto docNode = codesmithyNode.first->second.asValueMap().insert({ "doc", Nemu::ViewContext::Value::Map() });
    docNode.first->second.asValueMap().insert({ "api", Nemu::ViewContext::Value::Map() });
}

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
    InitiateContext(configuration, handler->context());

    // Add "classes" array under the "api" node...
    std::map<std::string, Nemu::ViewContext::Value>& apiMap =
        handler->context().map()["codesmithy"].asValueMap()["doc"].asValueMap()["api"].asValueMap();
    auto classesNode = apiMap.insert({ "classes", Nemu::ViewContext::Value::Array() });
    Nemu::ViewContext::Value::Array& documentedClasses = classesNode.first->second.asValueArray();

    // ... and populate it.
    const std::vector<CodeSmithy::DoxygenXMLIndex::ClassInfo>& doxygenClasses = doxygenIndex.classes();
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
    InitiateContext(configuration, handler->context());

    // Add "class" map under the "api" node...
    std::map<std::string, Nemu::ViewContext::Value>& apiMap =
        handler->context().map()["codesmithy"].asValueMap()["doc"].asValueMap()["api"].asValueMap();
    auto classNode = apiMap.insert({ "class", Nemu::ViewContext::Value::Map() });
    Nemu::ViewContext::Value::Map& documentedClass = classNode.first->second.asValueMap();

    // ... and populate it.
    documentedClass["name"] = classDocumentation.name();
    auto functionsNode = documentedClass.insert({ "functions", Nemu::ViewContext::Value::Map() });
    Nemu::ViewContext::Value::Map& functions = functionsNode.first->second.asValueMap();
    for (const CodeSmithy::DoxygenXMLFunctionDocumentation& functionsDocumentation : classDocumentation.functions())
    {
        functions["name"] = functionsDocumentation.name();
    }
    auto variablesNode = documentedClass.insert({ "variables", Nemu::ViewContext::Value::Map() });
    Nemu::ViewContext::Value::Map& variables = variablesNode.first->second.asValueMap();
    for (const CodeSmithy::DoxygenXMLVariableDocumentation& variableDocumentation : classDocumentation.variables())
    {
        variables["name"] = variableDocumentation.name();
    }

    routes.emplace_back(routePattern, handler);
}

}

DoxygenContentScheme::DoxygenContentScheme()
    : m_name("doxygen"), m_indexCallbacks("doxygen", "page.html", "/docs/api/index.html"),
    m_classCallbacks("doxygen", "page.html", "/docs/api/class.html")
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

    AddIndexRoute(configuration, doxygenIndex, m_indexCallbacks, routes);

    for (const DoxygenXMLIndex::ClassInfo& classInfo : doxygenIndex.classes())
    {
        boost::filesystem::path classDocumentationFilePath =
            doxygenIndexPath.parent_path() / (classInfo.refId + ".xml");
        CodeSmithy::DoxygenXMLClassDocumentation classDocumentation =
            CodeSmithy::DoxygenXMLClassDocumentation::FromFile(classDocumentationFilePath);

        AddClassRoute(configuration, classDocumentation, m_classCallbacks, routes);
    }

    return routes;
}
