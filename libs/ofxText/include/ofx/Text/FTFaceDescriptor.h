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


/// \brief A class used to look up memory-cached fonts.
///
/// Cached fonts must exist on the filesystem.
class FTFaceDescriptor
{
public:
    FTFaceDescriptor();
    
    /// \brief Create a FTFaceDescriptor from the given path.
    /// \param path The font path.
    FTFaceDescriptor(const std::filesystem::path& path);

    /// \brief Create a FTFaceDescriptor from the given parameters.
    /// \param path The font path.
    /// \param faceIndex FT_Open_Face for a detailed description of this parameter.
    FTFaceDescriptor(const std::filesystem::path& path, FT_Long faceIndex);

    /// \returns the font resource URI.
    std::filesystem::path path() const;

    /// \returns the face index.
    FT_Long faceIndex() const;

    /// \brief A comparison operator used with std::map and other collections.
    /// \param other The other object to compare.
    /// \returns true iff this key is less than the other key.
    bool operator < (const FTFaceDescriptor& other) const;

    /// \brief Check equality between two objects.
    /// \param other The other object to compare.
    /// \returns true iff this object is equal to the other.
    bool operator == (const FTFaceDescriptor& other) const;

    /// \brief Check equality between two objects.
    /// \param other The other object to compare.
    /// \returns true iff this object is not equal to the other.
    bool operator != (const FTFaceDescriptor& other) const;

    /// \returns the json representation of the FTFaceDescriptor.
    ofJson toJSON() const;

    enum
    {
        /// \brief The default face index.
        DEFAULT_FACE_INDEX = 0
    };

private:
    /// \brief The font path.
    std::filesystem::path _path;

    /// \brief See FT_Open_Face for a detailed description of this parameter.
    FT_Long _faceIndex = DEFAULT_FACE_INDEX;

};


} } // namespace ofx::Text
