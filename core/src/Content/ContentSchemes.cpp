/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Content/ContentSchemes.hpp"

using namespace CodeSmithy::ContentPlatform;

bool ContentSchemes::find(const std::string& name, std::shared_ptr<ContentScheme>& scheme) const noexcept
{
    for (const std::shared_ptr<ContentScheme>& s : m_schemes)
    {
        if (s->name() == name)
        {
            scheme = s;
            return true;
        }
    }
    return false;
}

void ContentSchemes::add(std::shared_ptr<ContentScheme> scheme)
{
    m_schemes.push_back(scheme);
}
