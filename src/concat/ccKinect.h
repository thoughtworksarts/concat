#pragma once

#include "ofMain.h"
#include "ofxKinectV2OSC.h"
#include "ccBodyRenderer.h"

class ccKinect {

public:
	void setup(vector<bool> _bodyGroupStates);
	void update(vector<bool> _bodyGroupStates);
    void draw();

	void enable3d();

	vector<bool> bodyGroupStates;

protected:
    void drawSkeletons();

    ofxKinectV2OSC kinect;
    Skeleton* skeleton;
    vector<Skeleton>* skeletons;
    ofTrueTypeFont smallFont, largeFont;
	ccBodyRenderer renderer;
    ofVec2f infoPosition, renderTranslation;

};
