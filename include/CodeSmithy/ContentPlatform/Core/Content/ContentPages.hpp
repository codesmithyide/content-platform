/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_CONTENTPAGES_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_CONTENTPAGES_HPP_

#include <string>
#include <vector>

namespace CodeSmithy
{
namespace ContentPlatform
{

class ContentPages
{
public:
    typedef std::vector<std::string>::iterator iterator;

    size_t size() const noexcept;
    const std::string& at(size_t pos) const;

    iterator begin() noexcept;
    iterator end() noexcept;

    void pushBack(const std::string& page);

private:
    std::vector<std::string> m_pages;
};

}
}

#endif
