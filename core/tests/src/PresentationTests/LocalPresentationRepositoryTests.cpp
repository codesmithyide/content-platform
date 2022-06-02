/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "LocalPresentationRepositoryTests.hpp"

using namespace Ishiko;

LocalPresentationRepositoryTests::LocalPresentationRepositoryTests(const TestNumber& number,
    const TestContext& context)
    : TestSequence(number, "LocalPresentationRepository tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void LocalPresentationRepositoryTests::ConstructorTest1(Test& test)
{
}
