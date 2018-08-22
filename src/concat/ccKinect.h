#pragma once

#include "ofMain.h"
#include "ofxKinectV2OSC.h"

class ccKinect {

public:
	void setup();
	void update();
    void draw();

protected:
    void drawSkeletons();

    ofxKinectV2OSC kinect;
    Skeleton* skeleton;
    vector<Skeleton>* skeletons;
    ofTrueTypeFont smallFont, largeFont;
    BodyRenderer renderer;
    ofVec2f infoPosition;
};
