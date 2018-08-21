#pragma once

#include "ofMain.h"
#include "ofxAnimatableFloat.h"
#include "ccSegment.h"

class ccRobot {

public:
	void setup(vector<vector<float>>& _targetAngles);
	void update();
	void draw();
    void resetAnimation();
    void toggleWireframes();

protected:
    void setupCurrentAngles();
    void setupSegments();
    void incrementTargetPosition();
    void animateToNewPosition();
	void setCoordinateSystem();

	int numAngles;
	vector<vector<float>> targetAngles;
	vector<ofxAnimatableFloat> currentAngles;
	int currentPositionIndex;

    vector<ccSegment> segments;
    ccSegment baseSegment, headSegment;
    ccSegment lowerSegment, upperSegment;

	ofMaterial material;
};
