/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "JSONContentRepositoryTests.hpp"
#include "CodeSmithy/ContentPlatform/Core/Content/JSONContentRepository.hpp"

using namespace CodeSmithy::ContentPlatform;
using namespace Ishiko;

JSONContentRepositoryTests::JSONContentRepositoryTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "JSONContentRepository tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructorTest1);
}

void JSONContentRepositoryTests::ConstructorTest1(Test& test)
{
    JSONContentRepository repository;

    ISHIKO_TEST_PASS();
}
