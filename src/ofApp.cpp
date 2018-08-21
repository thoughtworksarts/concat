#include "ofApp.h"

void ofApp::setup(){
    ofToggleFullscreen();
    dataParser.setup();
    robot.setup(dataParser.getTargetAngles());

	smallFont.loadFont("selena.otf", 16);
	largeFont.loadFont("selena.otf", 48);
	kinect.setup(12345, smallFont);
	skeletons = kinect.getSkeletons();
	renderer.setup(skeletons, largeFont);
}

void ofApp::update(){
	kinect.update();
    robot.update();
}

void ofApp::draw(){
    ofBackground(ofColor::black);
    robot.draw();

	//kinect.drawDebug();
	renderer.draw();
}

void ofApp::keyPressed(int key){
    if (key == 'r') {
        robot.resetAnimation();
    } else if (key == 'w') {
        robot.toggleWireframes();
    } else if (key == 'l') {
        robot.toggleLights();
    }
}
