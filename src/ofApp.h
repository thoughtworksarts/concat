#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
    void setup();
    void update();
    void draw();
    void drawArmSegment();
    void setCoordinateSystem();

    int armSegmentLength, halfArmSegmentLength;
    int rotationHandleLength;

    vector<vector<float>> movements;
    int currentArmPosition;
};
