/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Presentation/LocalPresentationRepository.hpp"
#include <Ishiko/FileSystem.hpp>

using namespace CodeSmithy::ContentPlatform;

LocalPresentationRepository::LocalPresentationRepository(const boost::filesystem::path& presentationConfigurationFile)
{
    JSONParserCallbacks callbacks(*this);
    Ishiko::JSONPushParser jsonParser(callbacks);

    std::string data = Ishiko::FileSystem::ReadFile(presentationConfigurationFile);
    jsonParser.onData(data, true);
}

std::vector<PresentationProfile> LocalPresentationRepository::getProfiles() const
{
    return m_profiles;
}

LocalPresentationRepository::JSONParserCallbacks::JSONParserCallbacks(LocalPresentationRepository& repository)
    : m_repository(repository)
{
}

void LocalPresentationRepository::JSONParserCallbacks::onMemberName(boost::string_view data)
{
    if (m_context == std::vector<std::string>({ "profiles", "[]" }))
    {
        m_repository.m_profiles.emplace_back(data.to_string());
    }
    m_context.push_back(data.to_string());
}

void LocalPresentationRepository::JSONParserCallbacks::onMemberEnd()
{
    if (m_context.empty())
    {
        // TODO: error
        return;
    }
    m_context.pop_back();
}

void LocalPresentationRepository::JSONParserCallbacks::onArrayBegin()
{
    m_context.push_back("[]");
}

void LocalPresentationRepository::JSONParserCallbacks::onArrayEnd()
{
    if (m_context.empty())
    {
        // TODO: error
        return;
    }
    m_context.pop_back();
}

void LocalPresentationRepository::JSONParserCallbacks::onString(boost::string_view data)
{
    if (m_context.empty())
    {
        // TODO: error
        return;
    }

    // TODO: I have to hardcode every profile. Obviously this needs to be made generic
    if (m_context == std::vector<std::string>({ "profiles", "[]", "page", "template-engine", "options",
        "templates-root-directory" }))
    {
        // TODO: this needs to be transalated into an absolute path
        m_repository.m_profiles.back().templateEngineConfiguration().set("templates-root-directory", data.to_string());
    }
    else if (m_context == std::vector<std::string>({ "profiles", "[]", "doxygen", "template-engine", "options",
        "templates-root-directory" }))
    {
        // TODO: this needs to be transalated into an absolute path
        m_repository.m_profiles.back().templateEngineConfiguration().set("templates-root-directory", data.to_string());
    }
}
