//
//  ofCharacter.h
//  openFrameworksLib
//
//  Created by Christopher Baker on 4/23/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofGlyph.h"

class ofCharacter  {
public:
    ofGlyph*  glyphRef;
    ofPoint   position;
    ofPoint   rotation;
    ofPoint   scale;
    
    void draw(bool asShape = false) {
        ofPushMatrix();
        ofTranslate(position);
        ofScale(scale.x,scale.y,scale.z);
        ofRotateX(rotation.x);
        ofRotateY(rotation.y);
        ofRotateZ(rotation.z);
        glyphRef->getFontRef()->drawChar(glyphRef->getGlyphIndex(),ofPoint(0,0,0),asShape);
        ofPopMatrix();
    }
    
};
