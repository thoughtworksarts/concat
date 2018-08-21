#include "ccRobot.h"

void ccRobot::setup(vector<vector<float>>& _targetAngles) {
    targetAngles = _targetAngles;
    showWireframes = false;

	segmentLength = 200;
	jointSize = 50;
	segmentBoxThickness = 10;
	segmentBoxLength = segmentLength - jointSize;

	headLength = 70;
	rotationHandleLength = 30;

	halfSegmentLength = segmentLength * 0.5;
	halfHeadLength = headLength * 0.5;
	halfJointSize = jointSize * 0.5;

	currentPositionIndex = 0;
	numAngles = 6;
	numSegments = 3;

	setupCurrentAngles();
	setupPrimitives();
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
    drawSegment(0);
    ofRotateYDeg(currentAngles.at(0).getCurrentValue());
    ofRotateZDeg(currentAngles.at(1).getCurrentValue());
    drawSegment(1);
    ofRotateZDeg(currentAngles.at(2).getCurrentValue());
    ofRotateYDeg(currentAngles.at(3).getCurrentValue());
    drawSegment(2);
    ofRotateZDeg(currentAngles.at(4).getCurrentValue());
    ofRotateYDeg(currentAngles.at(5).getCurrentValue());
    drawHead();
    ofPopMatrix();
}

void ccRobot::resetAnimation() {
    currentPositionIndex = 0;
}

void ccRobot::toggleWireframes() {
    showWireframes = !showWireframes;
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

void ccRobot::setupPrimitives() {
    ofBoxPrimitive segmentBox;
    for (int i = 0; i < numSegments; i++) {
        int thickness = 50 - i * segmentBoxThickness;
        segmentBoxes.push_back(segmentBox);
        segmentBoxes.back().set(thickness, segmentBoxLength, thickness);
    }

    ofSpherePrimitive joint;
    for (int i = 0; i < numSegments; i++) {
        joints.push_back(joint);
        joints.back().setRadius(halfJointSize - 5 * i);
    }

    material.setShininess(120);
    material.setSpecularColor(ofColor(255, 255, 255, 255));
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

void ccRobot::drawSegment(int segmentId) {
	material.begin();
	ofFill();

	ofPushMatrix();
	ofTranslate(0, halfSegmentLength);

	if (showWireframes) {
		ofSetColor(ofColor::white);
		segmentBoxes.at(segmentId).drawWireframe();
	}
	else {
		ofSetColor(ofColor::grey);
        segmentBoxes.at(segmentId).draw();
	}

	ofTranslate(0, halfSegmentLength);

	if (showWireframes) {
		ofSetColor(ofColor::white);
		joints.at(segmentId).drawWireframe();
	}
	else {
		ofSetColor(ofColor::grey);
		joints.at(segmentId).draw();
	}

	ofPopMatrix();

	ofSetColor(ofColor::green);
	ofSetLineWidth(1);
	ofDrawLine(0, halfSegmentLength, rotationHandleLength, halfSegmentLength);
	ofTranslate(0, segmentLength);

	material.end();
}

void ccRobot::drawHead() {
	ofSetColor(ofColor::wheat);
	ofSetLineWidth(2);
	ofDrawLine(0, 0, 0, headLength);
	ofSetColor(ofColor::red);
	ofSetLineWidth(1);
	ofDrawLine(0, halfHeadLength, rotationHandleLength, halfHeadLength);
	ofTranslate(0, headLength);
}

void ccRobot::setCoordinateSystem() {
	ofTranslate(ofGetWidth() * 0.75, ofGetHeight());
	ofRotateZDeg(180);
	ofRotateYDeg(180);
}
