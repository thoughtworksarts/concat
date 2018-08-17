#include "ofApp.h"

void ofApp::setup(){
    armSegmentLength = 200;
    rotationHandleLength = 30;
    halfArmSegmentLength = armSegmentLength * 0.5;
}

void ofApp::update(){

}

void ofApp::draw(){
    ofPushMatrix();
    setCoordinateSystem();
    drawLine();
    ofPopMatrix();
}

void ofApp::drawLine(){
    ofSetColor(ofColor::wheat);
    ofDrawLine(0, 0, 0, armSegmentLength);
    ofSetColor(ofColor::green);
    ofDrawLine(0, halfArmSegmentLength, rotationHandleLength, halfArmSegmentLength);
}

void ofApp::setCoordinateSystem(){
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight());
    ofRotateZ(180);
    ofRotateY(180);
}
