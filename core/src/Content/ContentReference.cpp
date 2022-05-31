/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Content/ContentReference.hpp"

using namespace CodeSmithy::ContentPlatform;

ContentReference::ContentReference(std::string scheme, std::string id)
    : m_scheme(std::move(scheme)), m_id(std::move(id))
{
}

const std::string& ContentReference::scheme() const noexcept
{
    return m_scheme;
}

const std::string& ContentReference::id() const noexcept
{
    return m_id;
}

bool ContentReference::operator==(const ContentReference& other) const noexcept
{
    return ((m_scheme == other.m_scheme) && (m_id == other.m_id));
}

bool ContentReference::operator!=(const ContentReference& other) const noexcept
{
    return !(*this == other);
}
