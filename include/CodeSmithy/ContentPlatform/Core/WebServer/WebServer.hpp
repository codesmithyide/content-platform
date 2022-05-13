/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_WEBSERVER_WEBSERVER_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_WEBSERVER_WEBSERVER_HPP_

#include "../Presentation.hpp"
#include <Ishiko/Configuration.hpp>
#include <Ishiko/Logging.hpp>
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
   
    WebServer(const Presentation& presentation, Ishiko::Logger& logger);

    void run();
    void stop();

private:
    Nemu::WebApplication m_app;
};

}
}

#endif
