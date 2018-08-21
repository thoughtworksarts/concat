#include "ofApp.h"

void ccParser::setup(){
    fileIndex = 0;
    readFile();
}

void ccParser::readFile(){
    loadFileNameFromIndex();
    ofBuffer buffer = ofBufferFromFile(fileName);

    if (!buffer.size()) {
        cout << "Couldn't read " << fileName << endl;
    } else {
        loadFileContents(buffer);
    }
}

void ccParser::loadPreviousFile(){
    fileIndex--;
    if(fileIndex < 0){
        fileIndex = numFiles - 1;
    }
    readFile();
}

void ccParser::loadNextFile(){
    fileIndex++;
    if(fileIndex >= numFiles){
        fileIndex = 0;
    }
    readFile();
}

string ccParser::getCurrentFileName(){
    return fileName;
}

vector<vector<float>> ccParser::getTargetAngles() {
    return targetAngles;
}

void ccParser::loadFileNameFromIndex(){
    ofDirectory dir("./");
    dir.allowExt("txt");
    dir.listDir();
    fileName = dir.getPath(fileIndex);
    numFiles = dir.size();
}

void ccParser::loadFileContents(ofBuffer& buffer){
    targetAngles.clear();
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
