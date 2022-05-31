/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_TESTS_WEBSERVERTESTS_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_TESTS_WEBSERVERTESTS_HPP_

#include <Ishiko/TestFramework.hpp>

class WebServerTests : public Ishiko::TestSequence
{
public:
    WebServerTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void ConstructorTest2(Ishiko::Test& test);
    static void RunTest1(Ishiko::Test& test);
    static void RunTest2(Ishiko::Test& test);
    static void RunTest3(Ishiko::Test& test);
};

#endif
