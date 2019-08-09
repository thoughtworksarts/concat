#pragma once

#include "ofMain.h"

class ccInfo {

public:
	void setup();
	void update(string currentFileName);
    void draw();

protected:
    string info;
    ofVec2f infoPosition;
};
