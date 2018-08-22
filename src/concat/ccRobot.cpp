#include "ccRobot.h"

void ccRobot::setup(const vector<vector<float>>& _targetAngles) {
    targetAngles = _targetAngles;
    currentPositionIndex = 0;
	numAngles = 6;
    playing = false;

	setupCurrentAngles();
	setupSegments();
    ofEnableDepthTest();
}

void ccRobot::update() {
    if (playing) {
        if (ofGetFrameNum() % 60 == 0) {
            incrementTargetPosition();
            animateToIndexPosition();
        }

        for (int i = 0; i < currentAngles.size(); i++) {
            currentAngles.at(i).update(ofGetLastFrameTime());
        }
    }
}

void ccRobot::draw() {
    ofBackground(ofColor::black);
    ofPushMatrix();
    setCoordinateSystem();
    baseSegment.draw();

    ofRotateYDeg(currentAngles.at(0).getCurrentValue() - 90);
    ofRotateZDeg(currentAngles.at(1).getCurrentValue());
    lowerSegment.draw();

    upperSegment.translateToRotationCenter();
    ofRotateZDeg(currentAngles.at(2).getCurrentValue() + 90);
    ofRotateYDeg(currentAngles.at(3).getCurrentValue());
    upperSegment.draw();

    headSegment.translateToRotationCenter();
    ofRotateZDeg(currentAngles.at(4).getCurrentValue());
    ofRotateYDeg(currentAngles.at(5).getCurrentValue());
    headSegment.draw();

    ofPopMatrix();
}

void ccRobot::togglePlaying() {
    playing = !playing;
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

    baseSegment.setup(material);
    baseSegment.setJointRadius(0);
    baseSegment.setBoxSize(800, 50, 800);

    lowerSegment.setup(material);
    lowerSegment.setJointRadius(100);
    lowerSegment.setBoxSize(90, 460, 90);

    upperSegment.setup(material);
    upperSegment.setJointRadius(50);
    upperSegment.setBoxSize(70, 340, 70);

    headSegment.setup(material);
    headSegment.setJointRadius(35);
    headSegment.setBoxSize(30, 100, 30);
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
	ofTranslate(ofGetWidth() * 0.75, ofGetHeight(), -400);
	ofRotateZDeg(180);
	ofRotateYDeg(180);
}
