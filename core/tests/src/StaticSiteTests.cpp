/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "StaticSiteTests.hpp"
#include "StaticSiteTests/StaticSiteGeneratorTests.hpp"

using namespace Ishiko;

StaticSiteTests::StaticSiteTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "StaticSite tests", context)
{
    append<StaticSiteGeneratorTests>();
}
