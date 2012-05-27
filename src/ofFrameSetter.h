//
//  ofTextTypesetter.h
//  openFrameworksLib
//
//  Created by Christopher Baker on 4/22/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

// the typesetter places glyphs in lines
#include "ofMain.h"
#include "ofUnicode.h"
#include "ofFormattedText.h"
#include "ofTextFrame.h"
#include "ofTypesetter.h"
#include "ofLineSegment.h"

class ofFrameSetter {
public:
	struct Settings;

    ofFrameSetter() {}
    virtual ~ofFrameSetter() {}
    
    //ofTextFrame createFrame(ofFormattedText formattedText, 
    //                        ofPath& boundingPath, 
    //                        Settings frameSettings) {
        // create frame based on formatted text        
    //}

    ofTextFrame createFrame(string utf8String, 
                            ofPath& boundingPath) {//, 
                            //Settings frameSettings) {
        string txt = utf8String;
        ofTextFrame textFrame;
        textFrame.setBoundingPath(boundingPath);
        //settings = frameSettings;

        //vector<ofRectangle>  ff  = subdivideBoundingPath(boundingPath, 10);

        
        
        
        return textFrame;
    }
    
    
    struct Settings { // the settings critical for line filling process
        int none;
        Settings();
    };
    

    ofFrameSetter::Settings settings;
    
//protected:    

    ofTypesetter typesetter;

    
    
    static vector<ofRectangle> createLines(ofPath& boundingPath, float _lineHeight, ofTextFrameProgression tfp = OF_TEXT_FRAME_PROGRESS_RIGHTTOLEFT);
    static vector<ofRectangle> splitLines(ofPath& boundingPath, ofRectangle& testRect);
    static vector<ofLineSegment> clipLineToPath(ofPath& path, const ofLineSegment& line);

    
    // hacks due to no core support yet.

    static bool isInsidePath(ofPath path, ofPoint p);
    static ofRectangle getBoundingBox(ofPath& path);
    static ofRectangle addRectToRect(const ofRectangle& rect,const ofRectangle& rect1);
    static ofPolyline rectToPolyline(ofRectangle rect);
                            
};
