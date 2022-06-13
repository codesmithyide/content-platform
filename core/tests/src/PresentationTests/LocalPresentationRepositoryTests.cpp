/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "LocalPresentationRepositoryTests.hpp"
#include "CodeSmithy/ContentPlatform/Core/Presentation/LocalPresentationRepository.hpp"
#include "CodeSmithy/ContentPlatform/Core/Presentation/PresentationProfile.hpp"
#include <vector>

using namespace CodeSmithy::ContentPlatform;
using namespace Ishiko;

LocalPresentationRepositoryTests::LocalPresentationRepositoryTests(const TestNumber& number,
    const TestContext& context)
    : TestSequence(number, "LocalPresentationRepository tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
}

void LocalPresentationRepositoryTests::ConstructorTest1(Test& test)
{
    boost::filesystem::path presentationConfigurationFile =
        test.context().getDataPath("websites/test-site-1/presentation.json");

    LocalPresentationRepository repository(presentationConfigurationFile);

    const std::vector<PresentationProfile>& profiles = repository.getProfiles();

    ISHIKO_TEST_ABORT_IF_NEQ(profiles.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(profiles[0].name(), "page");
    ISHIKO_TEST_ABORT_IF_NEQ(profiles[0].templateEngineConfiguration().size(), 2);

    std::string templatesRootDirectory =
        profiles[0].templateEngineConfiguration().value("templates-root-directory").asString();
    std::string layoutsRootDirectory =
        profiles[0].templateEngineConfiguration().value("layouts-root-directory").asString();

    ISHIKO_TEST_FAIL_IF_NEQ(templatesRootDirectory.substr(templatesRootDirectory.size() - 5), "pages");
    ISHIKO_TEST_FAIL_IF_NEQ(layoutsRootDirectory.substr(layoutsRootDirectory.size() - 7), "layouts");
    ISHIKO_TEST_PASS();
}

void LocalPresentationRepositoryTests::ConstructorTest2(Test& test)
{
    boost::filesystem::path presentationConfigurationFile =
        test.context().getDataPath("websites/doxygen-test-site-1/presentation.json");

    LocalPresentationRepository repository(presentationConfigurationFile);

    const std::vector<PresentationProfile>& profiles = repository.getProfiles();

    ISHIKO_TEST_ABORT_IF_NEQ(profiles.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(profiles[0].name(), "page");
    ISHIKO_TEST_ABORT_IF_NEQ(profiles[0].templateEngineConfiguration().size(), 2);

    std::string templatesRootDirectory =
        profiles[0].templateEngineConfiguration().value("templates-root-directory").asString();
    std::string layoutsRootDirectory =
        profiles[0].templateEngineConfiguration().value("layouts-root-directory").asString();

    ISHIKO_TEST_FAIL_IF_NEQ(templatesRootDirectory.substr(templatesRootDirectory.size() - 5), "pages");
    ISHIKO_TEST_FAIL_IF_NEQ(layoutsRootDirectory.substr(layoutsRootDirectory.size() - 7), "layouts");

    ISHIKO_TEST_FAIL_IF_NEQ(profiles[1].name(), "doxygen");
    ISHIKO_TEST_ABORT_IF_NEQ(profiles[1].templateEngineConfiguration().size(), 2);

    templatesRootDirectory = profiles[1].templateEngineConfiguration().value("templates-root-directory").asString();
    layoutsRootDirectory = profiles[1].templateEngineConfiguration().value("layouts-root-directory").asString();

    ISHIKO_TEST_FAIL_IF_NEQ(templatesRootDirectory.substr(templatesRootDirectory.size() - 9), "templates");
    ISHIKO_TEST_FAIL_IF_NEQ(layoutsRootDirectory.substr(layoutsRootDirectory.size() - 7), "layouts");
    ISHIKO_TEST_PASS();
}
