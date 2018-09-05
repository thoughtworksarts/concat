#include "ccLighting.h"

void ccLighting::setup() {
	numLights = 5;
	showLightPositions = false;
    showLighting = true;
    ofSetSmoothLighting(true);

    width = ofGetWidth() * 0.5;
    height = ofGetHeight();
    xPosition = ofGetWidth() * 0.5 + 1;

    for (int i = 0; i < numLights; i++) {
        ofLight light;
        lights.push_back(light);
        lights.back().setDiffuseColor(ofFloatColor(ofColor(100, 128, 128)));
        lights.back().setSpecularColor(ofFloatColor(1.f, 1.f, 1.f));
        lights.back().enable();
    }
}

void ccLighting::update() {
    if (showLighting) {
        ofEnableLighting();
    }

	if (showLightPositions) {
		lightingHeightAdjustment = ofMap(ofGetMouseY(), 0, ofGetHeight(), -0.25, 0);
		lightingDepth = ofMap(ofGetMouseX(), 0, ofGetWidth(), -200, 200);
		cout << "lightingHeightAdjustment = " << lightingHeightAdjustment << endl;
		cout << "lightingDepth = " << lightingDepth << endl;
	}
	else {
		lightingHeightAdjustment = 0.00130209;
		lightingDepth = -73.4375;
	}
	lights[0].setPosition(xPosition + width * 0.25, height * (0.45 + lightingHeightAdjustment), lightingDepth);
	lights[1].setPosition(xPosition + width * 0.75, height * (0.45 + lightingHeightAdjustment), lightingDepth);
	lights[2].setPosition(xPosition + width * 0.25, height * (0.95 + lightingHeightAdjustment), lightingDepth);
	lights[3].setPosition(xPosition + width * 0.75, height * (0.95 + lightingHeightAdjustment), lightingDepth);
	lights[4].setPosition(xPosition + width * 0.5, height * 0.9, 205);

}

void ccLighting::draw() {
    if (showLightPositions) {
        for (const auto& light : lights) {
            light.draw();
        }
    }
    ofDisableLighting();
}

void ccLighting::toggleLightPositions() {
    showLightPositions = !showLightPositions;
}

void ccLighting::toggleLighting() {
    showLighting = !showLighting;
}