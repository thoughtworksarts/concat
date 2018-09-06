#include "ofApp.h"

void ofApp::setup(){
    ofToggleFullscreen();
	bodyGroupStates = { 0, 0, 0 };
    dataParser.setup();
    robot.setup(dataParser.getTargetAngles());
    lighting.setup();
    kinect.setup(bodyGroupStates);
    info.setup();
    clock.setup();

}

void ofApp::update(){
	kinect.update(bodyGroupStates);
    robot.update();
    lighting.update();
    info.update(dataParser.getCurrentFileName());
    clock.update();
	updateBodyGroupStates();
}

void ofApp::draw(){
    ofBackground(ofColor::black);
    robot.draw();
	kinect.draw();
    lighting.draw();
    info.draw();
    clock.draw();
}

void ofApp::updateBodyGroupStates() {
	bodyGroupStates.clear();
	for (int i = 0; i < robot.segmentStates.size(); i++) {
		bool state;
		state = robot.segmentStates.at(i);
		bodyGroupStates.push_back(state);
	}
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
	else if (key == '3') {
		kinect.enable3d();
	}
}
