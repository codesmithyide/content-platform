/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_TESTS_STATICSITETESTS_STATICSITEGENERATORTESTS_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_TESTS_STATICSITETESTS_STATICSITEGENERATORTESTS_HPP_

#include <Ishiko/TestFramework.hpp>

class StaticSiteGeneratorTests : public Ishiko::TestSequence
{
public:
    StaticSiteGeneratorTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void RunTest1(Ishiko::Test& test);
    static void RunTest2(Ishiko::Test& test);
};

#endif
