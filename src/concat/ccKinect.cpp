#include "ccKinect.h"

void ccKinect::setup() {
    smallFont.load("selena.otf", 16);
    largeFont.load("selena.otf", 48);
    kinect.setup(12345, smallFont);
    skeletons = kinect.getSkeletons();
    renderer.setup(skeletons, largeFont);

    infoPosition.x = ofGetWidth() * 0.25;
    infoPosition.y = ofGetHeight() * 0.5;
}

void ccKinect::update() {
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
    //kinect.drawDebug();
    ofTranslate(ofGetWidth() * 0.25, 0);
    renderer.draw();
    ofPopMatrix();
}