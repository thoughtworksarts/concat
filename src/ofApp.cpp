#include "ofApp.h"

void ofApp::setup(){
    armSegmentLength = 200;
    headLength = 70;
    rotationHandleLength = 30;

    halfArmSegmentLength = armSegmentLength * 0.5;
    halfHeadLength = headLength * 0.5;

    currentArmPosition = 0;
    numAngles = 6;

    setupTargetAngles();
    setupCurrentAngles();
    setupPrimitives();
}

void ofApp::setupTargetAngles(){
    dataParser.setup();
    targetAngles = dataParser.getTargetAngles();
}

void ofApp::setupCurrentAngles(){
    ofxAnimatableFloat angle;
    for(int i = 0; i < numAngles; i++){
        currentAngles.push_back(angle);
        currentAngles.back().setup();
        currentAngles.back().setDuration(1);
        currentAngles.back().setCurve(LINEAR);
        currentAngles.back().reset(targetAngles.at(0).at(i));
    }
}

void ofApp::setupPrimitives() {
    box.set(30, 200, 30);
}

void ofApp::update(){
    segmentThickness = 8;

    if(ofGetFrameNum() % 60 == 0){
        incrementTargetArmPosition();
        animateToNewArmPosition();
    }

    for(int i = 0; i < currentAngles.size(); i++){
        currentAngles.at(i).update(ofGetLastFrameTime());
    }
}

void ofApp::incrementTargetArmPosition(){
    currentArmPosition++;
    if(currentArmPosition >= targetAngles.size()){
        currentArmPosition = 0;
    }
}

void ofApp::animateToNewArmPosition(){
    for(int i = 0; i < currentAngles.size(); i++){
        float targetAngle = targetAngles.at(currentArmPosition).at(i);
        currentAngles.at(i).animateTo(targetAngle);
    }
}

void ofApp::draw(){
    ofBackground(ofColor::black);
    ofPushMatrix();
    setCoordinateSystem();
    drawArmSegment();
    ofRotateY(currentAngles.at(0).getCurrentValue());
    ofRotateZ(currentAngles.at(1).getCurrentValue());
    drawArmSegment();
    ofRotateY(currentAngles.at(2).getCurrentValue());
    ofRotateZ(currentAngles.at(3).getCurrentValue());
    drawArmSegment();
    ofRotateY(currentAngles.at(4).getCurrentValue());
    ofRotateZ(currentAngles.at(5).getCurrentValue());
    drawHead();
    ofPopMatrix();
}

void ofApp::drawArmSegment(){
    ofSetColor(ofColor::wheat);
    ofSetLineWidth(segmentThickness);
    ofDrawLine(0, 0, 0, armSegmentLength);
    segmentThickness -= 2;

    ofPushMatrix();
    ofTranslate(0, halfArmSegmentLength);
    ofSetLineWidth(1);
    ofSetColor(ofColor::grey);
    box.draw();
    ofSetColor(ofColor::white);
    box.drawWireframe();
    ofPopMatrix();

    ofSetColor(ofColor::green);
    ofSetLineWidth(1);
    ofDrawLine(0, halfArmSegmentLength, rotationHandleLength, halfArmSegmentLength);
    ofTranslate(0, armSegmentLength);
}

void ofApp::drawHead(){
    ofSetColor(ofColor::wheat);
    ofSetLineWidth(2);
    ofDrawLine(0, 0, 0, headLength);
    ofSetColor(ofColor::red);
    ofSetLineWidth(1);
    ofDrawLine(0, halfHeadLength, rotationHandleLength, halfHeadLength);
    ofTranslate(0, headLength);
}

void ofApp::keyPressed(int key){
    if (key == ' ') {
        currentArmPosition = 0;
    }
}

void ofApp::setCoordinateSystem(){
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight());
    ofRotateZ(180);
    ofRotateY(180);
}
