#include "ofApp.h"

void ofApp::setup(){
    armLength = 200;
    jointSize = 50;
    armSegmentThickness = 10;
    armSegmentLength = armLength - jointSize;

    headLength = 70;
    rotationHandleLength = 30;

    halfArmLength = armLength * 0.5;
    halfHeadLength = headLength * 0.5;
    halfJointSize = jointSize * 0.5;

    currentArmPosition = 0;
    numAngles = 6;
    numArmSegments = 3;

    showWireframes = false;
    showLights = false;

    setupTargetAngles();
    setupCurrentAngles();
    setupPrimitives();
    setupLighting();
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
    ofBoxPrimitive armSegment;
    for (int i = 0; i < numArmSegments; i++) {
        int thickness = 50 - i * armSegmentThickness;
        armSegments.push_back(armSegment);
        armSegments.back().set(thickness, armSegmentLength, thickness);
    }

    ofSpherePrimitive joint;
    for (int i = 0; i < numArmSegments; i++) {
        joints.push_back(joint);
        joints.back().setRadius(halfJointSize - 5 * i);
    }
}

void ofApp::setupLighting() {
    pointLight1.setDiffuseColor(ofFloatColor(.85, .85, .55));
    pointLight1.setSpecularColor(ofFloatColor(1.f, 1.f, 1.f));
    pointLight1.setPosition(ofGetWidth() * 0.75, ofGetHeight() * 0.25, -20);
    pointLight1.enable();

    pointLight2.setDiffuseColor(ofFloatColor(.85, .85, .55));
    pointLight2.setSpecularColor(ofFloatColor(1.f, 1.f, 1.f));
    pointLight2.setPosition(ofGetWidth() * 0.25, ofGetHeight() * 0.25, -20);
    pointLight2.enable();

    material.setShininess(120);
    material.setSpecularColor(ofColor(255, 255, 255, 255));
}

void ofApp::update(){
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

    if (showWireframes) {
        ofDisableLighting();
        ofSetSmoothLighting(false);
    } else {
        ofEnableLighting();
        ofSetSmoothLighting(true);
    }

    if (showLights) {
        pointLight1.draw();
        pointLight2.draw();
    }

    ofPushMatrix();
    setCoordinateSystem();
    drawArmSegment(0);
    ofRotateY(currentAngles.at(0).getCurrentValue());
    ofRotateZ(currentAngles.at(1).getCurrentValue());
    drawArmSegment(1);
    ofRotateY(currentAngles.at(2).getCurrentValue());
    ofRotateZ(currentAngles.at(3).getCurrentValue());
    drawArmSegment(2);
    ofRotateY(currentAngles.at(4).getCurrentValue());
    ofRotateZ(currentAngles.at(5).getCurrentValue());
    drawHead();
    ofPopMatrix();
}

void ofApp::drawArmSegment(int segmentId){
    material.begin();
    ofFill();

    ofPushMatrix();
    ofTranslate(0, halfArmLength);

    if (showWireframes) {
        ofSetColor(ofColor::white);
        armSegments.at(segmentId).drawWireframe();
    } else {
        ofSetColor(ofColor::grey);
        armSegments.at(segmentId).draw();
    }

    ofTranslate(0, halfArmLength);

    if (showWireframes) {
        ofSetColor(ofColor::white);
        joints.at(segmentId).drawWireframe();
    } else {
        ofSetColor(ofColor::grey);
        joints.at(segmentId).draw();
    }

    ofPopMatrix();

    ofSetColor(ofColor::green);
    ofSetLineWidth(1);
    ofDrawLine(0, halfArmLength, rotationHandleLength, halfArmLength);
    ofTranslate(0, armLength);

    material.end();
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
    if (key == 'r') {
        currentArmPosition = 0;
    } else if (key == 'w') {
        showWireframes = !showWireframes;
    } else if (key == 'l') {
        showLights = !showLights;
    }
}

void ofApp::setCoordinateSystem(){
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight());
    ofRotateZ(180);
    ofRotateY(180);
}
