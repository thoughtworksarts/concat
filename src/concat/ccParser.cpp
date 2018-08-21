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

void ccParser::loadFileContents(ofBuffer& buffer){
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;

        if (line.substr(1, 2) == ". ") {
            pushToAnglesArray(line);
            startNewArray();
        }
    }
}

void ccParser::pushToAnglesArray(string line){
    string toPush = line.substr(3);
    if (contains(toPush, "/")) {
        toPush = ofToString(targetAngles.back().at(anglesArray.size()));
    }
    anglesArray.push_back(ofToFloat(toPush));
}

void ccParser::startNewArray(){
    if (anglesArray.size() == 6) {
        targetAngles.push_back(anglesArray);
        anglesArray.clear();
    }
}

bool ccParser::contains(string haystack, string needle){
    return haystack.find(needle) != string::npos;
}
