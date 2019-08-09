#include "ccInfo.h"

void ccInfo::setup() {
    infoPosition.x = ofGetWidth() - 350;
    infoPosition.y = 60;
}

void ccInfo::update(string currentFileName) {
    info = "";
    info += "r: reset animation\n";
    info += "w: toggle wireframes\n";
    info += "l: toggle lights\n";
    info += "f: toggle fullscreen\n";
    info += "SPACE: play / pause\n";
    info += "\n";
    info += "file: " + currentFileName;
}

void ccInfo::draw() {
    //ofSetColor(ofColor::white);
    //ofDrawBitmapString(info, infoPosition);
}
