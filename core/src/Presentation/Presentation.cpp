/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/content-platform/blob/main/LICENSE.txt
*/

#include "Presentation/Presentation.hpp"

using namespace CodeSmithy::ContentPlatform;

Presentation::Presentation(std::string templatesRootDir, std::string layoutsRootDir)
    : m_templatesRootDir(std::move(templatesRootDir)), m_layoutsRootDir(std::move(layoutsRootDir))
{
}

const std::string& Presentation::templatesRootDir() const
{
    return m_templatesRootDir;
}

const std::string& Presentation::layoutsRootDir() const
{
    return m_layoutsRootDir;
}
