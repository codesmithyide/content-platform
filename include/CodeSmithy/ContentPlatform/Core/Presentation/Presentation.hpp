/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_PRESENTATION_PRESENTATION_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_PRESENTATION_PRESENTATION_HPP_

#include "PresentationProfile.hpp"
#include <vector>

namespace CodeSmithy
{
namespace ContentPlatform
{

class Presentation
{
public:
    virtual std::vector<PresentationProfile> getProfiles() const = 0;
};

}
}

#endif
