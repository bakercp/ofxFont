//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Text/FontDescriptor.h"


namespace ofx {
namespace Text {


ofJson FontDescriptor::toJSON() const
{
    ofJson json;
    json["path"] = path;
    json["postscript_name"] = postscriptName;
    json["family"] = family;
    json["style"] = style;
    json["weight"] = weight;
    json["width"] = width;
    json["italic"] = italic;
    json["monospace"] = monospace;
//    json["size"] = size;
//
//    json["matrix"] = { affineTransform[0][0],
//                       affineTransform[0][1],
//                       affineTransform[0][2],
//                       affineTransform[1][0],
//                       affineTransform[1][1],
//                       affineTransform[1][2],
//                       affineTransform[2][0],
//                       affineTransform[2][1],
//                       affineTransform[2][2] };

    return json;
}


void FontDescriptor::fromJSON(const ofJson& json)
{
    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();

        if (key == "path") path = value;
        else if (key == "postscript_name") postscriptName = value;
        else if (key == "family") family = value;
        else if (key == "style") style = value;
        else if (key == "weight") weight = value;
        else if (key == "width") width = value;
        else if (key == "italic") italic = value;
        else if (key == "monospace") monospace = value;
//        else if (key == "size") size = value;
//        else if (key == "matrix")
//        {
//            if (9 == value.size())
//            {
//                affineTransform[0][0] = value[0];
//                affineTransform[0][1] = value[1];
//                affineTransform[0][2] = value[2];
//                affineTransform[1][0] = value[3];
//                affineTransform[1][1] = value[4];
//                affineTransform[1][2] = value[5];
//                affineTransform[2][0] = value[6];
//                affineTransform[2][1] = value[7];
//                affineTransform[2][2] = value[8];
//            }
//            else
//            {
//                ofLogWarning("FontDescriptor::fromJSON") << "Matrix does not have 9 elements, skipping.";
//            }
//        }
        else ofLogWarning("FontDescriptor::fromJSON") << "Unknown key " << key << " - " << json.dump(4);
        ++iter;
    }
}


bool FontDescriptor::operator < (const FontDescriptor& other) const
{
    if (path != other.path
    && !path.empty()
    && !other.path.empty())
    {
        return path < other.path;
    }
    else if (postscriptName != other.postscriptName
         && !postscriptName.empty()
         && !other.postscriptName.empty())
    {
        return postscriptName < other.postscriptName;
    }
    else if (family != other.family
             && !family.empty()
             && !other.family.empty())
    {
        return family < other.family;
    }
    else if (family != other.family
             && !family.empty()
             && !other.family.empty())
    {
        return family < other.family;
    }
    else if (style != other.style
             && !style.empty()
             && !other.style.empty())
    {
        return style < other.style;
    }
    else if (weight != other.weight
          && weight != FontWeight::FontWeightUndefined
          && other.weight != FontWeight::FontWeightUndefined)
    {
        return weight < other.weight;
    }
    else if (width != other.width
             && width != FontWidth::FontWidthUndefined
             && other.width != FontWidth::FontWidthUndefined)
    {
        return width < other.width;
    }
    else if (italic != other.italic)
    {
        return italic < other.italic;
    }
//    else if (monospace != other.monospace)
//    {
        return monospace < other.monospace;
//    }
//    else if (size != other.size)
//    {
//        return size < other.size;
//    }
//
//    return affineTransform[0][0] < other.affineTransform[0][0]
//        && affineTransform[0][1] < other.affineTransform[0][1]
//        && affineTransform[0][2] < other.affineTransform[0][2]
//        && affineTransform[1][0] < other.affineTransform[1][0]
//        && affineTransform[1][1] < other.affineTransform[1][1]
//        && affineTransform[1][2] < other.affineTransform[1][2]
//        && affineTransform[2][0] < other.affineTransform[2][0]
//        && affineTransform[2][1] < other.affineTransform[2][1]
//        && affineTransform[2][2] < other.affineTransform[2][2];
}


bool FontDescriptor::operator == (const FontDescriptor& other) const
{
    return path == other.path
        && postscriptName == other.postscriptName
        && family == other.family
        && style == other.style
        && weight == other.weight
        && width == other.width
        && italic == other.italic
        && monospace == other.monospace;
//        && size == other.size
//        && affineTransform == affineTransform;
}

    
bool FontDescriptor::operator != (const FontDescriptor& other) const
{
    return !(*this == other);
}



} } // namespace ofx::Text
