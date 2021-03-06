//
//  GUI.cpp
//  Bachelor
//
//  Created by Frederik Tollund Juutilainen on 13/04/16.

#include "GUI.hpp"

GUI::GUI(){
}

void GUI::setupStartGUI(Voronoi* voronoi, EvolutionaryAlgorithm* evolutionaryAlgorithm){
    this->voronoi = voronoi;
    this->evolutionaryAlgorithm = evolutionaryAlgorithm;
    
    // Add stuff to gui
    guiStart = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    guiStart->addHeader(" ::: Evolutionary Voronoi Tessellation :::"); // Header
    
    // Population size
    populationSizeSlider = guiStart->addSlider("Population size", 10, 250);
    populationSizeSlider->setPrecision(0);
    populationSizeSlider->setValue(evolutionaryAlgorithm->populationSize);
    
    // Dimensional constraints
    dimensionConstraints = guiStart->addFolder("Dimensional Constraints");
    widthConstraintToggle = dimensionConstraints->addToggle("Width",!voronoi->widthConstraint);
    heightConstraintToggle = dimensionConstraints->addToggle("Height",!voronoi->heightConstraint);
    depthConstraintToggle = dimensionConstraints->addToggle("Depth",!voronoi->depthConstraint);
    
    // Dimensions size
    dimensionsFolder = guiStart->addFolder("Dimension size");
    widthSlider = dimensionsFolder->addSlider("Width: ", 100, 1000);
    widthSlider->setPrecision(0);
    widthSlider->setValue(evolutionaryAlgorithm->dimensions.x);
    
    heightSlider = dimensionsFolder->addSlider("Height: ", 100, 1000);
    heightSlider->setPrecision(0);
    heightSlider->setValue(evolutionaryAlgorithm->dimensions.y);
    
    depthSlider = dimensionsFolder->addSlider("Depth: ", 1, 1000);
    depthSlider->setPrecision(0);
    depthSlider->setValue(evolutionaryAlgorithm->dimensions.z);
    
    // Genome size
    genomeSizeSlider = guiStart->addSlider("Genome Size", 5, 500);
    genomeSizeSlider->setPrecision(0);
    genomeSizeSlider->setValue(evolutionaryAlgorithm->genomeSize);
    
    // Fitness stuff
    fitnessFunctionsDropdown = guiStart->addDropdown("Fitness", fitnessFunctionChoices);
    
    // Cross over stuff
    crossoverProbability = guiStart->addSlider("Crossover %: ", 0, 100, evolutionaryAlgorithm->crossoverProbability*100);
    crossoverProbability->setStripeColor(ofColor::red);
    crossoverDropdown = guiStart->addDropdown("Crossover", crossover);
    crossoverDropdown->setStripeColor(ofColor::red);
    
    // Mutation stuff
    mutationFolder = guiStart->addFolder("Mutation");
    mutationRate = mutationFolder->addSlider("Mutation rate",0,100,evolutionaryAlgorithm->mutationRate*100);
    mutationProbability = mutationFolder->addSlider("Mutation %", 0, 100, evolutionaryAlgorithm->mutationProbability*100);
    
    
    // Start button
    startButton = guiStart->addButton("Start evolution!");
    guiStart->addFooter(); // Footer for collapsing
    
    // Add event listeners
    populationSizeSlider->onSliderEvent(this, &GUI::onSliderEvent);
    genomeSizeSlider->onSliderEvent(this, &GUI::onSliderEvent);
    fitnessFunctionsDropdown->onDropdownEvent(this, &GUI::onDropdownEvent);
    crossoverProbability->onSliderEvent(this, &GUI::onSliderEvent);
    crossoverDropdown->onDropdownEvent(this, &GUI::onDropdownEvent);
    mutationRate->onSliderEvent(this, &GUI::onSliderEvent);
    mutationProbability->onSliderEvent(this, &GUI::onSliderEvent);
    startButton->onButtonEvent(this, &GUI::onButtonEvent);
    widthConstraintToggle->onToggleEvent(this, &GUI::onToggleEvent);
    heightConstraintToggle->onToggleEvent(this, &GUI::onToggleEvent);
    depthConstraintToggle->onToggleEvent(this, &GUI::onToggleEvent);
    widthSlider->onSliderEvent(this, &GUI::onSliderEvent);
    heightSlider->onSliderEvent(this, &GUI::onSliderEvent);
    depthSlider->onSliderEvent(this, &GUI::onSliderEvent);
}

void GUI::setupRunGUI(){
    // Disable previous GUI
    guiStart->setVisible(false);
    guiStart->setEnabled(false);
    
    guiRun = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    guiRun->addHeader(ofToString(fitnessFunctionChoices[evolutionaryAlgorithm->fitnessType])); // Header
    
    renderFolder = guiRun->addFolder("Rendering");
    renderingToggle = renderFolder->addToggle("Show rendering",voronoi->isRendering);
    showCenterPointsToggle = renderFolder->addToggle("Show center points",voronoi->isShowingPoints);
    showTessellationMeshToggle = renderFolder->addToggle("Show tessellation",true);
    
    parametersFolder = guiRun->addFolder("Evolutionary parameters");
    populationSizelabel = parametersFolder->addLabel(ofToString("Population size: " + ofToString(evolutionaryAlgorithm->populationSize)));
    genomeSizeLabel = parametersFolder->addLabel("Genome size: " + ofToString(ofToString(evolutionaryAlgorithm->genomeSize)));
    fitnessTypeLabel = parametersFolder->addLabel("Fitness type: " + ofToString(fitnessFunctionChoices.at(evolutionaryAlgorithm->fitnessType)));
    crossoverLabel = parametersFolder->addLabel("Population size: " + ofToString(crossover.at(evolutionaryAlgorithm->crossoverType)));
    crossoverProbabilityLabel = parametersFolder->addLabel("Crossover % : " + ofToString(evolutionaryAlgorithm->crossoverProbability*100));
    mutationRateLabel = parametersFolder->addLabel("Mutation rate: " + ofToString(evolutionaryAlgorithm->mutationRate*100));
    mutationProbabilityLabel = parametersFolder->addLabel("Mutation probability " + ofToString(evolutionaryAlgorithm->mutationProbability*100));
    
    bestFitnessLabel = guiRun->addLabel("Best fitness: ");
    avgFitnessLabel = guiRun->addLabel("Average fitness: ");
    currentGenerationNumberLabel = guiRun->addLabel("Current generation: ");
    
    guiRun->addFRM();
    pauseButton = guiRun->addButton("Pause evolution");
    resetButton = guiRun->addButton(">>> RESET <<<");
    
    exportToCsvButton = guiRun->addButton("Export to CSV");
    exportToCsvButton->setStripeColor(ofColor::darkRed);
    
    // Add event listeners
    pauseButton->onButtonEvent(this, &GUI::onButtonEvent);
    resetButton->onButtonEvent(this, &GUI::onButtonEvent);
    exportToCsvButton->onButtonEvent(this, &GUI::onButtonEvent);
    renderingToggle->onToggleEvent(this, &GUI::onToggleEvent);
    showCenterPointsToggle->onToggleEvent(this, &GUI::onToggleEvent);
    showTessellationMeshToggle->onToggleEvent(this, &GUI::onToggleEvent);
    
    guiRun->addFooter(); // Footer for collapsing
    
}


void GUI::onButtonEvent(ofxDatGuiButtonEvent e){
    if(e.target == startButton){
        ofVec3f d = ofVec3f(widthSlider->getValue(),heightSlider->getValue(),depthSlider->getValue());
        voronoi->dimensions = d;
        evolutionaryAlgorithm->dimensions = d;
        setupRunGUI();
        evolutionaryAlgorithm->startEvolution();
    }
    
    if(e.target == resetButton){
        // Resets
        evolutionaryAlgorithm->evolutionStarted = false;
        evolutionaryAlgorithm->evolutionRunning = false;
        evolutionaryAlgorithm->population.clear(); // Clearing population
        evolutionaryAlgorithm->generationCount = 0;
        voronoi->clear();
        guiRun->setEnabled(false);
        guiRun->setVisible(false);
        guiStart->setEnabled(true);
        guiStart->setVisible(true);
        
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
    
    if(e.target == exportToCsvButton){
        evolutionaryAlgorithm->exportToCsv();
    }
}

void GUI::onToggleEvent(ofxDatGuiToggleEvent e){
    if(e.target == showCenterPointsToggle){
        voronoi->isShowingPoints = showCenterPointsToggle->getChecked();
    }
    
    if(e.target == showTessellationMeshToggle){
        voronoi->isShowingMesh = showTessellationMeshToggle->getChecked();
    }
    
    if(e.target == renderingToggle){
        voronoi->isShowingMesh = renderingToggle->getChecked();
    }
    
    if(e.target == widthConstraintToggle){
        voronoi->widthConstraint = !widthConstraintToggle->getChecked();
    }
    
    if(e.target == heightConstraintToggle){
        voronoi->heightConstraint = !heightConstraintToggle->getChecked();
    }
    
    if(e.target == depthConstraintToggle){
        voronoi->depthConstraint = !depthConstraintToggle->getChecked();
    }
    
}

void GUI::onDropdownEvent(ofxDatGuiDropdownEvent e){
    // Set type of crossover
    if(e.target == crossoverDropdown){
        evolutionaryAlgorithm->crossoverType = e.child;
    }
    
    if(e.target == fitnessFunctionsDropdown){
        evolutionaryAlgorithm->fitnessType = e.child;
    }
    
}

void GUI::onSliderEvent(ofxDatGuiSliderEvent e){
    if(e.target == populationSizeSlider){
        evolutionaryAlgorithm->populationSize = e.value;
    }
    
    if(e.target == genomeSizeSlider){
        evolutionaryAlgorithm->genomeSize = e.value;
    }
    
    if(e.target == crossoverProbability){
        evolutionaryAlgorithm->crossoverProbability = e.value;
    }
    
    if(e.target == mutationProbability){
        evolutionaryAlgorithm->mutationProbability = e.value/100;
    }
    
    if(e.target == mutationRate){
        evolutionaryAlgorithm->mutationRate = e.value/100;
    }
    
    if(e.target == widthSlider){
        evolutionaryAlgorithm->dimensions.x = e.value;
        voronoi->dimensions.x = e.value;

    }
    
    if(e.target == heightSlider){
        evolutionaryAlgorithm->dimensions.y = e.value;
        voronoi->dimensions.y = e.value;
    }
    
    if(e.target == depthSlider){
        evolutionaryAlgorithm->dimensions.z = e.value;
        voronoi->dimensions.z = e.value;
    }
}