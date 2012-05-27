#pragma once

#include "ofUnicode.h"
#include "ofFont.h"
#include "ofGlyph.h"

class ofGlyph;

class ofMappedGlyph {
public:  
    ofMappedGlyph() {};
    virtual ~ofMappedGlyph() {}
    
    ofGlyph*            glyphReference;
    ofUniChar           unicode;    // the unicode value of this char
    ofUniCharGlyphIdx   glyphIndex; // the index in the fon't glyph collection
};


class ofGlyphTex : public ofMappedGlyph {
public:
    ofGlyphTex() : ofMappedGlyph() {}
    virtual ~ofGlyphTex() {}
    // MIGRATE ALL OF THIS INFORMATION TO THE FONT
    // texture location data
    
    float getTexWidth()  const {return tW;};
    float getTexHeight() const {return tH;}
    
protected:
    // atlas mapping
    float tW,tH; // texture width / height
	float x1,x2,y1,y2;
	float t1,t2,v1,v2; 
    
    // TODO: add support
    // standalone tex
    ofTexture tex; 
    
    friend class ofFont;
    friend class ofGlyph;
    
};

class ofGlyphPath : public ofMappedGlyph {
public:
    ofGlyphPath() : ofMappedGlyph() {}
    virtual ~ofGlyphPath() {}
    
    ofPath path;
};