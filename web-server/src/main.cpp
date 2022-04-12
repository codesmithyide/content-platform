/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include <CodeSmithy/ContentPlatform/Core.hpp>
#include <Ishiko/Logging.hpp>
#include <iostream>
#include <memory>

using namespace CodeSmithy::ContentPlatform;

int main(int argc, char* argv[])
{
    try
    {
        // Create a log that sends its output to the console.
        Ishiko::StreamLoggingSink sink(std::cout);
        Ishiko::Logger log(sink);

        WebServer server(log);
        server.run();

        return 0;
    }
    catch (...)
    {
        // TODO
        return 0;
    }
}
