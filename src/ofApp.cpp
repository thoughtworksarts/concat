#include "ofApp.h"

void ofApp::setup(){
    ofToggleFullscreen();
    dataParser.setup();
    robot.setup(dataParser.getTargetAngles());
    lighting.setup();
    kinect.setup();
    clock.setup();

    infoPosition.x = ofGetWidth() - 350;
    infoPosition.y = 60;
}

void ofApp::update(){
    updateInfoOverlay();
	kinect.update();
    robot.update();
    lighting.update();
    clock.update();
}

void ofApp::draw(){
    ofBackground(ofColor::black);
    robot.draw();
    lighting.draw();
    kinect.draw();

    ofSetColor(ofColor::white);
    ofDrawBitmapString(info, infoPosition);

    clock.draw();
}

void ofApp::keyPressed(int key){
    if (key == 'r') {
        robot.resetAnimation();
        clock.stop();
    } else if (key == ' ') {
        robot.togglePlaying();
        clock.run();
    } else if (key == 'w') {
        robot.toggleWireframes();
        lighting.toggleLighting();
    } else if (key == 'l') {
        lighting.toggleLightPositions();
    } else if (key == OF_KEY_LEFT) {
        dataParser.loadPreviousFile();
        robot.newPositionSet(dataParser.getTargetAngles());
        robot.resetAnimation();
    } else if (key == OF_KEY_RIGHT) {
        dataParser.loadNextFile();
        robot.newPositionSet(dataParser.getTargetAngles());
        robot.resetAnimation();
    }
}

void ofApp::updateInfoOverlay() {
    info = "";
    info += "r: reset animation\n";
    info += "w: toggle wireframes\n";
    info += "l: toggle lights\n";
    info += "SPACE: play / pause\n";
    info += "\n";
    info += "file: " + dataParser.getCurrentFileName();
}
