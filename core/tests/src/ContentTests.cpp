/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "ContentTests.hpp"
#include "ContentTests/ContentSchemesTests.hpp"
#include "ContentTests/DoxygenContentSchemeTests.hpp"
#include "ContentTests/LocalContentRepositoryTests.hpp"
#include "ContentTests/PageContentSchemeTests.hpp"

using namespace Ishiko;

ContentTests::ContentTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Content tests", context)
{
    append<PageContentSchemeTests>();
    append<DoxygenContentSchemeTests>();
    append<ContentSchemesTests>();
    append<LocalContentRepositoryTests>();
}
