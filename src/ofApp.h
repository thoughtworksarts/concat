#pragma once

#include "ofMain.h"
#include "ofxAnimatableFloat.h"
#include "ofxKinectV2OSC.h"
#include "concat/ccParser.h"
#include "concat/ccRobot.h"
#include "concat/ccLighting.h"

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

	ofxKinectV2OSC kinect;
	Skeleton* skeleton;
	vector<Skeleton>* skeletons;
	ofTrueTypeFont smallFont, largeFont;
	BodyRenderer renderer;
};
