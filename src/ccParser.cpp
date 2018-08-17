#include "ofApp.h"

void ccParser::setup(){
    fileName = "coordinates-aug-3.txt";
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

void ccParser::loadFileContents(ofBuffer& buffer){
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;

        if (!line.empty()) {
            cout << line << endl;
        }
    }
}
