#pragma once

#include "ofMain.h"
#include "ofxKinectV2OSC.h"
#include "ccBodyRenderer.h"

class ccKinect {

public:
	void setup();
	void update();
    void draw();

	void enable3d();

protected:
    void drawSkeletons();

    ofxKinectV2OSC kinect;
    Skeleton* skeleton;
    vector<Skeleton>* skeletons;
    ofTrueTypeFont smallFont, largeFont;
	ccBodyRenderer renderer;
    ofVec2f infoPosition, renderTranslation;
};
