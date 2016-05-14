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
    populationSizeSlider->setPrecision(0);
    populationSizelabel = gui->addLabel("");
    populationSizelabel->setVisible(false);
    
    fitnessFunctionsDropdown = gui->addDropdown("Fitness", fitnessFunctionChoices);
    crossoverDropdown = gui->addDropdown("Crossover", crossover);
    showCenterPointsToggle = gui->addToggle("Show center points");
    showTessellationMeshToggle = gui->addToggle("Show tessellation");
    bestFitnessLabel = gui->addLabel("Best fitness: ");
    avgFitnessLabel = gui->addLabel("Average fitness: ");
    currentGenerationNumberLabel = gui->addLabel("Current generation: ");

    // Start button turns into pause button
    startButton = gui->addButton("Start evolution!");
    pauseButton = gui->addButton("Pause evolution");
    pauseButton->setVisible(false);
    pauseButton->onButtonEvent(this, &GUI::onButtonEvent);
    
    // Footer for collapsing
    gui->addFooter();
    
    // Value plotter
    averageValuePlotter = gui->addValuePlotter("Average fitness", 0, 2000);
    averageValuePlotter->setDrawMode(ofxDatGuiGraph::LINES);
    averageValuePlotter->setSpeed(0);
    
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
            pauseButton->setLabel("Continue evolution");
        }else{
            evolutionaryAlgorithm->evolutionRunning = true;
            pauseButton->setLabel("Pause evolution");
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
    populationSizeSlider->setEnabled(false);
    populationSizeSlider->setVisible(false);
    populationSizelabel->setLabel("Population size: " + ofToString(evolutionaryAlgorithm->populationSize));
    populationSizelabel->setVisible(true);
    
    
    
    startButton->ofxDatGuiComponent::setEnabled(false);
    startButton->setVisible(false);
    pauseButton->setVisible(true);
    
}

void GUI::updateGraph(float input){
    if(evolutionaryAlgorithm->evolutionRunning){
        averageValuePlotter->setSpeed(1);
        averageValuePlotter->setValue(input);
    }else{
        averageValuePlotter->setSpeed(0);
        
    }
    
}

void GUI::onSliderEvent(ofxDatGuiSliderEvent e){
    if(e.target == populationSizeSlider){
        evolutionaryAlgorithm->populationSize = (int) e.value;
        cout << e.value << endl;
    }
}