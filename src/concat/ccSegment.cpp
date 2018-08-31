#include "ccSegment.h"

void ccSegment::setup(ofMaterial& _material) {
    segmentMaterial = _material;
    showWireframes = false;
    //setBoxSize(1, 1, 1);
	setCylinderSize(1, 1);
    setJointRadius(1);
	segmentIsMoving = false;
	gradientDiff = 0;
	gradientSlope = true;
}

void ccSegment::translateToRotationCenter() {
    ofTranslate(0, joint.getRadius());
}

//TODO: Fix Smoothness of gradient
void ccSegment::draw() {
	if (segmentIsMoving) {
		segmentMaterial.setDiffuseColor(ofFloatColor(ofColor(100+gradientDiff, 0, 50)));
		if (gradientDiff < 255 && gradientSlope) {
			gradientDiff++;
		}
		else if (gradientDiff > 0 && !gradientSlope) {
			gradientDiff--;
		}
		else {
			gradientSlope = !gradientSlope;
		}
		
	}
	else {
		segmentMaterial.setDiffuseColor(ofFloatColor(ofColor::thistle));
	}
    segmentMaterial.begin();
    ofFill();
    ofPushMatrix();
    drawJoint();
	drawCylinder();
    drawRotationHandle();
    ofPopMatrix();
    ofTranslate(0, segmentHeight);
    segmentMaterial.end();
}

void ccSegment::setBoxSize(float width, float height, float depth) {
    box.set(width, height, depth);
	cylinder.set(width / 2, height / 2, width, height / 4);
    halfBoxWidth = width * 0.5;
    halfBoxHeight = height * 0.5;
    calculateSegmentHeight();
}

void ccSegment::setCylinderSize(float width, float height) {
	cylinder.set(width / 2, height, width, height);
	calculateCylinderSegmentHeight();
}


void ccSegment::setJointRadius(float radius) {
    joint.setRadius(radius);
    calculateSegmentHeight();
}

void ccSegment::toggleWireframes() {
    showWireframes = !showWireframes;
}

void ccSegment::calculateSegmentHeight() {
    segmentHeight = box.getHeight() + joint.getRadius();
}

void ccSegment::calculateCylinderSegmentHeight() {
	segmentHeight = cylinder.getHeight() + joint.getRadius();
}

void ccSegment::drawJoint() {
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

void ccSegment::drawBox() {
    ofTranslate(0, joint.getRadius() + halfBoxHeight);
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

void ccSegment::drawCylinder() {
	ofTranslate(0, joint.getRadius() + halfBoxHeight);
	ofSetLineWidth(1);

	if (showWireframes) {
		ofSetColor(ofColor::white);
		cylinder.drawWireframe();
	}
	else {
		ofSetColor(ofColor::grey);
		cylinder.draw();
	}
}

void ccSegment::drawSimpleCylinder(float joint1x, float joint1y, float joint2x, float joint2y, float radius) {
	float height = ofDist(joint1x, joint1y, joint2x, joint2y);
	drawCylinder();
}

void ccSegment::drawRotationHandle() {
    if (showWireframes) {
        ofSetLineWidth(2);
        ofDrawLine(halfBoxWidth, 0, box.getWidth(), 0);
    }
}

void ccSegment::toggleSegmentHasMoved() {
	segmentIsMoving = !segmentIsMoving;
}

bool ccSegment::isSegmentMoving() {
	return segmentIsMoving;
}