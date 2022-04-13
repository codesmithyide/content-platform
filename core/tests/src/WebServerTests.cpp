/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "WebServerTests.hpp"
#include "CodeSmithy/ContentPlatform/Core/WebServer/WebServer.hpp"
#include <Ishiko/Logging.hpp>

using namespace CodeSmithy::ContentPlatform;
using namespace Ishiko;

WebServerTests::WebServerTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "WebServer tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructorTest1);
}

void WebServerTests::ConstructorTest1(Test& test)
{
    Ishiko::NullLoggingSink sink;
    Ishiko::Logger log(sink);

    WebServer server(log);

    ISHIKO_TEST_PASS();
}
