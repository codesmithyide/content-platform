/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_CONTENTREFERENCE_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_CONTENTREFERENCE_HPP_

#include <string>

namespace CodeSmithy
{
namespace ContentPlatform
{

class ContentReference
{
public:
    ContentReference() = default;
    ContentReference(std::string scheme, std::string id);

    const std::string& scheme() const noexcept;
    const std::string& id() const noexcept;

    bool operator==(const ContentReference& other) const noexcept;
    bool operator!=(const ContentReference& other) const noexcept;

private:
    std::string m_scheme;
    std::string m_id;
};

}
}

#endif
