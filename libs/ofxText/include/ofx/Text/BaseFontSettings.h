//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>


namespace ofx {
namespace Text {


/// \brief A base class representing font settings.
class BaseFontSettings
{
public:
    /// \brief Create font settings with the given parameters.
    /// \param font The name of the font.
    /// \param size The size of the font.
    BaseFontSettings(const std::string& font,
                     float size = DEFAULT_SIZE);

    /// \brief Destroy the Base font settings.
    virtual ~BaseFontSettings();

    /// \brief Get the font name.
    /// \returns the name or filename.
    std::string font() const;

    /// \brief Get the font size.
    /// \returns the size.
    float size() const;

    enum
    {
        /// \brief The default font size.
        DEFAULT_SIZE = 48
    };

protected:
    /// \brief The font name.
    std::string  _font;

    /// \brief The font size.
    float _size;

};


} } // namespace ofx::Text
