/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_CONTENT_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_CONTENT_HPP_

#include <string>

namespace CodeSmithy
{
namespace ContentPlatform
{

class Content
{
public:
    virtual ~Content() = default;

    virtual std::string getTitle() const = 0;
    virtual void homepage() const = 0;
};

}
}

#endif
