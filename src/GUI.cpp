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
    vector<string> tessellationTypes = {"Cylinder","Sphere","Cone"};

    
    // Add stuff to gui
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    gui->addHeader(" ::: Evolutionary Voronoi Tessellation :::"); // Header
    tessellationTypeDropdown = gui->addDropdown("Tessellation types", tessellationTypes);
    populationSizeSlider = gui->addSlider("Population size", 10, 250);
    mutationDropdown = gui->addDropdown("Mutation", mutations);
    crossoverDropdown = gui->addDropdown("Crossover", crossover);
    fitnessFunctionsDropdown = gui->addDropdown("Fitness", fitnessFunctionChoices);
    showCenterPointsToggle = gui->addToggle("Show center points");
    showTessellationMeshToggle = gui->addToggle("Show tessellation");
    bestFitnessLabel = gui->addLabel("Best fitness: ");
    avgFitnessLabel = gui->addLabel("Average fitness: ");
    currentGenerationNumberLabel = gui->addLabel("Current generation");
    gui->addFRM(); // Framerate monitor
    startButton = gui->addButton("Start evolution!");
    gui->addFooter(); // Footer for collapsing
    
    // Add event listeners
    tessellationTypeDropdown->onDropdownEvent(this, &GUI::onDropdownEvent);
    showCenterPointsToggle->onButtonEvent(this, &GUI::onButtonEvent);
    showTessellationMeshToggle->onButtonEvent(this, &GUI::onButtonEvent);
    startButton->onButtonEvent(this, &GUI::onButtonEvent);
    populationSizeSlider->onSliderEvent(this, &GUI::onSliderEvent);
    

}

void GUI::setup(Voronoi* voronoi, EvolutionaryAlgorithm* evolutionaryAlgorithm){
    this->voronoi = voronoi;
    this->evolutionaryAlgorithm = evolutionaryAlgorithm;
    
    // Set initial values
    showCenterPointsToggle->setEnabled(voronoi->isShowingPoints);
    showTessellationMeshToggle->setEnabled(voronoi->isShowingMesh);
    populationSizeSlider->setValue(this->evolutionaryAlgorithm->populationSize);
}


void GUI::onButtonEvent(ofxDatGuiButtonEvent e){
    if(e.target == startButton){
        evolutionaryAlgorithm->startEvolution();
        cout << "Start button pressed" << endl;
    }
    
    if(e.target == showCenterPointsToggle){
        voronoi->isShowingPoints = showCenterPointsToggle->getEnabled();
    }
    
    if(e.target == showTessellationMeshToggle){
        voronoi->isShowingMesh = showTessellationMeshToggle->getEnabled();
        
    }
    
}

void GUI::onDropdownEvent(ofxDatGuiDropdownEvent e){
    if(e.target == tessellationTypeDropdown){
        voronoi->tessellationType = e.child;
    }
    
}




void GUI::onSliderEvent(ofxDatGuiSliderEvent e){
    if(e.target == populationSizeSlider){
        evolutionaryAlgorithm->populationSize = (int) e.value;
        cout << e.value << endl;
    }
    
    
}