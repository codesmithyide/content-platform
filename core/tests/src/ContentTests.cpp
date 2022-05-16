/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "ContentTests.hpp"
#include "ContentTests/LocalContentRepositoryTests.hpp"

using namespace Ishiko;

ContentTests::ContentTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Content tests", context)
{
    append<LocalContentRepositoryTests>();
}
