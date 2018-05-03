//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
// Copyright (c) 2014-2017 Devon Govett <https://github.com/devongovett/font-manager>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include <vector>
#include "ofx/Text/FontDescriptor.h"


namespace ofx {
namespace Text {


/// \brief A Font Manager.
///
/// The FontManager consists of a set of utilities for finding, listing and
/// matching the required fonts on a given system.
class FontManager
{
public:
    /// \brief Get all of the fonts avaialable on the system.
    ///
    /// These results are typically cached for speed, so subsequent calls will
    /// reflect the state when it was first called. This means fonts that are
    /// installed by the system after calling getAvailableFonts() may not be
    /// discovered across all platforms.
    ///
    /// \returns an vector of all font descriptors available on the system.
    static std::vector<FontDescriptor> getAvailableFonts();

    /// \brief Find all fonts matching the provided FontDescriptor.
    ///
    /// If no matching fonts are found, an empty vector is returned.
    ///
    /// \returns an array of font descriptors matching a query font descriptor.
    static std::vector<FontDescriptor> findFonts(const FontDescriptor& descriptor);

    /// \brief Find a font that best matches the given descriptor.
    ///
    /// This method always returns a valid path, so sometimes the output will
    /// not exactly match the input font descriptor if all input parameters
    /// could not be met.
    ///
    /// \returns a FontDescriptor that best matches the given descriptor.
    static FontDescriptor findFont(const FontDescriptor& descriptor);

    /// \brief Find a similar font that covers the required Unicode codepoints.
    ///
    /// This method will substitute the font with the given postscript name for
    /// another that contains the required characters. If a font matching
    /// postscriptName is not found, a font containing the given characters is
    /// still returned. If a font matching postscriptName is found, its
    /// characteristics (bold, italic, etc.) are used to find a suitable
    /// replacement. If the font already contains the characters in text, it is
    /// not replaced and the font descriptor for the original named font is
    /// returned.
    ///
    /// Passing an empty postscriptName should return a default font that
    /// contains the codepoints, if one is available.
    ///
    /// \param postscriptName The postscript name of the font to be checked.
    /// \param utf8Text UTF8-encoded text with the required Unicode codepoints.
    /// \returns a FontDescriptor that covers the required Unicode codepoints.
    static FontDescriptor substituteFont(const std::string& postscriptName,
                                         const std::string& utf8Text);

};


} } // namespace ofx::Text
