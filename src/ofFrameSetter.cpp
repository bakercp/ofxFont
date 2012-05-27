//
//  ofTextTypesetter.h
//  openFrameworksLib
//
//  Created by Christopher Baker on 4/22/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#include "ofFrameSetter.h"

ofFrameSetter::Settings::Settings() {
    none = -1;    
}


vector<ofRectangle> ofFrameSetter::splitLines(ofPath& boundingPath, ofRectangle& testRect) {
    
}

ofRectangle ofFrameSetter::addRectToRect(const ofRectangle& rect,const ofRectangle& rect1) {
    float x0 = MIN(rect.x, rect1.x);
    float x1 = MAX(rect.x + rect.width, rect1.x + rect.width);
    float y0 = MIN(rect.y, rect1.y);
    float y1 = MAX(rect.y + rect.height, rect1.y + rect.height);
    float _w = x1 - x0;
    float _h = y1 - y0;
    return ofRectangle(x0,y0,_w,_h);
}

ofPolyline ofFrameSetter::rectToPolyline(ofRectangle rect) {
    ofPolyline polyline;
    polyline.addVertex(rect.x,rect.y);
    polyline.addVertex(rect.x + rect.width, rect.y);
    polyline.addVertex(rect.x + rect.width, rect.y + rect.height);
    polyline.addVertex(rect.x, rect.y + rect.height);
    polyline.close();
    return polyline;

}

bool ofFrameSetter::isInsidePath(ofPath path, ofPoint p) {
    
    // THIS IS AN ESTIMATE based on the poly line.
    // certainly more accurate ways to do when mode==PATHS
    // this is a simple extension of the polyline crossing algorithm
    // using ray casting across polys, including holes
    // TODO: account for winding?
    vector<ofPolyline> polys = path.getOutline();
    
    int count = 0;
    for(int i = 0; i < polys.size(); i++) {
        count +=  polys[i].inside(p.x,p.y) ? 1 : 0;
    }
    return count % 2;

}
ofRectangle ofFrameSetter::getBoundingBox(ofPath& path) {
    vector<ofPolyline> lines = path.getOutline();
    ofRectangle bb;
    for(int i = 0; i < lines.size(); i++) {
        ofRectangle thisBB = lines[i].getBoundingBox();
        if(i == 0) { 
            bb = thisBB;
        } else {
            bb = addRectToRect(bb,lines[i].getBoundingBox());
        }
    }
    return bb;
}


vector<ofRectangle> ofFrameSetter::createLines(ofPath& path, float lineHeight, ofTextFrameProgression tfp) {
    
    vector<ofRectangle> rectangleBlock;
    ofRectangle bb = getBoundingBox(path);
    
    
    if(tfp == OF_TEXT_FRAME_PROGRESS_RIGHTTOLEFT) {
        
        int numLines = (int)(bb.height / lineHeight) + 1;
        
        float lastY, thisY;
        ofLineSegment thisLine, lastLine;
        vector<ofLineSegment> thisLineSegments, lastLineSegments;
        
        float epsilon = 0.001f; // the amount of pixels to overshoot the bounding box
        
        for(int i = 0; i < numLines; i++) {
            thisY     = bb.y + epsilon + (i * lineHeight); // epsilon here prevents line coincidence for rect top line
            
            thisLine.p0 = ofPoint(bb.x-epsilon,thisY);
            thisLine.p1 = ofPoint(bb.x + bb.width + epsilon,thisY);
            thisLineSegments = clipLineToPath(path,thisLine);
            
            if(i != 0) { // skip the first line
                
                for(int j = 0; j < thisLineSegments.size(); j++) {
                    
                    ofLineSegment ll = thisLineSegments[j]; // lower line segment
                    
                    // cycle through all line segments in the last line
                    for(int k = 0; k < lastLineSegments.size(); k++) {
                        
                        ofLineSegment ul = lastLineSegments[k]; // upper line segment
                        
                        // short circuit cases for blazing speed.
                        if(ul.p0.x > ll.p1.x) {
                            break;
                        } else if(ul.p1.x < ll.p0.x) {
                            continue;
                        }
                        
                        ofPoint p;
                        
                        ofPoint xtp0 = ofPoint(ll.p0.x,bb.y-epsilon);
                        ofPoint xtp1 = ofPoint(ll.p1.x,bb.y-epsilon);
                        ofPoint xlp0 = ofPoint(ul.p0.x,bb.y+bb.height+epsilon);
                        ofPoint xlp1 = ofPoint(ul.p1.x,bb.y+bb.height+epsilon);

                       
                        // intersect upwards
                        bool X_tp0 = ofLineSegmentIntersection(ll.p0,xtp0,ul.p0,ul.p1,p);
                        bool X_tp1 = ofLineSegmentIntersection(ll.p1,xtp1,ul.p0,ul.p1,p);
                        
                        // intersect downwards
                        bool X_lp0 = ofLineSegmentIntersection(ul.p0,xlp0,ll.p0,ll.p1,p);
                        bool X_lp1 = ofLineSegmentIntersection(ul.p1,xlp1,ll.p0,ll.p1,p);
                        
                        // TODO: fix this algo in the ofLineSegment class ...
                        
//                        // intersection issue when line is coincident https://skitch.com/bakercp/8apmg/skitched-20120502-134532
//                        // intersect upwards ( could use static ofLineSegmentIntersection in ofMath.h )
//                        bool X_tp0 = ofLineSegment::ofLineIntersects(ofLineSegment(ll.p0,xtp0),ofLineSegment(ul.p0,ul.p1),p);
//                        bool X_tp1 = ofLineSegment::ofLineIntersects(ofLineSegment(ll.p1,xtp1),ofLineSegment(ul.p0,ul.p1),p);
//                        
//                        // intersect downwards
//                        bool X_lp0 = ofLineSegment::ofLineIntersects(ofLineSegment(ul.p0,xlp0),ofLineSegment(ll.p0,ll.p1),p);
//                        bool X_lp1 = ofLineSegment::ofLineIntersects(ofLineSegment(ul.p1,xlp1),ofLineSegment(ll.p0,ll.p1),p);
//                        
//                        ofPoint pp;
//                        bool X_lp0A = ofLineSegmentIntersection(ul.p0,xlp0,ll.p0,ll.p1,pp);

                        
                        
                        // check for rectangles
                        if(X_tp0) {
                            ofRectangle rect(ll.p0.x,lastY,0,lineHeight);
                            if(X_tp1) {
                                rect.width = ll.p1.x-ll.p0.x;
//                                if(rect.width <= 0) cout << "11" << endl; 
                                    rectangleBlock.push_back(rect);
                            } else if(X_lp0) {
                                rect.width = ul.p0.x-ll.p0.x;
//                                if(rect.width <= 0) cout << "22" << endl; 
//                                if(rect.width == 0) {
//                                    cout << "22!!>" << pp << "<>" << p << endl;
//                                } 
                                    rectangleBlock.push_back(rect);
                            } else if(X_lp1) {
                                rect.width = ul.p1.x-ll.p0.x;
//                                if(rect.width <= 0) cout << "33" << endl; 
                                rectangleBlock.push_back(rect);
                            }
                        } else if(X_tp1) {
                            ofRectangle rect(ll.p1.x,lastY,0,lineHeight);
                            if(X_lp0) {
                                rect.width = ul.p0.x-ll.p1.x;
//                                if(rect.width <= 0) cout << "44" << endl; 
                                rectangleBlock.push_back(rect);
                            } else if(X_lp1) {
                                rect.width = ul.p1.x-ul.p1.x;
//                                if(rect.width <= 0) cout << "55" << endl; 
                                rectangleBlock.push_back(rect);
                            }
                        } else if(X_lp0) {
                            ofRectangle rect(ul.p0.x,lastY,0,lineHeight);
                            if(X_lp1) {
                                rect.width = ul.p1.x-ul.p0.x;
//                                if(rect.width <= 0) cout << "66" << endl; 
                                rectangleBlock.push_back(rect);
                            }
                        }
                    }
                }
            }
            
            lastY             = thisY;
            lastLine          = thisLine;
            lastLineSegments  = thisLineSegments;
            
        }
        
        return rectangleBlock;
        
    } else if(tfp == OF_TEXT_FRAME_PROGRESS_TOPTOBOTTOM) {
        ofLog(OF_LOG_ERROR, "ofFrameSetter::createLines : Not implemented.");
    } else {
        ofLog(OF_LOG_ERROR, "ofFrameSetter::createLines : unknown ofTextFrameProgression value.");
    }
}

//-----------------------------------------------------------

vector< ofLineSegment > ofFrameSetter::clipLineToPath(ofPath& path, const ofLineSegment& line) {
    
    vector<ofPoint> intersections;
    
    intersections.push_back(line.p0); // add the first point to the beginning
    
    // get a list of the poly verts
    vector<ofPolyline> polys = path.getOutline();
    
    for(int k = 0; k < polys.size(); k++) {
        vector<ofPoint> verts = polys[k].getVertices();
        for(int i = 0; i < verts.size(); i++) {
            int nextI = i != (verts.size() - 1) ? i + 1 : 0;
            ofPoint intersection;
            if(ofLineSegmentIntersection(verts[i], verts[nextI],line.p0,line.p1,intersection)) {
                // cycle through and insert at appropriate distance from intersections[0];
                float dist = intersection.distance(intersections[0]); // distance to origin
                bool didInsert = false;
                
                // order the intersection points along the line, between the ends
                // several ways to do this. distance may not be the quickest
                // http://local.wasp.uwa.edu.au/~pbourke/geometry/cliplinetopoly/
                for(int j = 1; j < intersections.size(); j++) {
                    if(intersections[j].distance(intersections[0]) > dist) {
                        intersections.insert(intersections.begin() + j, intersection);
                        didInsert = true;
                        break;
                    }
                }    
                
                if(!didInsert) {
                    intersections.push_back(intersection); // if required, add it on the end   
                }
            } 
        }
    }
    
    intersections.push_back(line.p1); // add the last point on the end
    
    vector<ofLineSegment> insideLines;
    
    // if line midpoint is inside, then we assume it is inside
    for(int i = 1; i < (int)intersections.size(); i++) {
        if(isInsidePath(path,intersections[i-1].getMiddle(intersections[i]))){
            ofLineSegment thisLine(intersections[i-1],intersections[i]);
            insideLines.push_back(thisLine);
        }
    }
    
    return insideLines;
}
