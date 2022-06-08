/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_CONTENTSCHEME_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_CONTENTSCHEME_HPP_

#include <Ishiko/Configuration.hpp>
#include <Nemu.hpp>
#include <string>
#include <vector>

namespace CodeSmithy
{
namespace ContentPlatform
{

/**
    \brief The ContentScheme class is an abtract class that represents schemes to convert content into web pages.

    Content implementations use implementations of this interface to convert content of a specific kind into a series
    of routes that can be returned as part of the routes returned by Content::getRoutes.
*/
class ContentScheme
{
public:
    virtual const std::string& name() const noexcept = 0;
    // TODO: name for this function
    virtual std::vector<Nemu::Route> instantiate(const Ishiko::Configuration& configuration) = 0;
};

}
}

#endif
