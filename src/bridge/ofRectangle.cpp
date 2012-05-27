#include "ofRectangle.h"

ofRectangle::ofRectangle (){ 
	x = y = width = height = 0.0f; 
}

ofRectangle::~ ofRectangle (){}

ofRectangle::ofRectangle (float _x, float _y, float _w, float _h){
	x = _x;
	y = _y;
	width = _w;
	height = _h;
}

ofRectangle::ofRectangle (ofPoint pos, float _w, float _h){
	x = pos.x;
	y = pos.y;
	width = _w;
	height = _h;
}

ofRectangle::ofRectangle (ofPoint p0, ofPoint p1) {
    x = p0.x;
    y = p0.y;
    width  = p1.x - p0.x;
    height = p1.y - p0.y;
}


ofRectangle::ofRectangle (ofRectangle const & r){
	x = r.x;
	y = r.y;
	width = r.width;
	height = r.height;
}

void ofRectangle::set (float px, float py, float w, float h){
	x		= px;
	y		= py;
	width	= w;
	height	= h;
}

void ofRectangle::set (ofPoint p0, ofPoint p1) {
    x = p0.x;
    y = p0.y;
    width  = p1.x - p0.x;
    height = p1.y - p0.y;
}

void ofRectangle::set (ofPoint pos, float w, float h){
    set(pos.x, pos.y, w, h);
}

void ofRectangle::set (ofRectangle const & rect){
    set(rect.x, rect.y, rect.width, rect.height);
}

void ofRectangle::setFromCenter (float px, float py, float w, float h){
	x		= px - w*0.5f;
	y		= py - h*0.5f;
	width	= w;
	height	= h;
}

void ofRectangle::setFromCenter (ofPoint pos, float w, float h){
    setFromCenter(pos.x, pos.y, w, h);
}

ofPoint ofRectangle::getCenter (){
	return ofPoint(x + width * 0.5f, y + height * 0.5f, 0);
}

bool ofRectangle::inside (float px, float py){
	return px > x && py > y && px < x + width && py < y + height;
}

bool ofRectangle::inside (ofPoint p){
	return inside(p.x, p.y);
}

bool ofRectangle::inside (float px, float py, float w, float h){
    return inside(px, py) && inside(px + w, py + h);
}

bool ofRectangle::inside (ofPoint p, float w, float h) {
    return inside(p.x, p.y, w, h);
}

bool ofRectangle::inside (ofRectangle const & r){
    return inside(r.x, r.y, r.width, r.height);
}

void ofRectangle::add (float px, float py){
    float x0 = MIN(x, px);
    float x1 = MAX(x + width, px);
    float y0 = MIN(y, py);
    float y1 = MAX(y + height, py);
    float _w = x1 - x0;
    float _h = y1 - y0;
    set(x0,y0,_w,_h);
}

void ofRectangle::add (ofPoint p){
    add(p.x, p.y);
}

void ofRectangle::add (float px, float py, float w, float h) {
    float x0 = MIN(x, px);
    float x1 = MAX(x + width, px + w);
    float y0 = MIN(y, py);
    float y1 = MAX(y + height, py + h);
    float _w = x1 - x0;
    float _h = y1 - y0;
    set(x0,y0,_w,_h);
}

void ofRectangle::add (ofPoint p, float w, float h) {
    add(p.x, p.y, w, h);
}

void ofRectangle::add (ofRectangle const & r){
    add(r.x, r.y, r.width, r.height);
}

ofPolyline ofRectangle::getAsPolyline() {
    ofPolyline polyline;
    polyline.addVertex(x,y);
    polyline.addVertex(x + width, y);
    polyline.addVertex(x + width, y + height);
    polyline.addVertex(x, y + height);
    polyline.close();
    return polyline;
}


ofPoint ofRectangle::getMin() {
    return ofPoint(getMinX(),getMinY());
}

ofPoint ofRectangle::getMax() {
    return ofPoint(getMaxX(),getMaxY());
}

float ofRectangle::getMinX() {
    return MIN(x, x + width);  // - width
}

float ofRectangle::getMaxX() {
    return MAX(x, x + width);  // - width
}

float ofRectangle::getMaxY() {
    return MIN(y, y + height);  // - height
}

float ofRectangle::getMinY() {
    return MAX(y, y + height);  // - height
}

ofRectangle & ofRectangle::operator = (ofRectangle const & rect){
	x = rect.x;
	y = rect.y;
	width = rect.width;
	height = rect.height;
	return *this;
}

ofRectangle & ofRectangle::operator + (const ofPoint & point){
	x += point.x;
	y += point.y;
	return *this;
}

bool ofRectangle::operator == (ofRectangle const & r){
	return (x == r.x) && (y == r.y) && (width == r.width) && (height == r.height);
}

bool ofRectangle::operator != (ofRectangle const & r){
	return (x != r.x) || (y != r.y) || (width != r.width) || (height != r.height);
}

