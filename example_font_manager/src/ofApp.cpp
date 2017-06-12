//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//

#include "ofApp.h"


void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);

    {
        // List available systemfonts.
        auto fonts = ofxText::FontManager::getAvailableFonts();

        for (const auto& descriptor: fonts)
        {
            std::cout << "Family: " << descriptor.family << ", Name: " << descriptor.postscriptName << std::endl;
        }

        ofLogNotice("ofApp::setup") << fonts.size() << " system fonts found.";
    }

    {
        // Find all thin fonts.
        ofxText::FontDescriptor descriptor;
        descriptor.weight = ofxText::FontWeightThin;

        auto fonts = ofxText::FontManager::findFonts(descriptor);

        for (const auto& descriptor: fonts)
        {
            std::cout << "Family: " << descriptor.family << ", Name: " << descriptor.postscriptName << ", Path: " << descriptor.path << std::endl;
        }

        ofLogNotice("ofApp::setup") << fonts.size() << " matching fonts found.";
    }

    {
        // Find the best thin monospace font.
        ofxText::FontDescriptor descriptor;
        descriptor.weight = ofxText::FontWeightThin;
        descriptor.monospace = true;
        ofxText::FontDescriptor result = ofxText::FontManager::findFont(descriptor);
        ofLogNotice("ofApp::setup") << "The best matching font is:" << result.toJSON().dump(4);
    }

    {
        // Find the best thin monospace font.
        ofxText::FontDescriptor descriptor;
        descriptor.weight = ofxText::FontWeightThin;
        descriptor.monospace = true;
        ofxText::FontDescriptor result = ofxText::FontManager::findFont(descriptor);

        // Assuming that this font does not have emojis, find a font that does.
        std::string utf8Text = "😃😇😍😜";
        result = ofxText::FontManager::substituteFont(result.postscriptName,
                                                      utf8Text);

        ofLogNotice("ofApp::setup") << "The best matching font that includes our code points is:" << result.toJSON().dump(4);

    }
}
