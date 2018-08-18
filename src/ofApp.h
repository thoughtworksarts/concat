#pragma once

#include "ofMain.h"
#include "ofxAnimatableFloat.h"
#include "ccParser.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void setupTargetAngles();
    void setupCurrentAngles();
    void setupPrimitives();
    void setupLighting();
    void update();
    void incrementTargetArmPosition();
    void animateToNewArmPosition();
    void draw();
    void drawArmSegment(int segmentId);
    void drawHead();
    void keyPressed(int key);

protected:
    void setCoordinateSystem();
    int numAngles, numArmSegments, numLights;
    int armLength, armSegmentLength, armSegmentThickness, jointSize, halfJointSize, halfArmLength;
    int headLength, halfHeadLength;
    int rotationHandleLength;

    vector<vector<float>> targetAngles;
    vector<ofxAnimatableFloat> currentAngles;
    int currentArmPosition;

    ccParser dataParser;

    vector<ofBoxPrimitive> armSegments;
    vector<ofSpherePrimitive> joints;
    vector<ofLight> lights;

    ofMaterial material;
    bool showWireframes, showLights;

    float lightingHeightAdjustment;
    float lightingDepth;
};
