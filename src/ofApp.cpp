#include "ofApp.h"

void ofApp::setup(){
    ofToggleFullscreen();
    dataParser.setup();
    robot.setup(dataParser.getTargetAngles());
    lighting.setup();
    kinect.setup();
    info.setup();
    clock.setup();
}

void ofApp::update(){
	kinect.update();
    robot.update();
    lighting.update();
    info.update(dataParser.getCurrentFileName());
    clock.update();
}

void ofApp::draw(){
    ofBackground(ofColor::black);
    robot.draw();
    lighting.draw();
    kinect.draw();
    info.draw();
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
    } else if (key == 'f') {
        ofToggleFullscreen();
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
