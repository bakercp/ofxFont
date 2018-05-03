//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <ft2build.h>
#include FT_FREETYPE_H
#include "ofConstants.h"
#include "ofPixels.h"
#include "ofRectangle.h"
#include "ofx/Text/FTFontSettings.h"


namespace ofx {
namespace Text {


/// \brief An FTFont represents a resolved font with specific render settings.
class FTFont//: public BaseFont
{
public:
    FTFont();

    /// \brief Create an FTFont with a parent and settings.
    /// \param settings The font settings.
    FTFont(const FTFontSettings& settings);

    virtual ~FTFont();

    /// \brief Load the font with the given settings.
    /// \param settings The font settings to load.
    /// \returns true if loaded successfully.
    bool setup(const FTFontSettings& settings);

    bool isScalable() const /*override*/;
    bool hasFixedSizes() const /*override*/;
    bool isFixedWidth() const /*override*/;
    bool isSFNT() const /*override*/;
    bool hasHorizontalGlyphMetrics() const /*override*/;
    bool hasVerticalGlyphMetrics() const /*override*/;
    bool hasKerning() const /*override*/;
    bool hasMultipleMasters() const /*override*/;
    bool hasGlyphNames() const /*override*/;
    bool isCIDKeyed() const /*override*/;
    bool hasColorBitmaps() const /*override*/;

    std::string postscriptName() const /*override*/;
    std::string familyName() const /*override*/;
    std::string styleName() const /*override*/;

    int maxAdvanceWidth() const /*override*/;
    int maxAdvanceHeight() const /*override*/;
    int underlinePosition() const /*override*/;
    int underlineThickness() const /*override*/;
    int descender() const /*override*/;
    int ascender() const /*override*/;
    int height() const /*override*/;
    int unitsPerEm() const /*override*/;
    std::size_t numGlyphsInFont() const /*override*/;
    ofRectangle boundingBox() const /*override*/;

    /// \brief Determine if a font is "tricky".
    ///
    /// This is used to describe fonts that are handled in a special way by
    /// FreeType.
    ///
    /// \sa http://freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_FACE_FLAG_TRICKY
    /// \returns true if the font is "tricky".
    bool isTricky() const;

    /// \returns a string with some debugging information.
    std::string toString() const
    {
        std::stringstream ss;
        ss << "       Scalable? " << isScalable() << std::endl;
        ss << "  hasFixedSizes? " << hasFixedSizes() << std::endl;
        ss << "   isFixedWidth? " << isFixedWidth() << std::endl;
        ss << "         isSFNT? " << isSFNT() << std::endl;
        ss << "     hasKerning? " << hasKerning() << std::endl;
        ss << "  hasGlyphNames? " << hasGlyphNames() << std::endl;
        ss << "hasColorBitmaps? " << hasColorBitmaps() << std::endl;
        ss << " postscriptName? " << postscriptName() << std::endl;
        ss << "     familyName? " << familyName() << std::endl;
        ss << "      styleName? " << styleName() << std::endl;
        return ss.str();
    }

private:
    /// \brief True Has this font has been initialized.
    bool _isInitialized = false;

    /// \brief True if font is scalable.
    bool _isScalable = false;

    /// \brief True if the font has fixed sizes.
    bool _hasFixedSizes = false;

    /// \brief True if the font is a fixed width font.
    bool _isFixedWidth = false;

    /// \brief True if the font uses the SFNT storage format.
    bool _isSFNT = false;

    /// \brief True if the font has horizontal glyph metrics.
    bool _hasHorizontalGlyphMetrics = false;

    /// \brief True if the font has vertical glyph metrics.
    bool _hasVerticalGlyphMetrics = false;

    /// \brief True if the font has accessible kerning data.
    bool _hasKerning = false;

    /// \brief True if the font has multiple masters.
    bool _hasMultipleMasters = false;

    /// \brief True if the font has glyph names.
    bool _hasGlyphNames = false;

    /// \brief True if the font is CID keyed.
    bool _isCIDKeyed = false;

    /// \brief True if the font is "tricky".
    ///
    /// This is used to describe fonts that are handled in a special way by
    /// FreeType.
    bool _isTricky = false;
    bool _hasColorBitmaps = false;

    std::string _postscriptName;
    std::string _familyName;
    std::string _styleName;

    int _maxAdvanceWidth = 0;
    int _maxAdvanceHeight = 0;
    int _underlinePosition = 0;
    int _underlineThickness = 0;
    int _descender = 0;
    int _ascender = 0;
    int _height = 0;
    int _unitsPerEm = 0;
    std::size_t _numGlyphsInFont = 0;
    ofRectangle _boundingBox;

    /// \brief The strike index for fonts with fixed sizes.
    FT_Int _strikeIndex = 0;

    /// \brief The glyph pixel format.
    ofPixelFormat _glyphPixelFormat = OF_PIXELS_GRAY;

    /// \brief The transform matrix applied to each glyph.
    ///
    /// This is not applied to an entire face because transforms applied to
    /// cached faces affect all other sizes.
    FT_Matrix _transformMatrix;

    friend class FTFontCache;
    friend class FTFontGlyph;

};


} } // namespace ofx::Text
