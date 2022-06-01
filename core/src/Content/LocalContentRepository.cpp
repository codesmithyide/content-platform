/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Content/LocalContentRepository.hpp"
#include <Ishiko/FileSystem.hpp>

using namespace CodeSmithy::ContentPlatform;

LocalContentRepository::LocalContentRepository(const boost::filesystem::path& contentConfigurationFile)
{
    JSONParserCallbacks callbacks(*this);
    Ishiko::JSONPushParser jsonParser(callbacks);

    std::string data = Ishiko::FileSystem::ReadFile(contentConfigurationFile);
    jsonParser.onData(data, true);
}

std::string LocalContentRepository::getTitle() const
{
    return m_title;
}

ContentReference LocalContentRepository::getHomepage() const
{
    return m_homepage;
}

Nemu::Routes LocalContentRepository::getRoutes() const
{
    return m_routes;
}

LocalContentRepository::JSONParserCallbacks::JSONParserCallbacks(LocalContentRepository& repository)
    : m_repository(repository)
{
}

void LocalContentRepository::JSONParserCallbacks::onMemberName(boost::string_view data)
{
    m_context.push_back(data.to_string());
}

void LocalContentRepository::JSONParserCallbacks::onMemberEnd()
{
    if (m_context.empty())
    {
        // TODO: error
        return;
    }
    m_context.pop_back();
}

void LocalContentRepository::JSONParserCallbacks::onArrayBegin()
{
    m_context.push_back("[]");
}

void LocalContentRepository::JSONParserCallbacks::onArrayEnd()
{
    if (m_context.empty())
    {
        // TODO: error
        return;
    }
    m_context.pop_back();
}

void LocalContentRepository::JSONParserCallbacks::onString(boost::string_view data)
{
    if (m_context.empty())
    {
        // TODO: error
        return;
    }
    if (m_context.back() == "title")
    {
        m_repository.m_title = data.to_string();
    }
    else if (m_context == std::vector<std::string>({ "homepage", "page" }))
    {
        m_repository.m_homepage = ContentReference("page", data.to_string());
    }
    else if (m_context == std::vector<std::string>({ "content", "[]", "page", "path" }))
    {
        // TODO: remove prefix in a more configurable way
        // TODO: 6 because "pages"
        std::string page = data.to_string();
        std::string pattern = page.substr(5);

        // TODO: when I have proper support for schemes I definitely need to try to reuse the handlers
        // TODO: better way to put the path together
        m_repository.m_routes.add(
            // TODO: what if abolsute path etc.
            Nemu::Route(pattern,
                std::make_shared<Nemu::FunctionWebRequestHandler>(
                    // TODO: view takes the path in relation to the templates root dir which we set as "pages" in our
                    // case so we take substr(6). This is all brittle so improve.
                    // TODO: risk here that title appears after content in json file. FIX
                    [page = page.substr(6), title = m_repository.m_title](const Nemu::WebRequest& request,
                        Nemu::WebResponseBuilder& response, void* handlerData, Ishiko::Logger& logger)
                    {
                        Nemu::ViewContext context;
                        context["codesmithy_page_title"] = title;
                        response.view(page, context, "page.html");
                    })));
    }
    else if (m_context == std::vector<std::string>({ "content", "[]", "doxygen", "index" }))
    {
        // TODO: this doesn't work because the prefix is assumed to be pages. How to map this to appropriate URL.
        std::string page = data.to_string();

        // TODO: remove prefix in a more configurable way
        // TODO: 6 because "pages"
        std::string pattern = page.substr(5);

        // TODO: better way to put the path together
        m_repository.m_routes.add(
            // TODO: what if abolsute path etc.
            Nemu::Route(pattern,
                std::make_shared<Nemu::FunctionWebRequestHandler>(
                    // TODO: view takes the path in relation to the templates root dir which we set as "pages" in our
                    // case so we take substr(6). This is all brittle so improve.
                    // TODO: risk here that title appears after content in json file. FIX
                    [page = page.substr(6), title = m_repository.m_title](const Nemu::WebRequest& request,
                        Nemu::WebResponseBuilder& response, void* handlerData, Ishiko::Logger& logger)
                    {
                        Nemu::ViewContext context;
                        context["codesmithy_page_title"] = title;
                        response.view(page, context, "page.html");
                    })));
    }
}
