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
        JSONParserCallbacks(LocalPresentationRepository& repository,
            boost::filesystem::path configurationFileDirectory);

        void onMemberName(boost::string_view data) override;
        void onMemberEnd() override;
        void onArrayBegin() override;
        void onArrayEnd() override;
        void onString(boost::string_view data) override;

    private:
        // Adds an item to the teplate engine configuration of the last profile of m_profiles vector. The value is a
        // path that will be appended to m_configurationFileDirectory to make it an absolute path.
        void setConfigurationPath(const std::string& name, const std::string& path);

        LocalPresentationRepository& m_repository;
        // We need the directory of the configuration file because path inside it are relative to the configuration
        // file.
        boost::filesystem::path m_configurationFileDirectory;
        std::vector<std::string> m_context;
    };

    std::vector<PresentationProfile> m_profiles;
};

}
}

#endif
