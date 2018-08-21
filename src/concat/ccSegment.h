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
    void drawBox();
    void drawJoint();
    void drawRotationHandle();

	int rotationHandleLength;
    float segmentHeight, halfBoxWidth, halfBoxHeight;

    ofMaterial material;
	ofBoxPrimitive box;
	ofSpherePrimitive joint;

    bool showWireframes;
};
