#include "ofApp.h"

void ofApp::setup(){
    
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
    ofDrawLine(0, 0, 0, 200);
}

void ofApp::setCoordinateSystem(){
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight());
    ofRotateZ(180);
}
