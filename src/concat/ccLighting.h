#pragma once

#include "ofMain.h"

class ccLighting {

public:
	void setup();
	void update();
	void draw();
    void toggleLightPositions();
    void toggleLighting();

protected:
	int numLights;
	vector<ofLight> lights;
	bool showLightPositions, showLighting;

	float lightingHeightAdjustment;
	float lightingDepth;

    int width, height, xPosition;
};
