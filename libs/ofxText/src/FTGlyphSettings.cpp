//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/Text/FTGlyphSettings.h"


namespace ofx {
namespace Text {


FTGlyphSettings::FTGlyphSettings(): FTGlyphSettings(true)
{
}


FTGlyphSettings::FTGlyphSettings(bool antialiased):
    FTGlyphSettings(antialiased ? AUTO_LOAD_FLAGS : AUTO_LOAD_FLAGS_NO_ANTIALIAS,
                    FT_RENDER_MODE_NORMAL)
{
}


FTGlyphSettings::FTGlyphSettings(FT_Int32 loadFlags, FT_Render_Mode renderMode):
    _loadFlags(loadFlags),
    _renderMode(renderMode)
{
}


FTGlyphSettings::~FTGlyphSettings()
{
}


FT_Render_Mode FTGlyphSettings::renderMode() const
{
    return _renderMode;
}


FT_Int32 FTGlyphSettings::loadFlags() const
{
    return _loadFlags;
}


} } // namespace ofx::Text
