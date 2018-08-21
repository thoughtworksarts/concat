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
    void toggleLights();

protected:
    void setupCurrentAngles();
    void setupPrimitives();
    void setupLighting();
    void incrementTargetArmPosition();
    void animateToNewArmPosition();
    void drawArmSegment(int segmentId);
    void drawHead();
	void setCoordinateSystem();

	int numAngles, numArmSegments, numLights;
	int armLength, armSegmentLength, armSegmentThickness, jointSize, halfJointSize, halfArmLength;
	int headLength, halfHeadLength;
	int rotationHandleLength;

	vector<vector<float>> targetAngles;
	vector<ofxAnimatableFloat> currentAngles;
	int currentArmPosition;

	vector<ofBoxPrimitive> armSegments;
	vector<ofSpherePrimitive> joints;
	vector<ofLight> lights;

	ofMaterial material;
	bool showWireframes, showLights;

	float lightingHeightAdjustment;
	float lightingDepth;
};
