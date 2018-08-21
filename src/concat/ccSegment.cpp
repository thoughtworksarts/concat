#include "ccSegment.h"

void ccSegment::setup(ofMaterial& _material) {
    material = _material;
    rotationHandleLength = 30;
    showWireframes = false;
    setBoxSize(1, 1, 1);
    setJointRadius(1);
}

void ccSegment::setBoxSize(float width, float height, float depth) {
    box.set(width, height, depth);
    halfBoxHeight = height * 0.5;
    calculateSegmentHeight();
}

void ccSegment::setJointRadius(float radius) {
    joint.setRadius(radius);
    calculateSegmentHeight();
}

void ccSegment::draw() {
	material.begin();
	ofFill();

	ofPushMatrix();
	ofTranslate(0, halfBoxHeight);

	if (showWireframes) {
		ofSetColor(ofColor::white);
		box.drawWireframe();
	}
	else {
		ofSetColor(ofColor::grey);
        box.draw();
	}

	ofTranslate(0, halfBoxHeight);

	if (showWireframes) {
		ofSetColor(ofColor::white);
		joint.drawWireframe();
	}
	else {
		ofSetColor(ofColor::grey);
		joint.draw();
	}

	ofPopMatrix();

	ofSetColor(ofColor::green);
	ofSetLineWidth(1);
	ofDrawLine(0, halfBoxHeight, rotationHandleLength, halfBoxHeight);
	ofTranslate(0, segmentHeight);

	material.end();
}

void ccSegment::toggleWireframes() {
    showWireframes = !showWireframes;
}

void ccSegment::calculateSegmentHeight() {
    segmentHeight = box.getHeight() + joint.getRadius() * 2;
}