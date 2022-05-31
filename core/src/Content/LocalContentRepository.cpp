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

ContentPages LocalContentRepository::getPages() const
{
    return m_pages;
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
        m_repository.m_pages.pushBack(data.to_string());
    }
}
