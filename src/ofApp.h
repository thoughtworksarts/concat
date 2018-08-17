#pragma once

#include "ofMain.h"
#include "ofxAnimatableFloat.h"
#include "ccParser.h"

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
    void drawHead();
    void setCoordinateSystem();

    int numAngles;
    int armSegmentLength, halfArmSegmentLength;
    int headLength, halfHeadLength;
    int rotationHandleLength;

    int segmentThickness;

    vector<vector<float>> targetAngles;
    vector<ofxAnimatableFloat> currentAngles;
    int currentArmPosition;

    ccParser dataParser;
};
