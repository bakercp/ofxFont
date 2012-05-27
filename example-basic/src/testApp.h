#pragma once

#include "ofMain.h"
//#include "ofTextUtils.h"
#include "ofFrameSetter.h"


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

    ofFont ttf0;
    ofFont ttf1;
    ofFont ttf2;
    ofFont ttf3;
    
    float aScale;
    //vector<ofCharacter> offsets;
    
    ofPath boundingPath;
    ofPath amperPath;
    ofFrameSetter frameSetter;
    
    vector<ofRectangle> rects;
    
    ofTextFrame frame;
    
    string txt;
    string ttx;
    string ttt;
};
