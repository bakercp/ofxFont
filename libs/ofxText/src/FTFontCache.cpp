//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Text/FTFontCache.h"
#include <codecvt>
#include FT_TRUETYPE_TABLES_H
#include FT_TRUETYPE_IDS_H
#include FT_SFNT_NAMES_H

//#ifdef TARGET_LINUX
//#include <fontconfig/fontconfig.h>
//#endif

#include "ofLog.h"
#include "ofx/Text/FontManager.h"


// This section defines FreeType error strings.
#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  { e, s },
#define FT_ERROR_START_LIST     {
#define FT_ERROR_END_LIST       { 0, 0 } };
const struct {
    int          code;
    const char*  message;
} FT_Errors[] =
#include FT_ERRORS_H


namespace ofx {
namespace Text {


std::string FT_ERROR_TO_STRING(int error)
{
    return std::to_string(FT_Errors[error].code) + ": " + FT_Errors[error].message;
}


std::string SfntNameToUTF8(const FT_SfntName& name)
{
    // Copy the string to
    std::u16string u16(reinterpret_cast<char16_t*>(name.string), name.string_len / sizeof(char16_t));

    // Text is in UTF16-big-endian.
    // Loop through each utf16 char and convert to little endian.
    for (auto& c: u16) c = ((c >> 8) & 0x00FF) | ((c << 8) & 0xFF00);

    std::string utf8result;

    try
    {
        utf8::utf16to8(u16.begin(), u16.end(), std::back_inserter(utf8result));
    }
    catch (const utf8::exception& utfcpp_ex)
    {
        ofLogError("SfntNameToUTF8") << utfcpp_ex.what();
    }

    return utf8result;
}


FTFontCache& FTFontCache::instance()
{
    static FTFontCache instance;
    return instance;
}


void FTFontCache::setup(const Settings& settings)
{
    // Clear the cache data.
    clear();

    // Here we attempt to set an LCD filter. If it is not implemented, it will
    // return an error that can be ignored.
    FT_Error error = FT_Library_SetLcdFilter(_library, settings.lcdFilter);

    if (error != 0)
    {
        ofLogWarning("FTFontCache::setup") << "FT_Library_SetLcdFilter: " << FT_ERROR_TO_STRING(error);
    }
}


FTFontCache::Settings FTFontCache::settings() const
{
    return _settings;
}


FTFontCache::FTFontCache()
{
    FT_Error error = FT_Init_FreeType(&_library);

    if (error != 0)
    {
        ofLogError("FTFontCache::FTFontCache") << "FT_Init_FreeType: " << FT_ERROR_TO_STRING(error);
    }

    // Initialize caches with default settings.
    setup(Settings());
}


FTFontCache::~FTFontCache()
{
    // We need to clear the font map before we free everything.
    clear();

    // Release the libary.
    FT_Done_FreeType(_library);
}


void FTFontCache::clear()
{
    _faceIdCache.clear();
    _fontBufferCache.clear();
    _fontDescriptorCache.clear();
}


FT_Library FTFontCache::ftLibrary()
{
    return _library;
}

    
std::shared_ptr<struct FT_FaceRec_> FTFontCache::getFace(const FTFaceDescriptor& faceDescriptor,
                                                         const FTSizeDescriptor& sizeDescriptor) const
{
    auto faceIter = _faceIdCache.find(faceDescriptor);

    if (faceIter == _faceIdCache.end())
    {
        std::shared_ptr<const ofBuffer> pBuffer = getBufferForFontPath(faceDescriptor.path());
        
        if (pBuffer && pBuffer->size() > 0)
        {
            FT_Face _face = nullptr;
            FT_Error error = FT_New_Memory_Face(_library,
                                                reinterpret_cast<const FT_Byte*>(pBuffer->getData()),
                                                pBuffer->size(),
                                                faceDescriptor.faceIndex(),
                                                &_face);
            if (error != 0)
            {
                ofLogError("FTFontCache::getFace") << "Error Loading Face: " << FT_ERROR_TO_STRING(error) << " : " << faceDescriptor.toJSON().dump(4);
                return nullptr;
            }

            // Wrap the FT_Face with a shared pointer to automatically call
            // FT_Done_Face upon destruction.
            auto face = std::shared_ptr<struct FT_FaceRec_>(_face, FT_Done_Face);
            
            auto result = _faceIdCache.insert(std::make_pair(faceDescriptor, face));

            if (result.second)
            {
                faceIter = result.first;
            }
            else
            {
                ofLogError("FTFontCache::getFace") << "Unable to insert or load FT_Face into cache.";
                return nullptr;
            }
        }
        else
        {
            ofLogError("FTFontCache::getFace") << "Buffer empty.";
            return nullptr;
        }
    }
    else
    {
        ofLogVerbose("FTFontCache::getFace") << "Face exists.";
    }

    // Ensure that the size is correct.
    FT_Error error = FT_Set_Char_Size(faceIter->second.get(),
                                      sizeDescriptor.charWidth(),
                                      sizeDescriptor.charHeight(),
                                      sizeDescriptor.horzResolution(),
                                      sizeDescriptor.vertResolution());

    if (error != 0)
    {
        ofLogError("FTFontCache::getFace") << "Error Setting Char Size: " << FT_ERROR_TO_STRING(error) << " : " << faceDescriptor.toJSON().dump(4);
        return nullptr;
    }

    return faceIter->second;
}


FTFaceDescriptor FTFontCache::getFaceDescriptorForFontDescriptor(const FontDescriptor& _fontDescriptor)
{
    FontDescriptor fontDescriptor = _fontDescriptor;
    
    if (!std::filesystem::exists(ofToDataPath(fontDescriptor.path, true)))
    {
        fontDescriptor.path.clear();
        ofLogWarning("FTFontCache::getFaceDescriptorForFontDescriptor") << "Unable to find font: " << _fontDescriptor.path;
    }
        
    fontDescriptor = FontManager::findFont(fontDescriptor);
    
    return FTFaceDescriptor(fontDescriptor.path, getFaceIndexForFontDescriptor(fontDescriptor));
}


std::shared_ptr<const ofBuffer> FTFontCache::getBufferForFontPath(const std::filesystem::path& _fontPath) const
{
    std::string absoluteFontPath = ofToDataPath(_fontPath, true);

    auto bufferIter = _fontBufferCache.find(absoluteFontPath);

    if (bufferIter == _fontBufferCache.end())
    {
        if (std::filesystem::exists(absoluteFontPath) && std::filesystem::is_regular(absoluteFontPath))
        {
            // We didn't have the buffer cached, so load it.
            auto result = _fontBufferCache.insert(std::make_pair(absoluteFontPath, std::make_shared<const ofBuffer>(ofBufferFromFile(absoluteFontPath))));

            if (result.second && result.first->second->size() > 0)
            {
                bufferIter = result.first;
            }
            else
            {
                _fontBufferCache.erase(result.first);
                ofLogError("FTFontCache::getBufferForFontPath") << "Unable to insert or load ofBuffer into cache.";
                return nullptr;
            }
        }
        else
        {
            ofLogError("FTFontCache::getBufferForFontPath") << "Invalid path: " << absoluteFontPath;
            return nullptr;
        }
    }

    return bufferIter->second;
}


std::vector<FontDescriptor> FTFontCache::getFontDescriptorsForPath(const std::filesystem::path& _fontPath) const
{
    std::string absoluteFontPath = ofToDataPath(_fontPath, true);

    auto iter = _fontDescriptorCache.find(absoluteFontPath);

    if (iter != _fontDescriptorCache.end())
    {
        return iter->second;
    }

    std::vector<FontDescriptor> results;

    FT_Face face;
    FT_Error error = 0;

    error = FT_New_Face(_library, absoluteFontPath.data(), -1, &face);

    if (error != 0)
    {
        ofLogError("FTFontCache::findFTFaceIndex") << "FT_New_Face: " << FT_ERROR_TO_STRING(error);
        return results;
    }

    FT_Long numFaces = face->num_faces;

    FT_Done_Face(face);

    for (FT_Long i = 0; i < numFaces; ++i)
    {
        error = FT_New_Face(_library, absoluteFontPath.data(), i, &face);

        if (error != 0)
        {
            ofLogError("FTFontCache::findFTFaceIndex") << "FT_New_Face: " << FT_ERROR_TO_STRING(error);
        }
        else
        {
            FontDescriptor descriptor;
            descriptor.path = absoluteFontPath;

            const char* postscriptName = FT_Get_Postscript_Name(face);
            descriptor.postscriptName = postscriptName ? postscriptName : "";
            descriptor.family = face->family_name ? face->family_name : "";
            descriptor.style = face->style_name ? face->style_name : "";

            // If the font is compatible, we attempt to get the more accurate
            // family and style names. Apparently, FreeType is known to get
            // these wrong sometimes.
            //
            // We also attempt to fill in values for width and weight.
            if (FT_IS_SFNT(face))
            {
                FT_UInt nameCount = FT_Get_Sfnt_Name_Count(face);

                std::string style;
                std::string family;

                for (FT_UInt n = 0; n < nameCount; ++n)
                {
                    FT_SfntName name;

                    if (!FT_Get_Sfnt_Name(face, n, &name))
                    {
                        // Handle en-us only.
                        if (name.platform_id == TT_PLATFORM_MICROSOFT
                            && name.encoding_id == TT_MS_ID_UNICODE_CS
                            && name.language_id == TT_MS_LANGID_ENGLISH_UNITED_STATES)
                        {
                            if (name.name_id == TT_NAME_ID_FONT_FAMILY && family.empty())
                            {
                                family = SfntNameToUTF8(name);
                            }
                            else if (name.name_id == TT_NAME_ID_FONT_SUBFAMILY && style.empty())
                            {
                                style = SfntNameToUTF8(name);
                            }
                            else if (name.name_id == TT_NAME_ID_PREFERRED_FAMILY)
                            {
                                family = SfntNameToUTF8(name);
                            }
                            else if (name.name_id == TT_NAME_ID_PREFERRED_SUBFAMILY)
                            {
                                style = SfntNameToUTF8(name);
                            }
                        }
                    }
                }

                if (!family.empty() && descriptor.family != family)
                {
                    descriptor.family = family;
                }

                if (!style.empty() && descriptor.style != style)
                {
                    descriptor.style = style;
                }

                TT_OS2* os2Header = (TT_OS2*)FT_Get_Sfnt_Table(face, FT_SFNT_OS2);

                if (os2Header)
                {
                    descriptor.weight = (FontWeight)os2Header->usWeightClass;
                    descriptor.width = (FontWidth)os2Header->usWidthClass;
                }
            }

            descriptor.italic = (face->style_flags & FT_STYLE_FLAG_ITALIC) != 0;
            descriptor.monospace = FT_IS_FIXED_WIDTH(face);

            results.push_back(descriptor);
        }

        FT_Done_Face(face);
    }

    // Cache the results.
    if (!results.empty())
    {
        _fontDescriptorCache[absoluteFontPath] = results;
    }

    return results;
}


int64_t FTFontCache::getFaceIndexForFontDescriptor(const FontDescriptor& descriptor) const
{
    auto faces = FTFontCache::getFontDescriptorsForPath(descriptor.path);

    const auto size = faces.size();

    if (size == 0)
    {
        ofLogError("FTFontCache::getFaceIndexForFontDescriptor") << "No faces found for path.";
        return -1;
    }
    else if (size == 1)
    {
        // There was only one match.
        return 0;
    }
    else
    {
        if (descriptor.postscriptName.empty())
        {
            ofLogWarning("FTFontCache::getFaceIndexForFontDescriptor") << "postscriptName is empty.";
        }

        for (std::size_t i = 0; i < faces.size(); ++i)
        {
            if (faces[i].postscriptName == descriptor.postscriptName)
            {
                return i;
            }
        }
    }

    ofLogError("FTFontCache::getFaceIndexForFontDescriptor") << "No match found.";

    return -1;
}


} } // namespace ofx::Text
