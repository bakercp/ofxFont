#pragma once

#include "ofMain.h"
//#include "ofTextUtils.h"
#include "ofFrameSetter.h"

#include "ofTextConverter.h"
#include "ofUTF8.h"


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    
    void setupFonts();

    void drawPathAndRects(ofPath& path, vector<ofRectangle>& rects) {
        
        path.draw(0,0);

        for(int k = 0; k < rects.size(); k++) {
            ofSetColor(0,255,255);
            ofNoFill();
            
            ofRect(rects[k]);
            ofSetColor(0,255,255,80);
            ofFill();
            
            ofRect(rects[k]);
            
            if(rects[k].width == 0.0f) {
                ofNoFill();
                ofSetColor(255,0,0);
                ofRect(rects[k]);
            }
            
        }
    }
    
    ofFont ttf0;
    ofFont ttf1;
    ofFont ttf2;
    ofFont ttf3;
    
    float aScale;
    //vector<ofCharacter> offsets;
    
    ofPath boundingPath;
    ofPath amperPath;
    ofPath circlePath;
    ofFrameSetter frameSetter;
    
    vector<ofRectangle> frameRects;
    vector<ofRectangle> frame2Rects;
    vector<ofRectangle> frame3Rects;
    
    ofTextFrame frame;
    ofTextFrame frame2;
    ofTextFrame frame3;
    
    string txt;
    string ttx;
    string ttt;
};
