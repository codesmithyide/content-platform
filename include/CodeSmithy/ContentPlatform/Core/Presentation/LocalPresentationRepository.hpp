/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_PRESENTATION_LOCALPRESENTATIONREPOSITORY_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_PRESENTATION_LOCALPRESENTATIONREPOSITORY_HPP_

#include "Presentation.hpp"
#include "PresentationProfile.hpp"
#include <boost/filesystem.hpp>
#include <Ishiko/JSON.hpp>
#include <string>
#include <vector>

namespace CodeSmithy
{
namespace ContentPlatform
{

class LocalPresentationRepository : public Presentation
{
public:
    LocalPresentationRepository(const boost::filesystem::path& presentationConfigurationFile);

    std::vector<PresentationProfile> getProfiles() const override;

private:
    class JSONParserCallbacks : public Ishiko::JSONPushParser::Callbacks
    {
    public:
        JSONParserCallbacks(LocalPresentationRepository& repository);

        void onMemberName(boost::string_view data) override;
        void onMemberEnd() override;
        void onArrayBegin() override;
        void onArrayEnd() override;
        void onString(boost::string_view data) override;

    private:
        LocalPresentationRepository& m_repository;
        std::vector<std::string> m_context;
    };

    std::vector<PresentationProfile> m_profiles;
};

}
}

#endif
