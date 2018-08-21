#pragma once

#include "ofMain.h"

class ccParser {
    public:
    void setup();
    void readFile();
    vector<vector<float>> getTargetAngles();

    protected:
    string fileName;
    vector<vector<float>> targetAngles;
    vector<float> anglesArray;

    void loadFileContents(ofBuffer& buffer);
};
