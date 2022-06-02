/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include <CodeSmithy/ContentPlatform/Core.hpp>
#include <Ishiko/Configuration.hpp>
#include <Ishiko/Logging.hpp>
#include <iostream>
#include <memory>

using namespace CodeSmithy::ContentPlatform;

int main(int argc, char* argv[])
{
    try
    {
        WebServer::CommandLineSpecification commandLineSpec;
        Ishiko::Configuration configuration = commandLineSpec.createDefaultConfiguration();
        Ishiko::CommandLineParser parser;
        parser.parse(commandLineSpec, argc, argv, configuration);
        // TODO: validate the configuration at some point

        // Create a log that sends its output to stdout and stderr.
        Ishiko::StandardStreamsLoggingSink sink;
        Ishiko::Logger log(sink);

        WebServer::Configuration webServerConfiguration(configuration);
        log.setLevel(webServerConfiguration.logLevel());

        WebServer server(webServerConfiguration, log);
        server.run();

        return 0;
    }
    catch (...)
    {
        // TODO
        return 0;
    }
}
