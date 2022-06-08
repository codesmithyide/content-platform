/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_STATICSITE_STATICSITEGENERATOR_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_STATICSITE_STATICSITEGENERATOR_HPP_

#include "../Content/Content.hpp"
#include "../Presentation/Presentation.hpp"
#include <boost/filesystem.hpp>
#include <Ishiko/Configuration.hpp>
#include <Ishiko/Logging.hpp>
#include <memory>

namespace CodeSmithy
{
namespace ContentPlatform
{

class StaticSiteGenerator
{
public:
    class CommandLineSpecification : public Ishiko::CommandLineSpecification
    {
    public:
        CommandLineSpecification();
    };

    class Configuration
    {
    public:
        Configuration(const Ishiko::Configuration& configuration);

        const boost::filesystem::path& content() const;
        const boost::filesystem::path& presentation() const;
        const boost::filesystem::path& outputDirectory() const;

    private:
        boost::filesystem::path m_content;
        boost::filesystem::path m_presentation;
        boost::filesystem::path m_outputDirectory;
    };

    StaticSiteGenerator(const Configuration& configuration, Ishiko::Logger& logger);

    void run();

private:
    Ishiko::Logger& m_logger;
    std::shared_ptr<Content> m_content;
    std::shared_ptr<Presentation> m_presentation;
    boost::filesystem::path m_outputDirectory;
};

}
}

#endif
