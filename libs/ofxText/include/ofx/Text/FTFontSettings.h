//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofx/Text/FontDescriptor.h"
#include "ofx/Text/FTSizeDescriptor.h"


namespace ofx {
namespace Text {


/// \brief A settings object to describe a given ofFTFont.
///
/// This class is used to configure an FTFont and is used as a key for the
/// FTFont cache present in FTFontCache.
class FTFontSettings
{
public:
    /// \brief Create an FTFontSettings with the given parameters.
    /// \param fontDescriptor The font descriptor.
    /// \param size The point size of the font.
    FTFontSettings(const FontDescriptor& fontDescriptor, float size);

    /// \brief Create an FTFontSettings with the given parameters.
    /// \param fontDescriptor The font descriptor.
    /// \param fontSizeDescriptor The font size descriptor.
    FTFontSettings(const FontDescriptor& fontDescriptor,
                   const FTSizeDescriptor& fontSizeDescriptor);

    /// \brief Destroy the font settings.
    virtual ~FTFontSettings();

    /// \returns the font descriptor.
    FontDescriptor fontDescriptor() const;

    /// \returns the font size descriptor.
    FTSizeDescriptor fontSizeDescriptor() const;

    /// \brief A comparison operator used with std::map and other collections.
    /// \returns true iff this key is less than the other key.
    bool operator < (const FTFontSettings& other) const;

private:
    /// \brief The font descriptor.
    FontDescriptor _fontDescriptor;

    /// \brief The font size descriptor.
    FTSizeDescriptor _fontSizeDescriptor;

};


} } // namespace ofx::Text


