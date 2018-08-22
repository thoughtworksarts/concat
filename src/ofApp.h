#pragma once

#include "ofMain.h"
#include "concat/ccParser.h"
#include "concat/ccRobot.h"
#include "concat/ccLighting.h"
#include "concat/ccKinect.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

protected:
    void updateInfoOverlay();
    string info;
    ofVec2f infoPosition;

    ccParser dataParser;
    ccRobot robot;
    ccLighting lighting;
    ccKinect kinect;
};
