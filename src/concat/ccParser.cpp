#include "ofApp.h"

void ccParser::setup(){
    fileName = "test-slash-syntax.txt";
	readFile();
}

void ccParser::readFile(){
    ofBuffer buffer = ofBufferFromFile(fileName);

    if (!buffer.size()) {
        cout << "Couldn't read " << fileName << endl;
    } else {
        loadFileContents(buffer);
    }
}

vector<vector<float>> ccParser::getTargetAngles() {
    return targetAngles;
}

void ccParser::pushToAnglesArray(string line){
    string toPush = line.substr(3);
    if (contains(toPush, "/")) {
        toPush = "-100";
    }
    anglesArray.push_back(ofToFloat(toPush));
}

void ccParser::startNewArray(){
    if (anglesArray.size() == 6) {
        targetAngles.push_back(anglesArray);
        anglesArray.clear();
    }
}

void ccParser::loadFileContents(ofBuffer& buffer){
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;

        if (line.substr(1, 2) == ". ") {
            pushToAnglesArray(line);
            startNewArray();
        }
    }
}

bool ccParser::contains(string haystack, string needle){
    return haystack.find(needle) != string::npos;
}
