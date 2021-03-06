//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofAppRunner.h"
#include "ofApp.h"


int main()
{
    ofGLWindowSettings settings;
    settings.width = 80;
    settings.height = 60;
    settings.setGLVersion(3, 2);
    settings.windowMode = OF_WINDOW;
    auto window = ofCreateWindow(settings);
    auto app = std::make_shared<ofApp>();

    ofRunApp(window, app);
    return ofRunMainLoop();
}
