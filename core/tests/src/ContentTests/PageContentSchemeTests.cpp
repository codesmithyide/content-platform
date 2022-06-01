/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "PageContentSchemeTests.hpp"
#include "CodeSmithy/ContentPlatform/Core/Content/PageContentScheme.hpp"

using namespace CodeSmithy::ContentPlatform;
using namespace Ishiko;

PageContentSchemeTests::PageContentSchemeTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "PageContentScheme tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void PageContentSchemeTests::ConstructorTest1(Test& test)
{
    PageContentScheme scheme;

    ISHIKO_TEST_FAIL_IF_NEQ(scheme.name(), "page");
    ISHIKO_TEST_PASS();
}
