#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setupStartGUI(&voronoi,&evolutionaryAlgorithm);
}

//--------------------------------------------------------------
void ofApp::update(){
    if(evolutionaryAlgorithm.evolutionRunning){
        if(evolutionaryAlgorithm.generationCount < 5000000)
        {
            evolutionaryAlgorithm.produceNextGeneration();
            evolutionaryAlgorithm.generationCount++;
            
        }
    }
}



//--------------------------------------------------------------
void ofApp::draw(){
    if(evolutionaryAlgorithm.evolutionRunning){
    voronoi.createPhenotype(&evolutionaryAlgorithm.population.front());
    }
    voronoi.draw();
    
    // Update GUI & CSV
    if(evolutionaryAlgorithm.evolutionRunning){
        gui.currentGenerationNumberLabel->setLabel("Current generation: " + ofToString(evolutionaryAlgorithm.generationCount));
        gui.bestFitnessLabel->setLabel("Best fitness: " + ofToString(evolutionaryAlgorithm.population.front().fitness));
        gui.avgFitnessLabel->setLabel("Average fitness: " + ofToString(evolutionaryAlgorithm.getAverageFitness()));
        evolutionaryAlgorithm.bestFitnessVector.push_back(evolutionaryAlgorithm.population.front().fitness);
        evolutionaryAlgorithm.avgFitnessVector.push_back(evolutionaryAlgorithm.getAverageFitness());
    }
    if(evolutionaryAlgorithm.evolutionStarted){
    gui.updateGraph(evolutionaryAlgorithm.getAverageFitness(),evolutionaryAlgorithm.population.front().fitness);
    }
    
    if(evolutionaryAlgorithm.generationCount == 10 || evolutionaryAlgorithm.generationCount == 100 || evolutionaryAlgorithm.generationCount == 1000){
        evolutionaryAlgorithm.evolutionRunning = false;
    }
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
