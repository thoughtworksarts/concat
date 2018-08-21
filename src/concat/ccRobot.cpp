#include "ccRobot.h"

void ccRobot::setup(vector<vector<float>>& _targetAngles) {
    targetAngles = _targetAngles;
    showWireframes = false;

	armLength = 200;
	jointSize = 50;
	armSegmentThickness = 10;
	armSegmentLength = armLength - jointSize;

	headLength = 70;
	rotationHandleLength = 30;

	halfArmLength = armLength * 0.5;
	halfHeadLength = headLength * 0.5;
	halfJointSize = jointSize * 0.5;

	currentArmPosition = 0;
	numAngles = 6;
	numArmSegments = 3;

	setupCurrentAngles();
	setupPrimitives();
}

void ccRobot::update() {
	if (ofGetFrameNum() % 60 == 0) {
		incrementTargetArmPosition();
		animateToNewArmPosition();
	}

	for (int i = 0; i < currentAngles.size(); i++) {
		currentAngles.at(i).update(ofGetLastFrameTime());
	}
}

void ccRobot::draw() {
    ofBackground(ofColor::black);
    ofPushMatrix();
    setCoordinateSystem();
    drawArmSegment(0);
    ofRotateY(currentAngles.at(0).getCurrentValue());
    ofRotateZ(currentAngles.at(1).getCurrentValue());
    drawArmSegment(1);
    ofRotateZ(currentAngles.at(2).getCurrentValue());
    ofRotateY(currentAngles.at(3).getCurrentValue());
    drawArmSegment(2);
    ofRotateZ(currentAngles.at(4).getCurrentValue());
    ofRotateY(currentAngles.at(5).getCurrentValue());
    drawHead();
    ofPopMatrix();
}

void ccRobot::resetAnimation() {
    currentArmPosition = 0;
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
    ofBoxPrimitive armSegment;
    for (int i = 0; i < numArmSegments; i++) {
        int thickness = 50 - i * armSegmentThickness;
        armSegments.push_back(armSegment);
        armSegments.back().set(thickness, armSegmentLength, thickness);
    }

    ofSpherePrimitive joint;
    for (int i = 0; i < numArmSegments; i++) {
        joints.push_back(joint);
        joints.back().setRadius(halfJointSize - 5 * i);
    }

    material.setShininess(120);
    material.setSpecularColor(ofColor(255, 255, 255, 255));
}

void ccRobot::incrementTargetArmPosition() {
	currentArmPosition++;
	if (currentArmPosition >= targetAngles.size()) {
		currentArmPosition = 0;
	}
}

void ccRobot::animateToNewArmPosition() {
	for (int i = 0; i < currentAngles.size(); i++) {
		float targetAngle = targetAngles.at(currentArmPosition).at(i);
		currentAngles.at(i).animateTo(targetAngle);
	}
}

void ccRobot::drawArmSegment(int segmentId) {
	material.begin();
	ofFill();

	ofPushMatrix();
	ofTranslate(0, halfArmLength);

	if (showWireframes) {
		ofSetColor(ofColor::white);
		armSegments.at(segmentId).drawWireframe();
	}
	else {
		ofSetColor(ofColor::grey);
		armSegments.at(segmentId).draw();
	}

	ofTranslate(0, halfArmLength);

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
	ofDrawLine(0, halfArmLength, rotationHandleLength, halfArmLength);
	ofTranslate(0, armLength);

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
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight());
	ofRotateZ(180);
	ofRotateY(180);
}
