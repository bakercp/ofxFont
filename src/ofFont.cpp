/*
 TODO:
 -- make sure UTF8 is used for all internal rendering, etc.
 -- make sure all input text is textconverted appropriately
 -- clean up all error / warning, messages , etc
 -- better index searching for unicode chars
 -- glyph auto generation?
 
 */


#include "ofFont.h"

static bool printVectorDebugInfo = false;
static int  fontGlobalDpi = 96; // a nice compromise

ofFont::Settings::Settings() {
    fontFilename        = ""; // must set on load
    fontSize            = 12;
    fontDpi             = 0;  // if <= 0 will default to fontGlobalDpi
    bAntiAliased        = true;
    bForceAutoHinting   = false;
    bUseKerning         = false;
    bMakePaths          = false;
    pathSimplifyAmt     = 0.3;
    fallbackSpaceChar   = 'p';
    faceNum             = 0;
    characterSet        = ofCharacterSet();
    bAutoGenerateGlyphs = false;

}

//--------------------------------------------------------
void ofFont::setGlobalDpi(int newDpi){
	fontGlobalDpi = newDpi;
}

//--------------------------------------------------------
static bool makePathForCharacter(FT_Face &face, ofPath& path);
static bool makePathForCharacter(FT_Face &face, ofPath& path){

		//int num			= face->glyph->outline.n_points;
    
        FT_GlyphSlot  slot = face->glyph;
    
		int nContours	= slot->outline.n_contours;
		int startPos	= 0;

		char * tags		= slot->outline.tags;
		FT_Vector * vec = slot->outline.points;

		//ofPath path;
        path.setUseShapeColor(false);

		for(int k = 0; k < nContours; k++){
			if( k > 0 ){
				startPos = slot->outline.contours[k-1]+1;
			}
			int endPos = slot->outline.contours[k]+1;

			if(printVectorDebugInfo){
				ofLog(OF_LOG_NOTICE, "--NEW CONTOUR\n");
			}

			//vector <ofPoint> testOutline;
			ofPoint lastPoint;

			for(int j = startPos; j < endPos; j++){

				if( FT_CURVE_TAG(tags[j]) == FT_CURVE_TAG_ON ){
					lastPoint.set((float)vec[j].x, (float)-vec[j].y, 0);
					if(printVectorDebugInfo){
						ofLog(OF_LOG_NOTICE, "flag[%i] is set to 1 - regular point - %f %f", j, lastPoint.x, lastPoint.y);
					}
					//testOutline.push_back(lastPoint);
					path.lineTo(lastPoint/64);

				}else{
					if(printVectorDebugInfo){
						ofLog(OF_LOG_NOTICE, "flag[%i] is set to 0 - control point", j);
					}

					if( FT_CURVE_TAG(tags[j]) == FT_CURVE_TAG_CUBIC ){
						if(printVectorDebugInfo){
							ofLog(OF_LOG_NOTICE, "- bit 2 is set to 2 - CUBIC");
						}

						int prevPoint = j-1;
						if( j == 0){
							prevPoint = endPos-1;
						}

						int nextIndex = j+1;
						if( nextIndex >= endPos){
							nextIndex = startPos;
						}

						ofPoint nextPoint( (float)vec[nextIndex].x,  -(float)vec[nextIndex].y );

						//we need two control points to draw a cubic bezier
						bool lastPointCubic =  ( FT_CURVE_TAG(tags[prevPoint]) != FT_CURVE_TAG_ON ) && ( FT_CURVE_TAG(tags[prevPoint]) == FT_CURVE_TAG_CUBIC);

						if( lastPointCubic ){
							ofPoint controlPoint1((float)vec[prevPoint].x,	(float)-vec[prevPoint].y);
							ofPoint controlPoint2((float)vec[j].x, (float)-vec[j].y);
							ofPoint nextPoint((float) vec[nextIndex].x,	-(float) vec[nextIndex].y);

							//cubic_bezier(testOutline, lastPoint.x, lastPoint.y, controlPoint1.x, controlPoint1.y, controlPoint2.x, controlPoint2.y, nextPoint.x, nextPoint.y, 8);
                            // TODO use shifts
							path.bezierTo(controlPoint1.x/64, 
                                          controlPoint1.y/64, 
                                          controlPoint2.x/64, 
                                          controlPoint2.y/64, 
                                          nextPoint.x/64, 
                                          nextPoint.y/64);
						}

					}else{

						ofPoint conicPoint( (float)vec[j].x,  -(float)vec[j].y );

						if(printVectorDebugInfo){
							ofLog(OF_LOG_NOTICE, "- bit 2 is set to 0 - conic- ");
							ofLog(OF_LOG_NOTICE, "--- conicPoint point is %f %f", conicPoint.x, conicPoint.y);
						}

						//If the first point is connic and the last point is connic then we need to create a virutal point which acts as a wrap around
						if( j == startPos ){
							bool prevIsConnic = (  FT_CURVE_TAG( tags[endPos-1] ) != FT_CURVE_TAG_ON ) && ( FT_CURVE_TAG( tags[endPos-1]) != FT_CURVE_TAG_CUBIC );

							if( prevIsConnic ){
								ofPoint lastConnic((float)vec[endPos - 1].x, (float)-vec[endPos - 1].y);
								lastPoint = (conicPoint + lastConnic) / 2;

								if(printVectorDebugInfo){
									ofLog(OF_LOG_NOTICE, "NEED TO MIX WITH LAST");
									ofLog(OF_LOG_NOTICE, "last is %f %f", lastPoint.x, lastPoint.y);
								}
							}
						}

						//bool doubleConic = false;

						int nextIndex = j+1;
						if( nextIndex >= endPos){
							nextIndex = startPos;
						}

						ofPoint nextPoint( (float)vec[nextIndex].x,  -(float)vec[nextIndex].y );

						if(printVectorDebugInfo){
							ofLog(OF_LOG_NOTICE, "--- last point is %f %f", lastPoint.x, lastPoint.y);
						}

						bool nextIsConnic = (  FT_CURVE_TAG( tags[nextIndex] ) != FT_CURVE_TAG_ON ) && ( FT_CURVE_TAG( tags[nextIndex]) != FT_CURVE_TAG_CUBIC );

						//create a 'virtual on point' if we have two connic points
						if( nextIsConnic ){
							nextPoint = (conicPoint + nextPoint) / 2;
							if(printVectorDebugInfo){
								ofLog(OF_LOG_NOTICE, "|_______ double connic!");
							}
						}
						if(printVectorDebugInfo){
							ofLog(OF_LOG_NOTICE, "--- next point is %f %f", nextPoint.x, nextPoint.y);
						}

						//quad_bezier(testOutline, lastPoint.x, lastPoint.y, conicPoint.x, conicPoint.y, nextPoint.x, nextPoint.y, 8);
                        // TODO use shits
						path.quadBezierTo(lastPoint.x/64, 
                                          lastPoint.y/64, 
                                          conicPoint.x/64, 
                                          conicPoint.y/64, 
                                          nextPoint.x/64, 
                                          nextPoint.y/64);

						if( nextIsConnic ){
							lastPoint = nextPoint;
						}
					}
				}

			//end for
			}
			path.close();
		}

    // TODO : is it ever possible to return false here?  say, if a font file does not have contours?
	return true;
}

// TODO : move this code to a "font manager" and use for all
#ifdef TARGET_ANDROID
	#include <set>
	set<ofFont*> all_fonts;
	void ofUnloadAllFonts(){
		set<ofFont*>::iterator it;
		for(it=all_fonts.begin();it!=all_fonts.end();it++){
			(*it)->unloadFont();
		}
	}
	void ofReloadAllFonts(){
		set<ofFont*>::iterator it;
		for(it=all_fonts.begin();it!=all_fonts.end();it++){
			(*it)->reloadFont();
		}
	}
#endif

// a utility function for sorting glyph texture  collections
bool compare_glyph_tex_by_size(const ofGlyphTex & c1, const ofGlyphTex & c2){
	if(c1.getTexHeight() == c2.getTexHeight()) return c1.getTexWidth() > c2.getTexWidth();
	else return c1.getTexHeight() > c2.getTexHeight();
}

//------------------------------------------------------------------
ofFont::ofFont(){
	bLoadedOk		= false;
    
    // TODO: move this to a font manager
	#ifdef TARGET_ANDROID
		all_fonts.insert(this);
	#endif
	
    resetMetrics();

	// 3 pixel border around the glyph
	// We show 2 pixels of this, so that blending looks good.
	// 1 pixels is hidden because we don't want to see the real edge of the texture

	border			= 3;
	//visibleBorder	= 2;
	stringQuads.setMode(OF_PRIMITIVE_TRIANGLES);
	binded = false;
}

//------------------------------------------------------------------
ofFont::~ofFont(){
    unloadFont();
    
    // TODO: move this to a font manager
    #ifdef TARGET_ANDROID
        all_fonts.erase(this);
    #endif
}

//------------------------------------------------------------------
bool ofFont::unloadFont(){
	if (bLoadedOk){
        texAtlas.clear();
        resetMetrics();
        glyphs.clear();
        glyphTextures.clear();
        glyphPaths.clear();
        kerningTable.clear();
        bLoadedOk = false;
    }
    return true;
}

//------------------------------------------------------------------
void ofFont::reloadFont(){
	loadFont(settings);
}

//------------------------------------------------------------------
ofFont::Settings ofFont::getSettings() {
    return settings;
}


void ofFont::resetMetrics() {
    bHasKerning         = false; // even though we request kerning, it may not be supported in the font
    bHasPaths           = false;

    fontFamilyName      = "UNKNOWN";
    fontStyleName       = "UNKNOWN";

    numFacesInFont      = PARAMETER_UNKNOWN;
    currentFaceIndex    = PARAMETER_UNKNOWN;
    maxAdvanceWidth     = PARAMETER_UNKNOWN; 
    maxAdvanceHeight    = PARAMETER_UNKNOWN;
    underlinePosition   = PARAMETER_UNKNOWN;
    underlineThickness  = PARAMETER_UNKNOWN;
    ascender            = PARAMETER_UNKNOWN;
    descender           = PARAMETER_UNKNOWN;
    height              = PARAMETER_UNKNOWN; 

    // TODO: add the rest of the parameters here
    
}


//-----------------------------------------------------------
bool ofFont::loadFont(string fontFilename, 
                              int fontSize, 
                              bool bAntiAliased, 
                              bool bMakePaths, 
                              float pathSimplifyAmt, 
                              int fontDpi,
                              ofCharacterSet characterSet,
                              bool bAutoGenerateGlyphs) {

    settings.fontFilename        = fontFilename;
    settings.fontSize            = fontSize;
    settings.fontDpi             = fontDpi;
    settings.bAntiAliased        = bAntiAliased;
    settings.bMakePaths          = bMakePaths;
    settings.pathSimplifyAmt     = pathSimplifyAmt;
    settings.characterSet        = characterSet;
    settings.bAutoGenerateGlyphs = bAutoGenerateGlyphs;
    
    // all else is set in the default settings constructor
}
 
    

//-----------------------------------------------------------
bool ofFont::loadFont(Settings _settings) { 

    if(_settings.fontFilename.empty()) {
		ofLog(OF_LOG_ERROR,"ofFont::loadFont - No font name specified.");
		return false;
    }
    
    settings = _settings; // get a copy of the settings file

	//------------------------------------------------
	if (bLoadedOk == true){
		// we've already been loaded, try to clean up :
		unloadFont();
	}
	//------------------------------------------------

    string fontFilenameWithPath = ofToDataPath(settings.fontFilename);
        
	bLoadedOk = false;

	//--------------- load the library and typeface
	
    FT_Library library;
    
    FT_Error err;
    err = FT_Init_FreeType( &library );

    
    if (err){
		ofLog(OF_LOG_ERROR,"ofFont::loadFont - Error initializing freetype lib: FT_Error = %d", err);
		return false;
	}

    FT_Face       face;
    FT_GlyphSlot  slot;
    err = FT_New_Face( library, fontFilenameWithPath.c_str(), settings.faceNum, &face ); 
    
    if ( err == FT_Err_Unknown_File_Format )
    {
        ofLog(OF_LOG_ERROR,"ofFont::loadFont - Error loading font - unknown file format %d", err);
        return false;
    } else if ( err ) {
        ofLog(OF_LOG_ERROR,"ofFont::loadFont - Error loading font - corrupt file? %d", err);
        return false;
    }

    slot = face->glyph;  /* a small shortcut */

    
	if (err) {
        // simple error table in lieu of full table (see fterrors.h)
        string errorString = "unknown freetype";
        if(err == 1) errorString = "INVALID FILENAME";
        ofLog(OF_LOG_ERROR,"ofFont::loadFont - %s: %s: FT_Error = %d", errorString.c_str(), fontFilenameWithPath.c_str(), err);
		return false;
	}
    
    // get the correct dpi
    int fontDpi = settings.fontDpi <= 0 ? fontGlobalDpi : settings.fontDpi;
    float fontSize = settings.fontSize << 6; // shift into 1/64 scale

	FT_Set_Char_Size( face, fontSize, fontSize, fontDpi, fontDpi);
    
    vector<ofUniChar> characterSet = settings.characterSet.getCharacterSet(); 
    nGlyphs = (int)characterSet.size();

    
	//------------------------------------------------------
	//kerning would be great to support:
	//ofLog(OF_LOG_NOTICE,"FT_HAS_KERNING ? %i", FT_HAS_KERNING(face));
	//------------------------------------------------------

    bHasKerning = FT_HAS_KERNING(face) > 0 && settings.bUseKerning;

    bIsScalable = FT_IS_SCALABLE(face);  // does have scalable outlines?
                                         // true for TrueType, Type 1, Type 42, CID, OpenType/CFF, and PFR font formats.
                                         // parameters below only valid for scalable fonts;
    
    bHasFixedSizes          = FT_HAS_FIXED_SIZES(face);
    bIsFixedWith            = FT_IS_FIXED_WIDTH(face);
    bIsSFNT                 = FT_IS_SFNT(face);
    bHasHorzGlyphMetrics    = FT_HAS_HORIZONTAL(face);
    bHasVertGlyphMetrics    = FT_HAS_VERTICAL(face);
    bHasFastGlyphs          = FT_HAS_FAST_GLYPHS(face);
    bHasMultipleMasters     = FT_HAS_MULTIPLE_MASTERS(face);
    bHasGlyphNames          = FT_HAS_GLYPH_NAMES(face);
    
    fontFamilyName      =      face->family_name;
    fontStyleName       =      face->style_name;
    maxAdvanceWidth     = (int)face->max_advance_width   >> 6;
    maxAdvanceHeight    = (int)face->max_advance_height  >> 6;
    underlinePosition   = (int)face->underline_position  >> 6;
    underlineThickness  = (int)face->underline_thickness >> 6;
    descender           = -1 * ((int)face->descender     >> 6); // free type descenders are negative
    ascender            = (int)face->ascender            >> 6;
    height              = (int)face->height              >> 6;

    unitsPerEm          = (int)face->units_per_EM        >> 6;
    
    numGlyphsInFont     = (int)face->num_glyphs; // num glyphs in font
    
    boundingBox         =  ofRectangle((face->bbox.xMin) >> 6,
                                       (face->bbox.yMin) >> 6,
                                       (face->bbox.xMax-face->bbox.xMin) >> 6,
                                       (face->bbox.yMax-face->bbox.yMax) >> 6);
    
    
	// initialize our vectors
	glyphs.resize(nGlyphs);
    glyphTextures.resize(nGlyphs);
    glyphPaths.resize(nGlyphs);
    kerningTable.resize(nGlyphs*nGlyphs);

    //--------------------------------------------------

	vector<ofPixels> expanded_data(nGlyphs); // a collection of glyph texture pixels

	long areaSum=0; // this is used for the tex atlas

    FT_Int32         loadMode = settings.bForceAutoHinting ? FT_LOAD_DEFAULT       : FT_LOAD_TARGET_LIGHT;
    FT_Render_Mode renderMode = settings.bAntiAliased      ? FT_RENDER_MODE_NORMAL : FT_RENDER_MODE_MONO;
    
	//--------------------- load each char -----------------------
	for (ofUniCharGlyphIdx glyphIdx = 0 ; glyphIdx < nGlyphs; glyphIdx++){
        
		//------------------------------------------ anti aliased or not:

        ofUniChar unicode = characterSet[glyphIdx]; // You should use the UTF-32 representation form of Unicode; for example, 
                                 // if you want to load character U+1F028, use value 0x1F028 as the value for charcode
        
        
        // we use the default unicode charmap.  all of our text processing is done based on a unicode charmap
        // we do no glyph transformations with vector formats.  that can be done elswhere
        
        FT_UInt charIndex = FT_Get_Char_Index( face, unicode );// FT assumes a unicode charmap, returns 0 (missing glyph if problem)
        
		err = FT_Load_Glyph( face,charIndex,loadMode );

        if(err){
			ofLog(OF_LOG_ERROR,"ofFont::loadFont - Error with FT_Load_Glyph %i: FT_Error = %d", glyphIdx, err);
		}
        
        /*
        FT_Glyph  glyph; // a handle to the glyph image
        err = FT_Get_Glyph( slot, &glyph );
        if(err){
			ofLog(OF_LOG_ERROR,"ofFont::loadFont - Error with FT_Get_Glyph %i: FT_Error = %d", i, err);
		}
        FT_Done_Glyph(glyph); // delete the glyph
        */
        

        // render the glyph -- places a bitmap in the bitmap slot of the glyph
		FT_Render_Glyph(slot, renderMode); // rasterizes outlines, etc.
		
		//------------------------------------------
		FT_Bitmap& bitmap= slot->bitmap;

		// prepare the texture:
		/*int width  = ofNextPow2( bitmap.width + border*2 );
		int height = ofNextPow2( bitmap.rows  + border*2 );


		// ------------------------- this is fixing a bug with small type
		// ------------------------- appearantly, opengl has trouble with
		// ------------------------- width or height textures of 1, so we
		// ------------------------- we just set it to 2...
		if (width == 1) width = 2;
		if (height == 1) height = 2;*/

		// -------------------------
		// info about the character:
        // >> many dimensions are expressed as 1/64th of a pixel. 
        // e.g. advance.x = 64 is actually 1 pixel.  (64 >> 6 = 1)
        glyphs[glyphIdx].font           = this; // a reference back to its parent
		glyphs[glyphIdx].glyphIndex     = glyphIdx;
        glyphs[glyphIdx].unicode        = unicode;
		glyphs[glyphIdx].height         = slot->bitmap_top;
		glyphs[glyphIdx].width          = slot->bitmap.width;
		glyphs[glyphIdx].setWidth       = slot->advance.x >> 6; // internally expressed 1/64th of a pixel
		glyphs[glyphIdx].topExtent 		= slot->bitmap.rows;
		glyphs[glyphIdx].leftExtent		= slot->bitmap_left;
        
        // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_Glyph_Metrics
        // http://www.freetype.org/freetype2/docs/tutorial/step2.html
        //glyphs[glyphIdx].width        = slot->metrics.width        >> 6; // same as above
        //glyphs[glyphIdx].height       = slot->metrics.height       >> 6; // same as above
        glyphs[glyphIdx].horiAdvance    = slot->metrics.horiAdvance  >> 6;
        glyphs[glyphIdx].horiBearingX   = slot->metrics.horiBearingX >> 6;
        glyphs[glyphIdx].horiBearingY   = slot->metrics.horiBearingY >> 6;
        // the next three are only reliable when bHasVertGlyphMetrics == true
        glyphs[glyphIdx].vertAdvance    = slot->metrics.vertAdvance  >> 6;
        glyphs[glyphIdx].vertBearingX   = slot->metrics.vertBearingX >> 6;
        glyphs[glyphIdx].vertBearingY   = slot->metrics.vertBearingY >> 6;

        // unicode information for quick reference
        glyphs[glyphIdx].bIsSpace       = Poco::Unicode::isSpace(unicode);
        glyphs[glyphIdx].bIsDigit       = Poco::Unicode::isDigit(unicode);
        glyphs[glyphIdx].bIsPunct       = Poco::Unicode::isPunct(unicode);
        glyphs[glyphIdx].bIsAlpha       = Poco::Unicode::isAlpha(unicode);
        glyphs[glyphIdx].bIsLower       = Poco::Unicode::isLower(unicode);
        glyphs[glyphIdx].bIsUpper       = Poco::Unicode::isUpper(unicode);
 
        
		//this accounts for the fact that we are showing 2*visibleBorder extra pixels
		//so we make the size of each char that many pixels bigger
		float stretch = 0;//(float)(visibleBorder * 2);
        
        int fheight	= glyphs[glyphIdx].height;
		int bwidth	= glyphs[glyphIdx].width;
		int top		= glyphs[glyphIdx].topExtent - glyphs[glyphIdx].height;
		int lextent	= glyphs[glyphIdx].leftExtent;

		float corr	= (float)(( (settings.fontSize - fheight) + top) - settings.fontSize);

        // texture information
        glyphTextures[glyphIdx].glyphIndex = glyphIdx;          // the glyph _index_
		glyphTextures[glyphIdx].tW         = bitmap.width;      // texture width
		glyphTextures[glyphIdx].tH         = bitmap.rows;       // texture height
		glyphTextures[glyphIdx].x1         = lextent + bwidth + stretch; // x start
		glyphTextures[glyphIdx].y1         = fheight + corr + stretch;   // y start
		glyphTextures[glyphIdx].x2	       = (float) lextent;            // x end
		glyphTextures[glyphIdx].y2	       = -top + corr;                // y end


        // build kerning table if possible and requested
        if(bHasKerning) {
            FT_Vector  ft_kerning;
            FT_UInt    kerningMode = FT_KERNING_DEFAULT; // default for now b/c we are using pixel units
            FT_Error   kerningError;

            for (ofUniCharGlyphIdx rightBottomGlyphIdx = 0 ; rightBottomGlyphIdx < nGlyphs; rightBottomGlyphIdx++){

                // we grab the unicode char b/c the glyphs themselves are not fully loaded yet    
                ofUniChar rightBottomUnicode = characterSet[rightBottomGlyphIdx];

                kerningError = FT_Get_Kerning( face,          // handle to face object 
                          unicode,              // left/top glyph unicode      
                          rightBottomUnicode,   // right/bottom glyph unicode     
                          kerningMode,          // kerning mode          
                          &ft_kerning );        // target vector           

                if(!kerningError) {
                    ofVec2f kerning((ft_kerning.x >> 6),(ft_kerning.y >> 6));
                    kerningTable[ glyphIdx * nGlyphs + rightBottomGlyphIdx ] = kerning;
                } else {
                    ofLog(OF_LOG_ERROR,"ofFont::loadFont - Error with FT_Get_Kerning %i/%i: FT_Error = %d", glyphIdx, rightBottomGlyphIdx, kerningError);
                }
            }
        }

        // Allocate Memory For The Texture Data.
		expanded_data[glyphIdx].allocate(glyphTextures[glyphIdx].tW, 
                                         glyphTextures[glyphIdx].tH, 
                                         2);
        
        
		//-------------------------------- clear data:
		expanded_data[glyphIdx].set(0,255); // every luminance pixel = 255
		expanded_data[glyphIdx].set(1,0);

		if (settings.bAntiAliased == true){
			ofPixels bitmapPixels;
			bitmapPixels.setFromExternalPixels(bitmap.buffer,bitmap.width,bitmap.rows,1);
			expanded_data[glyphIdx].setChannel(1,bitmapPixels);
		} else {
			//-----------------------------------
			// true type packs monochrome info in a
			// 1-bit format, hella funky
			// here we unpack it:
			unsigned char *src =  bitmap.buffer;
			for(int j=0; j <bitmap.rows;j++) {
				unsigned char b=0;
				unsigned char *bptr =  src;
				for(int k=0; k < bitmap.width ; k++){
                    int idx = 2*(k+j*glyphTextures[glyphIdx].tW);
					expanded_data[glyphIdx][idx] = 255;
					if (k%8==0){
						b = (*bptr++);
					}
					expanded_data[glyphIdx][idx + 1] = b&0x80 ? 255 : 0;
					b <<= 1;
				}
				src += bitmap.pitch;
			}
            
			//-----------------------------------
		}
                
        // continue area sum for texatalas
		areaSum += (glyphs[glyphIdx].width+border*2)*(glyphs[glyphIdx].height+border*2);
        
        // BUILD CONTOURS IF REQUESTED
        if(settings.bMakePaths){
            ofPath p;
			if(makePathForCharacter( face, p )) {
                glyphPaths[glyphIdx].path = p;

                if(settings.pathSimplifyAmt > 0) {
                    glyphPaths[glyphIdx].path.simplify(settings.pathSimplifyAmt);
                }
                
                glyphPaths[glyphIdx].path.getTessellation();
                bHasPaths = true;

            } else {
                // TODO: fill in possible path error problems
                // failed to create the path for some reason
                glyphPaths[glyphIdx].path = ofPath();
                bHasPaths = false;
            }
		}
        
	} // END MAIN LOADING LOOP
      // WE CAN NOW LOOK UP OUR GLYPH INDICIES via charToIndex && IndexToChar

    // double check that space has a setWidth
    // if none, revert to the _width_ of an the fallback space char (usually 'p')
    if(glyphs[unicodeToGlyphIndex(' ')].setWidth <= 0) {
        glyphs[unicodeToGlyphIndex(' ')].setWidth = glyphs[unicodeToGlyphIndex(settings.fallbackSpaceChar)].width;
    }
    
	vector<ofGlyphTex> sortedGlyphTextures = glyphTextures;
	sort(sortedGlyphTextures.begin(),sortedGlyphTextures.end(),&compare_glyph_tex_by_size);

	// pack in a texture, algorithm to calculate min w/h from
	// http://upcommons.upc.edu/pfc/bitstream/2099.1/7720/1/TesiMasterJonas.pdf

	bool packed = false;
	float alpha = logf(areaSum)*1.44269;

	int w;
	int h;
	while(!packed){
		w = pow(2,floor((alpha/2.f) + 0.5)); // there doesn't seem to be a round in cmath for windows.
		//w = pow(2,round(alpha/2.f));
		h = w;//pow(2,round(alpha - round(alpha/2.f)));
		int x=0;
		int y=0;
		int maxRowHeight = sortedGlyphTextures[0].tH + border*2;
		for(ofUniCharGlyphIdx gIdx = 0; gIdx < nGlyphs; gIdx++){
            float thisTexH = sortedGlyphTextures[gIdx].tH;
            float thisTexW = sortedGlyphTextures[gIdx].tW;
			if(x+thisTexW + border*2 > w){
				x = 0;
				y += maxRowHeight;
				maxRowHeight = thisTexH + border*2;
				if(y + maxRowHeight > h){
					alpha++;
					break;
				}
			}
			x+= thisTexW + border*2;
			if(gIdx==(nGlyphs-1)) packed = true;
		}
	}
    
    // create the atlas
	ofPixels atlasPixels;
	atlasPixels.allocate(w,h,2);
	atlasPixels.set(0,255);
	atlasPixels.set(1,0);

	int x=0;
	int y=0;
	int maxRowHeight = sortedGlyphTextures[0].tH + border*2;
    
	for(ofUniCharGlyphIdx sortedGlyphIdx=0; sortedGlyphIdx < nGlyphs; sortedGlyphIdx++){
        ofUniCharGlyphIdx thisGlyphIndex = sortedGlyphTextures[sortedGlyphIdx].glyphIndex;
        float thisTexH = sortedGlyphTextures[sortedGlyphIdx].tH;
        float thisTexW = sortedGlyphTextures[sortedGlyphIdx].tW;
		ofPixels & charPixels = expanded_data[thisGlyphIndex];
        if(x + thisTexW + border*2 > w){
			x = 0;
			y += maxRowHeight;
			maxRowHeight = thisTexH + border * 2;
		}

        int xb = x + border; 
        int yb = y + border;
        
		glyphTextures[thisGlyphIndex].t2 = float(           xb) / float(w);
		glyphTextures[thisGlyphIndex].v2 = float(           yb) / float(h);
		glyphTextures[thisGlyphIndex].t1 = float(thisTexW + xb) / float(w);
		glyphTextures[thisGlyphIndex].v1 = float(thisTexH + yb) / float(h);
		
        charPixels.pasteInto(atlasPixels,xb,yb);
		x+= thisTexW + border*2;
	}

    // allocate the texture atlas
	texAtlas.allocate(atlasPixels.getWidth(),atlasPixels.getHeight(),GL_LUMINANCE_ALPHA,false);

	if(settings.bAntiAliased && settings.fontSize > 20){ // TODO: add thresh to settings for more flexibility?
		texAtlas.setTextureMinMagFilter(GL_LINEAR,GL_LINEAR);
	}else{
		texAtlas.setTextureMinMagFilter(GL_NEAREST,GL_NEAREST);
	}

    // load up the texture atlas from the atlast pixels
	texAtlas.loadData(atlasPixels.getPixels(),atlasPixels.getWidth(),atlasPixels.getHeight(),GL_LUMINANCE_ALPHA);

    // ------------- close the library and typeface
    FT_Done_Face(face);
    FT_Done_FreeType(library);

  	bLoadedOk = true;
	return true;
}


//-----------------------------------------------------------
bool ofFont::isLoaded() {
	return bLoadedOk;
}

//-----------------------------------------------------------
bool ofFont::isAntiAliased() {
	return settings.bAntiAliased;
}

//-----------------------------------------------------------
bool ofFont::hasKerning() {
	return bHasKerning;
}

//-----------------------------------------------------------
bool ofFont::hasPaths() {
    return bHasPaths;
}

//-----------------------------------------------------------
float ofFont::getSize() {
	return settings.fontSize;
}

//-----------------------------------------------------------
float ofFont::charWidth(ofUniCharGlyphIdx glyphIdx) {
    if(isValidGlyphIdx(glyphIdx)) {
        return glyphs[glyphIdx].setWidth;
    } else {
        return 0;
    }
}

//-----------------------------------------------------------
float ofFont::charWidth(UniChar unicode) {
    return charWidth(unicodeToGlyphIndex(unicode));
}

void ofFont::drawChar(ofUniCharGlyphIdx glyphIdx, ofPoint p , bool drawAsPath) {
    if(drawAsPath && !hasPaths()) {
        ofLog(OF_LOG_ERROR, "ofFont:drawChar - attempting to draw paths, but no paths found.");
        return;
    }

    if(isValidGlyphIdx(glyphIdx)) {
    
        if(glyphs[glyphIdx].isSpace()) {
            // TODO: tone it down ... no errors or warnings should be thrown here.
            ofLog(OF_LOG_ERROR, "ofFont:drawChar - we don't render spaces!");
            return;
        }
        
        if(drawAsPath) {
            glyphPaths[glyphIdx].path.setFilled(ofGetStyle().bFill);
///            glyphPaths[glyphIdx].path.draw(p);
            
            // no core support
            ofPushMatrix();
            ofTranslate(p);
            glyphPaths[glyphIdx].path.draw();
            ofPopMatrix();

            
            
            
        } else {
            bool alreadyBinded = binded;
            if(!alreadyBinded) bind();
            
            float	x1, y1, x2, y2;
            float   t1, v1, t2, v2;
            t2		= glyphTextures[glyphIdx].t2;
            v2		= glyphTextures[glyphIdx].v2;
            t1		= glyphTextures[glyphIdx].t1;
            v1		= glyphTextures[glyphIdx].v1;
            
            x1		= glyphTextures[glyphIdx].x1+p.x;
            y1		= glyphTextures[glyphIdx].y1+p.y;
            x2		= glyphTextures[glyphIdx].x2+p.x;
            y2		= glyphTextures[glyphIdx].y2+p.y;
            
            int firstIndex = stringQuads.getVertices().size();
                        
            stringQuads.addVertex(ofVec3f(x1,y1));
            stringQuads.addVertex(ofVec3f(x2,y1));
            stringQuads.addVertex(ofVec3f(x2,y2));
            stringQuads.addVertex(ofVec3f(x1,y2));
            
            stringQuads.addTexCoord(ofVec2f(t1,v1));
            stringQuads.addTexCoord(ofVec2f(t2,v1));
            stringQuads.addTexCoord(ofVec2f(t2,v2));
            stringQuads.addTexCoord(ofVec2f(t1,v2));
            
            stringQuads.addIndex(firstIndex);
            stringQuads.addIndex(firstIndex+1);
            stringQuads.addIndex(firstIndex+2);
            stringQuads.addIndex(firstIndex+2);
            stringQuads.addIndex(firstIndex+3);
            stringQuads.addIndex(firstIndex);
            
            if(!alreadyBinded) unbind();
            
        }
    
    } else {
        ofLog(OF_LOG_ERROR, "ofFont:drawChar - invalid glyph index!");
    }
}

//-----------------------------------------------------------
void ofFont::drawChar(ofUniChar unicode, ofPoint p, bool drawAsPath) {
    if(drawAsPath && !hasPaths()) {
        ofLog(OF_LOG_ERROR, "ofFont: drawChar - attempting to draw paths, but no paths found.");
        return;
    } else {
        drawChar(unicodeToGlyphIndex(unicode),p,drawAsPath);
    }
}

//-----------------------------------------------------------
void ofFont::drawCharPath(ofUniCharGlyphIdx glyphIdx, ofPoint position) {
    drawChar(glyphIdx,position,true);
}

//-----------------------------------------------------------
void ofFont::drawCharPath(ofUniChar unicode, ofPoint position) {
    drawChar(unicode,position,true);
}

//-----------------------------------------------------------
void ofFont::drawCharTex(ofUniCharGlyphIdx glyphIdx , ofPoint position) {
    drawChar(glyphIdx,position,false);
}

//-----------------------------------------------------------
void ofFont::drawCharTex(ofUniChar unicode, ofPoint position) {
    drawChar(unicode,position,false);
}


//-----------------------------------------------------------
ofVec2f ofFont::getKerningByGlyphIndex(ofUniCharGlyphIdx leftTopCharIndex, ofUniCharGlyphIdx rightBotomCharIndex) {
    if(hasKerning() &&
       (isValidGlyphIdx(leftTopCharIndex)) &&
       (isValidGlyphIdx(rightBotomCharIndex)) ) { 
        return kerningTable[ leftTopCharIndex * nGlyphs + rightBotomCharIndex ];
    } else {
        return ofVec2f(0.0f,0.0f);
    }
}


//-----------------------------------------------------------
ofVec2f ofFont::getKerning(ofUniChar leftChar, ofUniChar rightChar) {
    if(hasKerning()) {
        return getKerningByGlyphIndex(unicodeToGlyphIndex(leftChar), unicodeToGlyphIndex(rightChar));
    } else {
        return ofVec2f(0.0f,0.0f);
    }
}

//-----------------------------------------------------------
float ofFont::getHorizontalKerning(ofUniChar leftChar, ofUniChar rightChar) {
    return getKerning(leftChar, rightChar).x;
}

//-----------------------------------------------------------
float   ofFont::getVerticalKerning(ofUniChar topChar, ofUniChar bottomChar) {
    return getKerning(topChar, bottomChar).y;
}

//-----------------------------------------------------------
ofUniCharGlyphIdx ofFont::unicodeToGlyphIndex(UniChar unicode) {
        
    
    // TODO: should this be in the characterset class?
    // TODO: search shortcut
    //if(settings.characterSet.hasAsciiCharacters()) {
        // if we know we have the ascii char set, then we don't have to search for chars in that range
        //    if(character >= ASCII_START_CHARACTER && 
        //       character < UNICODE_START_CHARACTER) {
        //    return (character - ASCII_START_CHARACTER);
        //  }
    //}
    
    // otherwise, we have to quickly search for our char
    ofUniCharGlyphIdx indexMin = 0;
    ofUniCharGlyphIdx indexMax = nGlyphs - 1;
    
    // binary search for our glyph index of the unicode char we want

    // continue searching while [imin,imax] is not empty
    while ( indexMin <= indexMax) {
        int indexMid = (indexMin + indexMax) >> 1; // find midpoint
        // determine which subarray to search
        if(glyphs[indexMid].unicode < unicode) {
            indexMin = indexMid + 1; // search upper half
        } else if (glyphs[indexMid].unicode > unicode ) {
            // search lower half
            indexMax = indexMid - 1;
        } else {
            return indexMid; // found at index
        }
    }
    
    return autoGenerateGlyph(unicode); // attempt to auto generate
}

//-----------------------------------------------------------
ofUniChar ofFont::glyphIndexToUnicode(ofUniCharGlyphIdx glyphIdx) {
    if(isValidGlyphIdx(glyphIdx)) {
        return glyphs[glyphIdx].unicode;
    } else {
        return UNICODE_INDEX_NOT_FOUND;
    }
}

//-----------------------------------------------------------
void ofFont::bind(){
	if(!binded){
        
        // TODO:
	    // we need transparency to draw text, but we don't know
	    // if that is set up in outside of this function
	    // we "pushAttrib", turn on alpha and "popAttrib"
	    // http://www.opengl.org/documentation/specs/man_pages/hardcopy/GL/html/gl/pushattrib.html

	    // **** note ****
	    // I have read that pushAttrib() is slow, if used often,
	    // maybe there is a faster way to do this?
	    // ie, check if blending is enabled, etc...
	    // glIsEnabled().... glGet()...
	    // http://www.opengl.org/documentation/specs/man_pages/hardcopy/GL/html/gl/get.html
	    // **************
		// (a) record the current "alpha state, blend func, etc"
		#ifndef TARGET_OPENGLES
			glPushAttrib(GL_COLOR_BUFFER_BIT);
		#else
			blend_enabled = glIsEnabled(GL_BLEND);
			texture_2d_enabled = glIsEnabled(GL_TEXTURE_2D);
			glGetIntegerv( GL_BLEND_SRC, &blend_src );
			glGetIntegerv( GL_BLEND_DST, &blend_dst );
		#endif

	    // (b) enable our regular ALPHA blending!
	    glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		texAtlas.bind();
		stringQuads.clear();
		binded = true;
	} else {
    }
}

//-----------------------------------------------------------
void ofFont::unbind(){
	if(binded){
		stringQuads.drawFaces();
		texAtlas.unbind();

		#ifndef TARGET_OPENGLES
			glPopAttrib();
		#else
			if( !blend_enabled )
				glDisable(GL_BLEND);
			if( !texture_2d_enabled )
				glDisable(GL_TEXTURE_2D);
			glBlendFunc( blend_src, blend_dst );
		#endif
		binded = false;
	} else {
    }
}


//-----------------------------------------------------------
ofUniCharGlyphIdx ofFont::autoGenerateGlyph(ofUniChar unicode) {
    if(settings.bAutoGenerateGlyphs) {
        return createGlyph(unicode);
    } else {
        // glyph auto generation is disabled
        return UNICODE_INDEX_NOT_FOUND;
    }
}

//-----------------------------------------------------------
ofUniCharGlyphIdx ofFont::createGlyph(ofUniChar unicode) {
    // TODO generate glyph here
    //settings.characterSet.addUnicodeCharacter(unicode)
    // create it, generate paths, reconstruct texAtlas , etc
    // tricky parts
    // - kerning table updating
    // -- 1D kerning table -- could we use a set for quicker inserts?
    // - updating internal glyph index references in all locations
    // - keeping the library and face structures open
    // - adding the glyph face to the texatlas --
    // - keep track of space remaining and only resize when it has gotten
    // -- too big --- or always create a very large texture for the atlas to begin?
    // -- or create a a "secondary" texture for all auto generated glyphs?
    // -- hmph.
    ofLog(OF_LOG_ERROR,"ofFont::createGlyph() not implemented.");
    return UNICODE_INDEX_NOT_FOUND;
}

//-----------------------------------------------------------
int ofFont::getNumGlyphs() {
	return nGlyphs;
}

//-----------------------------------------------------------
ofGlyph ofFont::getGlyph(ofUniCharGlyphIdx glyphIdx) {
    if(isValidGlyphIdx(glyphIdx)) {
        return glyphs[glyphIdx];
    } else {
        // TODO invalid glyphidx
    }
}

//-----------------------------------------------------------
ofGlyph ofFont::getGlyph(ofUniChar unicode) {
    return getGlyph(unicodeToGlyphIndex(unicode));
}

//-----------------------------------------------------------
ofPath ofFont::getGlyphPath(ofUniCharGlyphIdx glyphIdx) {
    if(isValidGlyphIdx(glyphIdx)) {
        return glyphPaths[glyphIdx].path;
    } else {
        // TODO invalid glyphidx
    }
}

//-----------------------------------------------------------
ofPath ofFont::getGlyphPath(ofUniChar unicode) {
    return getGlyphPath(unicodeToGlyphIndex(unicode));
}

//-----------------------------------------------------------
ofTexture ofFont::getGlyphTex(ofUniCharGlyphIdx glyphIdx) {
    if(isValidGlyphIdx(glyphIdx)) {
        return glyphTextures[glyphIdx].tex;
    } else {
        // TODO invalid glyphidx
    }
}

//-----------------------------------------------------------
ofTexture ofFont::getGlyphTex(ofUniChar unicode) {
    return getGlyphTex(unicodeToGlyphIndex(unicode));
}

//-----------------------------------------------------------
string ofFont::getFamilyName() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::getFamilyName - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return fontFamilyName;
}
//-----------------------------------------------------------
string ofFont::getStyleName() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::getStyleName - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return fontStyleName;
}
//-----------------------------------------------------------
int ofFont::getNumFacesInFont() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::getNumFacesInFont - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return numFacesInFont;
}
//-----------------------------------------------------------
int ofFont::getCurrentFaceIndex() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::getCurrentFaceIndex - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return currentFaceIndex;
}
//-----------------------------------------------------------
int ofFont::getMaxAdvanceWidth() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::getMaxAdvanceWidth - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return maxAdvanceWidth;
}
//-----------------------------------------------------------
int ofFont::getMaxAdvanceHeight() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::getMaxAdvanceHeight - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return maxAdvanceHeight;
}
//-----------------------------------------------------------
int ofFont::getUnderlinePosition() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::getUnderlinePosition - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return underlinePosition;
}
//-----------------------------------------------------------
int ofFont::getUnderlineThickness() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::getUnderlineThickness - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return underlineThickness;
}
//-----------------------------------------------------------
int ofFont::getAscender() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::getAscender - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return ascender;
}
//-----------------------------------------------------------
int ofFont::getDescender() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::getDescender - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return descender;
}
//-----------------------------------------------------------
int ofFont::getHeight() {
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::getHeight - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return height;
}

//-----------------------------------------------------------
bool ofFont::isValidGlyphIdx(ofUniCharGlyphIdx glyphIdx) {
    return glyphIdx > -1 && glyphIdx < nGlyphs;
}

//-----------------------------------------------------------
bool ofFont::isScalable() { 
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::isScalable - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return bIsScalable;
}
//-----------------------------------------------------------
bool ofFont::hasFixedSizes() { 
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::hasFixedSizes - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return bHasFixedSizes; 
}
//-----------------------------------------------------------
bool ofFont::isFixedWith() { 
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::isFixedWith - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return bIsFixedWith;
}
//-----------------------------------------------------------
bool ofFont::isSFNT() { 
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::isSFNT - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return bIsSFNT;
}
//-----------------------------------------------------------
bool ofFont::hasHorzGlyphMetrics() { 
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::hasHorzGlyphMetrics - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return bHasHorzGlyphMetrics;
}
//-----------------------------------------------------------
bool ofFont::hasVertGlyphMetrics() { 
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::hasVertGlyphMetrics - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return bHasVertGlyphMetrics;
}
//-----------------------------------------------------------
bool ofFont::hasFastGlyphs() { 
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::hasFastGlyphs - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return bHasFastGlyphs;
}
//-----------------------------------------------------------
bool ofFont::hasMultipleMasters() { 
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::hasMultipleMasters - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return bHasMultipleMasters;
}
//-----------------------------------------------------------
bool ofFont::hasGlyphNames() { 
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::hasGlyphNames - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    }
    return bHasGlyphNames;
}



