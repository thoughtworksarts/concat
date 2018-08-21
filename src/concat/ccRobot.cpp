#include "ccRobot.h"

void ccRobot::setup(vector<vector<float>>& _targetAngles) {
    targetAngles = _targetAngles;
    currentPositionIndex = 0;
	numAngles = 6;

	setupCurrentAngles();
	setupSegments();
    ofEnableDepthTest();
}

void ccRobot::update() {
	if (ofGetFrameNum() % 60 == 0) {
		incrementTargetPosition();
		animateToNewPosition();
	}

	for (int i = 0; i < currentAngles.size(); i++) {
		currentAngles.at(i).update(ofGetLastFrameTime());
	}
}

void ccRobot::draw() {
    ofBackground(ofColor::black);
    ofPushMatrix();
    setCoordinateSystem();
    baseSegment.draw();
    ofRotateYDeg(currentAngles.at(0).getCurrentValue());
    ofRotateZDeg(currentAngles.at(1).getCurrentValue());
    lowerSegment.draw();
    ofRotateZDeg(currentAngles.at(2).getCurrentValue());
    ofRotateYDeg(currentAngles.at(3).getCurrentValue());
    upperSegment.draw();
    ofRotateZDeg(currentAngles.at(4).getCurrentValue());
    ofRotateYDeg(currentAngles.at(5).getCurrentValue());
    headSegment.draw();
    ofPopMatrix();
}

void ccRobot::resetAnimation() {
    currentPositionIndex = 0;
}

void ccRobot::toggleWireframes() {
    for (auto segment : segments) {
        segment.toggleWireframes();
    }
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
    baseSegment.setBoxSize(400, 100, 400);
    baseSegment.setJointRadius(100);
    segments.push_back(baseSegment);

    lowerSegment.setup(material);
    lowerSegment.setBoxSize(80, 300, 80);
    lowerSegment.setJointRadius(60);
    segments.push_back(lowerSegment);

    upperSegment.setup(material);
    upperSegment.setBoxSize(80, 300, 80);
    upperSegment.setJointRadius(60);
    segments.push_back(upperSegment);

    upperSegment.setup(material);
    upperSegment.setBoxSize(80, 300, 80);
    upperSegment.setJointRadius(60);
    segments.push_back(upperSegment);

    headSegment.setup(material);
    headSegment.setBoxSize(80, 300, 80);
    headSegment.setJointRadius(60);
    segments.push_back(headSegment);
}

void ccRobot::incrementTargetPosition() {
	currentPositionIndex++;
	if (currentPositionIndex >= targetAngles.size()) {
		currentPositionIndex = 0;
	}
}

void ccRobot::animateToNewPosition() {
	for (int i = 0; i < currentAngles.size(); i++) {
		float targetAngle = targetAngles.at(currentPositionIndex).at(i);
		currentAngles.at(i).animateTo(targetAngle);
	}
}

void ccRobot::setCoordinateSystem() {
	ofTranslate(ofGetWidth() * 0.75, ofGetHeight());
	ofRotateZDeg(180);
	ofRotateYDeg(180);
}
