#pragma once

#include "ofMain.h"
#include "ofxAnimatableFloat.h"

class ccRobot {

public:
	void setup(vector<vector<float>>& _targetAngles);
	void update();
	void draw();
    void resetAnimation();
    void toggleWireframes();

protected:
    void setupCurrentAngles();
    void setupPrimitives();
    void incrementTargetPosition();
    void animateToNewPosition();
    void drawSegment(int segmentId);
    void drawHead();
	void setCoordinateSystem();

	int numAngles, numSegments;
    int segmentLength, halfSegmentLength, segmentBoxLength, segmentBoxThickness;
    int jointSize, halfJointSize;
	int headLength, halfHeadLength;
	int rotationHandleLength;

	vector<vector<float>> targetAngles;
	vector<ofxAnimatableFloat> currentAngles;
	int currentPositionIndex;

	vector<ofBoxPrimitive> segmentBoxes;
	vector<ofSpherePrimitive> joints;

	ofMaterial material;
	bool showWireframes;
};
