#include "ofApp.h"

void ofApp::setup(){
    //ofToggleFullscreen();
    dataParser.setup();
    robot.setup(dataParser.getTargetAngles());
    lighting.setup();

	smallFont.load("selena.otf", 16);
	largeFont.load("selena.otf", 48);
	kinect.setup(12345, smallFont);
	skeletons = kinect.getSkeletons();
	renderer.setup(skeletons, largeFont);

    setupInfoOverlay();
}

void ofApp::update(){
	kinect.update();
    robot.update();
    lighting.update();
}

void ofApp::draw(){
    ofBackground(ofColor::black);
    robot.draw();
    lighting.draw();

	ofPushMatrix();
	//kinect.drawDebug();
	ofTranslate(ofGetWidth() *0.25, 0);
	renderer.draw();
	ofPopMatrix();


    ofSetColor(ofColor::white);
    ofDrawBitmapString(info, infoPosition);
}

void ofApp::keyPressed(int key){
    if (key == 'r') {
        robot.resetAnimation();
    } else if (key == 'w') {
        robot.toggleWireframes();
        lighting.toggleLighting();
    } else if (key == 'l') {
        lighting.toggleLightPositions();
    }
}

void ofApp::setupInfoOverlay() {
    info = "";
    info += "r: reset animation\n";
    info += "w: toggle wireframes\n";
    info += "l: toggle lights\n";

    infoPosition.x = ofGetWidth() - 250;
    infoPosition.y = 100;
}
