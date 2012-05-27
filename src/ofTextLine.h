//
//  ofTextLine.h
//  openFrameworksLib
//
//  Created by Christopher Baker on 4/25/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofTextRun.h"

class ofTextLine {
public:
    ofTextLine() {};
    virtual ~ofTextLine() {};
    void push_back(ofTextRun fragment) {runs.push_back(fragment);}
    bool empty() { return runs.empty();}
    void clear() { lineBoundingBox = ofRectangle(); runs.clear();};
    size_t size() { return runs.size();}
    ofTextRun& operator[](int pos) {return runs[pos];}
    void setLineBoundingBox(ofRectangle rect) { lineBoundingBox = rect;}
    ofRectangle getLineBoundingBox() {return lineBoundingBox;}
private:
    
    ofRectangle lineBoundingBox; // the bounding box
    
    vector<ofTextRun>  runs;
};
