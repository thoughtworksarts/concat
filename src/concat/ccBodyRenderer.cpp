#include "ccBodyRenderer.h"
#include <cmath>
#include <algorithm>

void ccBodyRenderer::setup(vector<Skeleton>* _skeletons) {
	skeletons = _skeletons;
	isDrawJointsEnabled = isDrawBonesEnabled = true;
	isDrawRangesEnabled = isFontEnabled = false;
	isDraw3dEnabled = false;
	ofEnableDepthTest();
}

void ccBodyRenderer::setup(vector<Skeleton>* _skeletons, ofTrueTypeFont _font, vector<bool> _bodyGroupStates) {
	bodyGroupStates = _bodyGroupStates;
	setup(_skeletons);
	loadFont(_font);
}

void ccBodyRenderer::updateBodyGroupStates(vector<bool> _bodyGroupStates) {
	bodyGroupStates = _bodyGroupStates;
}

void ccBodyRenderer::draw() {
	ofPushStyle();
	ofSetLineWidth(8);
	for (int i = 0; i < skeletons->size(); i++) {
		drawSkeleton(&skeletons->at(i));
	}
	ofPopStyle();
}

void ccBodyRenderer::toggleDraw3d() {
	isDraw3dEnabled = !isDraw3dEnabled;
}

void ccBodyRenderer::drawSkeleton(Skeleton* _skeleton) {
	skeleton = _skeleton;
	setupBodyGroups(skeleton);
	if (isDrawHandsEnabled)  drawHands();
	if (isDrawBonesEnabled)  drawBones();
	if (isDrawJointsEnabled) drawJoints();
	if (isDrawRangesEnabled) drawRanges();
}

void ccBodyRenderer::loadFont(ofTrueTypeFont _font) {
	font = _font;
	if (font.isLoaded()) {
		isFontEnabled = true;
	}
}

void ccBodyRenderer::toggleHands() {
	isDrawHandsEnabled = !isDrawHandsEnabled;
}

void ccBodyRenderer::toggleBones() {
	isDrawBonesEnabled = !isDrawBonesEnabled;
}

void ccBodyRenderer::toggleJoints() {
	isDrawJointsEnabled = !isDrawJointsEnabled;
}

void ccBodyRenderer::toggleRanges() {
	isDrawRangesEnabled = !isDrawRangesEnabled;
}

void ccBodyRenderer::hideAll() {
	isDrawHandsEnabled = false;
	isDrawBonesEnabled = false;
	isDrawJointsEnabled = false;
	isDrawRangesEnabled = false;
}

void ccBodyRenderer::showAll() {
	isDrawHandsEnabled = true;
	isDrawBonesEnabled = true;
	isDrawJointsEnabled = true;
	isDrawRangesEnabled = true;
}

void ccBodyRenderer::drawHands() {
	drawHand(skeleton->getLeftHand(), skeleton->getHandLeft());
	drawHand(skeleton->getRightHand(), skeleton->getHandRight());
}

void ccBodyRenderer::drawHand(Hand hand, Joint handJoint) {
	if (hand.isConfidentlyDetected()) {
		ofFill();
		if (hand.isOpen()) ofSetColor(ofColor::green);
		else ofSetColor(ofColor::red);
		ofCircle(handJoint.getPoint(), 25);
	}
}

void ccBodyRenderer::drawBones() {
	drawTorso();
	drawRightArm();
	drawLeftArm();
	drawRightLeg();
	drawLeftLeg();
}

void ccBodyRenderer::drawBone(Joint baseJoint, Joint connectingJoint) {
	TrackingState trackingState = combinedTrackingState(baseJoint, connectingJoint);

	if (trackingState == TRACKED) {
		ofSetLineWidth(10);
	}
	else if (trackingState == INFERRED) {
		ofSetLineWidth(1);
	}

	drawIn2dOr3d(baseJoint, connectingJoint);

}

void ccBodyRenderer::drawIn2dOr3d(Joint baseJoint, Joint connectingJoint) {
	if (isDraw3dEnabled) {
		draw3dBone(baseJoint, connectingJoint);
	}
	else {
		ofLine(baseJoint.getPoint(), connectingJoint.getPoint());
	}
}

void ccBodyRenderer::assignColorByGroup(Joint baseJoint, Joint connectingJoint) {
	if (upperBodyGroupIsMoving()) {
		if (jointIsInUpperBody(baseJoint) || jointIsInUpperBody(connectingJoint)) {
				setColorRed();
		}
	} 
	if (lowerBodyGroupIsMoving()) {
		if (jointIsInLowerBody(baseJoint) || jointIsInLowerBody(connectingJoint)) {
				setColorRed();
		}
	}
	if (headGroupIsMoving()) {
		if (jointIsInHead(baseJoint) || jointIsInHead(connectingJoint)) {
			setColorRed();
		}
	}
	
}

bool ccBodyRenderer::jointIsInHead(Joint joint) {
	for (int i = 0; i < headGroup.size(); i++) {
		string jointType = headGroup.at(i).getType();
		if (jointType._Equal(joint.getType()) ) {
			return true;
		}
		}
	return false;
	
}

bool ccBodyRenderer::jointIsInLowerBody(Joint joint) {
	for (int i = 0; i < lowerBodyGroup.size(); i++) {
		string jointType = lowerBodyGroup.at(i).getType();
		if (jointType._Equal(joint.getType())) {
			return true;
		}
	}
	return false;
}

bool ccBodyRenderer::jointIsInUpperBody(Joint joint) {
	for (int i = 0; i < upperBodyGroup.size(); i++) {
		string jointType = upperBodyGroup.at(i).getType();
		if (jointType._Equal(joint.getType())) {
			return true;
		}
	}
	return false; 
}

bool ccBodyRenderer::headGroupIsMoving() {
	return bodyGroupStates.at(0);
}

bool ccBodyRenderer::upperBodyGroupIsMoving() {
	return bodyGroupStates.at(1);
}

bool ccBodyRenderer::lowerBodyGroupIsMoving() {
	return bodyGroupStates.at(2);
}



void ccBodyRenderer::draw3dBone(Joint baseJoint, Joint connectingJoint) {
	material.setDiffuseColor(ofFloatColor(ofColor::thistle));
	assignColorByGroup(baseJoint, connectingJoint);

	float baseJointX = baseJoint.getPoint().x;
	float baseJointY = baseJoint.getPoint().y;
	float connectingJointX = connectingJoint.getPoint().x;
	float connectingJointY = connectingJoint.getPoint().y;
	float baseJointZ = baseJoint.getPoint().z;
	float connectingJointZ = connectingJoint.getPoint().z;
	float boneLength = baseJoint.getPoint().distance(connectingJoint.getPoint());
	ofVec3f centerPoint;
	centerPoint.set((baseJointX + connectingJointX) / 2, (baseJointY + connectingJointY) / 2, (baseJointZ + connectingJointZ) / 2);

	ofVec3f preRotateVec;
	ofVec3f postRotateVec;
	preRotateVec.set(0, 1, 0);
	postRotateVec.set(baseJointX - centerPoint.x, baseJointY - centerPoint.y, baseJointZ - centerPoint.z);
	preRotateVec.normalize();
	postRotateVec.normalize();

	float angle = std::acos(dot(preRotateVec, postRotateVec) / (mag(preRotateVec)*mag(postRotateVec)));
	float angleDegrees = (angle * 180) / PI;

	ofPushMatrix();

	ofTranslate(centerPoint);
	if(baseJointX>connectingJointX) {
		ofRotateZ(-angleDegrees);
	}
	else {
		ofRotateZ(angleDegrees);
	}
	material.begin();
	if (jointsAreHeadNeck(baseJoint, connectingJoint)) {
		drawNeckBone(boneLength);
	}
	else {
		ofDrawCylinder(0, 0, preSetZCoord, 25, boneLength*.6);
	}
	material.end();
	setColorDefault();
	ofRotateZ(-angle);
	ofPopMatrix();

}

bool ccBodyRenderer::jointsAreHeadNeck(Joint baseJoint, Joint connectingJoint) {
	bool headToNeck;
	bool neckToHead;
	headToNeck = (baseJoint.getType().find("Neck") != std::string::npos &&
		connectingJoint.getType().find("Head") != std::string::npos);
	neckToHead = (connectingJoint.getType().find("Neck") != std::string::npos &&
		baseJoint.getType().find("Head") != std::string::npos);
	
	return (neckToHead || headToNeck);
}

void ccBodyRenderer::drawNeckBone(float boneLength) {
	ofTranslate(0, -boneLength / 4, 0);
	ofDrawCylinder(0, 0, preSetZCoord, 25, boneLength*0.1);
	ofTranslate(0, boneLength / 4, 0);
}

float ccBodyRenderer::dot(ofVec3f a, ofVec3f b) {  //calculates dot product of a and b
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float ccBodyRenderer::mag(ofVec3f a)  //calculates magnitude of a
{
	return std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}


void ccBodyRenderer::drawTorso() {
	drawBone(skeleton->getHead(), skeleton->getNeck());
	drawBone(skeleton->getNeck(), skeleton->getSpineShoulder());
	drawBone(skeleton->getSpineShoulder(), skeleton->getSpineMid());
	drawBone(skeleton->getSpineMid(), skeleton->getSpineBase());
	drawBone(skeleton->getSpineShoulder(), skeleton->getShoulderRight());
	drawBone(skeleton->getSpineShoulder(), skeleton->getShoulderLeft());
	drawBone(skeleton->getSpineBase(), skeleton->getHipRight());
	drawBone(skeleton->getSpineBase(), skeleton->getHipLeft());
}

void ccBodyRenderer::drawRightArm() {
	drawBone(skeleton->getShoulderRight(), skeleton->getElbowRight());
	drawBone(skeleton->getElbowRight(), skeleton->getWristRight());
	drawBone(skeleton->getWristRight(), skeleton->getHandRight());
	drawBone(skeleton->getHandRight(), skeleton->getHandTipRight());
	drawBone(skeleton->getWristRight(), skeleton->getThumbRight());
}

void ccBodyRenderer::drawLeftArm() {
	drawBone(skeleton->getShoulderLeft(), skeleton->getElbowLeft());
	drawBone(skeleton->getElbowLeft(), skeleton->getWristLeft());
	drawBone(skeleton->getWristLeft(), skeleton->getHandLeft());
	drawBone(skeleton->getHandLeft(), skeleton->getHandTipLeft());
	drawBone(skeleton->getWristLeft(), skeleton->getThumbLeft());
}

void ccBodyRenderer::drawRightLeg() {
	drawBone(skeleton->getHipRight(), skeleton->getKneeRight());
	drawBone(skeleton->getKneeRight(), skeleton->getAnkleRight());
	drawBone(skeleton->getAnkleRight(), skeleton->getFootRight());
}

void ccBodyRenderer::drawLeftLeg() {
	drawBone(skeleton->getHipLeft(), skeleton->getKneeLeft());
	drawBone(skeleton->getKneeLeft(), skeleton->getAnkleLeft());
	drawBone(skeleton->getAnkleLeft(), skeleton->getFootLeft());
}

void ccBodyRenderer::drawJoints() {
	drawJoint(skeleton->getThumbRight());
	drawJoint(skeleton->getSpineBase());
	drawJoint(skeleton->getSpineMid());
	drawJoint(skeleton->getNeck());
	drawJoint(skeleton->getHead());
	drawJoint(skeleton->getShoulderLeft());
	drawJoint(skeleton->getElbowLeft());
	drawJoint(skeleton->getWristLeft());
	drawJoint(skeleton->getHandLeft());
	drawJoint(skeleton->getShoulderRight());
	drawJoint(skeleton->getElbowRight());
	drawJoint(skeleton->getWristRight());
	drawJoint(skeleton->getHandRight());
	drawJoint(skeleton->getHipLeft());
	drawJoint(skeleton->getKneeLeft());
	drawJoint(skeleton->getAnkleLeft());
	drawJoint(skeleton->getFootLeft());
	drawJoint(skeleton->getHipRight());
	drawJoint(skeleton->getKneeRight());
	drawJoint(skeleton->getAnkleRight());
	drawJoint(skeleton->getFootRight());
	drawJoint(skeleton->getSpineShoulder());
	drawJoint(skeleton->getHandTipLeft());
	drawJoint(skeleton->getThumbLeft());
	drawJoint(skeleton->getHandTipRight());
}

void ccBodyRenderer::drawJoint(Joint joint) {
	if (joint.getTrackingState() == TRACKED || joint.getTrackingState() == INFERRED) {
		ofSetColor(ofColor::lightGray);
		ofFill();
		assignColorByGroup(joint, joint);
		material.begin();
		drawJointIn2dOr3d(joint);
		material.end();
		setColorDefault();
	}
}

void ccBodyRenderer::drawJointIn2dOr3d(Joint joint) {
	if (isDraw3dEnabled) {
		if (isHead(joint)) {
			ofDrawSphere(joint.getPoint().x, joint.getPoint().y, preSetZCoord, 80);
		}
		else {
			ofDrawSphere(joint.getPoint().x, joint.getPoint().y, preSetZCoord, 20);
		}
	}
	else {
		ofCircle(joint.getPoint(), 10);
	}
}

bool ccBodyRenderer::isHead(Joint joint) {
	return (joint.getType().find("Head") != std::string::npos);
}

void ccBodyRenderer::drawRanges() {
	ofSetColor(ofColor::purple);
	ofNoFill();
	ofSetLineWidth(1);
	drawRange(skeleton->getLeftHandRange(), skeleton->getHandLeft(), skeleton->getLeftHandNormal());
	drawRange(skeleton->getRightHandRange(), skeleton->getHandRight(), skeleton->getRightHandNormal());
}

void ccBodyRenderer::drawRange(ofRectangle range, Joint hand, ofVec2f normal) {
	ofRect(range);
	if (isFontEnabled) {
		normalReport = ofToString(normal.x) + ", " + ofToString(normal.y);
		font.drawString(normalReport, hand.x(), hand.y() - 50);
	}
}

TrackingState ccBodyRenderer::combinedTrackingState(Joint &joint1, Joint &joint2) {
	if (joint1.isTracked() && joint2.isTracked()) return TRACKED;
	if (joint1.isInferred() && joint2.isTracked()) return INFERRED;
	if (joint1.isTracked() && joint2.isInferred()) return INFERRED;
	return NOT_TRACKED;
}

void ccBodyRenderer::setCoordinateSystem() {
	preSetZCoord = -400;
	ofTranslate(ofGetWidth() * 0.3, ofGetHeight() - (0.25*ofGetHeight()), -400);

}

void ccBodyRenderer::setColorRed() {
	material.setDiffuseColor(ofFloatColor(ofColor(100, 0, 0)));
}

void ccBodyRenderer::setColorDefault() {
	material.setDiffuseColor(ofFloatColor(ofColor::thistle));
}

void ccBodyRenderer::setupBodyGroups(Skeleton* skeleton) {

	headGroup.clear();
	upperBodyGroup.clear();
	lowerBodyGroup.clear();


	headGroup.push_back(skeleton->getHead());
	headGroup.push_back(skeleton->getNeck());

	upperBodyGroup.push_back(skeleton->getElbowLeft());
	upperBodyGroup.push_back(skeleton->getElbowRight());
	upperBodyGroup.push_back(skeleton->getHandLeft());
	upperBodyGroup.push_back(skeleton->getHandRight());
	upperBodyGroup.push_back(skeleton->getHandTipLeft());
	upperBodyGroup.push_back(skeleton->getHandTipRight());
	upperBodyGroup.push_back(skeleton->getShoulderLeft());
	upperBodyGroup.push_back(skeleton->getShoulderRight());
	upperBodyGroup.push_back(skeleton->getSpineBase());
	upperBodyGroup.push_back(skeleton->getSpineMid());
	upperBodyGroup.push_back(skeleton->getWristLeft());
	upperBodyGroup.push_back(skeleton->getWristRight());
	upperBodyGroup.push_back(skeleton->getThumbLeft());
	upperBodyGroup.push_back(skeleton->getThumbRight());
	upperBodyGroup.push_back(skeleton->getSpineShoulder());

	lowerBodyGroup.push_back(skeleton->getAnkleLeft());
	lowerBodyGroup.push_back(skeleton->getAnkleRight());
	lowerBodyGroup.push_back(skeleton->getFootLeft());
	lowerBodyGroup.push_back(skeleton->getFootRight());
	lowerBodyGroup.push_back(skeleton->getHipLeft());
	lowerBodyGroup.push_back(skeleton->getHipRight());
	lowerBodyGroup.push_back(skeleton->getKneeRight());
	lowerBodyGroup.push_back(skeleton->getKneeLeft());

}



