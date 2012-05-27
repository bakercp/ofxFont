//
//  ofTextLayoutManager.h
//  openFrameworksLib
//
//  Created by Christopher Baker on 4/22/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

class ofLayoutManager() {

    // bounding boxes
    ofRectangle getStringBoundingBox(string s, float x = 0.0f, float y = 0.0f, bool shrinkToContours = true);
    ofRectangle getStringBoundingBox(string s, ofPoint p, bool shrinkToContours = true);
    ofRectangle getStringBoundingBox(ofTextBlock textBlock, bool shrinkToContours = true);

    // drawing!
    // characters
    ofCharacter drawChar(int character, float x, float y, bool asShapes = false);
    ofCharacter drawChar(int character, ofPoint p, bool asShapes = false);
    ofCharacter drawCharAsShapes(int character, float x, float y);
    ofCharacter drawCharAsShapes(int character, ofPoint p);

    // strings
    ofTextBlock drawString(string s, float x = 0.0f, float y = 0.0f, float w = FLT_MAX, float h = FLT_MAX, bool asShapes = false);
    ofTextBlock drawString(string s, ofRectangle boundingBox, bool asShapes = false);
    ofTextBlock drawString(string s, ofPolyline shape, bool asShapes = false);
    void        drawString(ofTextBlock textBlock, ofVec2f offset = ofVec2f(0,0), bool asShapes = false);
    ofTextBlock drawStringAsShapes(string s, float x = 0.0f, float y = 0.0f, float w = FLT_MAX, float h = FLT_MAX);	
    ofTextBlock drawStringAsShapes(string s, ofRectangle boundingBox);
    ofTextBlock drawStringAsShapes(string s, ofPolyline shape);
    void        drawStringAsShapes(ofTextBlock textBlock, ofVec2f offset = ofVec2f(0,0));

    ofPath      getCharacterAsPoints(int character, float x = 0.0f, float y = 0.0f);
    ofPath      getCharacterAsPoints(int character, ofPoint p);

    ofTextBlock getStringAsPoints(string s, float x = 0.0f, float y = 0.0f, float w = FLT_MAX, float h = FLT_MAX);
    ofTextBlock getStringAsPoints(string s, ofRectangle boundingBox);
    ofTextBlock getStringAsPoints(string s, ofPolyline shape);

    ofTextBlock getCharacterOffsets(string s, float x = 0.0f, float y = 0.0f, float w = FLT_MAX, float h = FLT_MAX);
    ofTextBlock getCharacterOffsets(string s, ofRectangle boundingBox);
    ofTextBlock getCharacterOffsets(string s, ofPolyline shape);

};