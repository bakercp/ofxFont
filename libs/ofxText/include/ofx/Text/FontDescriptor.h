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


/// \brief An enumeration describing a font's weight.
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


/// \brief An enumeration describing a font's width.
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


/// \brief A FontDescriptor can be used to describing and matching fonts.
///
/// This class represents a minimal set of font properties used for locating
/// installed system fonts or finding substitutes with similar properties.
///
/// This class does not represent rendering information such as font size or
/// resolution.
class FontDescriptor
{
public:
    /// \brief The path to the font file in the filesystem.
    ///
    /// \note This is not applicable for queries, only for results.
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

    /// \brief Convert the object to JSON.
    /// \returns the JSON representation of the object.
    ofJson toJSON() const;

    /// \brief Convert JSON to the a FontDescriptor.
    /// \param json the JSON representation of the object.
    void fromJSON(const ofJson& json);

    /// \brief A comparison operator used with std::map and other collections.
    /// \param other The other object to compare.
    /// \returns true iff this key is less than the other key.
    bool operator < (const FontDescriptor& other) const;

    /// \brief Check equality between two objects.
    /// \param other The other object to compare.
    /// \returns true iff this object is equal to the other.
    bool operator == (const FontDescriptor& other) const;

    /// \brief Check equality between two objects.
    /// \param other The other object to compare.
    /// \returns true iff this object is not equal to the other.
    bool operator != (const FontDescriptor& other) const;

};


} } // namespace ofx::Text
