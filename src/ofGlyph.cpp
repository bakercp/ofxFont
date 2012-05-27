#include "ofGlyph.h"

//---------------------------------------------
//---------------------------------------------


//----------------------------------------------------------
ofGlyph::ofGlyph() {}
//----------------------------------------------------------
ofGlyph::~ofGlyph() {}

//----------------------------------------------------------
ofUniChar ofGlyph::getUnicode() {return unicode;}

//----------------------------------------------------------
ofUniCharGlyphIdx  ofGlyph::getGlyphIndex() {return glyphIndex;}

//----------------------------------------------------------
string ofGlyph::getGlyphName() {return glyphName;}

//----------------------------------------------------------
ofFont* ofGlyph::getFontRef()  {return font;}

//----------------------------------------------------------
float ofGlyph::getHeight()     {return height;}
//----------------------------------------------------------
float ofGlyph::getWidth()      {return width;}
//----------------------------------------------------------
float ofGlyph::getTopExtent()  {return topExtent;}
//----------------------------------------------------------
float ofGlyph::getLeftExtent() {return leftExtent;}

//----------------------------------------------------------
float ofGlyph::getHoriBearingX() {return horiBearingX;}
//----------------------------------------------------------
float ofGlyph::getHoriBearingY() {return horiBearingY;}
//----------------------------------------------------------
float ofGlyph::getHoriAdvance()  {return horiAdvance;}
// TODO: add warning if vert metrics are not reliable?
//----------------------------------------------------------
float ofGlyph::getVertBearingX() {return vertBearingX;}
//----------------------------------------------------------
float ofGlyph::getVertBearingY() {return vertBearingY;}
//----------------------------------------------------------
float ofGlyph::getVertAdvance()  {return vertAdvance;}

//----------------------------------------------------------
ofRectangle ofGlyph::getBoundingBox() {return boundingBox;}

// unicode information
//----------------------------------------------------------
bool ofGlyph::isSpace() {return bIsSpace;}
//----------------------------------------------------------
bool ofGlyph::isDigit() {return bIsDigit;}
//----------------------------------------------------------
bool ofGlyph::isPunct() {return bIsPunct;}
//----------------------------------------------------------
bool ofGlyph::isAlpha() {return bIsAlpha;}
//----------------------------------------------------------
bool ofGlyph::isLower() {return bIsLower;}
//----------------------------------------------------------
bool ofGlyph::isUpper() {return bIsUpper;}
