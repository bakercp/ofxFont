//
//  ofTextLayout.h
//  openFrameworksLib
//
//  Created by Christopher Baker on 4/23/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofMain.h"


// layout
//ofTextBlock  textLayout(string s, ofRectangle bb, bool draw, bool drawShapes);
//ofTextBlock  textLayout(string s, ofPolyline  bb, bool draw, bool drawShapes);

/*
//-----------------------------------------------------------
float ofFont::stringWidth(string s) {
    ofRectangle rect = getStringBoundingBox(s, 0,0);
    return rect.width;
}
float 		stringWidth(string s);
float 		stringHeight(string s);

 
 
 // scaling parameters that do not affect font allocation
 float 			lineHeightScale;
 float			letterSpaceScale;
 float			spaceScale;

 
 //-----------------------------------------------------------
 float ofFont::getLineHeight() {
 return height * lineHeightScale;
 }
 
 //-----------------------------------------------------------
 void ofFont::setLineHeightScale(float _lineHeightScale) {
 lineHeightScale = _lineHeightScale;
 }
 
 //-----------------------------------------------------------
 float ofFont::getLineHeightScale(){
 return lineHeightScale;
 }
 
 //-----------------------------------------------------------
 void ofFont::setLetterSpaceScale(float _letterSpaceScale) {
 letterSpaceScale = _letterSpaceScale;
 }
 
 //-----------------------------------------------------------
 float ofFont::getLetterSpaceScale(){
 return letterSpaceScale;
 }
 
 //-----------------------------------------------------------
 void ofFont::setSpaceScale(float _spaceScale) {
 spaceScale = _spaceScale;
 }
 
 //-----------------------------------------------------------
 float ofFont::getSpaceScale(){
 return spaceScale;
 }

 /*
 //-----------------------------------------------------------
 float ofFont::_widthString(string c, int start, int stop) {
 // assume no new lines
 float width = 0.0f;
 if(start >= 0 && stop < (int)c.length() - 1) {
 for (int i = start; i < stop; i++) {
 width += charWidth(c[i]); // scaling in charWidth
 if((i - 1) >= start) { // apply kerning if needed
 width += getHorizontalKerning(c[i-1], c[i]);
 }
 }
 } else {
 // start or stop were out of bounds
 ofLogWarning("ofFont::_widthString start / stop were out of bounds.");
 }
 return width;
 }
 */

*/