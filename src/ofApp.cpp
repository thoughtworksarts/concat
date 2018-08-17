#include "ofApp.h"

void ofApp::setup(){
    armSegmentLength = 200;
    rotationHandleLength = 30;
    halfArmSegmentLength = armSegmentLength * 0.5;
}

void ofApp::update(){

}

void ofApp::draw(){
    ofBackground(ofColor::black);
    ofPushMatrix();
    setCoordinateSystem();
    drawArmSegment();
    drawArmSegment();
    drawArmSegment();
    ofPopMatrix();
}

void ofApp::drawArmSegment(){
    ofSetColor(ofColor::wheat);
    ofSetLineWidth(3);
    ofDrawLine(0, 0, 0, armSegmentLength);
    ofSetColor(ofColor::green);
    ofSetLineWidth(1);
    ofDrawLine(0, halfArmSegmentLength, rotationHandleLength, halfArmSegmentLength);
    ofTranslate(0, armSegmentLength);
}

void ofApp::setCoordinateSystem(){
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight());
    ofRotateZ(180);
    ofRotateY(180);
}
