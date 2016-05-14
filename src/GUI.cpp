//
//  GUI.cpp
//  Bachelor
//
//  Created by Frederik Tollund Juutilainen on 13/04/16.
//
//

#include "GUI.hpp"

GUI::GUI(){
    // Add stuff to gui
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    gui->addHeader(" ::: Evolutionary Voronoi Tessellation :::"); // Header
    populationSizeSlider = gui->addSlider("Population size", 10, 250);
    populationSizelabel = gui->addLabel("");
    populationSizelabel->setVisible(false);
    crossoverDropdown = gui->addDropdown("Crossover", crossover);
    crossoverLabel = gui->addLabel("Crossvaddv");
    crossoverLabel->setVisible(false);
    fitnessFunctionsDropdown = gui->addDropdown("Fitness", fitnessFunctionChoices);
    showCenterPointsToggle = gui->addToggle("Show center points");
    showTessellationMeshToggle = gui->addToggle("Show tessellation");
    bestFitnessLabel = gui->addLabel("Best fitness: ");
    avgFitnessLabel = gui->addLabel("Average fitness: ");
    currentGenerationNumberLabel = gui->addLabel("Current generation: ");
    startButton = gui->addButton("Start evolution!");
    
    gui->addFooter(); // Footer for collapsing
    
    // Add event listeners
    showCenterPointsToggle->onButtonEvent(this, &GUI::onButtonEvent);
    showTessellationMeshToggle->onButtonEvent(this, &GUI::onButtonEvent);
    startButton->onButtonEvent(this, &GUI::onButtonEvent);
    populationSizeSlider->onSliderEvent(this, &GUI::onSliderEvent);
    crossoverDropdown->onDropdownEvent(this, &GUI::onDropdownEvent);
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
        disableElements();
        evolutionaryAlgorithm->startEvolution();
    }
    
    if(e.target == showCenterPointsToggle){
        voronoi->isShowingPoints = showCenterPointsToggle->getEnabled();
    }
    
    if(e.target == showTessellationMeshToggle){
        voronoi->isShowingMesh = showTessellationMeshToggle->getEnabled();
        
    }
    
    if(e.target == pauseButton){
        if(evolutionaryAlgorithm->evolutionRunning){
            evolutionaryAlgorithm->evolutionRunning = false;
            pauseButton->setLabel("Pause evolution");
        }else{
            evolutionaryAlgorithm->evolutionRunning = true;
            pauseButton->setLabel("Continue evolution");
        }
    }
}

void GUI::onDropdownEvent(ofxDatGuiDropdownEvent e){
    // Set type of crossover
    if(e.target == crossoverDropdown){
        evolutionaryAlgorithm->crossoverType = e.child;
    }
    
}

void GUI::disableElements(){
    // Turns sliders in to labels (and so on)
    crossoverDropdown->setVisible(false);
    crossoverLabel->setLabel(crossover.at(evolutionaryAlgorithm->crossoverType));
    crossoverLabel->setVisible(true);
    
    populationSizeSlider->setVisible(false);
    populationSizelabel->setLabel(ofToString(evolutionaryAlgorithm->populationSize));
    populationSizelabel->setVisible(true);
    
    gui->addFRM(); // Framerate monitor
    startButton->setVisible(false);
    pauseButton = gui->addButton("Pause evolution");
    pauseButton->onButtonEvent(this, &GUI::onButtonEvent);
    
}


void GUI::onSliderEvent(ofxDatGuiSliderEvent e){
    if(e.target == populationSizeSlider){
        evolutionaryAlgorithm->populationSize = (int) e.value;
        cout << e.value << endl;
    }
    
    
}