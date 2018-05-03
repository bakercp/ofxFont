//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/Text/FTFontSettings.h"


namespace ofx {
namespace Text {


FTFontSettings::FTFontSettings(const FontDescriptor& fontDescriptor,
                               float size):
    FTFontSettings(fontDescriptor, FTSizeDescriptor(size))
{
}


FTFontSettings::FTFontSettings(const FontDescriptor& fontDescriptor,
                               const FTSizeDescriptor& fontSizeDescriptor):
    _fontDescriptor(fontDescriptor),
    _fontSizeDescriptor(fontSizeDescriptor)
{
}


FTFontSettings::~FTFontSettings()
{
}


FontDescriptor FTFontSettings::fontDescriptor() const
{
    return _fontDescriptor;
}


FTSizeDescriptor FTFontSettings::fontSizeDescriptor() const
{
    return _fontSizeDescriptor;
}


bool FTFontSettings::operator < (const FTFontSettings& other) const
{
    if (_fontDescriptor != other._fontDescriptor)
        return _fontDescriptor < other._fontDescriptor;
    return _fontSizeDescriptor < other._fontSizeDescriptor;
}


} } // namespace ofx::Text
