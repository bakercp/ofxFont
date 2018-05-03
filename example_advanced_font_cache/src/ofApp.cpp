//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//

#include "ofApp.h"


void ofApp::setup()
{
    std::string path = "verdana.ttf";

    // 1. Get a reference to the FTFontCache.
    auto& cache = ofxText::FTFontCache::instance();

    {
        ofSetLogLevel(OF_LOG_SILENT);
        // Test invalid path.
        auto buffer_0 = cache.getBufferForFontPath("");
        assert(!buffer_0);
        assert(cache._fontBufferCache.size() == 0);
        ofSetLogLevel(OF_LOG_NOTICE);
    }

    {
        // Test memory buffer cache.
        auto buffer_0 = cache.getBufferForFontPath(path);
        assert(buffer_0 && buffer_0->size() > 0);
        // Load it again.
        auto buffer_1 = cache.getBufferForFontPath(path);
        assert(buffer_1 && buffer_1->size() > 0);
        // Make sure it's the same memory.
        assert(buffer_0 == buffer_1);
        // Make sure there is just one buffer cached.
        assert(cache._fontBufferCache.size() == 1);
    }
    {
        // Make sure there is just one buffer cached.
        assert(cache._fontBufferCache.size() == 1);
        // Make sure the reference count is correct (one in the cache).
        assert(cache._fontBufferCache.begin()->second.use_count() == 1);
    }
    {
        ofxText::FTFaceDescriptor faceId_0(path);
        ofxText::FTSizeDescriptor sizeId_0(12);

        FT_Face face_0 = cache.getFace(faceId_0, sizeId_0);

        // Make sure there is only one FT_Face cached.
        assert(cache._faceIdCache.size() == 1);
        
        FT_Face face_1 = cache.getFace(faceId_0, sizeId_0);

        // Make sure the instances are the same.
        assert(face_0 == face_1);
    }


//    {
//        ofxText::FontDescriptor fd;
//        fd.postscriptName = "Verdana";
//        fd.path = ofToDataPath("verdana.ttf", true);
//
//        // We can get an FT_Face from the cache. The FT_Face is owned by the cache.
//        FT_Face face = cache.getFaceByDescriptor(fd);
//        std::cout << "getFaceByDescriptor()" << std::endl;
//        std::cout << ftFaceToString(face) << std::endl;
//    }
//    {
//        ofxText::FontDescriptor fd;
//        fd.postscriptName = "Verdana";
//
//        // We can get an FT_Face from the cache. The FT_Face is owned by the cache.
//        FT_Face face = cache.getFaceByDescriptor(fd);
//        std::cout << "getFaceByDescriptor()" << std::endl;
//        std::cout << ftFaceToString(face) << std::endl;
//    }
//    {
//        ofxText::FontDescriptor fd;
//        fd.monospace = true;
//        fd.weight = ofxText::FontWeightHeavy;
//
//        // We can get an FT_Face from the cache. The FT_Face is owned by the cache.
//        FT_Face face = cache.getFaceByDescriptor(fd);
//        std::cout << "getFaceByDescriptor()" << std::endl;
//        std::cout << ftFaceToString(face) << std::endl;
//    }


    ofExit();
}



std::string ofApp::ftFaceToString(FT_Face face) const
{
    std::stringstream ss;

    if (face != nullptr)
    {
        ss << "--" << std::endl;
        ss << "Postscript Name: " << FT_Get_Postscript_Name(face) << std::endl;
        ss << "    Family Name: " << face->family_name << std::endl;
        ss << "     Style Name: " << face->style_name << std::endl;
    }
    else
    {
        ss << "face was a nullptr" << std::endl;
    }

    return ss.str();
}
