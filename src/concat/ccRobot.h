#pragma once

#include "ofMain.h"
#include "ofxAnimatableFloat.h"
#include "ccSegment.h"

class ccRobot {

public:
	void setup(const vector<vector<float>>& _targetAngles);
	void update();
    void draw();
    void togglePlaying();
    void newPositionSet(const vector<vector<float>>& _targetAngles);
    void resetAnimation();
    void toggleWireframes();

protected:
    void setupCurrentAngles();
    void setupSegments();
    void incrementTargetPosition();
    void animateToIndexPosition();
    void resetToIndexPosition();
	void setCoordinateSystem();
    bool oneSecondHasPassed();
	bool jointIsInMotion(int angleIndex1, int angleIndex2);

	int numAngles;
	vector<vector<float>> targetAngles;
	vector<ofxAnimatableFloat> currentAngles;
	int currentPositionIndex;

    ccSegment baseSegment, headSegment;
    ccSegment lowerSegment, upperSegment;

	ofMaterial material;
    bool playing;
    int previousMod;

};
