//
//  ofTextTypesetter.h
//  openFrameworksLib
//
//  Created by Christopher Baker on 4/22/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

// the typesetter places glyphs in lines

/*
Line layout includes word wrapping, hyphenation, and line breaking in either vertical or horizontal rectangles. A typesetter object takes as input an attributed string and produces a line of typeset glyphs (composed into glyph runs) in a CTLine object. The typesetter performs character-to-glyph encoding, glyph ordering, and positional operations, such as kerning, tracking, and baseline adjustments. If multiline layout is needed, it is performed by a framesetter object, which calls into the typesetter to generate the typeset lines to fill the frame.

A framesetter encapsulates a typesetter and provides a reference to it as a convenience, but a caller may also choose to create a freestanding typesetter.
*/

#include "ofMain.h"
//#include "linebreak.h"
//#include "linebreakdef.h"

enum ofTypesetterLanguage {
    // very limited set used for linebreaker
    OF_TYPESETTER_LANG_EN, // English
    OF_TYPESETTER_LANG_DE, // German
    OF_TYPESETTER_LANG_ES, // Spanish
    OF_TYPESETTER_LANG_FR, // French
    OF_TYPESETTER_LANG_RU, // Russian
    OF_TYPESETTER_LANG_ZH, // Chinese
};

// Unicode / UTF8 utilities

// Language utils
string ofTextLangaugeToString(ofTypesetterLanguage lang);




enum ofTypesetterWordwrap {
    OF_TYPESETTER_WORDWRAP_NONE,
    OF_TYPESETTER_WORDWRAP_WRAP,
    OF_TYPESETTER_WORDWRAP_OVERFLOW,
    
//    WrapWithOverflow,
//    NoWrap,
//    Wrap
};

enum ofTypesetterLineEnding{
    OF_TYPESETTER_LINE_ENDING_NONE,
    OF_TYPESETTER_LINE_ENDING_ELLIPSES,
};

enum ofTypesetterFlowDirection {
    OF_TYPESETTER_FLOW_DIRECTION_HORIZONTAL,
    OF_TYPESETTER_FLOW_DIRECTION_VERTICAL,
};

class ofUniCharBreak {
public:
    ofUniCharBreak(ofUniChar _c, char _breakStatus) {
        c           = _c;
        breakStatus = _breakStatus;
    }
    
    ofUniChar  c;
    char       breakStatus;
};


// formatted text
//http://msdn.microsoft.com/en-us/library/ms752098.aspx

class ofTypesetter {
public:
    ofTypesetter();
    virtual ~ofTypesetter();
    
    void setFont(ofFont* font);
    ofFont* getFont();
    bool isFontLoaded();
    
    
    string hyphenate(string utf8String);
    
    vector<ofUniCharBreak> breakLines(string utf8String);
    
    void setLanguage(ofTypesetterLanguage lang);
    ofTypesetterLanguage getLanguage();

    
    //int suggestLineBreak(string utf8String, float width, int startIndex = 0);
    //int suggestLineBreakWithOffset(string utf8String, float width, int startIndex = 0, float offset = 0.0f);
    
    //ofTypesetterWordwrap
    //ofTypesetterLineEnding
    //ofTypesetterFlowDirection
    
protected:
    
private:
    ofFont* font;

    ofTypesetterLanguage lang;

};