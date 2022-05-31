/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "LocalContentRepositoryTests.hpp"
#include "CodeSmithy/ContentPlatform/Core/Content/LocalContentRepository.hpp"

using namespace CodeSmithy::ContentPlatform;
using namespace Ishiko;

LocalContentRepositoryTests::LocalContentRepositoryTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "LocalContentRepository tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructorTest1);
}

void LocalContentRepositoryTests::ConstructorTest1(Test& test)
{
    boost::filesystem::path contentConfigurationFile = test.context().getTestDataPath("websites/test-site-1/content.json");

    LocalContentRepository repository(contentConfigurationFile);

    ISHIKO_TEST_FAIL_IF_NEQ(repository.getTitle(), "Test Site 1");
    ISHIKO_TEST_FAIL_IF_NEQ(repository.getHomepage(), ContentReference("page", "pages/index.html"));
    ISHIKO_TEST_PASS();
}
