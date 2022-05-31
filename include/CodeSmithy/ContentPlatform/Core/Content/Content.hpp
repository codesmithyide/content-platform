/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_CONTENT_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_CONTENT_HPP_

#include "ContentReference.hpp"
#include <string>

namespace CodeSmithy
{
namespace ContentPlatform
{

// TODO: I don't like the name of this class. It's not really all the content but information about the content that is
// needed to put the site together. ContentManifest? ContentProvider?
class Content
{
public:
    virtual ~Content() = default;

    virtual std::string getTitle() const = 0;
    virtual ContentReference getHomepage() const = 0;
};

}
}

#endif
