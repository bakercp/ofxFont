//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Text/FTSizeDescriptor.h"


namespace ofx {
namespace Text {


FTSizeDescriptor::FTSizeDescriptor():
    FTSizeDescriptor(DEFAULT_SIZE, DEFAULT_RESOLUTION_DPI)
{
}
    
    
FTSizeDescriptor::FTSizeDescriptor(float size, FT_UInt resolution):
    FTSizeDescriptor(size * POINTS_TO_FRACTIONAL_POINTS,
                     size * POINTS_TO_FRACTIONAL_POINTS,
                     resolution,
                     resolution,
                     DEFAULT_HORIZONTAL_RESOLUTION_SCALER)
{
}


FTSizeDescriptor::FTSizeDescriptor(FT_F26Dot6 charWidth,
                   FT_F26Dot6 charHeight,
                   FT_UInt horzResolution,
                   FT_UInt vertResolution,
                   FT_UInt horzResolutionScaler):
    _charWidth(charWidth),
    _charHeight(charHeight),
    _horzResolution(horzResolution),
    _vertResolution(vertResolution),
    _horzResolutionScaler(horzResolutionScaler)
{
    // Normalize according to FT_Set_Char_Size.
    if (!_charWidth)
        _charWidth = _charHeight;
    else if (!_charHeight)
        _charHeight = _charWidth;

    if (!_horzResolution)
        _horzResolution = _vertResolution;
    else if (!_vertResolution)
        _vertResolution = _horzResolution;

    if (_charWidth < 1 * POINTS_TO_FRACTIONAL_POINTS)
        _charWidth = 1 * POINTS_TO_FRACTIONAL_POINTS;
    if (_charHeight < 1 * POINTS_TO_FRACTIONAL_POINTS)
        _charHeight = 1 * POINTS_TO_FRACTIONAL_POINTS;

    if (!_horzResolution)
        _horzResolution = _vertResolution = FRACTIONAL_POINTS_RESOLUTION_DPI;

    if (!_horzResolutionScaler)
        _horzResolutionScaler = DEFAULT_HORIZONTAL_RESOLUTION_SCALER;
}


float FTSizeDescriptor::size() const
{
    return _charHeight / float(POINTS_TO_FRACTIONAL_POINTS);
}


FT_F26Dot6 FTSizeDescriptor::charWidth() const
{
    return _charWidth;
}


FT_F26Dot6 FTSizeDescriptor::charHeight() const
{
    return _charHeight;
}


FT_UInt FTSizeDescriptor::horzResolution() const
{
    return _horzResolution;
}


FT_UInt FTSizeDescriptor::vertResolution() const
{
    return _vertResolution;
}


FT_UInt FTSizeDescriptor::horzResolutionScaler() const
{
    return _horzResolutionScaler;
}


bool FTSizeDescriptor::operator < (const FTSizeDescriptor& other) const
{
    if (_charWidth != other._charWidth)
        return _charWidth < other._charWidth;
    else if (_charHeight != other._charHeight)
        return _charHeight < other._charHeight;
    else if (_horzResolution != other._horzResolution)
        return _horzResolution < other._horzResolution;
    else if (_vertResolution != other._vertResolution)
        return _vertResolution < other._vertResolution;
    return _horzResolutionScaler < other._horzResolutionScaler;
}


bool FTSizeDescriptor::operator == (const FTSizeDescriptor& other) const
{
    return _charWidth == other._charWidth
        && _charHeight == other._charHeight
        && _horzResolution == other._horzResolution
        && _vertResolution == other._vertResolution
        && _horzResolutionScaler == other._horzResolutionScaler;
}


bool FTSizeDescriptor::operator != (const FTSizeDescriptor& other) const
{
    return !(*this == other);
}


ofJson FTSizeDescriptor::toJSON() const
{
    ofJson json;
    json["char_width"] = _charWidth;
    json["char_height"] = _charHeight;
    json["horz_resolution"] = _horzResolution;
    json["vert_resolution"] = _vertResolution;
    json["horz_resolution_scaler"] = _horzResolutionScaler;
    return json;
}


} } // namespace ofx::Text
