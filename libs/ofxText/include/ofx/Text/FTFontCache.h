//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include <unordered_map>
#include <vector>
#include <ft2build.h>
#include FT_LCD_FILTER_H
#include "ofx/Text/FTFontSettings.h"
#include "ofx/Text/FTFaceDescriptor.h"
#include "ofx/Text/FTSizeDescriptor.h"


namespace ofx {
namespace Text {


//class FTFaceCache
//{
//public:
//    std::vector<std::shared_ptr<FT_Face>> _faces;
//    ofBuffer _buffer;
//};



/// \brief A shared cache for FTFont objects.
class FTFontCache
{
public:
    /// \brief The settings required for an FTFontCache.
    struct Settings
    {
        /// \brief Maximum number font files loaded into memory.
        std::size_t maxBufferedFonts = DEFAULT_MAX_BUFFERED_FONTS;

        /// \brief The maximum number of bytes permitted for open font files.
        ///
        /// This is the read-only memory buffered when loading multiple FT_Face files.
        std::size_t maxBufferedBytes = DEFAULT_MAX_BUFFERED_BYTES;
        
        /// \brief The lcdFilter lcd filter to use.
        /// \sa https://www.freetype.org/freetype2/docs/reference/ft2-lcd_filtering.html
        FT_LcdFilter lcdFilter = FT_LCD_FILTER_DEFAULT;

        enum
        {
            /// \brief The maximum buffered fonts.
            DEFAULT_MAX_BUFFERED_FONTS = 10,

            /// \brief The maximum number of buffered bytes.
            DEFAULT_MAX_BUFFERED_BYTES = 16 * 1000000,

            /// \brief The default maximum number of cached faces per font.

        };
    };

    /// \brief An instance of the FTFontCache.
    /// \returns A reference to the singleton.
    static FTFontCache& instance();

    /// \brief Set up the cache with the given settings.
    ///
    /// The cache will be cleared when setup() is called.
    ///
    /// \param settings The settings to apply.
    void setup(const Settings& settings);

    /// \returns the current cache settings.
    Settings settings() const;

    /// \brief Clear all caches.
    void clear();

    /// \returns An FT_Library pointer to the initialized Freetype Library.
    FT_Library ftLibrary();

private:
    FTFontCache();
    FTFontCache(const FTFontCache&) = delete;
    FTFontCache& operator = (const FTFontCache&) = delete;

    /// \brief Destroys the FTFontCache.
    ~FTFontCache();


    /// \brief Get an FT_Face with an active size.
    ///
    /// This function returns an FT_Face with an active FT_Size specified by
    /// the given FTSizeDescriptor. The returned FT_Face object is always
    /// owned by the cache. Users should not try to free the FT_Face.
    ///
    /// The user should not modify the returned FT_Face object, as it may be
    /// shared with other instances. For example, the user should never change
    /// the face's transformation matrix (e.g. the user should never call
    /// FT_Set_Transform on the face). If a glyph should be transformed, this
    /// should occur after the glyph has been loaded.
    ///
    /// This should return a valid FT_Face. In the event that an invalid font is
    /// requested and no fallback option is available, this will log a fatal
    /// error and return a nullptr.
    ///
    /// \param faceDescriptor The FTFaceDescriptor to load.
    /// \param sizeDescriptor The FTSizeDescriptor to load.
    /// \returns an FT_Face that is owned by the cache or nullptr on failure.
    std::shared_ptr<struct FT_FaceRec_> getFace(const FTFaceDescriptor& faceDescriptor,
                                                const FTSizeDescriptor& sizeDescriptor) const;

    FTFaceDescriptor getFaceDescriptorForFontDescriptor(const FontDescriptor& fontDescriptor);
    
    /// \brief Get a pointer to the cached memory for a FTFaceDescriptor.
    ///
    /// Fonts that share the same fontPath will share the same underlying
    /// memory block.
    ///
    /// \param fontPath The path of the font to get.
    /// \returns a pointer to the cached memory for the requested font path, or nullptr on failure.
    std::shared_ptr<const ofBuffer> getBufferForFontPath(const std::filesystem::path& fontPath) const;

    /// \brief Get and cache a list of font descriptors for a given font path.
    ///
    /// These font descriptors are used to find the correct freetype face index
    /// for loading fonts when the freetype face index is not already known.
    ///
    /// These values are cached. Subsequent calls with the same fontPath will
    /// return identical results until th FTFontCache is cleared.
    ///
    /// The index of the std::vector<FontDescriptor> corresponds to the freetype
    /// face index used when loading the FT_Face.
    ///
    /// \param fontPath The path of the font to get.
    /// \returns a collection of FontDescriptors for the given path.
    std::vector<FontDescriptor> getFontDescriptorsForPath(const std::filesystem::path& fontPath) const;

    /// \brief Get the freetype face index for the given FontDescriptor.
    ///
    /// The FontDescriptor must have a valid path to work correctly. This method
    /// will call getFontDescriptorsForPath() internally to get the valid
    /// indices.
    ///
    /// A returned value of < 0 means there was an error.
    ///
    /// A returned value of >= 0 is a succues.
    ///
    /// \param descriptor The font descriptor to to query.
    /// \returns a freetype face index >= 0 for success, or < 0 for failure.
    int64_t getFaceIndexForFontDescriptor(const FontDescriptor& descriptor) const;
    
    /// \brief Cached faces.
    ///
    /// FT_Faces are cached here and associated with a specific FTFaceDescriptor.
    ///
    /// Each FT_Face is loaded from memory mapped and cached in the
    /// _fontFileBuffers. Each FT_Face represents an FT_Face that has
    /// has been sized with FT_Set_Char_Size upon creation.
    mutable std::map<FTFaceDescriptor, std::shared_ptr<struct FT_FaceRec_>> _faceIdCache;

    /// \brief A collection of memory mapped font file buffers.
    mutable std::unordered_map<std::string, std::shared_ptr<const ofBuffer>> _fontBufferCache;

    /// \brief Cache mapping font paths to font descriptors.
    ///
    /// This is used for mapping font paths to freetype face indices.
    ///
    /// The index of the std::vector<FontDescriptor> corresponds to the freetype
    /// face index used when loading the FT_Face.
    mutable std::unordered_map<std::string, std::vector<FontDescriptor>> _fontDescriptorCache;

    /// \brief The Freetype library.
    FT_Library _library;

    /// \brief Cache settings;
    Settings _settings;

    friend FTFontSettings;
    
};


} } // namespace ofx::Text
