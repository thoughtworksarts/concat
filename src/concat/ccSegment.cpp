#include "ccSegment.h"

void ccSegment::setup(ofMaterial& _material) {
    material = _material;
    rotationHandleLength = 100;
    showWireframes = false;
    setBoxSize(1, 1, 1);
    setJointRadius(1);
}

void ccSegment::setBoxSize(float width, float height, float depth) {
    box.set(width, height, depth);
    halfBoxWidth = width * 0.5;
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
    drawBox();
    drawJoint();
	ofPopMatrix();

    drawRotationHandle();
	ofTranslate(0, segmentHeight);
	material.end();
}

void ccSegment::toggleWireframes() {
    showWireframes = !showWireframes;
}

void ccSegment::calculateSegmentHeight() {
    segmentHeight = box.getHeight() + joint.getRadius() * 2;
}

void ccSegment::drawBox() {
    ofTranslate(0, halfBoxHeight);
    ofSetLineWidth(1);

    if (showWireframes) {
        ofSetColor(ofColor::white);
        box.drawWireframe();
    }
    else {
        ofSetColor(ofColor::grey);
        box.draw();
    }
}

void ccSegment::drawJoint() {
    ofTranslate(0, halfBoxHeight);
    ofSetLineWidth(1);

    if (showWireframes) {
        ofSetColor(ofColor::white);
        joint.drawWireframe();
    }
    else {
        ofSetColor(ofColor::grey);
        joint.draw();
    }
}

void ccSegment::drawRotationHandle() {
    if (showWireframes) {
        ofSetColor(ofColor::green);
        ofSetLineWidth(2);
        ofDrawLine(halfBoxWidth, halfBoxHeight, rotationHandleLength, halfBoxHeight);
    }
}