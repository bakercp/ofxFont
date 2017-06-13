//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
// Copyright (c) 2014-2017 Devon Govett <https://github.com/devongovett/font-manager>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include <vector>
#include "ofConstants.h"
#include "ofJson.h"


namespace ofx {
namespace Text {


enum FontWeight
{
    FontWeightUndefined   = 0,
    FontWeightThin        = 100,
    FontWeightUltraLight  = 200,
    FontWeightLight       = 300,
    FontWeightNormal      = 400,
    FontWeightMedium      = 500,
    FontWeightSemiBold    = 600,
    FontWeightBold        = 700,
    FontWeightUltraBold   = 800,
    FontWeightHeavy       = 900
};

enum FontWidth
{
    FontWidthUndefined      = 0,
    FontWidthUltraCondensed = 1,
    FontWidthExtraCondensed = 2,
    FontWidthCondensed      = 3,
    FontWidthSemiCondensed  = 4,
    FontWidthNormal         = 5,
    FontWidthSemiExpanded   = 6,
    FontWidthExpanded       = 7,
    FontWidthExtraExpanded  = 8,
    FontWidthUltraExpanded  = 9
};



/// When querying fonts, any of the items can be filled.
///Font descriptors are normal JavaScript objects that describe characteristics of a font. They are passed to the findFonts and findFont methods and returned by all of the methods. Any combination of the fields documented below can be used to find fonts, but all methods return full font descriptors.


struct FontDescriptor
{
    /// \brief The path to the font file in the filesystem.
    ///
    /// This is not applicable for queries, only for results.
    std::string path;

    /// \brief The PostScript name of the font (e.g 'Arial-BoldMT').
    ///
    /// This uniquely identities a font in most cases.
    std::string postscriptName;

    /// \brief The font family name (e.g 'Arial').
    std::string family;

    /// \brief The font style name (e.g. 'Bold')
    std::string style;

    /// The font weight (e.g. 400 for normal weight).
    ///
    /// Should be a multiple of 100, between 100 and 900.
    FontWeight weight = FontWeightNormal;

    /// \brief The font width (e.g. 5 for normal width).
    ///
    /// Should be an integer between 1 and 9. See below for width documentation.
    FontWidth width = FontWidthNormal;

    /// \brief Whether the font is italic or not.
    bool italic = false;

    /// \brief Whether the font is monospace or not.
    bool monospace = false;

    ofJson toJSON() const
    {
        ofJson json;
        json["path"] = path;
        json["postscript_name"] = postscriptName;
        json["family"] = family;
        json["style"] = style;
        json["weight"] = weight;
        json["width"] = width;
        json["italic"] = italic;
        json["monospace"] = monospace;
        return json;
    }
};


/// \brief A Font Manager
class FontManager
{
public:
    /// \returns an array of all font descriptors available on the system.
    static std::vector<FontDescriptor> getAvailableFonts();

    /// \returns an array of font descriptors matching a query font descriptor.
    ///          The returned array may be empty if no fonts match the font descriptor.
    static std::vector<FontDescriptor> findFonts(const FontDescriptor& descriptor);


    /// \returns a single font descriptors matching a query font descriptors as well as possible.
    // This method always returns a result (never null), so sometimes the output will not exactly
    // match the input font descriptor if not all input parameters could be met.
    static FontDescriptor findFont(const FontDescriptor& descriptor);

//    Substitutes the font with the given postscriptName with another font that contains the characters in text. If a font matching postscriptName is not found, a font containing the given characters is still returned. If a font matching postscriptName is found, its characteristics (bold, italic, etc.) are used to find a suitable replacement. If the font already contains the characters in text, it is not replaced and the font descriptor for the original font is returned.


    static FontDescriptor substituteFont(const std::string& postscriptName,
                                         const std::string& utf8Text);

};


} } // namespace ofx::Text
