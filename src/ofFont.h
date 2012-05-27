#pragma once

#include "ofMain.h"

#include "ofFontTypes.h"

#include "ofUnicode.h"
#include "ofGlyph.h"
#include "ofMappedGlyph.h"
#include "ofCharacterSet.h"

#include "ft2build.h"
#include "freetype2/freetype/freetype.h"
#include "freetype2/freetype/ftglyph.h"
#include "freetype2/freetype/ftoutln.h"
#include "freetype2/freetype/fttrigon.h"

#include FT_GLYPH_H

//--------------------------------------------------


class ofGlyph;

#define UNICODE_INDEX_NOT_FOUND        -1
#define PARAMETER_UNKNOWN              -1
typedef unsigned int     ofUniCharCount;
typedef ofUniCharCount*  ofUniCharCountPtr;


class ofFont {
public:
	struct Settings;

	ofFont();
	virtual ~ofFont();
	
	//set the default dpi for all typefaces.
	static void setGlobalDpi(int newDpi);
			
    bool 		loadFont(Settings _settings); // no default b/c filename must be specified
    // 			-- default (without dpi), non-full char set, anti aliased, 96 dpi:
	
    bool 		loadFont(string filename, 
                         int fontsize, 
                         bool bAntiAliased=true, 
                         bool bMakePaths=false, 
                         float pathhSimplifyAmt=0.3, 
                         int dpi=0,
                         ofCharacterSet characterSet = ofCharacterSet(),
                         bool bAutoGenerateGlyphs = false);
     
    bool        unloadFont(); // unloads all data 
    void        reloadFont(); // reloads font with existing Settings object.

    ofFont::Settings getSettings(); // useful for making copies
    
	bool		isLoaded();
	bool		isAntiAliased();
    bool        hasKerning();
    bool        hasPaths();

    float       getSize();
    float       getLineHeight();
    float       getLineHeightScale();
  	void 		setLineHeightScale(float scale);
	float 		getLetterSpaceScale();
	void 		setLetterSpaceScale(float scale);
	float 		getSpaceScale();
	void 		setSpaceScale(float scale);
    
    // font properties
    // read only variables set by the font.  see below for details
    string      getFamilyName();
    string      getStyleName();
    int         getNumFacesInFont();
    int         getCurrentFaceIndex();
    int         getMaxAdvanceWidth();
    int         getMaxAdvanceHeight();
    int         getUnderlinePosition();
    int         getUnderlineThickness();
    int         getAscender();
    int         getDescender();
    int         getHeight();
    
    bool        isScalable();
    bool        hasFixedSizes();
    bool        isFixedWith();
    bool        isSFNT();
    bool        hasHorzGlyphMetrics();
    bool        hasVertGlyphMetrics();
    bool        hasFastGlyphs();
    bool        hasMultipleMasters();
    bool        hasGlyphNames();
    
    //

    ofVec2f     getKerning(ofUniChar leftTopChar, ofUniChar rightBottomChar);
    float       getHorizontalKerning(ofUniChar leftChar, ofUniChar rightChar);
    float       getVerticalKerning(ofUniChar topChar, ofUniChar bottomChar);
   
    ofVec2f     getKerningByGlyphIndex(ofUniCharGlyphIdx leftTopCharIndex, ofUniCharGlyphIdx rightBotomCharIndex);

    // character width
    float   charWidth(ofUniCharGlyphIdx glyphIdx);
    float   charWidth(UniChar unicode);
    
    // single char drawing
    void    drawChar(ofUniCharGlyphIdx glyphIdx    , ofPoint position = ofPoint(0,0,0), bool drawAsPath = false);
    void    drawChar(ofUniChar unicode             , ofPoint position = ofPoint(0,0,0), bool drawAsPath = false);
    
    void    drawCharPath(ofUniCharGlyphIdx glyphIdx, ofPoint position = ofPoint(0,0,0));
    void    drawCharPath(ofUniChar unicode         , ofPoint position = ofPoint(0,0,0));
    
    void    drawCharTex(ofUniCharGlyphIdx glyphIdx , ofPoint position = ofPoint(0,0,0));
    void    drawCharTex(ofUniChar unicode          , ofPoint position = ofPoint(0,0,0));

    //			get the num chars in the loaded char set
	int			getNumGlyphs();	

    // TODO: what should these return?  copies?  references?  values?
    ofGlyph     getGlyph(ofUniCharGlyphIdx glyphIdx);
    ofGlyph 	getGlyph(ofUniChar unicode);
    
    ofPath      getGlyphPath(ofUniCharGlyphIdx glyphIdx);
    ofPath      getGlyphPath(ofUniChar unicode);
    
    ofTexture   getGlyphTex(ofUniCharGlyphIdx glyphIdx);
    ofTexture   getGlyphTex(ofUniChar unicode);
	
    struct Settings { // the settings critical for font allocation

        string  fontFilename;           // the font filename
        int     fontSize;               // the font file size
        int     fontDpi;                // the font dpi
        bool    bAntiAliased;           // should the font be created w/ antialiasing
        bool    bForceAutoHinting;      // should auto hinting be forced
        bool    bUseKerning;            // should a kerning table be generated
        bool    bMakePaths;             // should the font be created with paths
        float   pathSimplifyAmt;        // contour simplification factor
        int     fallbackSpaceChar;      // in the event that a font does not contain a setWidth 
                                        // for the space ' ' character, the width of this char
                                        // will be used.  Defaults to 'p';
		int     faceNum;                // for fonts that contain multiple faces
        //ofTextEncoding inputEncoding;   // the input text encoding.  all internal work is done w/ UTF-8
        ofCharacterSet characterSet;    // the character set used generated initially
        bool    bAutoGenerateGlyphs;    // will create glyphs when not found

        Settings();
	};
    
    
//protected:
    
    ofFont::Settings settings;    // all settings required for font allocation
    
    void resetMetrics(); // will reset metrics
    
    
    // character properties
    int nGlyphs;  // the size of the cps vector
    
    ofUniChar         glyphIndexToUnicode(ofUniCharGlyphIdx glyphIdx);
    ofUniCharGlyphIdx unicodeToGlyphIndex(UniChar unicode);

    bool              isValidGlyphIdx(ofUniCharGlyphIdx idx);

    ofUniCharGlyphIdx autoGenerateGlyph(ofUniChar unicode); // like createGlyph, but checks settings
    ofUniCharGlyphIdx createGlyph(ofUniChar unicode);
    
    vector<ofGlyph>     glyphs;
    vector<ofGlyphTex>  glyphTextures;
    vector<ofGlyphPath> glyphPaths;
    
    // KERNING TABLE
    // [ (leftGlyph_0,rightGlyph_0),...,(leftGlyph_0,rightGlyph_n)] 
    // [ (leftGlyph_1,rightGlyph_0),...,(leftGlyph_1,rightGlyph_n)]
    // [                            ...                           ]
    // [ (leftGlyph_n,rightGlyph_0),...,(leftGlyph_n,rightGlyph_n)]

    // to access a kerning pair:
    // kerningTable[ leftCharIndex * nGlyphs + rightCharIndex ];

    vector<ofVec2f> kerningTable; 

    bool			bLoadedOk;      // is the font ready to use
    bool            bHasKerning;    // does the font have kerning data?
    bool            bHasPaths;      // is this an utline font 

    // READ ONLY variables, set by the font
    string          fontName;           // the font name
    string          fontFamilyName;     // the font family name
    string          fontStyleName;      // the font style name

    int             numFacesInFont;     // The number of faces in the font file (for collections)
    int             currentFaceIndex;   // The currently loaded face index.  Usually 0.

    int             maxAdvanceWidth;    // The maximal advance width, in pixels, for all glyphs in this face. 
    // This can be used to make word wrapping computations faster.
    int             maxAdvanceHeight;   // The maximal advance height, in pixels, for all glyphs in this face. 
    // This is only relevant for vertical layouts, and is set to ‘height’ 
    // for fonts that do not provide vertical metrics.
    int             underlinePosition;  // The position, in pixels, of the underline line for this face. 
    // It's the center of the underlining stem.
    int             underlineThickness; // The thickness, in pixels, of the underline for this face.

    int             ascender;           // The typographic ascender of the face, expressed in pixels
    int             descender;          // The typographic descender of the face, expressed in pixels
    int             height;             // The height is the vertical distance between two consecutive baselines, 
                                        // expressed in pixels. It is always positive.
                                        // leading.

    int             unitsPerEm;
    
    ofRectangle    boundingBox; // The font bounding box. 
                                // The box is large enough to contain any glyph from the font. 
                                // Thus, ‘boundingBox.getMaxY()’ can be seen as the ‘maximal ascender’, and 
                                // ‘boundingBox.getMinY()’ as the ‘minimal descender’.
        

     
    int numGlyphsInFont;        // set by the font
    
    
    // face parameters
    bool bIsScalable;
    bool bHasFixedSizes;
    bool bIsFixedWith;
    bool bIsSFNT;
    bool bHasHorzGlyphMetrics;
    bool bHasVertGlyphMetrics;
    bool bHasFastGlyphs;
    bool bHasMultipleMasters;
    bool bHasGlyphNames;

    
private:
    
    
#ifdef TARGET_ANDROID
	friend void ofUnloadAllFontTextures();
	friend void ofReloadAllFontTextures();
#endif
#ifdef TARGET_OPENGLES
	GLint blend_src, blend_dst;
	GLboolean blend_enabled;
	GLboolean texture_2d_enabled;
#endif
    
    // texture
	void bind();
	void unbind();

    // texture related variables
	int         border;//, visibleBorder;
	bool        binded;
	ofTexture   texAtlas;
	ofMesh      stringQuads;
    


};


