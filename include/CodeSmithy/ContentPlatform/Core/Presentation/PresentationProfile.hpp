/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_PRESENTATION_PRESENTATIONPROFILE_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_PRESENTATION_PRESENTATIONPROFILE_HPP_

#include <Ishiko/Configuration.hpp>
#include <string>

namespace CodeSmithy
{
namespace ContentPlatform
{

class PresentationProfile
{
public:
    PresentationProfile(std::string name);

    const std::string& name() const noexcept;
    const Ishiko::Configuration& templateEngineConfiguration() const noexcept;
    Ishiko::Configuration& templateEngineConfiguration();

private:
    std::string m_name;
    Ishiko::Configuration m_templateEngineConfiguration;
};

}
}

#endif
