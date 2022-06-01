/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Content/DoxygenContentScheme.hpp"

using namespace CodeSmithy::ContentPlatform;

DoxygenContentScheme::DoxygenContentScheme()
    : m_name("doxygen")
{
}

const std::string& DoxygenContentScheme::name() const noexcept
{
    return m_name;
}

std::vector<Nemu::Route> DoxygenContentScheme::instantiate(const Ishiko::Configuration& configuration)
{
    std::vector<Nemu::Route> routes;

    // TODO

    return routes;
}
