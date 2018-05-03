//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <ft2build.h>
#include FT_FREETYPE_H
#include "ofJson.h"


namespace ofx {
namespace Text {


/// \brief A class used to cache face sizes.
///
/// These settings correspond to the settings require to activate a size within
/// an FT_Face using FT_Set_Char_Size.
class FTSizeDescriptor
{
public:
    /// \brief Create a FTSizeDescriptor from the given parameters.
    /// \param size The point size.
    /// \param resolution The horizontal and vertical resolution in pixels per inch.
    FTSizeDescriptor(float size, FT_UInt resolution = DEFAULT_RESOLUTION_DPI);

    /// \brief Create a FTSizeDescriptor from the given parameters.
    /// \param charWidth The nominal width, in 26.6 fractional points.
    /// \param charHeight The nominal height, in 26.6 fractional points.
    /// \param horzResolution The horizontal resolution in dpi.
    /// \param vertResolution The vertical resolution in dpi.
    /// \param horzResolutionScaler The horizontal resolution scaler.
    ///        Must be greater than 0, or the default will be used.
    FTSizeDescriptor(FT_F26Dot6 charWidth,
                     FT_F26Dot6 charHeight,
                     FT_UInt horzResolution,
                     FT_UInt vertResolution,
                     FT_UInt horzResolutionScaler = DEFAULT_HORIZONTAL_RESOLUTION_SCALER);

    /// \returns the point size.
    float size() const;

    /// \returns the nominal width, in 26.6 fractional points (72pt = 1 inch).
    FT_F26Dot6 charWidth() const;

    /// \returns the nominal height, in 26.6 fractional points (72pt = 1 inch).
    FT_F26Dot6 charHeight() const;

    /// \returns the horizontal resolution in pixels per inch.
    FT_UInt horzResolution() const;

    /// \returns the vertical resolution in pixels per inch.
    FT_UInt vertResolution() const;

    /// \returns the horizontal resolution scaler.
    FT_UInt horzResolutionScaler() const;

    /// \brief A comparison operator used with std::map and other collections.
    /// \param other The other object to compare.
    /// \returns true iff this key is less than the other key.
    bool operator < (const FTSizeDescriptor& other) const;

    /// \brief Check equality between two objects.
    /// \param other The other object to compare.
    /// \returns true iff this object is equal to the other.
    bool operator == (const FTSizeDescriptor& other) const;

    /// \brief Check equality between two objects.
    /// \param other The other object to compare.
    /// \returns true iff this object is not equal to the other.
    bool operator != (const FTSizeDescriptor& other) const;

    /// \returns the json representation of the FTFontId.
    ofJson toJSON() const;

    enum
    {
        // \brief 26.6 fractional scaler.
        // Used to convert 26.6 fixed point fractional points to points.
        POINTS_TO_FRACTIONAL_POINTS = 64,

        /// \brief The resolution in DPI used for 26.6 fractional points.
        FRACTIONAL_POINTS_RESOLUTION_DPI = 72,

        /// \brief The default resolution.
        DEFAULT_RESOLUTION_DPI = 96,

        /// \brief This will default to OF global DPI in the future.
        DEFAULT_HORIZONTAL_DPI = DEFAULT_RESOLUTION_DPI,

        /// \brief This will default to PF global DPI in the future.
        DEFAULT_VERTICAL_DPI = DEFAULT_RESOLUTION_DPI,

        /// \brief Freetype 2 can benefit from a horizontal resolution
        /// scaler to get better vertical hinting.
        DEFAULT_HORIZONTAL_RESOLUTION_SCALER = 100
        
    };

private:
    /// \brief The nominal width, in 26.6 fractional points (72pt = 1 inch).
    FT_F26Dot6 _charWidth = 0;

    /// \brief The nominal height, in 26.6 fractional points (72pt = 1 inch).
    FT_F26Dot6 _charHeight = 0;

    /// \brief The horizontal resolution in pixels per inch.
    FT_UInt _horzResolution = 0;

    /// \brief The vertical resolution in pixels per inch.
    FT_UInt _vertResolution = 0;

    /// \brief The default horizontal resolution scaler.
    FT_UInt _horzResolutionScaler = DEFAULT_HORIZONTAL_RESOLUTION_SCALER;

};


} } // namespace ofx::Text
