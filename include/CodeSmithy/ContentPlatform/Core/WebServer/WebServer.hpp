/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_WEBSERVER_WEBSERVER_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_WEBSERVER_WEBSERVER_HPP_

#include "../Content/Content.hpp"
#include "../Presentation.hpp"
#include <Ishiko/Configuration.hpp>
#include <Ishiko/Logging.hpp>
#include <Ishiko/Networking.hpp>
#include <Nemu.hpp>
#include <memory>

namespace CodeSmithy
{
namespace ContentPlatform
{

class WebServer
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

        Ishiko::Port port() const;
        Ishiko::LogLevel logLevel() const;

    private:
        Ishiko::Port m_port;
        Ishiko::LogLevel m_logLevel;
    };
   
    WebServer(const Configuration& configuration, const Content& content, const Presentation& presentation,
        Ishiko::Logger& logger);

    void run();
    void stop();

private:
    Nemu::WebApplication m_app;
};

}
}

#endif
