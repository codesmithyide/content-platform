/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_DOXYGENCONTENTSCHEME_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_DOXYGENCONTENTSCHEME_HPP_

#include "ContentScheme.hpp"
#include <Nemu.hpp>
#include <string>

namespace CodeSmithy
{
namespace ContentPlatform
{

class DoxygenContentScheme : public ContentScheme
{
public:
    DoxygenContentScheme();

    const std::string& name() const noexcept override;
    std::vector<Nemu::Route> instantiate(const Ishiko::Configuration& configuration) override;

private:
    std::string m_name;
    Nemu::ViewWebRequestHandler::DeclarativeCallbacks m_callbacks;
};

}
}

#endif
