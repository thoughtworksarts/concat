#pragma once

#include "ofMain.h"

class ccSegment {

public:
	void setup(ofMaterial& _material);
    void translateToRotationCenter();
	void draw();
    void setBoxSize(float width, float height, float depth);
	void setCylinderSize(float width, float height);
    void setJointRadius(float radius);
    void toggleWireframes();
	void drawSimpleCylinder(float joint1x, float joint1y, float joint2x, float joint2y, float radius);

	void toggleSegmentHasMoved();

	bool isSegmentMoving();

	bool segmentIsMoving;



protected:
    void calculateSegmentHeight();
	void calculateCylinderSegmentHeight();
    void drawJoint();
    void drawBox();
	void drawCylinder();
    void drawRotationHandle();

    float segmentHeight, halfBoxWidth, halfBoxHeight;

	ofMaterial segmentMaterial;
	ofBoxPrimitive box;
	ofCylinderPrimitive cylinder;
	ofSpherePrimitive joint;

    bool showWireframes;

	//std::vector<float> gradient;

	int gradientDiff;
	bool gradientSlope;

};
