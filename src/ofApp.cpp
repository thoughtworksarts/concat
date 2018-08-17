#include "ofApp.h"

void ofApp::setup(){
    
}

void ofApp::update(){

}

void ofApp::draw(){
    ofPushMatrix();
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight());
    drawLine();
    ofPopMatrix();
}

void ofApp::drawLine(){
    ofSetColor(ofColor::wheat);
    ofDrawLine(0, 0, 200, -200);
}
