/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_LOCALCONTENTREPOSITORY_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_LOCALCONTENTREPOSITORY_HPP_

#include "Content.hpp"
#include "ContentSchemes.hpp"
#include <boost/filesystem.hpp>
#include <Ishiko/JSON.hpp>
#include <Nemu.hpp>
#include <string>
#include <vector>

namespace CodeSmithy
{
namespace ContentPlatform
{

class LocalContentRepository : public Content
{
public:
    LocalContentRepository(const boost::filesystem::path& contentConfigurationFile);

    std::string getTitle() const override;
    ContentReference getHomepage() const override;
    Nemu::Routes getRoutes() const override;

private:
    class JSONParserCallbacks : public Ishiko::JSONPushParser::Callbacks
    {
    public:
        JSONParserCallbacks(LocalContentRepository& repository);

        void onMemberName(boost::string_view data) override;
        void onMemberEnd() override;
        void onArrayBegin() override;
        void onArrayEnd() override;
        void onString(boost::string_view data) override;

    private:
        LocalContentRepository& m_repository;
        std::vector<std::string> m_context;
    };

    // TODO: this shouldn't live in the Content I think. The supported schemes are independent of the actual content.
    ContentSchemes m_schemes;
    std::string m_title;
    ContentReference m_homepage;
    Nemu::Routes m_routes;
};

}
}

#endif
