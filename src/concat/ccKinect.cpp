#include "ccKinect.h"

void ccKinect::setup(vector<bool> _bodyGroupStates) {
    smallFont.load("selena.otf", 16);
    largeFont.load("selena.otf", 48);
    kinect.setup(12345, smallFont);
    skeletons = kinect.getSkeletons();

	bodyGroupStates = _bodyGroupStates;

    renderer.setup(skeletons, largeFont, bodyGroupStates);

    infoPosition.x = ofGetWidth() * 0.25;
    infoPosition.y = ofGetHeight() * 0.5;
    renderTranslation.x = ofGetWidth() * -0.25;

	renderer.setCoordinateSystem();

}

void ccKinect::update(vector<bool> _bodyGroupStates) {
	bodyGroupStates = _bodyGroupStates;
	renderer.updateBodyGroupStates(bodyGroupStates);
    kinect.update();
}

void ccKinect::draw() {
    if (kinect.hasSkeletons()) {
        drawSkeletons();
    }
    else {
        ofSetColor(ofColor::grey);
        ofDrawBitmapString("Searching for skeletons...", infoPosition);
    }
}

void ccKinect::drawSkeletons() {
    ofPushMatrix();
    ofTranslate(renderTranslation);
    renderer.drawSkeleton(kinect.getNearestSkeleton());
    ofPopMatrix();
}

void ccKinect::enable3d() {
	renderer.toggleDraw3d();
}