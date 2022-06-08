/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "WebServerTests.hpp"
#include "CodeSmithy/ContentPlatform/Core/Content/LocalContentRepository.hpp"
#include "CodeSmithy/ContentPlatform/Core/Presentation/LocalPresentationRepository.hpp"
#include "CodeSmithy/ContentPlatform/Core/WebServer/WebServer.hpp"
#include <Ishiko/HTTP.hpp>
#include <Ishiko/Logging.hpp>
#include <thread>

using namespace CodeSmithy::ContentPlatform;
using namespace Ishiko;

WebServerTests::WebServerTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "WebServer tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("Constructor test 3", ConstructorTest3);
    append<HeapAllocationErrorsTest>("run test 1", RunTest1);
    append<HeapAllocationErrorsTest>("run test 2", RunTest2);
    append<HeapAllocationErrorsTest>("run test 3", RunTest3);
    append<HeapAllocationErrorsTest>("run test 4", RunTest4);
    append<HeapAllocationErrorsTest>("run test 5", RunTest5);
}

void WebServerTests::ConstructorTest1(Test& test)
{
    boost::filesystem::path contentConfigurationFile =
        test.context().getTestDataPath("websites/test-site-1/content.json");
    boost::filesystem::path presentationConfigurationFile =
        test.context().getTestDataPath("websites/test-site-1/presentation.json");

    NullLoggingSink sink;
    Logger log(sink);

    Configuration configuration = WebServer::CommandLineSpecification().createDefaultConfiguration();
    configuration.set("content", contentConfigurationFile.string());
    configuration.set("presentation", presentationConfigurationFile.string());

    WebServer server(configuration, log);

    const Nemu::Routes& routes = server.routes();

    ISHIKO_TEST_ABORT_IF_NEQ(routes.size(), 3);
    ISHIKO_TEST_FAIL_IF_NEQ(routes.at(0).pathPattern(), "/index.html");
    ISHIKO_TEST_FAIL_IF_NEQ(routes.at(1).pathPattern(), "/*");
    ISHIKO_TEST_FAIL_IF_NEQ(routes.at(2).pathPattern(), "*");
    ISHIKO_TEST_PASS();
}

void WebServerTests::ConstructorTest2(Test& test)
{
    boost::filesystem::path contentConfigurationFile =
        test.context().getTestDataPath("websites/test-site-2/content.json");
    boost::filesystem::path presentationConfigurationFile =
        test.context().getTestDataPath("websites/test-site-2/presentation.json");

    NullLoggingSink sink;
    Logger log(sink);

    Configuration configuration = WebServer::CommandLineSpecification().createDefaultConfiguration();
    configuration.set("content", contentConfigurationFile.string());
    configuration.set("presentation", presentationConfigurationFile.string());

    WebServer server(configuration, log);

    const Nemu::Routes& routes = server.routes();

    ISHIKO_TEST_ABORT_IF_NEQ(routes.size(), 4);
    ISHIKO_TEST_FAIL_IF_NEQ(routes.at(0).pathPattern(), "/index.html");
    ISHIKO_TEST_FAIL_IF_NEQ(routes.at(1).pathPattern(), "/docs/index.html");
    ISHIKO_TEST_FAIL_IF_NEQ(routes.at(2).pathPattern(), "/*");
    ISHIKO_TEST_FAIL_IF_NEQ(routes.at(3).pathPattern(), "*");
    ISHIKO_TEST_PASS();
}

void WebServerTests::ConstructorTest3(Test& test)
{
    boost::filesystem::path contentConfigurationFile =
        test.context().getTestDataPath("websites/doxygen-test-site-1/content.json");
    boost::filesystem::path presentationConfigurationFile =
        test.context().getTestDataPath("websites/doxygen-test-site-1/presentation.json");

    NullLoggingSink sink;
    Logger log(sink);

    Configuration configuration = WebServer::CommandLineSpecification().createDefaultConfiguration();
    configuration.set("content", contentConfigurationFile.string());
    configuration.set("presentation", presentationConfigurationFile.string());

    WebServer server(configuration, log);

    const Nemu::Routes& routes = server.routes();

    ISHIKO_TEST_ABORT_IF_NEQ(routes.size(), 5);
    ISHIKO_TEST_FAIL_IF_NEQ(routes.at(0).pathPattern(), "/index.html");
    ISHIKO_TEST_FAIL_IF_NEQ(routes.at(1).pathPattern(), "/docs/api/index.html");
    ISHIKO_TEST_FAIL_IF_NEQ(routes.at(2).pathPattern(), "/docs/api/class/class_polygon.html");
    ISHIKO_TEST_FAIL_IF_NEQ(routes.at(3).pathPattern(), "/*");
    ISHIKO_TEST_FAIL_IF_NEQ(routes.at(4).pathPattern(), "*");
    ISHIKO_TEST_PASS();
}

void WebServerTests::RunTest1(Test& test)
{
    boost::filesystem::path contentConfigurationFile =
        test.context().getTestDataPath("websites/test-site-1/content.json");
    boost::filesystem::path presentationConfigurationFile =
        test.context().getTestDataPath("websites/test-site-1/presentation.json");

    NullLoggingSink sink;
    Logger log(sink);

    Configuration configuration = WebServer::CommandLineSpecification().createDefaultConfiguration();
    configuration.set("content", contentConfigurationFile.string());
    configuration.set("presentation", presentationConfigurationFile.string());

    WebServer server(configuration, log);

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
    boost::filesystem::path presentationConfigurationFile =
        test.context().getTestDataPath("websites/test-site-1/presentation.json");

    NullLoggingSink sink;
    Logger log(sink);

    Configuration configuration = WebServer::CommandLineSpecification().createDefaultConfiguration();
    configuration.set("content", contentConfigurationFile.string());
    configuration.set("presentation", presentationConfigurationFile.string());

    WebServer server(configuration, log);

    std::thread serverThread(
        [&server]()
        {
            server.run();
        });

    // We download "/" and check it matches the expected output
    boost::filesystem::path outputPath1(test.context().getTestOutputPath("WebServerTests_RunTest2_root.bin"));
    std::ofstream responseFile1(outputPath1.string(), std::ios::out | std::ios::binary);
    Error error;
    HTTPClient::Get(IPv4Address::Localhost(), Port::http, "/", responseFile1, error);

    ISHIKO_TEST_FAIL_IF(error);

    responseFile1.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("WebServerTests_RunTest2_root.bin", "WebServerTests_RunTest2.bin");

    // We download "index.html" which is actually the same file that should have been returned when we downloaded "/"
    // and check it matches the same expected output.
    boost::filesystem::path outputPath2(test.context().getTestOutputPath("WebServerTests_RunTest2_index.bin"));
    std::ofstream responseFile2(outputPath2.string(), std::ios::out | std::ios::binary);
    HTTPClient::Get(IPv4Address::Localhost(), Port::http, "/index.html", responseFile2, error);

    ISHIKO_TEST_FAIL_IF(error);

    responseFile2.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("WebServerTests_RunTest2_index.bin", "WebServerTests_RunTest2.bin");

    server.stop();
    serverThread.join();

    ISHIKO_TEST_PASS();
}

void WebServerTests::RunTest3(Test& test)
{
    boost::filesystem::path contentConfigurationFile =
        test.context().getTestDataPath("websites/test-site-2/content.json");
    boost::filesystem::path presentationConfigurationFile =
        test.context().getTestDataPath("websites/test-site-2/presentation.json");

    NullLoggingSink sink;
    Logger log(sink);

    Configuration configuration = WebServer::CommandLineSpecification().createDefaultConfiguration();
    configuration.set("port", "8100");
    configuration.set("content", contentConfigurationFile.string());
    configuration.set("presentation", presentationConfigurationFile.string());

    WebServer server(configuration, log);

    std::thread serverThread(
        [&server]()
        {
            server.run();
        });

    // We download "/" and check it matches the expected output
    boost::filesystem::path outputPath1(test.context().getTestOutputPath("WebServerTests_RunTest3_root.bin"));
    std::ofstream responseFile1(outputPath1.string(), std::ios::out | std::ios::binary);
    Error error;
    HTTPClient::Get(IPv4Address::Localhost(), 8100, "/", responseFile1, error);

    ISHIKO_TEST_FAIL_IF(error);

    responseFile1.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("WebServerTests_RunTest3_root.bin", "WebServerTests_RunTest3_index.bin");

    // We download "index.html" which is actually the same file that should have been returned when we downloaded "/"
    // and check it matches the same expected output.
    boost::filesystem::path outputPath2(test.context().getTestOutputPath("WebServerTests_RunTest3_index.bin"));
    std::ofstream responseFile2(outputPath2.string(), std::ios::out | std::ios::binary);
    HTTPClient::Get(IPv4Address::Localhost(), 8100, "/index.html", responseFile2, error);

    ISHIKO_TEST_FAIL_IF(error);

    responseFile2.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("WebServerTests_RunTest3_index.bin", "WebServerTests_RunTest3_index.bin");

    boost::filesystem::path outputPath3(test.context().getTestOutputPath("WebServerTests_RunTest3_docs_index.bin"));
    std::ofstream responseFile3(outputPath3.string(), std::ios::out | std::ios::binary);
    HTTPClient::Get(IPv4Address::Localhost(), 8100, "/docs/index.html", responseFile3, error);

    ISHIKO_TEST_FAIL_IF(error);

    responseFile3.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("WebServerTests_RunTest3_docs_index.bin", "WebServerTests_RunTest3_docs_index.bin");

    server.stop();
    serverThread.join();

    ISHIKO_TEST_PASS();
}

void WebServerTests::RunTest4(Test& test)
{
    boost::filesystem::path contentConfigurationFile =
        test.context().getTestDataPath("websites/doxygen-test-site-1/content.json");
    boost::filesystem::path presentationConfigurationFile =
        test.context().getTestDataPath("websites/doxygen-test-site-1/presentation.json");

    NullLoggingSink sink;
    Logger log(sink);

    Configuration configuration = WebServer::CommandLineSpecification().createDefaultConfiguration();
    configuration.set("port", "8101");
    configuration.set("content", contentConfigurationFile.string());
    configuration.set("presentation", presentationConfigurationFile.string());

    WebServer server(configuration, log);

    std::thread serverThread(
        [&server]()
        {
            server.run();
        });

    // We download "/" and check it matches the expected output
    boost::filesystem::path outputPath1(test.context().getTestOutputPath("WebServerTests_RunTest4_root.bin"));
    std::ofstream responseFile1(outputPath1.string(), std::ios::out | std::ios::binary);
    Error error;
    HTTPClient::Get(IPv4Address::Localhost(), 8101, "/", responseFile1, error);

    ISHIKO_TEST_FAIL_IF(error);

    responseFile1.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("WebServerTests_RunTest4_root.bin", "WebServerTests_RunTest4_index.bin");

    // We download "index.html" which is actually the same file that should have been returned when we downloaded "/"
    // and check it matches the same expected output.
    boost::filesystem::path outputPath2(test.context().getTestOutputPath("WebServerTests_RunTest4_index.bin"));
    std::ofstream responseFile2(outputPath2.string(), std::ios::out | std::ios::binary);
    HTTPClient::Get(IPv4Address::Localhost(), 8101, "/index.html", responseFile2, error);

    ISHIKO_TEST_FAIL_IF(error);

    responseFile2.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("WebServerTests_RunTest4_index.bin", "WebServerTests_RunTest4_index.bin");

    boost::filesystem::path outputPath3(test.context().getTestOutputPath("WebServerTests_RunTest4_docs_api_index.bin"));
    std::ofstream responseFile3(outputPath3.string(), std::ios::out | std::ios::binary);
    HTTPClient::Get(IPv4Address::Localhost(), 8101, "/docs/api/index.html", responseFile3, error);

    ISHIKO_TEST_FAIL_IF(error);

    responseFile3.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("WebServerTests_RunTest4_docs_api_index.bin", "WebServerTests_RunTest4_docs_api_index.bin");

    boost::filesystem::path outputPath4(test.context().getTestOutputPath("WebServerTests_RunTest4_docs_api_class_polygon.bin"));
    std::ofstream responseFile4(outputPath4.string(), std::ios::out | std::ios::binary);
    HTTPClient::Get(IPv4Address::Localhost(), 8101, "/docs/api/class/class_polygon.html", responseFile4, error);

    ISHIKO_TEST_FAIL_IF(error);

    responseFile4.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("WebServerTests_RunTest4_docs_api_class_polygon.bin", "WebServerTests_RunTest4_docs_api_class_polygon.bin");

    server.stop();
    serverThread.join();

    ISHIKO_TEST_PASS();
}

void WebServerTests::RunTest5(Test& test)
{
    boost::filesystem::path contentConfigurationFile =
        test.context().getTestDataPath("websites/doxygen-test-site-2/content.json");
    boost::filesystem::path presentationConfigurationFile =
        test.context().getTestDataPath("websites/doxygen-test-site-2/presentation.json");

    NullLoggingSink sink;
    Logger log(sink);

    Configuration configuration = WebServer::CommandLineSpecification().createDefaultConfiguration();
    configuration.set("port", "8102");
    configuration.set("content", contentConfigurationFile.string());
    configuration.set("presentation", presentationConfigurationFile.string());

    WebServer server(configuration, log);

    std::thread serverThread(
        [&server]()
    {
        server.run();
    });

    // We download "/" and check it matches the expected output
    boost::filesystem::path outputPath1(test.context().getTestOutputPath("WebServerTests_RunTest5_root.bin"));
    std::ofstream responseFile1(outputPath1.string(), std::ios::out | std::ios::binary);
    Error error;
    HTTPClient::Get(IPv4Address::Localhost(), 8102, "/", responseFile1, error);

    ISHIKO_TEST_FAIL_IF(error);

    responseFile1.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("WebServerTests_RunTest5_root.bin", "WebServerTests_RunTest5_index.bin");

    // We download "index.html" which is actually the same file that should have been returned when we downloaded "/"
    // and check it matches the same expected output.
    boost::filesystem::path outputPath2(test.context().getTestOutputPath("WebServerTests_RunTest5_index.bin"));
    std::ofstream responseFile2(outputPath2.string(), std::ios::out | std::ios::binary);
    HTTPClient::Get(IPv4Address::Localhost(), 8102, "/index.html", responseFile2, error);

    ISHIKO_TEST_FAIL_IF(error);

    responseFile2.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("WebServerTests_RunTest5_index.bin", "WebServerTests_RunTest5_index.bin");

    boost::filesystem::path outputPath3(test.context().getTestOutputPath("WebServerTests_RunTest5_docs_api_index.bin"));
    std::ofstream responseFile3(outputPath3.string(), std::ios::out | std::ios::binary);
    HTTPClient::Get(IPv4Address::Localhost(), 8102, "/docs/api/index.html", responseFile3, error);

    ISHIKO_TEST_FAIL_IF(error);

    responseFile3.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("WebServerTests_RunTest5_docs_api_index.bin", "WebServerTests_RunTest5_docs_api_index.bin");

    server.stop();
    serverThread.join();

    ISHIKO_TEST_PASS();
}
