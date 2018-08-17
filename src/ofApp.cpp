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
}

void ofApp::setupTargetAngles(){
    vector<float> pos1;
    pos1.push_back(107.556142);
    pos1.push_back(18.287954);
    pos1.push_back(-31.694707);
    pos1.push_back(-80.173142);
    pos1.push_back(54.40202);
    pos1.push_back(47.5225);

    vector<float> pos2;
    pos2.push_back(110.502873);
    pos2.push_back(16.85499);
    pos2.push_back(-20.773317);
    pos2.push_back(-87.495543);
    pos2.push_back(57.44562);
    pos2.push_back(56.339155);

    vector<float> pos3;
    pos3.push_back(113.372196);
    pos3.push_back(16.271157);
    pos3.push_back(-11.389181);
    pos3.push_back(-92.732377);
    pos3.push_back(60.845318);
    pos3.push_back(63.778976);

    vector<float> pos4;
    pos4.push_back(116.29416);
    pos4.push_back(16.350309);
    pos4.push_back(-3.061874);
    pos4.push_back(-96.456603);
    pos4.push_back(64.53781);
    pos4.push_back(70.298685);

    vector<float> pos5;
    pos5.push_back(119.329193);
    pos5.push_back(17.022485);
    pos5.push_back(4.454193);
    pos5.push_back(-98.926051);
    pos5.push_back(68.481621);
    pos5.push_back(76.19116);

    vector<float> pos6;
    pos6.push_back(122.479141);
    pos6.push_back(18.291301);
    pos6.push_back(11.296822);
    pos6.push_back(-100.255313);
    pos6.push_back(72.590903);
    pos6.push_back(81.70761);

    vector<float> pos7;
    pos7.push_back(125.665559);
    pos7.push_back(20.23136);
    pos7.push_back(17.556564);
    pos7.push_back(-100.57044);
    pos7.push_back(76.690369);
    pos7.push_back(87.145924);

    vector<float> pos8;
    pos8.push_back(128.66848);
    pos8.push_back(23.014765);
    pos8.push_back(23.309274);
    pos8.push_back(-100.123533);
    pos8.push_back(80.473966);
    pos8.push_back(92.88569);

    vector<float> pos9;
    pos9.push_back(130.993569);
    pos9.push_back(26.985379);
    pos9.push_back(28.554497);
    pos9.push_back(-99.550575);
    pos9.push_back(83.506039);
    pos9.push_back(99.348326);

    vector<float> pos10;
    pos10.push_back(131.877011);
    pos10.push_back(32.521767);
    pos10.push_back(33.035984);
    pos10.push_back(-99.957375);
    pos10.push_back(85.505193);
    pos10.push_back(106.654038);

    vector<float> pos11;
    pos11.push_back(130.740536);
    pos11.push_back(39.451151);
    pos11.push_back(36.417019);
    pos11.push_back(-102.461201);
    pos11.push_back(86.890494);
    pos11.push_back(114.382414);

    vector<float> pos12;
    pos12.push_back(127.112475);
    pos12.push_back(47.065512);
    pos12.push_back(38.297369);
    pos12.push_back(-107.858463);
    pos12.push_back(88.574989);
    pos12.push_back(121.605188);

    vector<float> pos13;
    pos13.push_back(120.883761);
    pos13.push_back(54.090575);
    pos13.push_back(38.374275);
    pos13.push_back(-116.263754);
    pos13.push_back(91.091263);
    pos13.push_back(127.016004);

    vector<float> pos14;
    pos14.push_back(112.75928);
    pos14.push_back(59.188555);
    pos14.push_back(36.617348);
    pos14.push_back(-126.960876);
    pos14.push_back(93.498382);
    pos14.push_back(129.876592);

    vector<float> pos15;
    pos15.push_back(103.855914);
    pos15.push_back(61.991292);
    pos15.push_back(33.621096);
    pos15.push_back(-139.462815);
    pos15.push_back(94.271113);
    pos15.push_back(132.207103);

    vector<float> pos16;
    pos16.push_back(93.941446);
    pos16.push_back(63.065103);
    pos16.push_back(30.362214);
    pos16.push_back(-155.992647);
    pos16.push_back(93.131507);
    pos16.push_back(141.560735);

    vector<float> pos17;
    pos17.push_back(77.775978);
    pos17.push_back(63.156367);
    pos17.push_back(25.114061);
    pos17.push_back(-191.962938);
    pos17.push_back(88.307968);
    pos17.push_back(204.464226);

    vector<float> pos18;
    pos18.push_back(62.817733);
    pos18.push_back(67.521004);
    pos18.push_back(3.044449);
    pos18.push_back(-237.169308);
    pos18.push_back(79.171296);
    pos18.push_back(260.532436);

    vector<float> pos19;
    pos19.push_back(57.977668);
    pos19.push_back(69.13058);
    pos19.push_back(-9.143051);
    pos19.push_back(-249.688436);
    pos19.push_back(78.663213);
    pos19.push_back(274.174776);

    vector<float> pos20;
    pos20.push_back(53.831612);
    pos20.push_back(65.322775);
    pos20.push_back(-9.497544);
    pos20.push_back(-255.251856);
    pos20.push_back(80.194003);
    pos20.push_back(277.264364);

    targetAngles.push_back(pos1);
    targetAngles.push_back(pos2);
    targetAngles.push_back(pos3);
    targetAngles.push_back(pos4);
    targetAngles.push_back(pos5);
    targetAngles.push_back(pos6);
    targetAngles.push_back(pos7);
    targetAngles.push_back(pos8);
    targetAngles.push_back(pos9);
    targetAngles.push_back(pos10);
    targetAngles.push_back(pos11);
    targetAngles.push_back(pos12);
    targetAngles.push_back(pos13);
    targetAngles.push_back(pos14);
    targetAngles.push_back(pos15);
    targetAngles.push_back(pos16);
    targetAngles.push_back(pos17);
    targetAngles.push_back(pos18);
    targetAngles.push_back(pos19);
    targetAngles.push_back(pos20);
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
    ofSetLineWidth(3);
    ofDrawLine(0, 0, 0, armSegmentLength);
    ofSetColor(ofColor::green);
    ofSetLineWidth(1);
    ofDrawLine(0, halfArmSegmentLength, rotationHandleLength, halfArmSegmentLength);
    ofTranslate(0, armSegmentLength);
}

void ofApp::drawHead(){
    ofSetColor(ofColor::wheat);
    ofSetLineWidth(4);
    ofDrawLine(0, 0, 0, headLength);
    ofSetColor(ofColor::red);
    ofSetLineWidth(1);
    ofDrawLine(0, halfHeadLength, rotationHandleLength, halfHeadLength);
    ofTranslate(0, headLength);
}

void ofApp::setCoordinateSystem(){
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight());
    ofRotateZ(180);
    ofRotateY(180);
}
