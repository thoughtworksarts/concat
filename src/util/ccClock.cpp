#include "ccClock.h"

void ccClock::setup() {
    timePosition.x = ofGetWidth() - 120;
    timePosition.y = 100;
    font.load("selena.otf", 48);
    runClock = false;
}

void ccClock::update() {
    clock = "0:00";
    if (runClock) {
        int elapsedSeconds = (int)ofGetElapsedTimef();
        string minutes = ofToString(floor(elapsedSeconds / 60));
        string seconds = ofToString(elapsedSeconds % 60, 2, '0');
        clock = minutes + ":" + seconds;
    }
}

void ccClock::draw() {
    font.drawString(clock, timePosition.x, timePosition.y);
}

void ccClock::stop() {
    runClock = false;
}

void ccClock::run() {
    if (!runClock) {
        ofResetElapsedTimeCounter();
        runClock = true;
    }
}