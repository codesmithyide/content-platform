/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "ContentTests.hpp"
#include "PresentationTests.hpp"
#include "StaticSiteTests.hpp"
#include "WebServerTests.hpp"
#include "CodeSmithy/ContentPlatform/Core/linkoptions.hpp"
#include <Ishiko/TestFramework/Core.hpp>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("CodeSmithyContentPlatformCore Library Tests");

    theTestHarness.context().setTestDataDirectory("../../data");
    theTestHarness.context().setTestOutputDirectory("../../output");
    theTestHarness.context().setReferenceDataDirectory("../../reference");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<PresentationTests>();
    theTests.append<ContentTests>();
    theTests.append<StaticSiteTests>();
    theTests.append<WebServerTests>();

    return theTestHarness.run();
}
