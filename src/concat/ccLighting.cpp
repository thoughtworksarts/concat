#include "ccLighting.h"

void ccLighting::setup() {
	numLights = 5;
	showLightPositions = false;
    showLighting = true;

    ofEnableDepthTest();

    for (int i = 0; i < numLights; i++) {
        ofLight light;
        lights.push_back(light);
        lights.back().setDiffuseColor(ofFloatColor(.85, .85, .55));
        lights.back().setSpecularColor(ofFloatColor(1.f, 1.f, 1.f));
        lights.back().enable();
    }
}

void ccLighting::update() {
    if (showLighting) {
        ofEnableLighting();
        ofSetSmoothLighting(true);
    }
    else {
        ofDisableLighting();
        ofSetSmoothLighting(false);
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
	lights[0].setPosition(ofGetWidth() * 0.25, ofGetHeight() * (0.45 + lightingHeightAdjustment), lightingDepth);
	lights[1].setPosition(ofGetWidth() * 0.75, ofGetHeight() * (0.45 + lightingHeightAdjustment), lightingDepth);
	lights[2].setPosition(ofGetWidth() * 0.25, ofGetHeight() * (0.95 + lightingHeightAdjustment), lightingDepth);
	lights[3].setPosition(ofGetWidth() * 0.75, ofGetHeight() * (0.95 + lightingHeightAdjustment), lightingDepth);
	lights[4].setPosition(ofGetWidth() * 0.5, ofGetHeight() * 0.9, 205);

}

void ccLighting::draw() {
    if (showLightPositions) {
        for (const auto& light : lights) {
            light.draw();
        }
    }
}

void ccLighting::toggleLightPositions() {
    showLightPositions = !showLightPositions;
}

void ccLighting::toggleLighting() {
    showLighting = !showLighting;
}