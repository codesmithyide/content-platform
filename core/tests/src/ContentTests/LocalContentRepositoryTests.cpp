/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "LocalContentRepositoryTests.hpp"
#include "CodeSmithy/ContentPlatform/Core/Content/LocalContentRepository.hpp"

using namespace CodeSmithy::ContentPlatform;
using namespace Ishiko;

LocalContentRepositoryTests::LocalContentRepositoryTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "LocalContentRepository tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructorTest1);
}

void LocalContentRepositoryTests::ConstructorTest1(Test& test)
{
    LocalContentRepository repository;

    ISHIKO_TEST_PASS();
}
