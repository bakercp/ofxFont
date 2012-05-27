//
//  ofBaseFont.h
//  openFrameworksLib
//
//  Created by Christopher Baker on 4/23/12.
//  Copyright (c) Christopher Baker. All rights reserved.
//

#pragma once

#include "ofUnicode.h"

//----------------------------------------------------------
// ofBaseFont
//----------------------------------------------------------
class ofBaseFont {
    
public:
    
	ofBaseFont() {}
	virtual ~ofBaseFont() {}
    
	virtual void loadFont(string fileName)  = 0;
	virtual void unloadFont()               = 0;
    
    bool    isLoaded()                      = 0;
	bool    isAntiAliased()                 = 0;
    bool    hasKerning()                    = 0;
    bool    hasContours()                   = 0;
    
    // font description
    virtual string  getName()               = 0;
    virtual string  getPostscriptName()     = 0;
    virtual string  getFamilyName()         = 0;
    virtual string  getStyleName()          = 0;     

    virtual float   getSize()               = 0;          // font size

    // font metrics
    virtual int getCurrentFaceIndex()       = 0;
    virtual int getNumFacesInFont()         = 0;        

    virtual int getMaxAdvanceWidth()        = 0;
    virtual int getMaxAdvanceHeight()       = 0;

    // metrics
    virtual float   getHeight()             = 0;
    virtual float   getAscent()             = 0;
    virtual float   getDescent()            = 0;
    virtual int     getUnitsPerEm()         = 0;
    virtual int     getGlyphCount()         = 0;
    virtual float   getUnderlinePosition()  = 0;
    virtual float   getUnderlineThickness() = 0;
    virtual float   getSlantAngle()         = 0;
    virtual float   getCapHeight()          = 0;
    virtual float   getXHeight()            = 0;
    
    virtual int     getNumGlyphs()          = 0;
    
    virtual void drawGlyph(ofGlyph& glyph, 
                           ofPoint& position, 
                           ofPoint& rotation, 
                           ofColor& color) = 0;
    
    virtual void drawGlyphs(vector<ofGlyph>& glyphs, 
                            vector<ofPoint>& positions, 
                            vector<ofPoint>& rotations, 
                            vector<ofColor>& color) = 0;

    virtual vector<ofRectangle> getAdvancesForGlyphs(vector<ofGlyph>& glyphs) = 0;
    
    // kerning
    ofVec2f     getKerning(int leftChar, int rightChar)             = 0;
    float       getHorizontalKerning(int leftChar, int rightChar)   = 0;
    float       getVerticalKerning(int topChar, int bottomChar)     = 0;

    
    
    // glyph interaction
    virtual int                 getGlyphIndex(ofUniChar character) = 0;
    virtual ofGlyph             getGlyphForCharacter(ofUniChar character) = 0;
    
    virtual vector<ofGlyph>     getGlyphsForCharacters(const vector<ofUniChar> &characters) = 0;
    virtual vector<ofGlyph>     getGlyphsForIndices(const vector<ofUniCharGlyphIdx> &indices) = 0;


};
