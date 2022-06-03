/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "DoxygenContentSchemeTests.hpp"
#include "CodeSmithy/ContentPlatform/Core/Content/DoxygenContentScheme.hpp"
#include <Ishiko/Configuration.hpp>
#include <Nemu.hpp>

using namespace CodeSmithy::ContentPlatform;
using namespace Ishiko;

DoxygenContentSchemeTests::DoxygenContentSchemeTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "DoxygenContentScheme tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("instantiate test 1", InstantiateTest1);
}

void DoxygenContentSchemeTests::ConstructorTest1(Test& test)
{
    DoxygenContentScheme scheme;

    ISHIKO_TEST_FAIL_IF_NEQ(scheme.name(), "doxygen");
    ISHIKO_TEST_PASS();
}


void DoxygenContentSchemeTests::InstantiateTest1(Test& test)
{
    DoxygenContentScheme scheme;

    Configuration schemeConfiguration;
    //schemeConfiguration.set("path", data.to_string());
    // TODO: this is a hack for now. Variables that should be passed to the ViewContext need a proper solution
    //schemeConfiguration.set("title", m_repository.getTitle());
    std::vector<Nemu::Route> routes = scheme.instantiate(schemeConfiguration);

    ISHIKO_TEST_ABORT_IF_NEQ(routes.size(), 1);
    ISHIKO_TEST_PASS();
}
