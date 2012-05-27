//
//  ofTextFrame.h
//  openFrameworksLib
//
//  Created by Christopher Baker on 4/25/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofTextLine.h"

enum ofTextFrameProgression {
	OF_TEXT_FRAME_PROGRESS_TOPTOBOTTOM = 0,
	OF_TEXT_FRAME_PROGRESS_RIGHTTOLEFT = 1,
};

enum ofTextFramePathFill {
	OF_TEXT_FRAME_PATH_FILL_EVENODD    = 0,
	OF_TEXT_FRAME_PATH_FILL_WINDINGNUM = 1,
};

class ofTextFrame {
public:
    ofTextFrame() {
        frameProgression = OF_TEXT_FRAME_PROGRESS_TOPTOBOTTOM;
        framePathFill    = OF_TEXT_FRAME_PATH_FILL_EVENODD;
    }
    virtual ~ofTextFrame() {};

    void setBoundingPath(ofPath _path) {path = _path;}
    ofPath getBoundingPath() {return path;}
    
    ofTextFrameProgression getFrameProgression() {return frameProgression;}
    ofTextFramePathFill getFramePathFill() {return framePathFill;}
    void setFrameProgression(ofTextFrameProgression _frameProgression) { frameProgression = _frameProgression; };
    void setFramePathFill(ofTextFramePathFill _framePathFill) {framePathFill = _framePathFill;};
    
    void push_back(ofTextLine line) {lines.push_back(line);}
    bool empty() { return lines.empty();}
    void clear() { path.clear(); lines.clear();};
    size_t size() { return lines.size();}
    ofTextLine& operator[](int pos) {return lines[pos];}

private:
    //ofPolyline boundingPolyline;
    
    ofPath path;
    vector<ofTextLine> lines;
    
    ofTextFrameProgression frameProgression;
    ofTextFramePathFill    framePathFill;
};

