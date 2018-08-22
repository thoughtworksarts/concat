#pragma once

#include "ofMain.h"
#include "util/ccParser.h"
#include "util/ccClock.h"
#include "util/ccInfo.h"
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
    ccParser dataParser;
    ccInfo info;
    ccClock clock;
    ccRobot robot;
    ccLighting lighting;
    ccKinect kinect;
};
