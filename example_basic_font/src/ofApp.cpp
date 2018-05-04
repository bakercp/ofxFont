//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//

#include "ofApp.h"


void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    auto& cache = ofxText::FTFontCache::instance();

    std::cout << ofxText::FontManager::findFont().toJSON().dump(4) << std::endl;
    
    
    //    emojiTest();
    //    textTest();
}


void ofApp::draw()
{
    ofBackground(0);
    ofEnableAlphaBlending();

    ofSetColor(255, 255, 0);
    ofDrawRectangle(ofGetMouseX(), ofGetMouseY(), 40, 40);

    ofSetColor(255);
}


//void ofApp::fontMangerTest()
//{
//}
//
//
//void ofApp::emojiTest()
//{
//    // 1. Get a reference to the FTFontCache.
//    auto& cache = ofxText::FTFontCache::instance();
//    auto fontPath = "Roboto-Regular.ttf";
//
////    // We can get an FT_Face from the cache. The FT_Face is owned by the cache.
////    ofxText::FTFaceId* pFaceId_0 = cache.getFaceIdForPathAndFaceIndex(fontPath, 0);
////
////    assert(pFaceId_0 != nullptr);
////    std::cout << pFaceId_0->first << ", " << pFaceId_0->second << std::endl;
////
////    // We don't have a default font, so we pass an empty string.
////    ofxText::FontDescriptor fd_0;
////    fd_0.path = fontPath;
////
////    // We can get an FT_Face from the cache. The FT_Face is owned by the cache.
////    ofxText::FTFaceId* pFaceId_1 = cache.getFaceIdForFontDescriptor(fd_0);
////    assert(pFaceId_1 != nullptr);
////    std::cout << pFaceId_1->first << ", " << pFaceId_1->second << std::endl;
////
////    // Make sure they point to the same thing.
////    assert(pFaceId_0 == pFaceId_1);
////
////    // We can get an FT_Face from the cache. The FT_Face is owned by the cache.
////    FT_Face face_0 = cache.getFaceForFontDescriptor(fd_0);
////    assert(face_0 != nullptr);
////
////    std::cout << face_0->family_name << std::endl;
////
////    ofxText::FTFontSettings settings_0(fd_0, 42);
////
////    FT_Size size_0 = cache.getSizeForFontSettings(settings_0);
////
////    const char* text = "h";
////
////    assert(face_0 == size_0->face);
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//    //= ofxText::FontManager::substituteFont("","😃😇😍😜");
//
//
//
//
//    // We can get an FT_Face from the cache. The FT_Face is owned by the cache.
////    FT_Face face = cache.getFaceForFontDescriptor(fd);
////
////    if (face)
////    {
////        std::cout << face->family_name << std::endl;
////    }
//
//
//
////    /// Step 6. Get the glyph for the single codepoint.
//////    const ofxFontGlyph* glyph = font->getGlyphByCodePoint(txt[0]);
////
////    /// Step 7. Query various aspects of the glyph.
//////    std::cout << glyph->toString() << std::endl;
////
////    std::cout << "0. -----------------------" << std::endl;
////    FT_Face face = cache.getFTFace(font);
////    std::cout << "1. -----------------------" << std::endl;
////
////    FT_Size size = cache.getFTSize(font);
////    std::cout << "2. -----------------------" << std::endl;
//
//
////
//    /// Step 8. Get a copy of the glyph pixels.
////    ofPixels pixels = cache.getBitmapForGlyph(glyph);
////
////    ofSaveImage(pixels, "out.png");
////
//////    std::string codePoints = "😃😇😍😜😸🙈🐺🐰👽🐉💰🏡🎅🍪🍕🚀🚻💩📷📦1⃣2⃣3⃣4⃣5⃣6⃣7⃣8⃣9⃣0⃣💏👩‍❤️‍💋‍👨👨‍❤️‍💋‍👨👩‍❤️‍💋‍👩💑👩‍❤️‍👨👨‍❤️‍👨👩‍❤️‍👩👪👨‍👩‍👦👨‍👩‍👧👨‍👩‍👧‍👦👨‍👩‍👦‍👦👨‍👩‍👧‍👧👨‍👨‍👦👨‍👨‍👧👨‍👨‍👧‍👦👨‍👨‍👦‍👦👨‍👨‍👧‍👧👩‍👩‍👦👩‍👩‍👧👩‍👩‍👧‍👦👩‍👩‍👦‍👦👩‍👩‍👧‍👧👁‍🗨";
//
//
//
//
////    font->loadGlyphs(codePoints);
//
////    ofSaveImage(font->_atlas.getPixels(), "out.jpg");
////    ofSaveImage(font->_atlas.getPixels(), "out.png");
////    ofSaveImage(font->_atlas.getPixels(), "out.gif");
//}
//
//
//void ofApp::textTest()
//{
////    std::string fileName = "Arial Unicode.ttf";
////
////    ofxFontSettings settings(fileName);
////    ofxFont font;
////    font.load(settings);
////
////    std::string codePoints = "那隻敏捷的棕色狐狸躍過那隻懶狗。 שועל החום הזריז קפץ מעל הכלב העצלן. A g 中國文字 صِف خَلقَ خَودِ كَمِثلِ الشَمسِ إِذ بَزَغَت — يَحظى الضَجيعُ بِها نَجلاءَ مِعطارِ Wow,これは面白い!!夜露死苦〠 สุนัขจิ้งจอกสีน้ำตาลอย่างรวดเร็วกระโดดข้ามสุนัขที่ขี้เกียจ";
////
////    font.loadGlyphs(codePoints);
////
////    ofSaveImage(font._atlas.getPixels(), fileName + ".png");
//}

