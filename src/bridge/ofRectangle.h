/*
 *  ofRectangle.h
 *  openFrameworksLib
 *
 *  Created by zachary lieberman on 1/9/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofPoint.h"
#include "ofPolyline.h"

class ofPolyline;

//----------------------------------------------------------
// ofRectangle
//----------------------------------------------------------

class ofRectangle {
	
public:

    ofRectangle ();
    virtual ~ ofRectangle ();
    ofRectangle (float _x, float _y, float _w, float _h);
    ofRectangle (ofPoint pos, float w, float h);
    ofRectangle (ofPoint p0, ofPoint p1);
    ofRectangle (ofRectangle const & r);

    void set (float px, float py, float w, float h);
    void set (ofPoint pos, float w, float h);
    void set (ofPoint p0, ofPoint p1);
    void set (ofRectangle const & rect);
    void setFromCenter (float px, float py, float w, float h);
    void setFromCenter (ofPoint pos, float w, float h);

    ofPoint getCenter ();
    bool inside (float px, float py);
    bool inside (ofPoint p);
    bool inside (float px, float py, float w, float h);
    bool inside (ofPoint p, float w, float h);
    bool inside (ofRectangle const & rect);

    void add (float px, float py);
    void add (ofPoint p);
    void add (float px, float py, float w, float h);
    void add (ofPoint p, float w, float h);
    void add (ofRectangle const & r);

    ofPolyline getAsPolyline();
    
    ofPoint getMin();
    ofPoint getMax();
        
    float getMinX();
    float getMaxX();
    float getMaxY();
    float getMinY();

    ofRectangle & operator = (const ofRectangle & rect);
    bool operator == (ofRectangle const & r);
    bool operator != (ofRectangle const & r);
    ofRectangle & operator + (const ofPoint & point);
    
    float x;
    float y;
    float width;
    float height;
};

