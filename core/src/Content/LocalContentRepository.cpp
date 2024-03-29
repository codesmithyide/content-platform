/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Content/DoxygenContentScheme.hpp"
#include "Content/LocalContentRepository.hpp"
#include "Content/PageContentScheme.hpp"
#include <Ishiko/FileSystem.hpp>

using namespace CodeSmithy::ContentPlatform;

LocalContentRepository::LocalContentRepository(const boost::filesystem::path& contentConfigurationFile)
{
    // TODO: adding schemes should be done somewhere else
    m_schemes.add(std::make_shared<DoxygenContentScheme>());
    m_schemes.add(std::make_shared<PageContentScheme>());

    boost::filesystem::path configurationFileDirectory =
        boost::filesystem::absolute(contentConfigurationFile.parent_path());

    JSONParserCallbacks callbacks(*this, configurationFileDirectory);
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

std::vector<Nemu::Route> LocalContentRepository::getRoutes() const
{
    return m_routes;
}

LocalContentRepository::JSONParserCallbacks::JSONParserCallbacks(LocalContentRepository& repository,
    boost::filesystem::path configurationFileDirectory)
    : m_repository(repository), m_configurationFileDirectory(std::move(configurationFileDirectory))
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
        std::shared_ptr<ContentScheme> scheme;
        bool found = m_repository.m_schemes.find("page", scheme);
        if (!found)
        {
            // TODO: report error
        }

        Ishiko::Configuration schemeConfiguration;
        schemeConfiguration.set("path", data.to_string());
        // TODO: this is a hack for now. Variables that should be passed to the ViewContext need a proper solution. Noy
        // so convinced it's a hack. This is after all specified in content.json and path is is also just a part
        // of the scheme. There isn't really a way we can guess whether the view will actually use any of this. One
        // thing to consider though is that we should avoid copy/pasting common things. So maybe what is needed is some
        // sort of hierarchical configuration.
        // Also the fact a View handler is used is also scheme specific so a common ViewContext breaks encapsulation.
        // TODO: in essence we want to make things like title more generic so users can specify what they want in the
        // content.json and well know it's page metadata.
        schemeConfiguration.set("title", m_repository.getTitle());
        std::vector<Nemu::Route> routes = scheme->instantiate(schemeConfiguration);
        m_repository.m_routes.insert(m_repository.m_routes.end(), routes.begin(), routes.end());
    }
    else if (m_context == std::vector<std::string>({ "content", "[]", "doxygen", "index" }))
    {
        std::shared_ptr<ContentScheme> scheme;
        bool found = m_repository.m_schemes.find("doxygen", scheme);
        if (!found)
        {
            // TODO: report error
        }

        Ishiko::Configuration schemeConfiguration;
        boost::filesystem::path doxygenIndexFilePath = m_configurationFileDirectory / data.to_string();
        schemeConfiguration.set("index", doxygenIndexFilePath.string());
        // TODO: this is a hack for now. Variables that should be passed to the ViewContext need a proper solution. Noy
        // so convinced it's a hack. This is after all specified in content.json and path is is also just a part
        // of the scheme. There isn't really a way we can guess whether the view will actually use any of this. One
        // thing to consider though is that we should avoid copy/pasting common things. So maybe what is needed is some
        // sort of hierarchical configuration.
        // Also the fact a View handler is used is also scheme specific so a common ViewContext breaks encapsulation.
        // TODO: in essence we want to make things like title more generic so users can specify what they want in the
        // content.json and well know it's page metadata.
        schemeConfiguration.set("title", m_repository.getTitle());
        std::vector<Nemu::Route> routes = scheme->instantiate(schemeConfiguration);
        m_repository.m_routes.insert(m_repository.m_routes.end(), routes.begin(), routes.end());
    }
}
