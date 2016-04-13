//
//  GUI.cpp
//  Bachelor
//
//  Created by Frederik Tollund Juutilainen on 13/04/16.
//
//

#include "GUI.hpp"

GUI::GUI(){
    vector<string> crossover = {"Single point crossover", "Two point crossover", "Uniform crossover", "Arithmetic crossover"};
    vector<string> mutations = {"Bit string mutation", "Boundary", "Non-Uniform", "Uniform", "Gaussian"};
        vector<string> fitnessFunctionChoices = {"1","2","3"};

    // Add stuff to gui
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    gui->addHeader(" ::: Evolutionary Voronoi Tessellation :::"); // Header
    populationSizeSlider = gui->addSlider("Population size", 10, 250);
    mutationDropdown = gui->addDropdown("Mutation", mutations);
    crossoverDropdown = gui->addDropdown("Crossover", crossover);
    fitnessFunctionsDropdown = gui->addDropdown("Fitness", fitnessFunctionChoices);
    showCenterPointsToggle = gui->addToggle("Show center points");
    showTessellationMeshToggle = gui->addToggle("Show tessellation");
    bestFitnessLabel = gui->addLabel("Best fitness: ");
    avgFitnessLabel = gui->addLabel("Average fitness: ");
    currentGenerationNumberLabel = gui->addLabel("Current generation");
    startButton = gui->addButton("Start evolution!");
    
    // Add event listeners
    startButton->onButtonEvent(this, &GUI::onButtonEvent);

}



void GUI::onButtonEvent(ofxDatGuiButtonEvent e){
    if(e.target == startButton){
        cout << "Start button pressed" << endl;
    }
    
    
}


void GUI::onSliderEvent(ofxDatGuiSliderEvent e){
    
}