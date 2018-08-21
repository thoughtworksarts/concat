#pragma once

#include "ofMain.h"

class ccSegment {

public:
	void setup(ofMaterial& _material);
	void draw();
    void setBoxSize(float width, float height, float depth);
    void setJointRadius(float radius);
    void toggleWireframes();

protected:
    void calculateSegmentHeight();

	int rotationHandleLength;
    float segmentHeight, halfBoxHeight;

    ofMaterial material;
	ofBoxPrimitive box;
	ofSpherePrimitive joint;

    bool showWireframes;
};
