#pragma once

#include "ofMain.h"

class ccParser {
    public:
    void setup();
    void readFile();

    protected:
    string fileName;

    void loadFileContents(ofBuffer& buffer);
};
