/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "StaticSiteGeneratorTests.hpp"
#include "CodeSmithy/ContentPlatform/Core/StaticSite/StaticSiteGenerator.hpp"
#include <boost/filesystem.hpp>
#include <Ishiko/Logging.hpp>

using namespace CodeSmithy::ContentPlatform;
using namespace Ishiko;

StaticSiteGeneratorTests::StaticSiteGeneratorTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "StaticSiteGenerator tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("run test 1", RunTest1);
    append<HeapAllocationErrorsTest>("run test 2", RunTest2);
}

void StaticSiteGeneratorTests::ConstructorTest1(Test& test)
{
    boost::filesystem::path contentConfigurationFile =
        test.context().getTestDataPath("websites/test-site-1/content.json");
    boost::filesystem::path presentationConfigurationFile =
        test.context().getTestDataPath("websites/test-site-1/presentation.json");
    boost::filesystem::path outputDirectory =
        test.context().getTestOutputPath("StaticSiteGeneratorTests_ConstructorTest1");

    NullLoggingSink sink;
    Logger log(sink);

    Configuration configuration = StaticSiteGenerator::CommandLineSpecification().createDefaultConfiguration();
    configuration.set("content", contentConfigurationFile.string());
    configuration.set("presentation", presentationConfigurationFile.string());
    configuration.set("output", outputDirectory.string());

    StaticSiteGenerator generator(configuration, log);

    ISHIKO_TEST_PASS();
}

void StaticSiteGeneratorTests::RunTest1(Test& test)
{
    boost::filesystem::path contentConfigurationFile =
        test.context().getTestDataPath("websites/test-site-1/content.json");
    boost::filesystem::path presentationConfigurationFile =
        test.context().getTestDataPath("websites/test-site-1/presentation.json");
    boost::filesystem::path outputDirectory = test.context().getTestOutputPath("StaticSiteGeneratorTests_RunTest1");

    NullLoggingSink sink;
    Logger log(sink);

    Configuration configuration = StaticSiteGenerator::CommandLineSpecification().createDefaultConfiguration();
    configuration.set("content", contentConfigurationFile.string());
    configuration.set("presentation", presentationConfigurationFile.string());
    configuration.set("output", outputDirectory.string());

    StaticSiteGenerator generator(configuration, log);

    generator.run();

    // TODO: directory comparison macro
    ISHIKO_TEST_FAIL_IF_FILES_NEQ("StaticSiteGeneratorTests_RunTest1/index.html",
        "StaticSiteGeneratorTests_RunTest1/index.html");
    ISHIKO_TEST_PASS();
}

void StaticSiteGeneratorTests::RunTest2(Test& test)
{
    boost::filesystem::path contentConfigurationFile =
        test.context().getTestDataPath("websites/test-site-2/content.json");
    boost::filesystem::path presentationConfigurationFile =
        test.context().getTestDataPath("websites/test-site-2/presentation.json");
    boost::filesystem::path outputDirectory = test.context().getTestOutputPath("StaticSiteGeneratorTests_RunTest2");

    NullLoggingSink sink;
    Logger log(sink);

    Configuration configuration = StaticSiteGenerator::CommandLineSpecification().createDefaultConfiguration();
    configuration.set("content", contentConfigurationFile.string());
    configuration.set("presentation", presentationConfigurationFile.string());
    configuration.set("output", outputDirectory.string());

    StaticSiteGenerator generator(configuration, log);

    generator.run();

    // TODO: directory comparison macro
    ISHIKO_TEST_FAIL_IF_FILES_NEQ("StaticSiteGeneratorTests_RunTest2/index.html",
        "StaticSiteGeneratorTests_RunTest2/index.html");
    ISHIKO_TEST_FAIL_IF_FILES_NEQ("StaticSiteGeneratorTests_RunTest2/docs/index.html",
        "StaticSiteGeneratorTests_RunTest2/docs/index.html");
    ISHIKO_TEST_PASS();
}
