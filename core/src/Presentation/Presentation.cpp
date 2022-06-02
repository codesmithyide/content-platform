/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Presentation/Presentation.hpp"

using namespace CodeSmithy::ContentPlatform;

const std::string& Presentation::templatesRootDir() const
{
    return m_templatesRootDir;
}

const std::string& Presentation::layoutsRootDir() const
{
    return m_layoutsRootDir;
}
