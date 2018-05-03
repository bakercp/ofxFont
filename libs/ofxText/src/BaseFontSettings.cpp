//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Text/BaseFontSettings.h"


namespace ofx {
namespace Text {


BaseFontSettings::BaseFontSettings(const std::string& font,
                                   float size):
    _font(font),
    _size(size)
{
}


BaseFontSettings::~BaseFontSettings()
{
}


std::string BaseFontSettings::font() const
{
    return _font;
}


float BaseFontSettings::size() const
{
    return _size;
}


} } // namespace ofx::Text
