/*
    Copyright (c) 2022-2023 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "StaticSite/StaticSiteGenerator.hpp"
#include "Content/LocalContentRepository.hpp"
#include "Presentation/LocalPresentationRepository.hpp"
#include <Ishiko/FileSystem.hpp>
#include <Nemu.hpp>
#include <vector>

using namespace CodeSmithy::ContentPlatform;

StaticSiteGenerator::CommandLineSpecification::CommandLineSpecification()
{
    // TODO: --content as mandatory option without default
    // TODO: --presentation as mandatory option without default
    // TODO: --output as mandatory option without default
    addNamedOption("log-level", { Ishiko::CommandLineSpecification::OptionType::toggle, "info" });
}

StaticSiteGenerator::Configuration::Configuration(const Ishiko::Configuration& configuration)
    : m_content(configuration.value("content").asString()),
    m_presentation(configuration.value("presentation").asString()),
    m_outputDirectory(configuration.value("output").asString())
{
}

const boost::filesystem::path& StaticSiteGenerator::Configuration::content() const
{
    return m_content;
}

const boost::filesystem::path& StaticSiteGenerator::Configuration::presentation() const
{
    return m_presentation;
}

const boost::filesystem::path& StaticSiteGenerator::Configuration::outputDirectory() const
{
    return m_outputDirectory;
}

StaticSiteGenerator::StaticSiteGenerator(const Configuration& configuration, Ishiko::Logger& logger)
    : m_logger(logger), m_outputDirectory(configuration.outputDirectory())
{
    m_content = std::make_shared<LocalContentRepository>(configuration.content());
    m_presentation = std::make_shared<LocalPresentationRepository>(configuration.presentation());
}

void StaticSiteGenerator::run()
{
    Nemu::MustacheTemplateEngine mustacheTemplateEngine;

    // We register the template engine profiles under the names specified by the presentation configuration. These
    // names need to match the schemes in the content configuration. The name of the scheme will be passed in when 
    // calling WebResponseBuilder::view(<scheme name>, ...) so it needs to match the name of a registered template
    // engine profile.
    Nemu::Views views;
    for (const PresentationProfile& profile : m_presentation->getProfiles())
    {
        views.set(profile.name(), mustacheTemplateEngine.createProfile(profile.templateEngineConfiguration()));
    }

    std::vector<Nemu::Route> routes = m_content->getRoutes();

    // TODO: verify we don't have wildcards in the routes

    boost::filesystem::create_directory(m_outputDirectory);

    for (const Nemu::Route& route : routes)
    {
        Nemu::WebRequest request(route.pathPattern());
        Nemu::WebResponseBuilder response;
        response.m_views = &views;
        route.requestHandler().run(request, response, m_logger);

        // TODO: error handling
        // TODO: check validity of the route as a path
        boost::filesystem::path outputPath = m_outputDirectory / route.pathPattern();

        boost::filesystem::create_directories(outputPath.parent_path());

        Ishiko::Error error;
        Ishiko::BinaryFile outputFile = Ishiko::BinaryFile::Create(outputPath, error);
        outputFile.write(response.body().c_str(), response.body().size(), error);
    }
}
