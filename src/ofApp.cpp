#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    setupGui();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::setupGui(){
    ofxDatGui* gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    vector<string> mutations = {"Bit string mutation", "Flip Bit", "Boundary"};
    vector<string> crossover = {"Single point", "Two point", "Uniform", "Arithmetic"};
    
    ofxDatGuiDropdown* mutationsDropdown;
    ofxDatGuiDropdown* crossoverDropdown;
    ofxDatGuiSlider* populationSizeSlider;
    
    populationSizeSlider = gui->addSlider("Population size", 10, 100);
    populationSizeSlider->setPrecision(0);
    populationSizeSlider->setValue(50);
    mutationsDropdown = gui->addDropdown("Mutations", mutations);
    crossoverDropdown = gui->addDropdown("Crossover", crossover);
    
    gui->addButton("Start!");
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
