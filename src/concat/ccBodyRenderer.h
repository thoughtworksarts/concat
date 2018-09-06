#pragma once
#include "ofMain.h"
#include "ofxKinectV2OSC.h"

class ccBodyRenderer {
public:
	virtual void setup(vector<Skeleton>* _skeletons);
	virtual void setup(vector<Skeleton>* _skeletons, ofTrueTypeFont _font, vector<bool> _bodyGroupStates);
	void draw();
	void drawSkeleton(Skeleton* _skeleton);
	void loadFont(ofTrueTypeFont _font);

	void toggleHands();
	void toggleBones();
	void toggleJoints();
	void toggleRanges();
	void hideAll();
	void showAll();

	void drawHands();
	virtual void drawHand(Hand hand, Joint handJoint);

	void drawBones();
	void drawTorso();
	void drawRightArm();
	void drawLeftArm();
	void drawRightLeg();
	void drawLeftLeg();
	virtual void drawBone(Joint joint1, Joint joint2);

	void draw3dBone(Joint joint1, Joint joint2);

	void drawJoints();
	virtual void drawJoint(Joint joint);

	void drawRanges();
	virtual void drawRange(ofRectangle range, Joint hand, ofVec2f normal);

	bool isDraw3dEnabled;
	void toggleDraw3d();

	float dot(ofVec3f a, ofVec3f b);
	float mag(ofVec3f a);

	void ccBodyRenderer::setCoordinateSystem();

	int preSetZCoord;

	bool jointsAreHeadNeck(Joint baseJoint, Joint connectingJoint);

	void drawIn2dOr3d(Joint baseJoint, Joint connectingJoint);

	void drawJointIn2dOr3d(Joint joint);

	void drawNeckBone(float boneLength);

	bool isHead(Joint joint);

	vector<Joint> headGroup;

	vector<Joint> upperBodyGroup;

	vector<Joint> lowerBodyGroup;

	void setupBodyGroups(Skeleton* skeleton);

	vector<bool> bodyGroupStates;

	void updateBodyGroupStates(vector<bool> _bodyGroupStates);

	void assignColorByGroup(Joint baseJoint, Joint connectingJoint);

	ofMaterial material;

	bool headGroupIsMoving();

	bool upperBodyGroupIsMoving();

	bool lowerBodyGroupIsMoving();

	bool jointIsInHead(Joint joint);

	bool jointIsInLowerBody(Joint joint);

	bool jointIsInUpperBody(Joint joint);

	void setColorRed();

	void setColorDefault();


protected:
	TrackingState combinedTrackingState(Joint &joint1, Joint &joint2);

	vector<Skeleton>* skeletons;
	Skeleton* skeleton;
	ofTrueTypeFont font;
	string normalReport;

	bool isDrawHandsEnabled, isDrawBonesEnabled, isDrawJointsEnabled, isDrawRangesEnabled, isFontEnabled;

};