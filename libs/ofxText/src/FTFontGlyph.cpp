////
//// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
////
//// SPDX-License-Identifier:    MIT
////
//
//
//#include "ofx/Text/FTFontGlyph.h"
//#include "ofx/Text/FTFont.h"
//
//
//#undef __FTERRORS_H__
//#define FT_ERRORDEF( e, v, s )  { e, s },
//#define FT_ERROR_START_LIST     {
//#define FT_ERROR_END_LIST       { 0, 0 } };
//const struct {
//    int          code;
//    const char*  message;
//} FT_Errors[] =
//#include FT_ERRORS_H
//
//
//namespace ofx {
//namespace Text {
//
//
//FTFontGlyph::FTFontGlyph(const FTFont& parent, FT_UInt glyphIndex):
//    _parent(parent),
//    _glyphIndex(glyphIndex)
//{
////    parent.parent().
//
//
//
////    // If we have not cached it, go ahead and do it.
////    FT_Error error = 0;
////
////    // Load glyph.
////    error = FT_Load_Glyph(_parent._ftFace,
////                          _glyphIndex,
////                          _parent.getEffectiveLoadFlags());
////    if (error)
////    {
////        ofLogError("FTFont::cacheGlyph") << "FT_Error loading Glyph: " << FT_Errors[error].code << ": " << FT_Errors[error].message;
////        return nullptr;
////    }
////
////    // Get a pointer to the glyph slot.
////    FT_GlyphSlot slot = _parent._ftFace->glyph;
////
//////    _parent._ftFace->glyph->face->charmap
////
////    // Get the glyph metrics.
////    FT_Glyph_Metrics  metrics = slot->metrics;
////
////    /// Get the glyph bitmap data.
////    FT_Bitmap bitmap = slot->bitmap;
////
////    _width = slot->bitmap.width;
////    _height = slot->bitmap_top;
////
////    _horizontalBearingX = metrics.horiBearingX;
////    _horizontalBearingY = metrics.horiBearingY;
////    _horizontalAdvance = metrics.horiAdvance;
////
////    _verticalBearingX = metrics.vertBearingX;
////    _verticalBearingY = metrics.vertBearingY;
////    _verticalAdvance = metrics.vertAdvance;
////
////    _linearHorizontalAdvance = slot->linearHoriAdvance;
////    _linearVerticalAdvance = slot->linearVertAdvance;
////    //    glyph->_transformedAdvanceX = slot->advance.x / DEFAULT_SCALER;
////    //    glyph->_transformedAdvanceY = slot->advance.y / DEFAULT_SCALER;
////
////    cout << "metrics w=" << (metrics.width >> 6) << endl;
////    cout << "bitmap.width w=" << bitmap.width << endl;
////
////    //    cps[i].height             = face->glyph->bitmap_top;
////    //    cps[i].width             = face->glyph->bitmap.width;
////    //    cps[i].setWidth         = face->glyph->advance.x >> 6;
////    //    cps[i].topExtent         = face->glyph->bitmap.rows;
////    //    cps[i].leftExtent        = face->glyph->bitmap_left;
////
////    /*    Here a small pseudo code fragment which shows how to use           */
////    /*    `lsb_delta' and `rsb_delta':                                       */
////    /*                                                                       */
////    /*    {                                                                  */
////    /*      FT_Pos  origin_x       = 0;                                      */
////    /*      FT_Pos  prev_rsb_delta = 0;                                      */
////    /*                                                                       */
////    /*                                                                       */
////    /*      for all glyphs do                                                */
////    /*        <compute kern between current and previous glyph and add it to */
////    /*         `origin_x'>                                                   */
////    /*                                                                       */
////    /*        <load glyph with `FT_Load_Glyph'>                              */
////    /*                                                                       */
////    /*        if ( prev_rsb_delta - face->glyph->lsb_delta >= 32 )           */
////    /*          origin_x -= DEFAULT_SCALER;                                              */
////    /*        else if ( prev_rsb_delta - face->glyph->lsb_delta < -32 )      */
////    /*          origin_x += DEFAULT_SCALER;                                              */
////    /*                                                                       */
////    /*        prev_rsb_delta = face->glyph->rsb_delta;                       */
////    /*                                                                       */
////    /*        <save glyph image, or render glyph, or ...>                    */
////    /*                                                                       */
////    /*        origin_x += face->glyph->advance.x;                            */
////    /*      endfor                                                           */
////    /*    }                                                                  */
////
////
////    /*    bitmap_left       :: This is the bitmap's left bearing expressed   */
////    /*                         in integer pixels.  Of course, this is only   */
////    /*                         valid if the format is                        */
////    /*                         @FT_GLYPH_FORMAT_BITMAP.                      */
////
////
////
////    //    bitmap_top =
////    //    This is the bitmap's top bearing expressed in */
////    /*                         integer pixels.  Remember that this is the    */
////    /*                         distance from the baseline to the top-most    */
////    /*                         glyph scanline, upwards y~coordinates being   */
////    /*                         *positive*.*/
////    //
////    //    int width  = cps[i].width;
////    //    int height = bitmap.rows;
////
////
////    //    FT_Bitmap         bitmap;
////    //    FT_Int            bitmap_left;
////    //    FT_Int            bitmap_top;
////    //
////    //    FT_Outline        outline;
////    //
////    //    FT_UInt           num_subglyphs;
////    //    FT_SubGlyph       subglyphs;
////    //
////    //    void*             control_data;
////    //    long              control_len;
////    //
////    //    FT_Pos            lsb_delta;
////    //    FT_Pos            rsb_delta;
////
////
////    //    cout << "SLOT:" << endl;
////    //    cout << "\trows = " << bitmap.rows << endl;
////    //    cout << "\twidth = " << bitmap.width << endl;
////    //    cout << "\tpitch =" << bitmap.pitch << endl;
////    //    cout << "\tnumGreys =" << bitmap.num_grays << endl;
////    //    cout << "\tpixelMode = " << (int)bitmap.pixel_mode << endl;
////    //    cout << "\tpaletteMode = " << (int)bitmap.palette_mode << endl;
////
////    int w = 0;
////    int h = 0;
////
////    // TODO: check render mode here to to see if rendering needs to happen.
////    // If it does need to happen, then ...
////    //
////
////    if (FT_RENDER_MODE_MAX != _parent._settings.renderMode())
////    {
////        error = FT_Render_Glyph(slot, _parent._settings.renderMode());
////
////        if (error)
////        {
////            ofLogError("FTFont::cacheGlyph") << "FT_Error rendering Glyph: " << FT_Errors[error].code << ": " << FT_Errors[error].message;
////            return nullptr;
////        }
////    }
////
////
////    //    glyph._codepoint = glyphIndex;
////    //    glyph._width     = w;
////    //    glyph._height    = h;
////    //
////    //    glyph._topExtent  = slot->bitmap_left;
////    //    glyph._leftExtent = slot->bitmap_top;
////    //
////    //    glyph._texture.texture = _atlas.getTextureReference();
////    //
////    //    float t0x = region.getMinX() / _atlas.getWidth();
////    //    float t1x = region.getMaxX() / _atlas.getWidth();
////    //
////    //    float t0y = region.getMinY() / _atlas.getHeight();
////    //    float t1y = region.getMaxY() / _atlas.getHeight();
////    //
////    //    glyph._texture.t0 = glm::vec2(t0x, t0y);
////    //    glyph._texture.t1 = glm::vec2(t1x, t1y);
////
////
////
////
////
////    //        ofUTF32Char _codepoint;
////    ///< \brief The glyph's Unicode codepoint.
////
////    //        std::string _name;
////    ///< \brief The glyph's ASCII name provided by the font.
////    ///< \note This may be empty.
////
////    //        float _setWidth; ///< \brief The glyph's set width.
////    //        float _topExtent; ///< \brief The glyph's top extent.
////    //        float _leftExtent; ///< \brief The glyph's left extent.
////    //        float _height; ///< \brief The glyph's height.
////    //        float _width; ///< \brief The glyph's width.
////    //        float _horizontalBearingX; ///< \brief Left side bearing for horizontal layout.
////    //        float _horizontalBearingY; ///< \brief Top side bearing for horizontal layout.
////    //        float _horizontalAdvance; ///< \brief Advance width for horizontal layout.
////    //        float _verticalBearingX; ///< \brief Left side bearing for vertical layout.
////    //        float _verticalBearingY; ///< \brief Top side bearing for vertical layout.
////    //        float _verticalAdvance; ///< \brief Advance height for vertical layout.
////    //
////    //        ofRectangle _boundingBox; ///< \brief The glyph's bounding rectangle.
////
////    //glyph->_contour = FTFontGlyph::createContour(slot);
////
////    // Add glyph to map
////
//}
//
//
//FTFontGlyph::~FTFontGlyph()
//{
//}
//
//
//const FTFont& FTFontGlyph::parent() const
//{
//    return _parent;
//}
//
//
//FT_UInt FTFontGlyph::glyphIndex() const
//{
//    return _glyphIndex;
//}
//
//
//bool FTFontGlyph::hasContour() const
//{
//    return _contour.getCommands().empty();
//}
//
//
//bool FTFontGlyph::hasTexture() const
//{
//    return false;// _texture.texture && _texture.texture->isAllocated();
//}
//
//
//FTFontGlyph::Contour& FTFontGlyph::contour()
//{
//    return _contour;
//}
//
//
//const FTFontGlyph::Contour& FTFontGlyph::contour() const
//{
//    return _contour;
//}
//
//
////FTFontGlyph::Texture& FTFontGlyph::texture()
////{
////    return _texture;
////}
////
////
////const FTFontGlyph::Texture& FTFontGlyph::texture() const
////{
////    return _texture;
////}
////
////
////FTFontGlyph::Pixels FTFontGlyph::pixels() const
////{
////
////
//////    _parent.parent().getpid()
////
////}
//
//
//FTFontGlyph::Contour FTFontGlyph::createContour(const FT_GlyphSlot& glyph)
//{
//    Contour contour;
//
//    contour.setUseShapeColor(false);
//
//    //int num = face->glyph->outline.n_points;
//    int startPos = 0;
//    char* tags = glyph->outline.tags;
//    short nContours = glyph->outline.n_contours;
//    FT_Vector* vec = glyph->outline.points;
//
//    for (std::size_t k = 0; k < nContours; ++k)
//    {
//        if (k > 0)
//        {
//            startPos = glyph->outline.contours[k - 1] + 1;
//        }
//
//        short endPos = glyph->outline.contours[k] + 1;
//
//        ofLogVerbose("FTFont::createContour()") << "--NEW CONTOUR";
//
//        glm::vec2 lastPoint;
//
//        for (std::size_t j = startPos; j < endPos; ++j)
//        {
//
//            if (FT_CURVE_TAG(tags[j]) == FT_CURVE_TAG_ON)
//            {
//                lastPoint = glm::vec2(vec[j].x, -vec[j].y);
//
//                ofLogVerbose("FTFont::createContour()") << "flag[" << j << "] is set to 1 - regular point - " << lastPoint.x <<  lastPoint.y;
//
//                contour.lineTo(lastPoint / FTFont::DEFAULT_SCALER);
//            }
//            else
//            {
//                ofLogVerbose("FTFont::createContour()") << "flag[" << j << "] is set to 0 - control point";
//
//                if (FT_CURVE_TAG(tags[j]) == FT_CURVE_TAG_CUBIC)
//                {
//                    ofLogVerbose("FTFont::createContour()") << "- bit 2 is set to 2 - CUBIC";
//
//                    std::size_t prevPoint = j - 1;
//
//                    if (0 == j)
//                    {
//                        prevPoint = endPos - 1;
//                    }
//
//                    std::size_t nextIndex = j + 1;
//
//                    if (nextIndex >= endPos)
//                    {
//                        nextIndex = startPos;
//                    }
//
//                    glm::vec2 nextPoint(vec[nextIndex].x, -vec[nextIndex].y);
//
//                    //we need two control points to draw a cubic bezier
//                    if (FT_CURVE_TAG(tags[prevPoint]) != FT_CURVE_TAG_ON
//                    &&  FT_CURVE_TAG(tags[prevPoint]) == FT_CURVE_TAG_CUBIC)
//                    {
//                        glm::vec2 controlPoint1(vec[prevPoint].x, -vec[prevPoint].y);
//
//                        glm::vec2 controlPoint2(vec[j].x, -vec[j].y);
//
//                        glm::vec2 nextPoint(vec[nextIndex].x, -vec[nextIndex].y);
//
//                        contour.bezierTo(controlPoint1.x / FTFont::DEFAULT_SCALER,
//                                         controlPoint1.y / FTFont::DEFAULT_SCALER,
//                                         controlPoint2.x / FTFont::DEFAULT_SCALER,
//                                         controlPoint2.y / FTFont::DEFAULT_SCALER,
//                                         nextPoint.x / FTFont::DEFAULT_SCALER,
//                                         nextPoint.y / FTFont::DEFAULT_SCALER);
//                    }
//                }
//                else
//                {
//                    glm::vec2 conicPoint(vec[j].x, -vec[j].y);
//
//                    ofLogVerbose("FTFont::createContour()") << "- bit 2 is set to 0 - conic- ";
//                    ofLogVerbose("FTFont::createContour()") << "--- conicPoint point is " << conicPoint;
//
//                    //If the first point is connic and the last point is connic then we need to create a virutal point which acts as a wrap around
//                    if (j == startPos)
//                    {
//                        if (FT_CURVE_TAG(tags[endPos-1]) != FT_CURVE_TAG_ON
//                        &&  FT_CURVE_TAG(tags[endPos-1]) != FT_CURVE_TAG_CUBIC)
//                        {
//                            glm::vec2 lastConnic(vec[endPos - 1].x, vec[endPos - 1].y);
//
//                            lastPoint = glm::mix(conicPoint, lastConnic, 0.5);
//
//                            ofLogVerbose("FTFont::createContour()")  << "NEED TO MIX WITH LAST: " << lastPoint;
//
//                        }
//                    }
//
//                    std::size_t nextIndex = j + 1;
//
//                    if (nextIndex >= endPos)
//                    {
//                        nextIndex = startPos;
//                    }
//
//                    glm::vec2 nextPoint(vec[nextIndex].x, -vec[nextIndex].y);
//
//                    ofLogVerbose("FTFont::createContour()")  << "--- last point is: " << lastPoint;
//
//                    //create a 'virtual on point' if we have two connic points
//
//                    if (FT_CURVE_TAG(tags[nextIndex]) != FT_CURVE_TAG_ON
//                    &&  FT_CURVE_TAG(tags[nextIndex]) != FT_CURVE_TAG_CUBIC)
//                    {
//                        nextPoint = glm::mix(conicPoint, nextPoint, 0.5);
//                        lastPoint = nextPoint;
//                        
//                        ofLogVerbose("FTFont::createContour()")  <<  "|_______ double connic!";
//                    }
//                    
//                    ofLogVerbose("FTFont::createContour()")  << "--- next point is: " << nextPoint;
//                    
//                    contour.quadBezierTo(lastPoint.x / FTFont::DEFAULT_SCALER,
//                                         lastPoint.y / FTFont::DEFAULT_SCALER,
//                                         conicPoint.x / FTFont::DEFAULT_SCALER,
//                                         conicPoint.y / FTFont::DEFAULT_SCALER,
//                                         nextPoint.x / FTFont::DEFAULT_SCALER,
//                                         nextPoint.y / FTFont::DEFAULT_SCALER);
//                    
//                }
//            }
//            
//            //end for
//        }
//        
//        contour.close();
//    }
//    
//    return contour;
//}
//
//} } // namespace ofx::Text
//
