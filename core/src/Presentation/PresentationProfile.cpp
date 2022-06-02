/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Presentation/PresentationProfile.hpp"

using namespace CodeSmithy::ContentPlatform;

PresentationProfile::PresentationProfile(std::string name)
    : m_name(std::move(name))
{
}

const std::string& PresentationProfile::name() const noexcept
{
    return m_name;
}

const Ishiko::Configuration& PresentationProfile::templateEngineConfiguration() const noexcept
{
    return m_templateEngineConfiguration;
}

Ishiko::Configuration& PresentationProfile::templateEngineConfiguration()
{
    return m_templateEngineConfiguration;
}
