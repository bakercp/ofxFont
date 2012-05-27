/*

//-----------------------------------------------------------
ofRectangle ofLayoutManager::getStringBoundingBox(ofTextBlock textBlock, bool shrinkToContours) {
    
    //vector<ofCharacter>::iterator it = offsets.begin();
    
    // keep track of mins and maxs for bounding box
    // initialize to extremes for min/max calcs
    float minx, miny, maxx, maxy;
    miny = minx =  numeric_limits<float>::max();
    maxx = maxy = -numeric_limits<float>::max();
    
    // TODO
//     while(it != offsets.end()) {
//     
//     int character = (*it).c;
//     ofVec2f offset = (*it).offset;
//     int charIndex = charToIndex(character);
//     
//     if(shrinkToContours) {
//     minx = MIN(minx,(offset.x + glyphs[charIndex].x2)); // min x
//     miny = MIN(miny,(offset.y + glyphs[charIndex].y2)); // min y
//     maxx = MAX(maxx,(offset.x + glyphs[charIndex].x1)); // max x
//     maxy = MAX(maxy,(offset.y + glyphs[charIndex].y1)); // max y
//     } else {
//     minx = 0;
//     miny = 0;
//     maxx = MAX(maxx,offset.x + glyphs[charIndex].setWidth); // max x
//     maxy = MAX(maxy,offset.y + settings.fontSize);       // max y
//     }
//     
//     ++it;
//     }
    
    return ofRectangle(minx, miny, maxx-minx, maxy-miny);
}

//-----------------------------------------------------------
ofRectangle ofLayoutManager::getStringBoundingBox(string s, ofPoint p, bool shrinkToContours) {
    return getStringBoundingBox(s, p.x, p.y, shrinkToContours);
}

//-----------------------------------------------------------
ofRectangle ofLayoutManager::getStringBoundingBox(string s, float x, float y, bool shrinkToContours ){
//    
//    if ( s.empty() || glyphs.empty() ) return ofRectangle();
//    return getStringBoundingBox(getCharacterOffsets(s, x, y), shrinkToContours);
//    
//    
//     int         index	= 0;
//     float		X       = 0.0f;
//     float		Y       = 0.0f;
//     
//     int len = (int)s.length();
//     
//     while(index < len) {
//     int charIndex = charToIndex(s[index]);
//     
//     if(s[index] == '\n') {
//     Y += lineHeight; // go to next row
//     X = 0.0f; //reset X Pos back to zero
//     } else if(isInCharacterSet(s[index])) {
//     // draw the character
//     
//     if(skrinkToContours) {
//     minx = MIN(minx,(X + glyphs[charIndex].x2)); // min x
//     miny = MIN(miny,(Y + glyphs[charIndex].y2)); // min y
//     maxx = MAX(maxx,(X + glyphs[charIndex].x1)); // max x
//     maxy = MAX(maxy,(Y + glyphs[charIndex].y1)); // max y
//     } else {
//     minx = 0;
//     miny = 0;
//     maxx = MAX(maxx,X + glyphs[charIndex].setWidth); // max x
//     maxy = MAX(maxy,Y + settings.fontSize);       // max y
//     }
//     
//     // calculate horizontal scaling 
//     float xScale = letterSpacing;            // respect existing letter spacing scaler
//     if(s[index] == ' ') xScale *= spaceSize; // respect existing space char scaler
//     
//     // advance the cursor
//     X += (glyphs[charIndex].setWidth * xScale);
//     
//     // adjust the cursor for kerning if needed
//     if(bHasKerning && ((index + 1) < len) && s[index+1] != '\n') {
//     X += getKerning(s[index], s[index+1]).x;
//     }
//     } else {
//     // unknown character
//     }
//     
//     index++;
//     }
}


//-----------------------------------------------------------
float ofLayoutManager::stringHeight(string s) {
    ofRectangle rect = getStringBoundingBox(s, 0,0);
    return rect.height;
}

ofTextBlock ofLayoutManager::drawString(string s, float x, float y, float w, float h, bool asShapes) {
    ofRectangle boundingBox(x,y,w,h);
    return textLayout(s, boundingBox, true, asShapes);
}

//=====================================================================
ofTextBlock ofLayoutManager::drawString(string s, ofRectangle boundingBox, bool asShapes) {
    return textLayout(s, boundingBox, true, asShapes);
}


//=====================================================================
void ofLayoutManager::drawString(ofTextBlock textBlock, ofVec2f offset, bool asShapes) {
    ofPushMatrix();
    ofTranslate(offset);
    
    // enable binding for the group
    bool alreadyBinded = binded;
    if(!alreadyBinded) bind();
    
    //for(int i = 0; i < (int)offsets.size(); i++) {
    //    _drawChar(offsets[i].c, offsets[i].offset, asShapes);
    //}
    
    if(!alreadyBinded) unbind();
    
    ofPopMatrix();
}



//=====================================================================
ofTextBlock ofLayoutManager::drawStringAsShapes(string s, float x, float y, float w, float h) {
    ofRectangle boundingBox(x,y,w,h);
    return textLayout(s, boundingBox, true, true);
}

//=====================================================================
ofTextBlock ofLayoutManager::drawStringAsShapes(string s, ofRectangle boundingBox) {
    return textLayout(s, boundingBox, true, true);
}

//=====================================================================
void ofLayoutManager::drawStringAsShapes(ofTextBlock textBlock, ofVec2f offset) {
    drawString(textBlock,offset,true);
}

//=====================================================================
void ofLayoutManager::_drawChar(int characterIndex, ofPoint p, bool asShapes) {
    
    if(Poco::Unicode::isSpace(glyphs[characterIndex].character)) {
        // we don't render spaces, but they are in the charset
        return;
    }
    
    // bind here if needed
    
    if(asShapes) {
        glyphs[characterIndex].path.setFilled(ofGetStyle().bFill);
        glyphs[characterIndex].path.draw(p);
    } else {
        bool alreadyBinded = binded;
        if(!alreadyBinded) bind();
        
        float	x1, y1, x2, y2;
        float   t1, v1, t2, v2;
        t2		= glyphs[characterIndex].t2;
        v2		= glyphs[characterIndex].v2;
        t1		= glyphs[characterIndex].t1;
        v1		= glyphs[characterIndex].v1;
        
        x1		= glyphs[characterIndex].x1+p.x;
        y1		= glyphs[characterIndex].y1+p.y;
        x2		= glyphs[characterIndex].x2+p.x;
        y2		= glyphs[characterIndex].y2+p.y;
        
        int firstIndex = stringQuads.getVertices().size();
        
        stringQuads.addVertex(ofVec3f(x1,y1));
        stringQuads.addVertex(ofVec3f(x2,y1));
        stringQuads.addVertex(ofVec3f(x2,y2));
        stringQuads.addVertex(ofVec3f(x1,y2));
        
        stringQuads.addTexCoord(ofVec2f(t1,v1));
        stringQuads.addTexCoord(ofVec2f(t2,v1));
        stringQuads.addTexCoord(ofVec2f(t2,v2));
        stringQuads.addTexCoord(ofVec2f(t1,v2));
        
        stringQuads.addIndex(firstIndex);
        stringQuads.addIndex(firstIndex+1);
        stringQuads.addIndex(firstIndex+2);
        stringQuads.addIndex(firstIndex+2);
        stringQuads.addIndex(firstIndex+3);
        stringQuads.addIndex(firstIndex);
        
        if(!alreadyBinded) unbind();
        
    }
}

//-----------------------------------------------------------
ofTextBlock  ofLayoutManager::textLayout(string input, 
                                ofRectangle bb,
                                bool draw,
                                bool drawShapes) {
    return textLayout(input,bb.getAsPolyline(),draw,drawShapes);
}

ofTextBlock  ofLayoutManager::textLayout(string input, 
                                ofPolyline bb,
                                bool draw,
                                bool drawShapes) {
    
    if(!bb.isClosed()) {
        // render as a line
    }
    
    
    ofCharacter    textCharacter;
    ofTextFragment textFragment;
    ofTextLine     textLine;
	ofTextBlock    textBlock;
    
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofFont::drawString - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    	return textBlock;
    }
    
	if (drawShapes && !bHasContours){
		ofLog(OF_LOG_ERROR,"ofFont::drawStringAsShapes - Error : contours not created for this font - call loadFont with makeContours set to true");
		return textBlock;
	}
    
    ofTextAlignHorz hAlign = ofGetTextAlignHorz();
    ofTextAlignVert vAlign = ofGetTextAlignVert();
    
    // bind as a group of textures if we are drawing
    bool alreadyBinded = binded;
    if(draw && !drawShapes && !alreadyBinded) bind();
    
    vector<ofRectangle> textLineBoxes = subdivideBoundingPolygon(bb,getLineHeight());
    vector< ofRectangle > currentRectLine;
    ofRectangle currentRectangle;
    ofRectangle nextRectangle;
    int currentRectLineIdx = 0;
    int currentRectIdx = 0;
//    
//     if(textLineBoxes.size() > 0) {
//     currentRectLine = textLineBoxes[currentRectLineIdx];
//     if(currentRectLine.size() > 0) {
//     currentRectangle = currentRectLine[currentRectIdx];
//     } else {
//     ofLog(OF_LOG_ERROR,"ofFont::No room.");
//     return textBlock;
//     }
//     } else {
//     ofLog(OF_LOG_ERROR,"ofFont::No room.");
//     return textBlock;
//     }
//     
    float currentLineMinX = currentRectangle.x;
    float currentLineMaxX = currentRectangle.x + currentRectangle.width;
    
    float currentLineWidth = currentLineMaxX  - currentLineMinX;
    
    float lineMinY = currentRectangle.y;
    float lineMaxY = currentRectangle.y + currentRectangle.height;
    
    // word wrapping!
	float		currentX       = currentLineMinX; // current x // will adjust all offsets
	float		currentY       = lineMinY;        // current y // will adjust all offsets
    
    //int len = (int)s.length();
    
    bool    isCharBreakMode = false;// (lineBreakMode == LINE_BREAK_MODE_NONE ||
    //lineBreakMode == LINE_BREAK_MODE_CHARACTER);
    
    // must make sure that the input string is in UTF-8 format
    string utf8String = convertToUTF8(input);
    
    // multibyte character iteration
    Poco::UTF8Encoding utf8;
    Poco::TextIterator begin(utf8String, utf8);
    Poco::TextIterator iter(utf8String, utf8);
    Poco::TextIterator end(utf8String);
    
    Poco::TextIterator lookAheadIter;
    
    int   lastChar          = -1;
    int   lastCharIdx       = -1;
//    
//     float lastCharWidth     =  0;
//     float lastCharKerning   =  0;
//        
    bool  isLastCharSpace   = false;
    bool  isLastCharNewLine = false;
    bool  hasLastChar       = false;
    ofCharacter lastOfChar;
    
    int   thisChar          = -1;
    int   thisCharIdx       = -1;
    float thisCharWidth     =  0;
    float thisCharKerning   =  0;
    bool  isThisCharSpace   = false;
    bool  isThisCharNewLine = false;
    bool  hasThisChar       = false;
    ofCharacter thisOfChar;
    
    bool isFirstCharInFragment = true;
    bool isFirstCharInLine     = true;
    bool isFirstCharInBlock    = true;
    
    // iterate through the UTF-8 characters
    while (iter != end) {
        
        // set the current items
        thisChar = *iter; // get the first UTF-8 character
        
        //cout << ">" << thisChar << "-" << (char)thisChar << endl;
        
        // determine if this is a new line control character
        if(thisChar == '\r') { // CARRIAGE RETURN, CR, \r
            lookAheadIter = iter; // get a look ahead iterator, without losing our place
            if(*(++lookAheadIter) == '\n') { // peek at the next character
                iter++; // advance, ignoring the \r
                continue; // skip processing the \r
            } else {
                isThisCharNewLine = true; // was just an \r, so process as new line 
            }
        } else {
            isThisCharNewLine = (thisChar == '\n'   || // \x000A (\n) (LINE FEED)
                                 thisChar == '\v'   || // \x000B (\v) (VERT TAB)
                                 thisChar == '\f'   || // \x000C (\f) (FORM FEED)
                                 // thisChar == 0x0085 || // \x0085 NEL // Poco::TextIterator does not handle this 
                                 thisChar == 0x2028 || // \x2028 (LINE SEPARATOR)
                                 thisChar == 0x2029);  // \x2029 (PARAGRAP SEPERATOR)
            // list of standard Unicode newline chars http://unicode.org/reports/tr18/
        }
        
        isFirstCharInLine     = (textLine.empty());
        
        thisCharIdx      = !isThisCharNewLine ? charToIndex(thisChar) : CHAR_INDEX_NOT_FOUND; 
        // get the character's index in our glyph set
        // short circuit newline chars for blazing for speed.
        
        bool  canBreak = false;
        float charOffsetX = 0;
        float proposedLineEndX = currentX;
        
        
        // TODO -- deal with unknown characters gracefully -- like 0x0085
        if(thisCharIdx != CHAR_INDEX_NOT_FOUND) {
            // this is a drawable character
            
            isThisCharSpace   = Poco::Unicode::isSpace(thisChar); // is this a space
            
            thisOfChar        = ofCharacter();              // clear the char
            thisOfChar.props  = glyphs[thisCharIdx];           // set the properties from the glyph set
            thisCharWidth     = _widthChar(thisCharIdx);    // find the width (w/ horz scaling)
            
            thisCharKerning   = 0.0f;
            if(!isFirstCharInLine && hasLastChar) {
                thisCharKerning = _getKerning(lastCharIdx, thisCharIdx).x; // get kerning from last char
            }
            
            ///////////////////////////////
            
            // we can consider breaking if it is not the very first char OR is a white space.
            // make this more complicated later with soft hyphens (&shy), etc
            canBreak = !isFirstCharInBlock && !isThisCharSpace;
            
            // now determine the total X displacement that will occur because of this character
            charOffsetX = thisCharKerning + thisCharWidth; // kerning adjustment from last character
            
            // what will be the total width of this line if we add this character to the line?
            proposedLineEndX = (currentX + charOffsetX);
        }
        
        bool justMadeNewLine = false;
        
        // we can break if we found a new line
        if(isThisCharNewLine || (canBreak && proposedLineEndX > currentLineMaxX)) {
            // what to do with a new line
            
            float currentFragmentStartX = textFragment.empty() ? currentLineMinX : textFragment[0].position.x;
            float currentFragmentWidth = proposedLineEndX - currentFragmentStartX;
            
            //int currentRectLineIdx = 0;
            //int currentRectIdx = 0;
            
            
//             currentRectIdx++;
//             if(currentRectIdx < currentRectLine.size()) {
//             nextRectangle = currentRectLine[currentRectIdx];
//             } else {
//             currentRectLineIdx++;
//             if(currentRectLineIdx < textLineBoxes.size()) {
//             currentRectLine = textLineBoxes[currentRectLineIdx];
//             currentRectIdx = 0;
//             if(currentRectIdx < currentRectLine.size()) {
//             nextRectangle = currentRectLine[currentRectIdx];
//             } else {
//             break;
//             cout << "finished." << endl;
//             }
//             } else {
//             break;
//             cout << "finished." << endl;
//             }
//             }
//            
            // calculate the next line's properties
            float nextY         = nextRectangle.y;
            
            float nextLineMinX  = nextRectangle.x;
            float nextLineMaxX  = nextRectangle.x + nextRectangle.width;
            float nextLineWidth = nextLineMaxX - nextLineMinX;
            ///////
            
            justMadeNewLine = true;
            
            if(!isThisCharNewLine && // don't do adjustments on a new line
               !textFragment.empty() && // don't do adjustments on a single char fragment
               currentFragmentWidth <= currentLineWidth // don't do adjustments when the word won't even fit on the next line
               ) {
                
                float offset = currentFragmentStartX - nextLineMinX;
                
                for(int k = 0; k < (int)textFragment.size(); k++) {
                    textFragment[k].position.x -= offset ;
                    textFragment[k].position.y = nextY;
                }
                
                currentX -= offset;
                
            } else {
                currentX = currentLineMinX;
            }   
            
            currentY = nextY; // we need to do this when the next line is at same Y, but different X
            currentLineMinX = nextLineMinX;
            currentLineMaxX = nextLineMaxX;
            currentLineWidth = nextLineWidth;
            currentRectangle = nextRectangle;
        }
        
        if(currentY > lineMaxY) {
            break; // we are done
        }
        
        
        // should create new current line?
        
        if(justMadeNewLine) {
            textLine.push_back(textFragment); // add the current fragment to the last line
            textFragment.clear(); // clear the fragment
            
            textBlock.push_back(textLine); // add the current line to the text block
            textLine.clear(); // clear the current line
        }
        
        if(isThisCharSpace && !isLastCharSpace) {
            textLine.push_back(textFragment); // add the current fragment to the last line
            textFragment.clear(); // clear the fragment
        }
        
        if(!isThisCharSpace && !isThisCharNewLine) { // we don't store spaces or new lines
            thisOfChar.position.set(currentX,currentY);
            textFragment.push_back(thisOfChar);
        }
        
        currentX += charOffsetX;
        
        // set the last items
        lastChar            = thisChar;
        lastCharIdx         = thisCharIdx;
        //lastCharWidth       = thisCharWidth;
        //lastCharKerning     = thisCharKerning;
        isLastCharSpace     = isThisCharSpace;
        isThisCharNewLine   = isThisCharNewLine;
        
        isFirstCharInBlock    = false; // is this the first character in the block?
        
        
        iter++; // move the iterator
        //currentChar++; // count the current character
        
        
    }
    
    // push the text fragment an line ont the block
    textLine.push_back(textFragment);
    textBlock.push_back(textLine); 
    
    
    // DRAW IT HERE
    
    
    //cout << "lines found = " << textBlock.size() << endl;
    
    
    
    if(draw) {
        
        for(int i = 0; i < (int)textBlock.size(); i++) {
            ofTextLine _line = textBlock[i];
            
            float lineMinX = 0;
            float lineMaxX = 0;
            
            for(int j = 0; j < (int)_line.size(); j++) {
                ofTextFragment _frag = _line[j];
                
                for(int k = 0; k < (int) _frag.size(); k++) {
                    ofCharacter _char = _frag[k];
                    
                    switch (hAlign) {
                        case OF_TEXT_ALIGN_HORZ_LEFT:
                            // do nothing.  this is default
                            // // // // //  // / // // // /
                            break;
                        case OF_TEXT_ALIGN_HORZ_RIGHT:
                            //   _frag[k].position += 
                            break;
                        case OF_TEXT_ALIGN_HORZ_CENTER:
                            
                            break;
                        case OF_TEXT_ALIGN_HORZ_JUSTIFIED:
                            // uh, wait a minute
                            break;
                            break;
                            
                        default:
                            break;
                    }
                    
                    
                    
                    
                    
                    
                    // ofCharacter _char = _frag[k];
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    ofFill();
                    ofSetColor(255);
                    _drawChar(_char.props.characterIndex, _char.position, drawShapes);
                }
            }
        }
    }
    
    // release textures if we previously bound them
    if(draw && !drawShapes && !alreadyBinded) unbind();
    
    return textBlock;
}

//------------------------------------------------------------------
ofPath ofLayoutManager::getCharacterAsPoints(int character, float x, float y){
    return getCharacterAsPoints(character, ofPoint(x,y));
}

//------------------------------------------------------------------
ofPath ofLayoutManager::getCharacterAsPoints(int character, ofPoint p){
	ofPath path;
    
    if(bHasContours == false ){
		ofLog(OF_LOG_ERROR, "getCharacterAsPoints: contours not created,  call loadFont with makeContours set to true" );
        return path;
	}
    
    int charIndex = charToIndex(character);
    
    if(charIndex == CHAR_INDEX_NOT_FOUND) {
		ofLog(OF_LOG_WARNING, "getCharacterAsPoints: character not in charset allocated." );
        return path;
    }
    
    path = glyphs[charIndex].path;
    path.translate(p); 
    return path;
}

//-----------------------------------------------------------
ofCharacter ofLayoutManager::drawChar(int character, float x, float y, bool asShapes) {
    
    ofCharacter co;
    int charIndex = charToIndex(character);
    
    if(charIndex == CHAR_INDEX_NOT_FOUND) {
		ofLog(OF_LOG_WARNING, "drawChar: >" + ofToString(character) + "< character not in charset allocated." );
        return co;
    }
    
    bool alreadyBinded = binded;
    if(!alreadyBinded) bind();
    
    ofPoint p(x,y,0);
    
    ofTextAlignHorz hAlign = ofGetTextAlignHorz();
    ofTextAlignVert vAlign = ofGetTextAlignVert();
    
    // no adjustments if hAlign -> left and vAlign -> baseline
    
    // make horizontal adjustments
    if (hAlign == OF_TEXT_ALIGN_HORZ_CENTER) {
        p.x -= _widthChar(charIndex) / 2.0f;
    } else if (hAlign == OF_TEXT_ALIGN_HORZ_RIGHT) {
        p.x -= _widthChar(charIndex);
    }
    
    // make vertical adjustments
    if (vAlign == OF_TEXT_ALIGN_VERT_CENTER) {
        p.y += getAscender() / 2;
    } else if (vAlign == OF_TEXT_ALIGN_VERT_TOP) {
        p.y += getAscender();
    } else if (vAlign == OF_TEXT_ALIGN_VERT_BOTTOM) {
        p.y -= getDescender();
    }
    
    // render
    _drawChar(charIndex, p, asShapes);
    
    // record and return actual offsets
    co.props = glyphs[charIndex];
    co.position = p;
    co.scale.set(1,1,1);
    co.rotation.set(0,0,0);
    
    if(!alreadyBinded) unbind();
    
    return co; 
    
}

//-----------------------------------------------------------
ofCharacter ofFont::drawChar(int character, ofPoint p, bool asShapes) {
    return drawChar(character,p.x,p.y,asShapes);
}

//-----------------------------------------------------------
ofCharacter ofFont::drawCharAsShapes(int character, float x, float y) {
    return drawChar(character, x, y, true);
}

//-----------------------------------------------------------
ofCharacter ofFont::drawCharAsShapes(int character, ofPoint p) {
    return drawChar(character, p.x, p.y, true);
}


//-----------------------------------------------------------
ofTextBlock ofFont::getStringAsPoints(string s, float x, float y, float w, float h) {
    ofRectangle boundingBox(x,y,w,h);
    return getStringAsPoints(s,boundingBox);
}

//-----------------------------------------------------------
ofTextBlock ofFont::getStringAsPoints(string s, ofRectangle boundingBox) {
    
	ofTextBlock shapes;
    
	if (!bLoadedOk){
		ofLog(OF_LOG_ERROR,"Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
		return shapes;
	};
    
    ofTextBlock offsets = getCharacterOffsets(s, boundingBox);
    
    // TODO
    //for(int i = 0; i < (int)offsets.size(); i++) {
    //    shapes.push_back(getCharacterAsPoints(s[i]));
    //    shapes.back().path.translate(offsets[i].offset);
    //}
    
	return shapes;
}

//-----------------------------------------------------------
ofTextBlock  ofFont::getCharacterOffsets(string s, float x, float y, float w, float h) {
    ofRectangle boundingBox(x,y,w,h);
    return getCharacterOffsets(s, boundingBox);
}

//-----------------------------------------------------------
ofTextBlock  ofFont::getCharacterOffsets(string s, ofRectangle boundingBox) {
    return textLayout(s, boundingBox, false, false);
}

*/
