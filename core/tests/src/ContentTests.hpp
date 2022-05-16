/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_TESTS_CONTENTTESTS_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_TESTS_CONTENTTESTS_HPP_

#include <Ishiko/TestFramework.hpp>

class ContentTests : public Ishiko::TestSequence
{
public:
    ContentTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);
};

#endif
