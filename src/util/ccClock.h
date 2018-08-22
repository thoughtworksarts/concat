#pragma once

#include "ofMain.h"

class ccClock {

public:
	void setup();
	void update();
    void draw();
    void stop();
    void run();

protected:
    string clock;
    bool runClock;
    ofTrueTypeFont font;
    ofVec2f timePosition;
};
