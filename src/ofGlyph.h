//
//  ofGlyph.h
//  openFrameworksLib
//
//  Created by Christopher Baker on 4/23/12.
//  Copyright (c) Christopher Baker. All rights reserved.
//

#pragma once

#include "ofFont.h"

class ofFont;


class ofGlyph {
public:
    ofGlyph();
    virtual ~ofGlyph();

    ofUniChar            getUnicode();
    ofUniCharGlyphIdx  getGlyphIndex();

    string getGlyphName();
    ofFont* getFontRef();
    
    // metrics
    float getHeight();
    float getWidth();
    float getTopExtent();
    float getLeftExtent();
    
    float getHoriBearingX();
    float getHoriBearingY();
    float getHoriAdvance();
    // TODO: add warning if vert metrics are not reliable?
    float getVertBearingX();
    float getVertBearingY();
    float getVertAdvance();
    
    ofRectangle getBoundingBox();
    
    // unicode information
    bool isSpace();
    bool isDigit();
    bool isPunct();
    bool isAlpha();
    bool isLower();
    bool isUpper();
    
    
protected:
    
    ofFont* font;                   // a reference to the parent font

    string glyphName;
    
	ofUniChar           unicode;    // the unicode value of this char
    ofUniCharGlyphIdx glyphIndex; // the index in the fon't glyph collection
    
    
    // metrics
	int height;
	int width;
	int setWidth;
	int topExtent;
	int leftExtent;
    
    int horiBearingX;
    int horiBearingY;
    int horiAdvance;
    int vertBearingX;
    int vertBearingY;
    int vertAdvance;
    
    ofRectangle boundingBox;
    
    // unicode information
    bool bIsSpace;
    bool bIsDigit;
    bool bIsPunct;
    bool bIsAlpha;
    bool bIsLower;
    bool bIsUpper;

    
    friend class ofFont; // so ofFont can set these protected variables directly
                         // we want them to be read only to everybody else
                         // and to any subclasses, but not to the rest of the world
    
};
