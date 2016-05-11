#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup(&voronoi,&evolutionaryAlgorithm);
}

//--------------------------------------------------------------
void ofApp::update(){
    if(evolutionaryAlgorithm.evolutionStarted){
        voronoi.createPhenotype(evolutionaryAlgorithm.population.front());
        
        if(evolutionaryAlgorithm.generationCount < 5000)
        {
            evolutionaryAlgorithm.produceNextGeneration();
            evolutionaryAlgorithm.generationCount++;
        }
    }
}



//--------------------------------------------------------------
void ofApp::draw(){
    voronoi.draw();
    
    // Update GUI
    if(evolutionaryAlgorithm.evolutionStarted){
        gui.currentGenerationNumberLabel->setLabel("Current generation: " + ofToString(evolutionaryAlgorithm.generationCount));
        gui.bestFitnessLabel->setLabel("Best fitness: " + ofToString(evolutionaryAlgorithm.population.front().fitness));
        gui.avgFitnessLabel->setLabel("Average fitness: " + ofToString(evolutionaryAlgorithm.getAverageFitness()));
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 32){
        if(evolutionaryAlgorithm.evolutionStarted){
            evolutionaryAlgorithm.evolutionStarted = false;
        }else{
            evolutionaryAlgorithm.evolutionStarted = true;
            
        }
    }
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
