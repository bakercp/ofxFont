//
//  ofCharacterSet.h
//  openFrameworksLib
//
//  Created by Christopher Baker on 4/23/12.
//  Copyright (c) Christopher Baker. All rights reserved.
//

#pragma once

#include "ofUnicode.h"

#include <string>
#include <vector>
#include <set>
#include <utility>

using namespace std;

// all character set information is stored as UTF8
class ofCharacterSet {
public:
    
    ofCharacterSet();                                  // create default
    ofCharacterSet(string utf8String);                 // create from string
    ofCharacterSet(vector<ofUniChar>& characterSet);   // create from a vector
    
    virtual ~ofCharacterSet();

    vector<ofUniChar> getCharacterSet();
    void clear();
    void addAsciiCharacters();
    void addStandardUnicodeCharacters();
    void addUnicodeCharacter(ofUniChar character);
    void addAllUnicodeCharacters();
    void addUnicodeBlock(ofUniChar blockStart, ofUniChar blockStop);
    void addUnicodeBlock(pair<ofUniChar,ofUniChar> blockRange);
    
    bool hasUnicodeCharacter(ofUniChar character);
    
    //vector<ofUniChar> getInvertedCharacterSet(); // TODO: maybe

    bool hasAsciiCharacters(); // have we added the standard ascii characters?
    bool hasStandardUnicodeCharacters(); // have we added the standard unicode characters?
    
private:
    
    bool _hasAsciiCharacters;
    bool _hasStandardUnicodeCharacters;
    
    set<ofUniChar> characters;
    set<ofUniChar>::iterator it; // can help speed insertion when sequences are used
};