//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
// Copyright (c) 2014-2017 Devon Govett <https://github.com/devongovett/font-manager>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/Text/FontManager.h"


namespace ofx {
namespace Text {

    
FontDescriptor FontManager::findFont()
{
    FontDescriptor fd;
    fd.family = "Arial";
    return findFont(fd);
}


} } // namespace ofx::Text

