/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "ContentSchemesTests.hpp"
#include "CodeSmithy/ContentPlatform/Core/Content/ContentSchemes.hpp"
#include "CodeSmithy/ContentPlatform/Core/Content/PageContentScheme.hpp"

using namespace CodeSmithy::ContentPlatform;
using namespace Ishiko;

ContentSchemesTests::ContentSchemesTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "ContentSchemes tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("add test 1", AddTest1);
}

void ContentSchemesTests::ConstructorTest1(Test& test)
{
    ContentSchemes schemes;

    ISHIKO_TEST_PASS();
}

void ContentSchemesTests::AddTest1(Test& test)
{
    ContentSchemes schemes;

    schemes.add(std::make_shared<PageContentScheme>());

    std::shared_ptr<ContentScheme> scheme;
    bool found = schemes.find("page", scheme);

    ISHIKO_TEST_ABORT_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(scheme->name(), "page");
    ISHIKO_TEST_PASS();
}
