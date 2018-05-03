//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofMain.h"
#include "ofxFont.h"


class ofApp: public ofBaseApp
{
public:
    void setup() override;
    std::string FT_ERROR_TO_STRING(int error);

};
