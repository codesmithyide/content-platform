/*
    Copyright (c) 2022-2023 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "PageContentSchemeTests.hpp"
#include "CodeSmithy/ContentPlatform/Core/Content/PageContentScheme.hpp"
#include <boost/filesystem.hpp>
#include <Ishiko/Configuration.hpp>
#include <Ishiko/Errors.hpp>
#include <Ishiko/FileSystem.hpp>
#include <Ishiko/Logging.hpp>
#include <Nemu.hpp>
#include <memory>

using namespace CodeSmithy::ContentPlatform;
using namespace Ishiko;

PageContentSchemeTests::PageContentSchemeTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "PageContentScheme tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("instantiate test 1", InstantiateTest1);
}

void PageContentSchemeTests::ConstructorTest1(Test& test)
{
    PageContentScheme scheme;

    ISHIKO_TEST_FAIL_IF_NEQ(scheme.name(), "page");
    ISHIKO_TEST_PASS();
}

void PageContentSchemeTests::InstantiateTest1(Test& test)
{
    boost::filesystem::path outputPath = test.context().getOutputPath("PageContentSchemeTests_InstantiateTest1.html");

    Nemu::Views views;
    views.set("page", std::make_shared<Nemu::DebugTemplateEngineProfile>());

    PageContentScheme scheme;

    Configuration schemeConfiguration;
    schemeConfiguration.set("path", "pages/index.html");
    schemeConfiguration.set("title", "PageContentSchemeTests_InstantiateTest1");
    std::vector<Nemu::Route> routes = scheme.instantiate(schemeConfiguration);

    ISHIKO_TEST_ABORT_IF_NEQ(routes.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(routes[0].pathPattern(), "/index.html");
    
    NullLoggingSink sink;
    Logger log(sink);
    Nemu::WebRequest request(Ishiko::URL("/index.html"));
    Nemu::WebResponseBuilder response;
    response.m_views = &views;
    routes[0].runHandler(request, response, log);

    // TODO: use exceptions
    Ishiko::Error error;
    BinaryFile file = BinaryFile::Create(outputPath, error);
    file.write(response.body().c_str(), response.body().size(), error);
    file.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("PageContentSchemeTests_InstantiateTest1.html");
    ISHIKO_TEST_PASS();
}
