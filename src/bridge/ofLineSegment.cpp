//
//  ofLineSegment.cpp
//  openFrameworksLib
//
//  Created by Christopher Baker on 4/22/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#include "ofLineSegment.h"


//----------------------------------------------------------
ofLineSegment::ofLineSegment() {
    p0 = ofPoint(0,0,0);
    p1 = ofPoint(0,0,0);
}

//----------------------------------------------------------
ofLineSegment::ofLineSegment(ofPoint _p0, ofPoint _p1) { 
    p0 = _p0; 
    p1 = _p1;
}

//----------------------------------------------------------
ofLineSegment::~ofLineSegment() { }

void ofLineSegment::set(float p0x, float p0y, float p0z, float p1x, float p1y, float p1z) {
    p0.set(p0x,p0y,p0z);
    p1.set(p1x,p1y,p1z);
}

void ofLineSegment::set(float p0x, float p0y, float p1x, float p1y) {
    p0.set(p0x,p0y);
    p1.set(p1x,p1y);
}


//----------------------------------------------------------
void ofLineSegment::set(const ofPoint& _p0, const ofPoint& _p1) {
    p0 = _p0;
    p1 = _p1;
}

//----------------------------------------------------------
void ofLineSegment::set(const ofLineSegment& line) 
{
    p0 = line.p0;
    p1 = line.p1;
}

//----------------------------------------------------------
ofPoint ofLineSegment::getMidPoint() {
    return p0.getMiddle(p1);
}

//----------------------------------------------------------
float ofLineSegment::getSlope() {
    return (p1.y - p0.y) / (p1.x - p0.x);
}

//----------------------------------------------------------
ofRectangle ofLineSegment::getBoundingBox() {
    float x = p0.x;
    float y = p0.y;
    float width  = p1.x - p0.x;
    float height = p1.y - p0.y;
    return ofRectangle(x,y,width,height);
}

//----------------------------------------------------------
float ofLineSegment::getLength() {
    return p0.distance(p1);
}

//----------------------------------------------------------
ofLineIntersectResult ofLineSegment::intersect(const ofLineSegment& other, ofPoint& intersection) {
    return ofLineSegment::ofLineIntersect((*this), other, intersection);
}

//----------------------------------------------------------
bool ofLineSegment::intersects(const ofLineSegment& other, ofPoint& intersection) {
    return ofLineSegment::ofLineIntersect((*this),other,intersection);
}

//----------------------------------------------------------
bool ofLineSegment::ofLineIntersects(const ofLineSegment& first, 
                                     const ofLineSegment& second, 
                                     ofPoint& intersection) {
    return ofLineSegment::ofLineIntersect(first, second, intersection) == OF_LINE_INTERESECTING;
}

//----------------------------------------------------------
//http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline2d/
// these intersections are all 2D.  for something like 3d
// http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline3d/
// TODO: intersection issue when line is coincident https://skitch.com/bakercp/8apmg/skitched-20120502-134532
// deal with this

ofLineIntersectResult ofLineSegment::ofLineIntersect(const ofLineSegment& l0, 
                                                     const ofLineSegment& l1, 
                                                     ofPoint& intersection) {
    
    float denom  = ((l1.p1.y - l1.p0.y)*(l0.p1.x - l0.p0.x)) -
                   ((l1.p1.x - l1.p0.x)*(l0.p1.y - l0.p0.y));
    
    float nume_a = ((l1.p1.x - l1.p0.x)*(l0.p0.y - l1.p0.y)) -
                   ((l1.p1.y - l1.p0.y)*(l0.p0.x - l1.p0.x));
    
    float nume_b = ((l0.p1.x - l0.p0.x)*(l0.p0.y - l1.p0.y)) -
                   ((l0.p1.y - l0.p0.y)*(l0.p0.x - l1.p0.x));
    
    if(denom == 0.0f){
        if(nume_a == 0.0f && nume_b == 0.0f) {return OF_LINE_COINCIDENT;}
        return OF_LINE_PARALLEL;
    }
    
    float ua = nume_a / denom;
    float ub = nume_b / denom;
    
    if(ua >= 0.0f && ua <= 1.0f && ub >= 0.0f && ub <= 1.0f){
        // Get the intersection point.
        intersection.x = l0.p0.x + ua*(l0.p1.x - l0.p0.x);
        intersection.y = l0.p0.y + ua*(l0.p1.y - l0.p0.y);
        return OF_LINE_INTERESECTING;
    }
    return OF_LINE_NOT_INTERESECTING;

    
}
