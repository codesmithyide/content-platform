/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "PresentationTests.hpp"
#include "PresentationTests/LocalPresentationRepositoryTests.hpp"

using namespace Ishiko;

PresentationTests::PresentationTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Presentation tests", context)
{
    append<LocalPresentationRepositoryTests>();
}
