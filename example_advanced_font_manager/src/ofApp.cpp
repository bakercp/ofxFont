//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//

#include "ofApp.h"


void ofApp::setup()
{
    // Task 1. List available system fonts.
    auto fonts = ofxText::FontManager::getAvailableFonts();

    // Remap them to group them by family.
    std::map<std::string, std::vector<ofxText::FontDescriptor>> familyMap;

    for (const auto& descriptor: fonts)
    {
        auto iter = familyMap.find(descriptor.family);
        if (iter != familyMap.end()) iter->second.push_back(descriptor);
        else familyMap[descriptor.family] = { descriptor };
    }

    ofLogNotice("ofApp::setup") << "There are " << fonts.size() << " unique fonts installed, in " << familyMap.size() << " font families.";

    // Task 2. Find all thin fonts.
    ofxText::FontDescriptor descriptor;
    descriptor.weight = ofxText::FontWeightThin;
    ofLogNotice("ofApp::setup") << "There are " << ofxText::FontManager::findFonts(descriptor).size() << " possible fonts that are \"Thin\".";

    // Task 3. Find the best thin monospace font.
    descriptor.monospace = true;
    auto result = ofxText::FontManager::findFont(descriptor);

    ofLogNotice("ofApp::setup") << "The best \"Thin\" AND \"Monospace\" font available is: " << result.path;

    // Task 4. Find a font with the right code points.
    // Does the best thin monospace have the codepoints we need? If not, what font should we use?
    std::string codePointsNeeded = "你好";
    result = ofxText::FontManager::substituteFont(result.postscriptName, codePointsNeeded);
    ofLogNotice("ofApp::setup") << "The best substitute for a thin monospace font that can represent \"" << codePointsNeeded << "\" is: " << result.path;


    // Task 5. Find a font with the right code points.
    // Does the best thin monospace have the codepoints we need? If not, what font should we use?
    codePointsNeeded = "😃";
    result = ofxText::FontManager::substituteFont(result.postscriptName, codePointsNeeded);
    ofLogNotice("ofApp::setup") << "The best substitute for a thin monospace font that can represent \"" << codePointsNeeded << "\" is: " << result.path;


    ofExit();
}
	
