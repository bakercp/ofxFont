////
//// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
////
//// SPDX-License-Identifier:    MIT
////
//
//
//#pragma once
//
//
//#include <ft2build.h>
//#include FT_FREETYPE_H
//#include "ofx/Text/BaseFontGlyph.h"
//#include "ofPath.h"
//
//
//namespace ofx {
//namespace Text {
//
//
//class FTFont;
//
//
///// \brief A representation of a FreeType glyph.
//class FTFontGlyph: public BaseFontGlyph
//{
//public:
//    /// \brief A typedef for contour data.
//    typedef ofPath Contour;
//
//    /// \brief A typedef for point data.
//    typedef glm::vec2 Point;
//
//    /// \brief A structure for a texture address.
//    struct MappedPixels
//    {
//        /// \brief Texture atlas data.
//        ofTexture* texture = nullptr;
//
//        /// \brief Normalized texture coordinate t0.
//        ///
//        /// For OF_ORIENTATION_DEFAULT, this is top-left corner of target
//        /// texture.
//        Point t0;
//
//        /// \brief Normalized texture coordinate t1.
//        /// For OF_ORIENTATION_DEFAULT, this is bottom-right corner of target
//        /// texture.
//        Point t1;
//
//        /// \brief The orientation of the target texture.
//        ///
//        /// This affects the way that the t0 and t1 coordinates are interpreted.
//        ofOrientation orientation = OF_ORIENTATION_DEFAULT;
//    };
//
//    /// \brief Destroy the FTFontGlyph.
//    virtual ~FTFontGlyph();
//
//    /// \returns a const pointer to the parent font or nullptr if none.
//    const FTFont& parent() const;
//
//    /// \brief Return the glyph index relative to the parent FTFace.
//    FT_UInt glyphIndex() const;
//
//    /// \returns true iff this glyph contains contour data.
//    bool hasContour() const;
//
//    /// \returns true iff this glyph contains texture data.
//    bool hasTexture() const;
//
//    /// \returns a reference to the contour data.
//    Contour& contour();
//
//    /// \returns a const reference to the contour data.
//    const Contour& contour() const;
//
////    /// \returns a reference to the texture data.
////    Texture& texture();
////
////    /// \returns a const reference to the texture data.
////    const Texture& texture() const;
////
////    /// \brief Get a copy of the raw glyph pixels.
////    ///
////    /// Glyph pixels are cached by the FTFontCache.
////    ///
////    /// \returns a copy of the raw glyph pixels.
////    Pixels pixels() const;
//
//    /// \returns a string with some debugging information.
//    std::string toString() const
//    {
//        std::stringstream ss;
//        ss << " codePoint? " << codePoint() << std::endl;
//        ss << "      name? " << name() << std::endl;
//        ss << "    height? " << height() << std::endl;
//        ss << "     width? " << width() << std::endl;
//        ss << "glyphIndex? " << glyphIndex() << std::endl;
//        ss << "hasContour? " << hasContour() << std::endl;
//        ss << "hasTexture? " << hasTexture() << std::endl;
//        return ss.str();
//    }
//
////protected:
//    /// \brief Construct an empty FTFontGlyph.
//    ///
//    /// Internal variables must be set by FTFont.
//    FTFontGlyph(const FTFont& parent, FT_UInt glyphIndex);
//
//    /// \brief Create a contour for the given FTFontGlyph.
//    /// \param glyph The glyph slot to generate.
//    /// \returns The generated contour.
//    static FTFontGlyph::Contour createContour(const FT_GlyphSlot& glyph);
//
//    /// \brief The parent font.
//    const FTFont& _parent;
//
//    /// \brief The internal glyph index as represented by the face.
//    /// \warning This is not the same as a Unicode code point.
//    FT_UInt _glyphIndex = 0;
//
//    /// \brief The contour data, if available.
//    Contour _contour;
//
////    /// \brief The texture data, if available.
////    Texture _texture;
//
//    /// \brief The raw pixel data.
//    // Pixels _pixels;
//
//    friend class FTFont;
//
//};
//
//
//} } // namespace ofx::Text

