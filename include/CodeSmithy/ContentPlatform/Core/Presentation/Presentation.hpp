/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_CONTENTPLATFORM_CORE_PRESENTATION_PRESENTATION_HPP_
#define _CODESMITHY_CONTENTPLATFORM_CORE_PRESENTATION_PRESENTATION_HPP_

#include <string>

namespace CodeSmithy
{
namespace ContentPlatform
{

class Presentation
{
public:
    Presentation(std::string templatesRootDir, std::string layoutsRootDir);

    // TODO: this is too simple and needs to be replaced by entire engine profiles configuration
    const std::string& templatesRootDir() const;
    const std::string& layoutsRootDir() const;

private:
    std::string m_templatesRootDir;
    std::string m_layoutsRootDir;
};

}
}

#endif
