/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "WebServerTests.hpp"
#include "CodeSmithy/ContentPlatform/Core/Content/LocalContentRepository.hpp"
#include "CodeSmithy/ContentPlatform/Core/WebServer/WebServer.hpp"
#include <Ishiko/HTTP.hpp>
#include <Ishiko/Logging.hpp>
#include <thread>

using namespace CodeSmithy::ContentPlatform;
using namespace Ishiko;

WebServerTests::WebServerTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "WebServer tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("run test 1", RunTest1);
    append<HeapAllocationErrorsTest>("run test 2", RunTest2);
}

void WebServerTests::ConstructorTest1(Test& test)
{
    boost::filesystem::path contentConfigurationFile =
        test.context().getTestDataPath("websites/test-site-1/content.json");
    boost::filesystem::path templatesDir = test.context().getTestDataPath("websites/test-site-1/templates");
    boost::filesystem::path layoutsDir = test.context().getTestDataPath("websites/test-site-1/layouts");

    NullLoggingSink sink;
    Logger log(sink);

    Configuration configuration = WebServer::CommandLineSpecification().createDefaultConfiguration();
    configuration.set("content", contentConfigurationFile.string());

    LocalContentRepository content(contentConfigurationFile);
    Presentation presentation(templatesDir.string(), layoutsDir.string());
    WebServer server(configuration, content, presentation, log);

    const Nemu::Routes& routes = server.routes();

    ISHIKO_TEST_ABORT_IF_NEQ(routes.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(routes.at(0).pathPattern(), "/*");
    ISHIKO_TEST_FAIL_IF_NEQ(routes.at(1).pathPattern(), "*");
    ISHIKO_TEST_PASS();
}

void WebServerTests::RunTest1(Test& test)
{
    boost::filesystem::path contentConfigurationFile =
        test.context().getTestDataPath("websites/test-site-1/content.json");
    boost::filesystem::path templatesDir = test.context().getTestDataPath("websites/test-site-1/templates");
    boost::filesystem::path layoutsDir = test.context().getTestDataPath("websites/test-site-1/layouts");

    NullLoggingSink sink;
    Logger log(sink);

    Configuration configuration = WebServer::CommandLineSpecification().createDefaultConfiguration();
    configuration.set("content", contentConfigurationFile.string());

    LocalContentRepository content(contentConfigurationFile);
    Presentation presentation(templatesDir.string(), layoutsDir.string());
    WebServer server(configuration, content, presentation, log);

    std::thread serverThread(
        [&server]()
        {
            server.run();
        });

    server.stop();
    serverThread.join();

    ISHIKO_TEST_PASS();
}

void WebServerTests::RunTest2(Test& test)
{
    boost::filesystem::path contentConfigurationFile =
        test.context().getTestDataPath("websites/test-site-1/content.json");
    boost::filesystem::path templatesDir = test.context().getTestDataPath("websites/test-site-1/pages");
    boost::filesystem::path layoutsDir = test.context().getTestDataPath("websites/test-site-1/layouts");

    NullLoggingSink sink;
    Logger log(sink);

    Configuration configuration = WebServer::CommandLineSpecification().createDefaultConfiguration();
    configuration.set("content", contentConfigurationFile.string());

    LocalContentRepository content(contentConfigurationFile);
    Presentation presentation(templatesDir.string(), layoutsDir.string());
    WebServer server(configuration, content, presentation, log);

    std::thread serverThread(
        [&server]()
        {
            server.run();
        });

    boost::filesystem::path outputPath(test.context().getTestOutputPath("WebServerTests_RunTest2.bin"));
    std::ofstream responseFile(outputPath.string(), std::ios::out | std::ios::binary);
    Error error;
    HTTPClient::Get(IPv4Address::Localhost(), Port::http, "/", responseFile, error);

    ISHIKO_TEST_FAIL_IF(error);

    responseFile.close();

    server.stop();
    serverThread.join();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("WebServerTests_RunTest2.bin", "WebServerTests_RunTest2.bin");
    ISHIKO_TEST_PASS();
}
