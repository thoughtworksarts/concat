#pragma once

#include "ofMain.h"

class ccSegment {

public:
	void setup(ofMaterial& _material);
    void translateToRotationCenter();
	void draw();
    void setBoxSize(float width, float height, float depth);
    void setJointRadius(float radius);
    void toggleWireframes();

protected:
    void calculateSegmentHeight();
    void drawJoint();
    void drawBox();
    void drawRotationHandle();

    float segmentHeight, halfBoxWidth, halfBoxHeight;

    ofMaterial material;
	ofBoxPrimitive box;
	ofSpherePrimitive joint;

    bool showWireframes;
};
