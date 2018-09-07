#include "ccRobot.h"

void ccRobot::setup(const vector<vector<float>>& _targetAngles) {
    targetAngles = _targetAngles;
    currentPositionIndex = 0;
	numAngles = 6;
    playing = false;
    previousMod = 1000;

	setupCurrentAngles();
	setupSegments();
    ofEnableDepthTest();

	segmentStates = { 0, 0, 0 };

}

void ccRobot::update() {
    if (playing) {
        if (oneSecondHasPassed()) {
            incrementTargetPosition();
            animateToIndexPosition();
        }

        for (int i = 0; i < currentAngles.size(); i++) {
            currentAngles.at(i).update(ofGetLastFrameTime());
        }
		updateSegmentStates();
    }
}

void ccRobot::updateSegmentStates() {
	segmentStates.clear();
	segmentStates.push_back(headSegment.isSegmentMoving());
	segmentStates.push_back(upperSegment.isSegmentMoving());
	segmentStates.push_back(lowerSegment.isSegmentMoving());
}

void ccRobot::draw() {
    ofBackground(ofColor::black);
	ofBackground(.5, 0);
    ofPushMatrix();
    setCoordinateSystem();

	ofTranslate(-600, -250, 0);
	ofRotateX(20);
	baseSegment.draw();
	ofRotateX(-20);
	ofTranslate(600, 250, 0);

    ofRotateYDeg(currentAngles.at(0).getCurrentValue() - 90);
    ofRotateZDeg(currentAngles.at(1).getCurrentValue());
	if (jointIsInMotion(0, 1)) {
		if (!lowerSegment.isSegmentMoving()) {
			lowerSegment.toggleSegmentHasMoved();
		}
	}
	else {
		if (lowerSegment.isSegmentMoving()) {
			lowerSegment.toggleSegmentHasMoved();
		}
	}
    lowerSegment.draw();
	

    upperSegment.translateToRotationCenter();
    ofRotateZDeg(currentAngles.at(2).getCurrentValue() + 90);
    ofRotateYDeg(currentAngles.at(3).getCurrentValue());
	if (jointIsInMotion(2, 3)) {
		if (!upperSegment.isSegmentMoving()) {
			upperSegment.toggleSegmentHasMoved();
		}
	}
	else {
		if (upperSegment.isSegmentMoving()) {
			upperSegment.toggleSegmentHasMoved();
		}
	}
    upperSegment.draw();

    headSegment.translateToRotationCenter();
    ofRotateZDeg(currentAngles.at(4).getCurrentValue());
    ofRotateYDeg(currentAngles.at(5).getCurrentValue());
	if (jointIsInMotion(4, 5)) {
		if (!headSegment.isSegmentMoving()) {
			headSegment.toggleSegmentHasMoved();
		}
	}
	else {
		if (headSegment.isSegmentMoving()) {
			headSegment.toggleSegmentHasMoved();
		}
	}
    headSegment.draw();

    ofPopMatrix();
}

void ccRobot::togglePlaying() {
    playing = !playing;
    ofResetElapsedTimeCounter();
}

void ccRobot::newPositionSet(const vector<vector<float>>& _targetAngles) {
    targetAngles = _targetAngles;
    currentPositionIndex = 0;
}

void ccRobot::resetAnimation() {
    currentPositionIndex = 0;
    resetToIndexPosition();
    playing = false;
}

void ccRobot::toggleWireframes() {
    baseSegment.toggleWireframes();
    lowerSegment.toggleWireframes();
    upperSegment.toggleWireframes();
    headSegment.toggleWireframes();
}

void ccRobot::setupCurrentAngles() {
    ofxAnimatableFloat angle;
    for (int i = 0; i < numAngles; i++) {
        currentAngles.push_back(angle);
        currentAngles.back().setup();
        currentAngles.back().setDuration(1);
        currentAngles.back().setCurve(LINEAR);
        currentAngles.back().reset(targetAngles.at(0).at(i));
    }
}

void ccRobot::setupSegments() {
    material.setShininess(120);
    material.setSpecularColor(ofColor(255, 255, 255, 255));
	material.setDiffuseColor(ofFloatColor (ofColor::thistle));

    baseSegment.setup(material);
    baseSegment.setJointRadius(0);
    baseSegment.setBoxSize(2000, 20, 800);

    lowerSegment.setup(material);
    lowerSegment.setJointRadius(100); 
    lowerSegment.setBoxSize(90, 800, 90);

    upperSegment.setup(material);
    upperSegment.setJointRadius(50);
    upperSegment.setBoxSize(70, 400, 70);

    headSegment.setup(material);
    headSegment.setJointRadius(35);
    headSegment.setBoxSize(70, 50, 30);
}

void ccRobot::incrementTargetPosition() {
	currentPositionIndex++;
	if (currentPositionIndex >= targetAngles.size()) {
		currentPositionIndex = 0;
	}
}

void ccRobot::animateToIndexPosition() {
    for (int i = 0; i < currentAngles.size(); i++) {
        float targetAngle = targetAngles.at(currentPositionIndex).at(i);
        currentAngles.at(i).animateTo(targetAngle);
    }
}

void ccRobot::resetToIndexPosition() {
    for (int i = 0; i < currentAngles.size(); i++) {
        float targetAngle = targetAngles.at(currentPositionIndex).at(i);
        currentAngles.at(i).reset(targetAngle);
    }
}

void ccRobot::setCoordinateSystem() {
	ofTranslate(ofGetWidth() * 0.7, ofGetHeight()- (.15*ofGetHeight()), -400);
	ofRotateZDeg(180);
	ofRotateYDeg(180);
}

bool ccRobot::oneSecondHasPassed() {
    uint64_t elapsed = ofGetElapsedTimeMillis();
    int currentMod = elapsed % 1000;
    bool returnValue = currentMod < previousMod;
    previousMod = currentMod;
    return returnValue;
}

bool ccRobot::jointIsInMotion(int angleIndex1, int angleIndex2) {

	if ((currentAngles.at(angleIndex1).getCurrentValue() 
		!= targetAngles.at(currentPositionIndex).at(angleIndex1))
		|| (currentAngles.at(angleIndex2).getCurrentValue() 
			!= targetAngles.at(currentPositionIndex).at(angleIndex2))) {
		return true;
	}

	return false;
}