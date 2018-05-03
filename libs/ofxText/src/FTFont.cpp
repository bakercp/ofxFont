//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/Text/FTFont.h"
#include "ofx/Text/FTFontCache.h"
#include "ofFileUtils.h"
#include "ofImage.h"
#include <cstdlib>


namespace ofx {
namespace Text {


FTFont::FTFont()
{
}


FTFont::FTFont(const FTFontSettings& settings)
{
    setup(settings);
}


FTFont::~FTFont()
{
    // The FTFontCache takes care of everything.
}


bool FTFont::setup(const FTFontSettings& settings)
{
    auto& cache = FTFontCache::instance();
    return true;
//
//    // Get the cached FT_Face face from the cache.
////    FT_Face _ftFace = cache.getFTFace(this);
//
//    // We attempt to cache all of the metrics in for the given face.
//    if (_ftFace != nullptr)
//    {
//        // Cache various face metrics and information.
//        _isScalable = FT_IS_SCALABLE(_ftFace);
//        _hasFixedSizes = FT_HAS_FIXED_SIZES(_ftFace);
//        _isFixedWidth = FT_IS_FIXED_WIDTH(_ftFace);
//        _isSFNT = FT_IS_SFNT(_ftFace);
//        _hasHorizontalGlyphMetrics = FT_HAS_HORIZONTAL(_ftFace);
//        _hasVerticalGlyphMetrics = FT_HAS_VERTICAL(_ftFace);
//        _hasKerning = FT_HAS_KERNING(_ftFace);
//        _hasMultipleMasters = FT_HAS_MULTIPLE_MASTERS(_ftFace);
//        _hasGlyphNames = FT_HAS_GLYPH_NAMES(_ftFace);
//        _isCIDKeyed = FT_IS_CID_KEYED(_ftFace);
//        _isTricky = FT_IS_TRICKY(_ftFace);
//        _hasColorBitmaps = FT_HAS_COLOR(_ftFace);
//
//        const char* postscriptName = FT_Get_Postscript_Name(_ftFace);
//        _postscriptName = (postscriptName != nullptr) ? postscriptName : "";
//        _familyName = (_ftFace->family_name != nullptr) ? _ftFace->family_name : "";
//        _styleName = (_ftFace->style_name != nullptr) ? _ftFace->style_name : "";
//
//        _maxAdvanceWidth = _ftFace->max_advance_width / DEFAULT_SCALER;
//        _maxAdvanceHeight = _ftFace->max_advance_height / DEFAULT_SCALER;
//        _underlinePosition = _ftFace->underline_position / DEFAULT_SCALER;
//        _underlineThickness = _ftFace->underline_thickness / DEFAULT_SCALER;
//
//        // Negative for inverted Y in openFrameworks.
//        _descender = (-1 * _ftFace->descender / DEFAULT_SCALER);
//        _ascender = _ftFace->ascender / DEFAULT_SCALER;
//        _height = _ftFace->height / DEFAULT_SCALER;
//        _unitsPerEm = _ftFace->units_per_EM / DEFAULT_SCALER;
//        _numGlyphsInFont = _ftFace->num_glyphs;
//
//        _boundingBox.set((_ftFace->bbox.xMin) / DEFAULT_SCALER,
//                         (_ftFace->bbox.yMin) / DEFAULT_SCALER,
//                         (_ftFace->bbox.xMax - _ftFace->bbox.xMin) / DEFAULT_SCALER,
//                         (_ftFace->bbox.yMax - _ftFace->bbox.yMax) / DEFAULT_SCALER);
//
//        // If we have fixed sizes, we must choose a strike index.
//        if (_hasFixedSizes)
//        {
//            FT_Int absoluteSizeDifference = std::numeric_limits<FT_Int>::max();
//
//            for (FT_Int index = 0; index < _ftFace->num_fixed_sizes; ++index)
//            {
//                // Calculate the absolute difference between the requested size and the available size.
//                FT_Int absoluteDelta = std::abs(static_cast<FT_Int>(settings.size()) - _ftFace->available_sizes[index].height);
//
//                if (absoluteDelta < absoluteSizeDifference)
//                {
//                    _strikeIndex = index;
//                    absoluteSizeDifference = absoluteDelta;
//                }
//            }
//        }
//
//        _faceIndex = settings.faceIndex();
//
//        // Interpret glyph loading flags.
//        if (settings.loadFlags() >= 0) // Negative values are used for "auto".
//        {
//            _ftLoadFlags = settings.loadFlags();
//        }
//        else if (hasColorBitmaps())
//        {
//            _ftLoadFlags = FT_LOAD_COLOR;
//        }
//        else if (settings.loadFlags() == FTFontSettings::AUTO_LOAD_FLAGS_NO_ANTIALIAS)
//        {
//            _ftLoadFlags = FT_LOAD_RENDER | FT_LOAD_TARGET_MONO;
//        }
//        else
//        {
//            _ftLoadFlags = FT_LOAD_RENDER | FT_LOAD_TARGET_NORMAL;
//        }
//
//        // Interpret the render mode.
//        _ftRenderMode = settings.renderMode();
//
//        // Interpret the pixel type.
//        if (_hasColorBitmaps && (_ftLoadFlags & FT_LOAD_COLOR))
//        {
//            // Color glyphs are stored in a BRGA format in FreeType.
//            _glyphPixelFormat = OF_PIXELS_BGRA;
//        }
//        else if (FT_RENDER_MODE_LCD   == FT_LOAD_TARGET_MODE(_ftLoadFlags)
//                 || FT_RENDER_MODE_LCD_V == FT_LOAD_TARGET_MODE(_ftLoadFlags)
//                 || FT_RENDER_MODE_LCD   == _ftRenderMode
//                 || FT_RENDER_MODE_LCD_V == _ftRenderMode)
//        {
//            // Allocate three layers for subpixel rendering.
//            _glyphPixelFormat = OF_PIXELS_RGB;
//        }
//        else
//        {
//            // Allocate a single grayscale plane.
//            _glyphPixelFormat = OF_PIXELS_GRAY;
//        }
//
//        _hres = settings.hres();
//        _horizontalDPI = settings.horizontalDPI();
//        _verticalDPI = settings.verticalDPI();
//
//        // Create a standard transform matrix, using hres for better hinting.
//        // In this case, we stretch the font in the horizontal direction
//        // and then draw it at the original width for better subpixel hinting.
//        _transformMatrix = {
//            static_cast<FT_Fixed>((1.0 / _hres) * 0x10000L),
//            static_cast<FT_Fixed>((0.0        ) * 0x10000L),
//            static_cast<FT_Fixed>((0.0        ) * 0x10000L),
//            static_cast<FT_Fixed>((1.0        ) * 0x10000L)
//        };
//    }
//    else
//    {
//        ofLogFatalError("FTFont::FTFont") << "Unable to load font face for font: " << settings.font();
//    }

}


bool FTFont::isScalable() const
{
    return _isScalable;
}


bool FTFont::hasFixedSizes() const
{
    return _hasFixedSizes;
}


bool FTFont::isFixedWidth() const
{
    return _isFixedWidth;
}


bool FTFont::isSFNT() const
{
    return _isSFNT;
}


bool FTFont::hasHorizontalGlyphMetrics() const
{
    return _hasHorizontalGlyphMetrics;
}


bool FTFont::hasVerticalGlyphMetrics() const
{
    return _hasVerticalGlyphMetrics;
}


bool FTFont::hasKerning() const
{
    return _hasKerning;
}


bool FTFont::hasMultipleMasters() const
{
    return _hasMultipleMasters;
}


bool FTFont::hasGlyphNames() const
{
    return _hasGlyphNames;
}


bool FTFont::isCIDKeyed() const
{
    return _isCIDKeyed;
}


bool FTFont::isTricky() const
{
    return _isTricky;
}


bool FTFont::hasColorBitmaps() const
{
    return _hasColorBitmaps;
}


std::string FTFont::postscriptName() const
{
    return _postscriptName;
}


std::string FTFont::familyName() const
{
    return _familyName;
}


std::string FTFont::styleName() const
{
    return _styleName;
}


int FTFont::maxAdvanceWidth() const
{
    return _maxAdvanceWidth;
}


int FTFont::maxAdvanceHeight() const
{
    return _maxAdvanceHeight;
}


int FTFont::underlinePosition() const
{
    return _underlinePosition;
}


int FTFont::underlineThickness() const
{
    return _underlineThickness;
}


int FTFont::descender() const
{
    return _descender;
}


int FTFont::ascender() const
{
    return _ascender;
}


int FTFont::height() const
{
    return _height;
}


int FTFont::unitsPerEm() const
{
    return _unitsPerEm;
}


std::size_t FTFont::numGlyphsInFont() const
{
    return _numGlyphsInFont;
}


ofRectangle FTFont::boundingBox() const
{
    return _boundingBox;
}


//const FTFontCache& FTFont::parent() const
//{
//    return _parent;
//}
//

//const FTFontGlyph* FTFont::getGlyphByCodePoint(char32_t codePoint) const
//{
//    return nullptr; //getGlyphByIndex(_parent.getGlyphIndexForCodePoint(*this, codePoint));
//}
//
//
//const FTFontGlyph* FTFont::getGlyphByIndex(FT_UInt glyphIndex) const
//{
//    // Create an iterator to look inside of our cache map to see if we have it.
//    auto iter = _glyphIndexToGlyphCache.find(glyphIndex);
//
//    // See if we have cached it already.
//    if (iter != _glyphIndexToGlyphCache.end())
//    {
//        return iter->second;
//    }
//    else
//    {
//        // Make a pointer to fill as needed.
//        // We don't use std::make_unique because the constructor is protected.
//        auto glyph = std::unique_ptr<FTFontGlyph>(new FTFontGlyph(*this,
//                                                                  glyphIndex));
//
//
//        // Get the raw pointer.
//        FTFontGlyph* pGlyph = glyph.get();
//        _glyphCache.push_back(std::move(glyph));
//        _glyphIndexToGlyphCache[glyphIndex] = pGlyph;
//        return pGlyph;
//    }
//}




//struct PositionedGlyph
//{
//    hb_glyph_info_t info;
//    hb_glyph_position_t position;
//};
//
//void FTFont::loadGlyphs(const std::string& text,
//                        const std::string& language,
//                        const hb_direction_t direction,
//                        const hb_script_t script)
//{
//    if (!_hbFont)
//    {
//        ofLogError("FTFont::loadGlyphs") << "This font is not loaded.";
//        return false;
//    }
//
//    // Create the Harfbuzz (HB) buffer.
//    hb_buffer_t* hbBuffer = hb_buffer_create();
//
//    // Set HB buffer direction.
//    hb_buffer_set_direction(hbBuffer, direction);
//
//    // Set HB buffer script.
//    hb_buffer_set_script(hbBuffer, script);
//
//    // Set HB buffer language
//    hb_buffer_set_language(hbBuffer,
//                           hb_language_from_string(language.data(),
//                                                   language.length()));
//
//    // Add the text to a HB buffer.
//    hb_buffer_add_utf8(hbBuffer,
//                       text.data(), // text
//                       text.length(), // text length
//                       0, // item offset
//                       text.length()); // item_length
//
//    // Shape the text.
//    hb_shape(_hbFont,  // font
//             hbBuffer, // buffer
//             nullptr,  // hb_feature_t array
//             0); // num features
//
//
//    // The final number of glyphs after shaping.
//    unsigned int glyphCount = 0;
//
//    hb_glyph_info_t* glyphInfo = hb_buffer_get_glyph_infos(hbBuffer,
//                                                           &glyphCount);
//
//
//    std::cout << text << std::endl;
//    std::cout << "glyph count = " << glyphCount << std::endl;
//
//    // If needed, get the actual glyph positions for layout.
//    hb_glyph_position_t* glyphPositions  = hb_buffer_get_glyph_positions(hbBuffer,
//                                                                         &glyphCount);
//
//    //FT_Error error;
//
//
//    // disable auto texture upload
////    _atlas.setUseTexture(false);
//
//    for (unsigned int i = 0; i < glyphCount; ++i)
//    {
//        cout << "IN HERE" << endl;
//
//        FTFontGlyph* glyph = cacheGlyph(glyphInfo[i].codepoint);
//
//        if (glyph != nullptr)
//        {
//
//            if (glyph->_pixels.getWidth() > 0)
//            {
//                cout << glyph->_pixels.getWidth() << " / " << glyph->_pixels.getHeight() <<  " : " <<glyph->_pixels.getPixelFormat() << endl;
//
//                cout << "Xxx" << endl;
//                ofSaveImage(glyph->_pixels, ofToString(i) + ".png");
//            }
//
//            ofRectangle region = _currentAtlas->pack(glyph->_pixels);
//
//            if (region.isEmpty())
//            {
//                ofLogError("FTFont::load") << "Unable to add glyph to the pixel map, failing.";
//                ofLogError("FTFont::load") << "In the future, this should be handled more intelligently.";
//                //            return result;
//            }
//        }
//        else
//        {
//            ofLogError("FTFont::load") << "Invalid glyph.";
//        }
//    }
//
////    _atlas.setUseTexture(true);
////    _atlas.update(); // upload the pixels to the texture
//
//    // Reset the HB buffer data
//    hb_buffer_reset(hbBuffer);
//
//    // Destroy the HB buffer
//    hb_buffer_destroy(hbBuffer);
//}




} } // namespace ofx::Text

