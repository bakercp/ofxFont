//
//  ofFormattedText.h
//  openFrameworksLib
//
//  Created by Christopher Baker on 5/1/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofTextRun.h"

class ofFormattedText {

public:
    ofFormattedText();
    virtual ~ofFormattedText();

public:
    
    string s; // UTF-8 string;
    
    ofFont* currentFont;
    ofColor currentFgColor;
    ofColor currentBgColor;
    bool    hasUnderline;
    ofColor underlineColor;
    // bool    bIsBold;
    // bool    bIsItalic;
    
    
    vector<ofTextRun> runs;

};
