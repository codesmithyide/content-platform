/*
    Copyright (c) 2022-2023 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "DoxygenContentSchemeTests.hpp"
#include "CodeSmithy/ContentPlatform/Core/Content/DoxygenContentScheme.hpp"
#include <boost/filesystem.hpp>
#include <Ishiko/Configuration.hpp>
#include <Ishiko/Errors.hpp>
#include <Ishiko/FileSystem.hpp>
#include <Ishiko/Logging.hpp>
#include <Nemu.hpp>
#include <memory>

using namespace CodeSmithy::ContentPlatform;
using namespace Ishiko;

namespace
{

void RunHandlerAndSaveToFile(Nemu::Views& views, const Nemu::Route& route, const std::string& url,
    const boost::filesystem::path& outputPath)
{
    NullLoggingSink sink;
    Logger log(sink);

    Nemu::WebRequest request(url);
    Nemu::WebResponseBuilder response;
    response.m_views = &views;
    route.runHandler(request, response, log);

    // TODO: use exceptions
    Ishiko::Error error;
    BinaryFile file = BinaryFile::Create(outputPath, error);
    file.write(response.body().c_str(), response.body().size(), error);
}

}

DoxygenContentSchemeTests::DoxygenContentSchemeTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "DoxygenContentScheme tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("instantiate test 1", InstantiateTest1);
    append<HeapAllocationErrorsTest>("instantiate test 2", InstantiateTest2);
}

void DoxygenContentSchemeTests::ConstructorTest1(Test& test)
{
    DoxygenContentScheme scheme;

    ISHIKO_TEST_FAIL_IF_NEQ(scheme.name(), "doxygen");
    ISHIKO_TEST_PASS();
}

void DoxygenContentSchemeTests::InstantiateTest1(Test& test)
{
    boost::filesystem::path inputhPath = test.context().getDataPath("websites/doxygen-test-site-1/doxygen/index.xml");

    Nemu::Views views;
    views.set("doxygen", std::make_shared<Nemu::DebugTemplateEngineProfile>());

    DoxygenContentScheme scheme;

    Configuration schemeConfiguration;
    schemeConfiguration.set("index", inputhPath.string());
    schemeConfiguration.set("title", "DoxygenContentSchemeTests_InstantiateTest1");
    std::vector<Nemu::Route> routes = scheme.instantiate(schemeConfiguration);

    ISHIKO_TEST_ABORT_IF_NEQ(routes.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(routes[0].pathPattern(), "/docs/api/index.html");
    ISHIKO_TEST_FAIL_IF_NEQ(routes[1].pathPattern(), "/docs/api/class/class_polygon.html");

    boost::filesystem::path outputPath =
        test.context().getOutputPath("DoxygenContentSchemeTests_InstantiateTest1_index.html");
    RunHandlerAndSaveToFile(views, routes[0], "/docs/api/index.html", outputPath);
    
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("DoxygenContentSchemeTests_InstantiateTest1_index.html");

    outputPath = test.context().getOutputPath("DoxygenContentSchemeTests_InstantiateTest1_class_polygon.html");
    RunHandlerAndSaveToFile(views, routes[1], "/docs/api/class/class_polygon.html", outputPath);

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("DoxygenContentSchemeTests_InstantiateTest1_class_polygon.html");
    ISHIKO_TEST_PASS();
}

void DoxygenContentSchemeTests::InstantiateTest2(Test& test)
{
    boost::filesystem::path inputhPath = test.context().getDataPath("websites/doxygen-test-site-2/doxygen/index.xml");

    Nemu::Views views;
    views.set("doxygen", std::make_shared<Nemu::DebugTemplateEngineProfile>());

    DoxygenContentScheme scheme;

    Configuration schemeConfiguration;
    schemeConfiguration.set("index", inputhPath.string());
    schemeConfiguration.set("title", "DoxygenContentSchemeTests_InstantiateTest2");
    std::vector<Nemu::Route> routes = scheme.instantiate(schemeConfiguration);

    ISHIKO_TEST_ABORT_IF_NEQ(routes.size(), 3);
    ISHIKO_TEST_FAIL_IF_NEQ(routes[0].pathPattern(), "/docs/api/index.html");
    ISHIKO_TEST_FAIL_IF_NEQ(routes[1].pathPattern(), "/docs/api/class/class_polygon.html");
    ISHIKO_TEST_FAIL_IF_NEQ(routes[2].pathPattern(), "/docs/api/class/class_rectangle.html");

    boost::filesystem::path outputPath =
        test.context().getOutputPath("DoxygenContentSchemeTests_InstantiateTest2_index.html");
    RunHandlerAndSaveToFile(views, routes[0], "/docs/api/index.html", outputPath);

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("DoxygenContentSchemeTests_InstantiateTest2_index.html");

    outputPath = test.context().getOutputPath("DoxygenContentSchemeTests_InstantiateTest2_class_polygon.html");
    RunHandlerAndSaveToFile(views, routes[1], "/docs/api/class/class_polygon.html", outputPath);

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("DoxygenContentSchemeTests_InstantiateTest2_class_polygon.html");

    outputPath = test.context().getOutputPath("DoxygenContentSchemeTests_InstantiateTest2_class_rectangle.html");
    RunHandlerAndSaveToFile(views, routes[2], "/docs/api/class/class_polygon.html", outputPath);

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("DoxygenContentSchemeTests_InstantiateTest2_class_rectangle.html");
    
    ISHIKO_TEST_PASS();
}
