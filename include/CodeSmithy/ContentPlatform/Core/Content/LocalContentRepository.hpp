/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_LOCALCONTENTREPOSITORY_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_CONTENT_LOCALCONTENTREPOSITORY_HPP_

#include "Content.hpp"
#include <boost/filesystem.hpp>
#include <Ishiko/JSON.hpp>
#include <string>

namespace CodeSmithy
{
namespace ContentPlatform
{

class LocalContentRepository : public Content
{
public:
    LocalContentRepository(const boost::filesystem::path& contentConfigurationFile);

    std::string getTitle() const override;
    void homepage() const override;

private:
    class JSONParserCallbacks : public Ishiko::JSONPushParser::Callbacks
    {
    public:
        JSONParserCallbacks(LocalContentRepository& repository);

        void onMemberName(boost::string_view data) override;
        void onString(boost::string_view data) override;

    private:
        LocalContentRepository& m_repository;
        std::string m_context;
    };

    std::string m_title;
};

}
}

#endif
