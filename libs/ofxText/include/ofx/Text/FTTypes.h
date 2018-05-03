//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


namespace ofx {
namespace Text {


/// \brief A utility class that fully defines an index for a FreeType font face.
///
/// The std::filesystem::path represents the absolute font path.
/// The FT_Long is the font face index of the font.
typedef std::pair<std::filesystem::path, int64_t> FTFaceId;


} } // namespace ofx::Text
