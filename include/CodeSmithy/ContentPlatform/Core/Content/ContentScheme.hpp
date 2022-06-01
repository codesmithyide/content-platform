/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_CONTENTSCHEME_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_CONTENTSCHEME_HPP_

#include <string>

namespace CodeSmithy
{
namespace ContentPlatform
{

class ContentScheme
{
public:
    virtual const std::string& name() const noexcept = 0;
};

}
}

#endif
