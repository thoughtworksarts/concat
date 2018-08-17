#pragma once

#include "ofMain.h"
#include "ofxAnimatableFloat.h"

class ofApp : public ofBaseApp{
    public:
    void setup();
    void setupTargetAngles();
    void setupCurrentAngles();
    void update();
    void incrementTargetArmPosition();
    void animateToNewArmPosition();
    void draw();
    void drawArmSegment();
    void setCoordinateSystem();

    int numAngles;
    int armSegmentLength, halfArmSegmentLength;
    int rotationHandleLength;

    vector<vector<float>> targetAngles;
    vector<ofxAnimatableFloat> currentAngles;
    int currentArmPosition;
};
