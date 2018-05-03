//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Text/FTFaceDescriptor.h"
#include "ofUtils.h"


namespace ofx {
namespace Text {



FTFaceDescriptor::FTFaceDescriptor(const std::filesystem::path& path):
    FTFaceDescriptor(path, DEFAULT_FACE_INDEX)
{
}


FTFaceDescriptor::FTFaceDescriptor(const std::filesystem::path& path,
                   FT_Long faceIndex):
    _path(ofToDataPath(path, true)),
    _faceIndex(faceIndex)
{
}


std::filesystem::path FTFaceDescriptor::path() const
{
    return _path;
}


FT_Long FTFaceDescriptor::faceIndex() const
{
    return _faceIndex;
}


bool FTFaceDescriptor::operator < (const FTFaceDescriptor& other) const
{
    if (_path != other._path)
        return _path < other._path;
    return _faceIndex < other._faceIndex;
}


bool FTFaceDescriptor::operator == (const FTFaceDescriptor& other) const
{
    return _path == other._path && _faceIndex == other._faceIndex;
}


bool FTFaceDescriptor::operator != (const FTFaceDescriptor& other) const
{
    return !(*this == other);
}


ofJson FTFaceDescriptor::toJSON() const
{
    ofJson json;
    json["path"] = _path.string();
    json["face_index"] = _faceIndex;
    return json;
}


} } // namespace ofx::Text
