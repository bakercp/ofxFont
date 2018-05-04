//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/Text/FTFontSettings.h"
#include "ofx/Text/FTFontCache.h"


namespace ofx {
namespace Text {


FTFontSettings::FTFontSettings()
{
}
    
    
FTFontSettings::FTFontSettings(const std::filesystem::path& fontPath,
                               float size):
    FTFontSettings(FTFaceDescriptor(fontPath), FTSizeDescriptor(size))
{
}


FTFontSettings::FTFontSettings(const FontDescriptor& fontDescriptor,
                               float size):
    FTFontSettings(fontDescriptor, FTSizeDescriptor(size))
{
}


FTFontSettings::FTFontSettings(const FontDescriptor& fontDescriptor,
                               const FTSizeDescriptor& fontSizeDescriptor):
    FTFontSettings(FTFontCache::instance().getFaceDescriptorForFontDescriptor(fontDescriptor),
                   fontSizeDescriptor)
{
}


FTFontSettings::FTFontSettings(const FTFaceDescriptor& faceDescriptor,
                               const FTSizeDescriptor& fontSizeDescriptor):
    _faceDescriptor(faceDescriptor),
    _fontSizeDescriptor(fontSizeDescriptor)
{
}

    
FTFontSettings::~FTFontSettings()
{
}


FTFaceDescriptor FTFontSettings::faceDescriptor() const
{
    return _faceDescriptor;
}


FTSizeDescriptor FTFontSettings::fontSizeDescriptor() const
{
    return _fontSizeDescriptor;
}


bool FTFontSettings::operator < (const FTFontSettings& other) const
{
    if (_faceDescriptor != other._faceDescriptor)
        return _faceDescriptor < other._faceDescriptor;
    
    return _fontSizeDescriptor < other._fontSizeDescriptor;
}


} } // namespace ofx::Text
