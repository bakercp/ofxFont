//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include <ft2build.h>
#include FT_FREETYPE_H
#include "ofJson.h"


namespace ofx {
namespace Text {


/// \brief FreeType 2 Glyph loading and rendering settings.
///
/// These settings are used when calling FT_Load_Glyph and FT_Render_Glyph. They
/// are interpreted according to the FT_Face that is being rendered.
class FTGlyphSettings
{
public:
    /// \brief Create default FTGlyphSettings for antialiased glyphs.
    FTGlyphSettings();

    /// Create FTGlyphSettings with the given parameters.
    ///
    /// The \p antialiased parameter is a shortcut for automatically chosing an
    /// appropriate combination of FreeType 2 load and render settings.
    ///
    /// \param antialiased Set to true to render an anti-aliased font.
    FTGlyphSettings(bool antialiased);

    /// Create FTGlyphSettings with the given parameters.
    ///
    /// \param loadFlags Load flags describes special settings used when loading
    ///     glyphs. Users are encouraged to use the default FT_LOAD_DEFAULT
    ///     along with a FT_LOAD_TARGET_* such as FT_LOAD_TARGET_NORMAL.
    ///     Please refer to the FreeType 2 documentation.
    /// \param renderMode Render mode describes the specific type of scanline
    ///     conversion performed on the font's internal vector outlines.
    ///     Usually this is ignored if set to FT_RENDER_MODE_MAX and render
    ///     settings are taken from the load flags. This should only be used
    ///     if the render mode is different than the render mode specified by
    ///     the load mode. If FT_LOAD_RENDER is not one of load flags and no
    ///     valid FT_RENDER_MODE_* is specified, the bitmaps will not be
    ///     rendered from the vector outlines and confusion may arise. Render
    ///     modes can be set to any of the following values defined by
    ///     FreeType 2:
    ///         - FT_RENDER_MODE_NORMAL
    ///             is the default render mode; it corresponds to 8-bit
    ///             anti-aliased bitmaps.
    ///         - FT_RENDER_MODE_MONO
    ///             This mode corresponds to 1-bit bitmaps (with 2~levels of
    ///             opacity).
    ///         - FT_RENDER_MODE_LCD
    ///             This mode corresponds to horizontal RGB and BGR sub-pixel
    ///             displays like LCD screens.  It produces 8-bit bitmaps that
    ///             are 3~times the width of the original glyph outline in
    ///             pixels, and which use the FT_PIXEL_MODE_LCD mode.
    ///         - FT_RENDER_MODE_LCD_V
    ///             This mode corresponds to vertical RGB and BGR sub-pixel
    ///             displays (like PDA screens, rotated LCD displays, etc.).
    ///         - Other modes are available.  Please refer to the FreeType 2
    ///             documentation.
    FTGlyphSettings(FT_Int32 loadFlags, FT_Render_Mode renderMode);

    /// \brief Destroy the FTGlyphSettings.
    ~FTGlyphSettings();

    /// \brief Get the load flags.
    ///
    /// If the render mode is set to AUTO_LOAD_FLAGS or
    /// AUTO_LOAD_FLAGS_NO_ANTIALIAS, then the exact flags will be interpreted
    /// upon loading.
    ///
    /// \returns the load flags.
    FT_Int32 loadFlags() const;

    /// \brief Get the render mode.
    ///
    /// The render mode describes how face contours are rasterized.
    /// This mode does not affect bitmaps already embedded in a font.
    ///
    /// \returns the render mode.
    FT_Render_Mode renderMode() const;

    enum
    {
        /// \brief Determine load flags automatically.
        AUTO_LOAD_FLAGS = -1,

        /// \brief Determine load flags automatically, without anti-alias.
        AUTO_LOAD_FLAGS_NO_ANTIALIAS = -2
    };

private:
    /// \brief The glyph load flags used when calling FT_Load_Glyph.
    FT_Int32 _loadFlags = 0;

    /// \brief The render mode used when calling FT_Render_Glyph.
    FT_Render_Mode _renderMode = FT_RENDER_MODE_NORMAL;

};
    

} } // namespace ofx::Text

