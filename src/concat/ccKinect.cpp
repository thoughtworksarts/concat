#include "ccKinect.h"

void ccKinect::setup() {
    smallFont.load("selena.otf", 16);
    largeFont.load("selena.otf", 48);
    kinect.setup(12345, smallFont);
    skeletons = kinect.getSkeletons();
    renderer.setup(skeletons, largeFont);
}

void ccKinect::update() {
    kinect.update();
}

void ccKinect::draw() {
    ofPushMatrix();
    //kinect.drawDebug();
    ofTranslate(ofGetWidth() * 0.25, 0);
    renderer.draw();
    ofPopMatrix();
}