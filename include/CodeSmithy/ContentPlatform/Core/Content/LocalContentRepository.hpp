/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_LOCALCONTENTREPOSITORY_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_LOCALCONTENTREPOSITORY_HPP_

#include "Content.hpp"

namespace CodeSmithy
{
namespace ContentPlatform
{

class LocalContentRepository : public Content
{
public:
    std::string getTitle() const override;
};

}
}

#endif
