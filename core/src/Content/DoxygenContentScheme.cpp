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

    const std::vector<DoxygenXMLIndex::ClassInfo>& doxygenClasses = doxygenIndex.classes();

    // TODO: functional decomposition
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

        std::shared_ptr<Nemu::ViewWebRequestHandler> handler = std::make_shared<Nemu::ViewWebRequestHandler>(m_callbacks);
        handler->context().map()["codesmithy"] = Nemu::ViewContext::Value::Map();
        handler->context().map()["codesmithy"].asValueMap()["page"] = Nemu::ViewContext::Value::Map();
        handler->context().map()["codesmithy"].asValueMap()["page"].asValueMap()["title"] = configuration.value("title").asString();
        handler->context().map()["codesmithy"].asValueMap()["doc"] = Nemu::ViewContext::Value::Map();
        handler->context().map()["codesmithy"].asValueMap()["doc"].asValueMap()["api"] = Nemu::ViewContext::Value::Map();
        handler->context().map()["codesmithy"].asValueMap()["doc"].asValueMap()["api"].asValueMap()["classes"] = Nemu::ViewContext::Value::Array();
        Nemu::ViewContext::Value::Array& documentedClasses = handler->context().map()["codesmithy"].asValueMap()["doc"].asValueMap()["api"].asValueMap()["classes"].asValueArray();
        for (const DoxygenXMLIndex::ClassInfo& classInfo : doxygenClasses)
        {
           documentedClasses.push_back(classInfo.name);
        }
        routes.emplace_back(routePattern, handler);
    }

    // TODO: functional decomposition
    for (const DoxygenXMLIndex::ClassInfo& classInfo : doxygenClasses)
    {
        // TODO: do the mapping in a more configurable way
        // TODO: we know it's an API we want to publish so we will display the index at /docs/api/index.html
        // TODO: do not reuse Doxygen scheme, come up with our own and ensure it works universally
        std::string routePattern = "/docs/api/class/" + classInfo.refId + ".html";

        std::string view = "docs/api/class.html";
        // TODO: Check view validity

        std::shared_ptr<Nemu::ViewWebRequestHandler> handler = std::make_shared<Nemu::ViewWebRequestHandler>(m_callbacks);
        handler->context().map()["codesmithy"] = Nemu::ViewContext::Value::Map();
        handler->context().map()["codesmithy"].asValueMap()["page"] = Nemu::ViewContext::Value::Map();
        handler->context().map()["codesmithy"].asValueMap()["page"].asValueMap()["title"] = configuration.value("title").asString();
        handler->context().map()["codesmithy"].asValueMap()["doc"] = Nemu::ViewContext::Value::Map();
        handler->context().map()["codesmithy"].asValueMap()["doc"].asValueMap()["api"] = Nemu::ViewContext::Value::Map();
        handler->context().map()["codesmithy"].asValueMap()["doc"].asValueMap()["api"].asValueMap()["class"] = Nemu::ViewContext::Value::Map();
        Nemu::ViewContext::Value::Map& documentedClass = handler->context().map()["codesmithy"].asValueMap()["doc"].asValueMap()["api"].asValueMap()["class"].asValueMap();
        
        boost::filesystem::path classDocumentationFilePath = doxygenIndexPath.parent_path() / (classInfo.refId + ".xml");
        DoxygenXMLClassDocumentation classDocumentation = DoxygenXMLClassDocumentation::FromFile(classDocumentationFilePath);

        documentedClass["name"] = classInfo.name;
      
        routes.emplace_back(routePattern, handler);
    }

    return routes;
}
