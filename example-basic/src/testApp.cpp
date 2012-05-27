#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    txt = "Az ZA AW wA AA TLOREM jIDd amet? CONectetur. adipiscing elit Crasporta lectus fermentum turpis bibendum in vehicula ligula pulvinar Etiam vitae lectus elit, ut aliquet dui. Sed odio eros, ultrices\nfacilisis rhoncus ac, viverra eget dolor. Vivamus ac erat a nisi laoreet ultricies. Donec tellus ligula,\ngravida quis laoreet non, scelerisque ac eros. Vestibulum \nelit orci, aliquet eget semper rutrum, aliquet nec arcu. Curabitur tempor iaculis ultricies. Proin vehicula mattis risus sit amet facilisis. Fusce quis pharetra elit. Nunc sodales sollicitudin consequat. Quisque a quam egestas arcu aliquet blandit sed a ligula.\nQuisAzque a sapien sed leo consequat hendrerit eget adipiscing justo. Donec id augue vitae mi dapibus congue. Suspendisse in metus a justo vestibulum ullamcorper\n vitae condimentum arcu. Sed volutpat laoreet odio eget gravida. Suspendisse quis quam quis velit vulputate dignissim. In quis purus placerat enim euismod ultrices. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Maecenas quis dolor purus, ac congue magna. Sed sit amet justo sit amet dui varius volutpat. In pellentesque interdum arcu, vel aliquet neque faucibus nec. Mauris eget tellus augue. Nam nisl quam, convallis id egestas vel, fringilla ac metus. Quisque sodales purus et velit fringilla aliquam.\nPellentesque a lorem diam. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nullam accumsan neque in mauris dignissim eu dapibus diam ultrices. Ut rhoncus, justo a ullamcorper mattis, lectus neque vestibulum nisi, non bibendum justo elit id diam. Vestibulum vel sapien mi. Donec a tortor risus. Ut est neque, molestie accumsan aliquet in, dapibus eget mi. Nam et enim mauris, vitae porttitor nulla. Aenean porttitor leo quis diam mattis at aliquam ante rutrum. Morbi quis ante neque.";
 
      txt += "Think it your unique\n designs evaluated.";
      txt += "Think it your unique\n      (designs) evaluated. ";
      txt += "Think it your unique                          \r\n(designs) evaluated. ";

      txt += "The fox.\r\nRox.\rRoxxxx.\nR00000!\nTimetimetime.\fTime222.\0x0085T9090\u2028Woot!\u2029Woot!\r\nANNN!";
      txt += "The fox.\r\nRox.\nIn a Box.\x000BTalks really big blocks ΑΩ€.\u2028HELLOOO\u2029THERE";//.\0x0085T9090\u2028Woot!\u2029Woot!\r\nANNN!";
  
/*    
    isThisCharNewLine = (thisChar == 0x000A || // LINE FEED, LF or \n
                         thisChar == 0x000B || // LINE TABULATION
                         thisChar == 0x000C || // FORM FEED, FF
                         thisChar == 0x0085 || // NEXT LINE, NEL
                         thisChar == 0x2028 || // LINE SEPERATOR, Zl
                         thisChar == 0x2029    // PARAGRAPH SEPERATOR, Zp

    */
    txt += "abc123⇒⟹↱↴℥℞ℑ℁℆ℌ€ȶÂȦÇĔËギクグケㇷㇻャヤヒパムሣሴሳቄችቼቖኪዕ";
    txt += "ÁÂÃÄÅÆΑΩ€";
    txt += "\u30A0\u30FF";  
    txt += "\u03FF\u03E8Ͽϼͽͼͻ";
    
    // ttx += "アァアィイゥウェエォオカガ";

    ttx = "€Think it your un\u00ADique\n designs\r\nevaluated. ÁÂÃÄÅÆΑΩ€";
    int margin = 100;

    boundingPath.lineTo(ofPoint(ofGetWidth()/2,margin));
    boundingPath.lineTo(ofPoint(ofGetWidth()-margin,ofGetHeight()-margin));
    boundingPath.lineTo(ofPoint(ofGetWidth()/2,ofGetHeight()/2+margin));
    boundingPath.lineTo(ofPoint(margin,ofGetHeight()-margin));
    boundingPath.scale(.5, .5);
    boundingPath.close();  
    boundingPath.setFilled(false);

    setupFonts();
    
    aScale = 1.0f;
    
}

//--------------------------------------------------------------
void testApp::setupFonts() {
    ofFont::Settings settings;
    
    settings.fontFilename = "Calibri.ttf";
    settings.fontSize = 50;
    settings.bAntiAliased = true;
    settings.bForceAutoHinting = false;
    settings.bUseKerning = true;
    settings.bMakePaths = true;

//    settings.characterSet.clear();
    settings.characterSet.addUnicodeBlock(0x30A0, 0x30FF); // Katakana
    settings.characterSet.addUnicodeBlock(0x0370, 0x03FF); // Greek
    settings.characterSet.addUnicodeBlock(0x2190, 0x21FF); // Arrows
    settings.characterSet.addUnicodeBlock(0x1200, 0x137F); // Ethiopic
    settings.characterSet.addUnicodeBlock(0x2100, 0x214F); // Letterlike Symbols
    
    //settings.characterSet.addUnicodeBlock(0x0400, 0x04FF);// : Cyrillic (256)
    settings.characterSet.addUnicodeBlock(0x3040, 0x309F);// : Hiragana (96)
    //settings.characterSet.addUnicodeBlock(0x2600, 0x26FF);// : Miscellaneous Symbols (256)
    
    ttf0.loadFont(settings);
    
    ////////
    
    settings.fontFilename = "Lucida Sans Unicode.ttf";//"FreeSerif.ttf";
    settings.fontSize = 50;
    settings.bAntiAliased = true;
    settings.bForceAutoHinting = false;
    settings.bUseKerning = true;
    
    ttf1.loadFont(settings);

    ////////
    
    settings.fontFilename = "verdana.ttf";
    settings.fontSize = 50;
    settings.bAntiAliased = true;
    settings.bForceAutoHinting = false;
    settings.bUseKerning = true;
    
    ttf2.loadFont(settings);
    
    ////////
    
    settings.fontFilename = "times.ttf";
    settings.fontSize = 50;
    settings.bAntiAliased = true;
    settings.bForceAutoHinting = false;
    settings.bUseKerning = true;
    
    ttf3.loadFont(settings);
    
    amperPath = ttf1.getGlyphPath((ofUniChar)'&');

    amperPath.scale(10,10);
    amperPath.setFilled(false);
    amperPath.translate(ofPoint(10,510));
    
    circlePath.arc(0,0,100,100,0,360);
//    circlePath.scale(10,10);
    circlePath.setFilled(false);
    circlePath.translate(ofPoint(10,510));

    
    
    frame = frameSetter.createFrame("This is a test.", amperPath);
    frame2 = frameSetter.createFrame("This is also a test", boundingPath);
    frame2 = frameSetter.createFrame("This is also a test", circlePath);

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofEnableAlphaBlending();
    
    ofBackground(0);
    
    int x = 400;
    int y = 100;
    int _x = x;
    int _y = y;

   // ofRectangle bb = ofRectangle(x,y,mouseX-x,mouseY-y);
    
    float lineHeight = ofMap(ofGetMouseX(), 0, ofGetWidth(), 2, 100); 
    
    frameRects = frameSetter.createLines(amperPath, lineHeight);
    frame2Rects = frameSetter.createLines(boundingPath, lineHeight);
    frame3Rects = frameSetter.createLines(circlePath, lineHeight);

    //bool in = amperPath.inside(ofGetMouseX(), ofGetMouseY());
    
    bool in = ofFrameSetter::isInsidePath(amperPath, ofPoint(ofGetMouseX(), ofGetMouseY())) ||
              ofFrameSetter::isInsidePath(boundingPath, ofPoint(ofGetMouseX(), ofGetMouseY()));
    
    if(in) {
        ofSetColor(0,255,0);
    } else {
        ofSetColor(255,0,0);
    }
    
    ofFill();
    ofEllipse(ofGetMouseX(), ofGetMouseY(), 20,20);
    
    ofNoFill();
    ofSetColor(255);
   // ttf0.drawString(txt,bb);
    
    //ttf0.texAtlas.draw(0,0);
    
   // ofPixels pix;
   // ttf0.texAtlas.readToPixels(pix);
    
    
    //cout << ttf0.texAtlas.getWidth() << "/" << ttf0.texAtlas.getHeight() << endl;
    
   // vector<int> chars = ttf0.settings.characterSet.getCharacterSet();
    
    ofPushMatrix();
    
    ofTranslate(ofGetMouseX(),ofGetMouseY());
    ofScale(aScale,aScale);
    
   // ofEnableAlphaBlending();
  //  ttf3.texAtlas.draw(100,100);
  
//    ttf3._drawChar('R', ofPoint(0,0),false);
//    ttf3._drawChar('R', ofPoint(20,20),true);

    //    drawCharTex(
    
    ttf3.drawChar((ofUniChar)0x20AC,ofPoint(0,0),true);
    ttf3.drawChar((ofUniChar)'&',ofPoint(20,0),false);
    ttf3.drawChar((ofUniChar)'&',ofPoint(40,0),true);
    
    ttf1.drawChar(ofTextConverter::toUnicode("Å")[0],ofPoint(80,0),true);
    
   // ofDisableAlphaBlending();
    
    ofPopMatrix();

    aScale += 0.001;
    aScale = aScale > 3 ? 1.0 : aScale;
    
    //ttf1.drawChar((ofUniChar)'R',ofPoint(ofGetMouseX(),ofGetMouseY()),true);
    
   // int s = ttf1.cps.size();
    
    ofPushMatrix();
   // ofTranslate(x,y);
    
    drawPathAndRects(amperPath,frameRects);
    
    ofTranslate(500,0);
    drawPathAndRects(boundingPath,frame2Rects);
    ofTranslate(200,0);
    drawPathAndRects(circlePath,frame3Rects);

    
    
    ofTranslate(100,100);
    
    //ofPolyline pp = ofFrameSetter::rectToPolyline(bb);
    //vector<ofRectangle> rectangles = ttf1.subdivideBoundingPolygon(boundingPolygon,ttf1.getLineHeight());

    ofEnableAlphaBlending();
    ofFill();
    int c = 10;
    int n = 0;
    int jj = 0;
    /*
    for(int i = 0; i < rectangles.size(); i++) {
        for(int j = 0; j < rectangles[i].size(); j++) {
            n = (n + 1) % c;
            ofSetColor(255 * n / (float)c,255 * n / (float)c,255,100);
            ofRect(rectangles[i][j]);
            jj++;
        }
    }
    */
   // cout << jj << endl;
    ofDisableAlphaBlending();

  
    
 //   ofTextBlock tb = ttf1.textLayout(txt, pp,true,false);

//    ofNoFill();
//    ofSetColor(255,255,255);
//    boundingPath.draw();
//    ofSetColor(255,0,0);
//    ofRect(ofFrameSetter::getBoundingBox(boundingPath));
    
    
    
    /*
    cout << "------------------------" << endl;
    cout << "Num lines=" << tb.size() << endl;
    for(int i = 0; i < (int)tb.size(); i++) {
        ofTextLine _line = tb[i];
        cout << "\tNum Fragments=" << _line.size() << endl;
        for(int j = 0; j < (int)_line.size(); j++) {
            ofTextFragment _frag = _line[j];
            cout << "\t\tNum Chars=" << _frag.size() << endl;
            for(int k = 0; k < (int) _frag.size(); k++) {
                ofCharacter _char = _frag[k];
                ofFill();
                ofSetColor(255);
                ttf1._drawChar(_char.props.characterIndex, _char.position,false);
            }
        }
    }*/
    
    ofPopMatrix();
    
//   ttf1.drawString(ttt);
    
    
   // string utf8String = convertToUTF8(input);
    
   // UTF8Encoding utf8;
   // TextIterator it(ttt, utf8);
   // TextIterator end(ttt);
    
   // TextIterator it2;
    
   // it2 = it;

   // ttf0.drawChar(*it,ofPoint(ofGetWidth()/2,ofGetHeight()/2));
    
    //ttf0.drawChar(*it,ofPoint(ofGetWidth()/2,ofGetHeight()/2+40));
    //ttf0.drawChar(*it,ofPoint(ofGetWidth()/2,ofGetHeight()/2+80));

    
    
    /*
    
   // cout << "ttt=" << ttt << endl;
    for (; it != end; ++it) { // multibyte character iteration
        int uc = *it;
       // cout << uc << endl;
       // if(uc == -1) cout << "got a -1" << endl;
        ttf0.drawChar(uc,ofPoint(_x,_y));
        _x+=30;
        if(_x > (ofGetWidth() - 40)) {_y+= 30; _x = x;};
    }
     */
     

    
/*
    for(int i = 880; i <= 0x03FF; i++) {
        ttf0.drawChar(i,ofPoint(_x,_y));
        _x+=30;
        if(_x > (ofGetWidth() - 40)) {_y+= 30; _x = x;};
    } 
    */
    
    //for(int i = 0; i < s/*chars.size()*/; i++) { 
    //   ttf1.drawChar(ttf1.cps[i].character/*chars[i]*/,ofPoint(_x,_y));
        //ttf1._drawChar(i,ofPoint(_x,_y));
    //    _x+=30;
    //    if(_x > (ofGetWidth() - 40)) {_y+= 30; _x = x;};
    //}
    
    ofNoFill();
    ofSetColor(255,255,0);
    //ofRect(bb);


    ofDisableAlphaBlending();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}