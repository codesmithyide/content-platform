/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Content/LocalContentRepository.hpp"
#include <Ishiko/FileSystem.hpp>

using namespace CodeSmithy::ContentPlatform;

LocalContentRepository::JSONParserCallbacks::JSONParserCallbacks(LocalContentRepository& repository)
    : m_repository(repository)
{
}

void LocalContentRepository::JSONParserCallbacks::onString(boost::string_view data)
{
    m_repository.m_title = data.to_string();
}

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
