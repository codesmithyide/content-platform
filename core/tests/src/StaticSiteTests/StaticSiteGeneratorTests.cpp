/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "StaticSiteGeneratorTests.hpp"

using namespace Ishiko;

StaticSiteGeneratorTests::StaticSiteGeneratorTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "StaticSiteGenerator tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void StaticSiteGeneratorTests::ConstructorTest1(Test& test)
{
}
