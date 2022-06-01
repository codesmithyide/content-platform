/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_CONTENT_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_CONTENT_HPP_

#include "ContentReference.hpp"
#include <Nemu.hpp>
#include <string>

namespace CodeSmithy
{
namespace ContentPlatform
{

// TODO: I don't like the name of this class. It's not really all the content but information about the content that is
// needed to put the site together. ContentManifest? ContentProvider?
// TODO: does this class also support pushing content as there could be a large number of pages. Granted it is unlikely
// to exceed what we can hold in memory. Given how I build the routing map now where 1 page is 1 route it'd have to fit
// though. Is there really a use case for routing that is so large that is stored on disk?
// TODO: should I invert the logic and pass in the Routes instance and add routes to it? That seems to work better with
// the schemes.
class Content
{
public:
    virtual ~Content() = default;

    virtual std::string getTitle() const = 0;
    virtual ContentReference getHomepage() const = 0;
    // TODO: see discussion above about number of pages and scalability
    virtual std::vector<Nemu::Route> getRoutes() const = 0;
};

}
}

#endif
