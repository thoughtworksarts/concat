#pragma once

#include "ofMain.h"

class ccParser {
public:
    void setup();
    void readFile();
    vector<vector<float>> getTargetAngles();

protected:
    void loadFileContents(ofBuffer& buffer);
    void pushToAnglesArray(string line);
    void startNewArray();
    bool contains(string haystack, string needle);

    string fileName;
    vector<vector<float>> targetAngles;
    vector<float> anglesArray;
};
