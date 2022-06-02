/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_TESTS_LOCALPRESENTATIONTREPOSITORYTESTS_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_TESTS_LOCALPRESENTATIONTREPOSITORYTESTS_HPP_

#include <Ishiko/TestFramework.hpp>

class LocalPresentationRepositoryTests : public Ishiko::TestSequence
{
public:
    LocalPresentationRepositoryTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
};

#endif
