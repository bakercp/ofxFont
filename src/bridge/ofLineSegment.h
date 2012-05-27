//
//  ofLineSegment.h
//  openFrameworksLib
//
//  Created by Christopher Baker on 4/22/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once
#include "ofPoint.h"
#include "ofRectangle.h"

class ofRectangle;

//----------------------------------------------------------
// ofLineSegment
//----------------------------------------------------------

enum ofLineIntersectResult { 
    OF_LINE_INTERESECTING,
    OF_LINE_NOT_INTERESECTING,
    OF_LINE_PARALLEL,
    OF_LINE_COINCIDENT 
};

class ofLineSegment {
public:
    ofLineSegment();
    ofLineSegment(ofPoint _p0, ofPoint _p1);
    virtual ~ofLineSegment();
    
    void set(float p0x, float p0y, float p0z, float p1x, float p1y, float p1z);
    void set(float p0x, float p0y, float p1x, float p1y);
    void set(const ofPoint& _p0, const ofPoint& _p1);
    void set(const ofLineSegment& line);
    
    ofPoint getMidPoint();
    float   getSlope();
    ofRectangle getBoundingBox();
    float   getLength();
    
    ofLineIntersectResult intersect(const ofLineSegment& other, ofPoint& intersection);
    bool intersects(const ofLineSegment& other, ofPoint& intersection);
    
    static bool ofLineIntersects(const ofLineSegment& first, 
                                 const ofLineSegment& second, 
                                 ofPoint& intersection);
    
    static ofLineIntersectResult ofLineIntersect(const ofLineSegment& first, 
                                                 const ofLineSegment& second, 
                                                 ofPoint& intersection);


    ofPoint p0;
    ofPoint p1;

protected:
private:
    
};
