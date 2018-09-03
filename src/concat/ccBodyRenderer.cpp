#include "ccBodyRenderer.h"

void ccBodyRenderer::setup(vector<Skeleton>* _skeletons) {
	skeletons = _skeletons;
	isDrawHandsEnabled = isDrawJointsEnabled = isDrawBonesEnabled = true;
	isDrawRangesEnabled = isFontEnabled = false;
	isDraw3dEnabled = false;
	ofEnableDepthTest();
}

void ccBodyRenderer::setup(vector<Skeleton>* _skeletons, ofTrueTypeFont _font) {
	setup(_skeletons);
	loadFont(_font);
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

void ccBodyRenderer::drawNeck(Joint head, Joint neck) {
	TrackingState trackingState = combinedTrackingState(head, neck);

	if (trackingState == TRACKED) {
		ofSetLineWidth(10);
		ofSetColor(ofColor::white);
		if (isDraw3dEnabled) {
			//Draw 3d Here
			float headX = head.getPoint().x;
			float headY = head.getPoint().y;
			float neckX = neck.getPoint().x;
			float neckY = neck.getPoint().y;
			float headZ = head.getPoint().z;
			float neckZ = neck.getPoint().z;
			float neckLength = head.getPoint().distance(neck.getPoint());
			ofVec3f centerPoint; 
			centerPoint.set((headX + neckX) / 2, (headY + neckY) / 2, (headZ + neckZ) / 2);

			ofVec3f preRotateVec;
			ofVec3f postRotateVec;

			preRotateVec.set(centerPoint.x - centerPoint.x, (centerPoint.y + neckLength / 2) - centerPoint.y, centerPoint.z - centerPoint.z);
			postRotateVec.set(headX - centerPoint.x, headY - centerPoint.y, headZ - centerPoint.z);
			
			float angle = atan2(preRotateVec.y - postRotateVec.y, preRotateVec.x - postRotateVec.x);
			float angleDeg = (angle * 180) / PI;

			ofPushMatrix();
			ofTranslate(centerPoint);
			ofRotateZ(-(-90-angleDeg));
			ofDrawCylinder(0, 0, 0, 25, neckLength);
			ofRotateZ(-(90-angleDeg));
			ofTranslate(-centerPoint);
			ofPopMatrix();
			ofDrawLine(head.getPoint(), neck.getPoint());
			
		}
		else {
			ofLine(head.getPoint(), neck.getPoint());
		}
	}
	else if (trackingState == INFERRED) {
		ofSetLineWidth(1);
		ofSetColor(ofColor::gray);
		if (isDraw3dEnabled) {
			//Draw 3d here
		}
		else {
			ofLine(head.getPoint(), neck.getPoint());
		}
	}
}

void ccBodyRenderer::drawTorso() {
	drawNeck(skeleton->getHead(), skeleton->getNeck());
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

void ccBodyRenderer::drawBone(Joint joint1, Joint joint2) {

	TrackingState trackingState = combinedTrackingState(joint1, joint2);

	if (trackingState == TRACKED) {
		ofSetLineWidth(10);
		ofSetColor(ofColor::white);
		if (isDraw3dEnabled) {
			//Draw 3d Here
			//ofDrawCylinder(joint1.getPoint().x, joint1.getPoint().y, 0, 20, joint2.getPoint().y - joint1.getPoint().y);
		}
		else {
			ofLine(joint1.getPoint(), joint2.getPoint());
		}
	}
	else if (trackingState == INFERRED) {
		ofSetLineWidth(1);
		ofSetColor(ofColor::gray);
		if (isDraw3dEnabled) {
			//Draw 3d here
		}
		else {
			ofLine(joint1.getPoint(), joint2.getPoint());
		}
	}
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
		if (isDraw3dEnabled) {
			ofDrawSphere(joint.getPoint(), 10);
		}
		else {
			ofCircle(joint.getPoint(), 10);
		}
	}
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
