/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_CONTENTSCHEMES_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_CONTENTSCHEMES_HPP_

#include "ContentScheme.hpp"
#include <memory>
#include <string>
#include <vector>

namespace CodeSmithy
{
namespace ContentPlatform
{

class ContentSchemes
{
public:
    bool find(const std::string& name, std::shared_ptr<ContentScheme>& scheme) const noexcept;

    void add(std::shared_ptr<ContentScheme> scheme);

private:
    std::vector<std::shared_ptr<ContentScheme>> m_schemes;
};

}
}

#endif
