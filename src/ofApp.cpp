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
}

void ofApp::update(){
    updateInfoOverlay();
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
    } else if (key == OF_KEY_LEFT) {
        dataParser.loadPreviousFile();
        robot.newPositionSet(dataParser.getTargetAngles());
    } else if (key == OF_KEY_RIGHT) {
        dataParser.loadNextFile();
        robot.newPositionSet(dataParser.getTargetAngles());
    }
}

void ofApp::updateInfoOverlay() {
    info = "";
    info += "r: reset animation\n";
    info += "w: toggle wireframes\n";
    info += "l: toggle lights\n";
    info += "\n";
    info += "file: " + dataParser.getCurrentFileName();

    infoPosition.x = ofGetWidth() - 350;
    infoPosition.y = 60;
}
