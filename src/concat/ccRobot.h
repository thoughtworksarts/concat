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
    void incrementTargetArmPosition();
    void animateToNewArmPosition();
    void drawArmSegment(int segmentId);
    void drawHead();
	void setCoordinateSystem();

	int numAngles, numArmSegments;
	int armLength, armSegmentLength, armSegmentThickness, jointSize, halfJointSize, halfArmLength;
	int headLength, halfHeadLength;
	int rotationHandleLength;

	vector<vector<float>> targetAngles;
	vector<ofxAnimatableFloat> currentAngles;
	int currentArmPosition;

	vector<ofBoxPrimitive> armSegments;
	vector<ofSpherePrimitive> joints;

	ofMaterial material;
	bool showWireframes;
};
