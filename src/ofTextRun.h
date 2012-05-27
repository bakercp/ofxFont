//
//  ofTextRun.h
//  openFrameworksLib
//
//  Created by Christopher Baker on 4/25/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofCharacter.h"

class ofTextRun {
public:
    ofTextRun() {};
    virtual ~ofTextRun() {};
    void push_back(ofCharacter character) {characters.push_back(character);}
    bool empty() { return characters.empty();}
    void clear() { characters.clear();}
    size_t size() { return characters.size();}
    ofCharacter& operator[](int pos) {return characters[pos];}
    
    /// points vector access
	size_t size() const;
	//const ofPoint& operator[] (int index) const;
	//ofPoint& operator[] (int index);
	void resize(size_t size);
    
    
private:
    vector<ofCharacter> characters;
};

