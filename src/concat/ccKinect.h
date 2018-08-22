#pragma once

#include "ofMain.h"
#include "ofxKinectV2OSC.h"

class ccKinect {

public:
	void setup();
	void update();
    void draw();

protected:
    ofxKinectV2OSC kinect;
    Skeleton* skeleton;
    vector<Skeleton>* skeletons;
    ofTrueTypeFont smallFont, largeFont;
    BodyRenderer renderer;
};
