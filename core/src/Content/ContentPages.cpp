/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Content/ContentPages.hpp"

using namespace CodeSmithy::ContentPlatform;

size_t ContentPages::size() const noexcept
{
    return m_pages.size();
}

const std::string& ContentPages::at(size_t pos) const
{
    return m_pages.at(pos);
}

void ContentPages::pushBack(const std::string& page)
{
    m_pages.push_back(page);
}
