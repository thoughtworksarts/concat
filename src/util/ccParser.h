#pragma once

#include "ofMain.h"

class ccParser {
public:
    void setup();
    void readFile();
    void loadPreviousFile();
    void loadNextFile();
    string getCurrentFileName();
    vector<vector<float>> getTargetAngles();

protected:
    void loadFileNameFromIndex();
    void loadFileContents(ofBuffer& buffer);
    void pushToAnglesArray(string line);
    void startNewArray();
    bool contains(string haystack, string needle);

    int fileIndex, numFiles;
    string fileName;
    vector<vector<float>> targetAngles;
    vector<float> anglesArray;
};
