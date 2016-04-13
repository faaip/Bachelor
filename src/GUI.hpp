//
//  GUI.hpp
//  Bachelor
//
//  Created by Frederik Tollund Juutilainen on 13/04/16.
//
//

#ifndef GUI_hpp
#define GUI_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Voronoi.hpp"
#include "EvolutionaryAlgorithm.hpp"
#include "ofxDatGui.h"

class GUI{
public:
    // Methods
    GUI();
    void setup(Voronoi* voronoi, EvolutionaryAlgorithm* evolutionaryAlgorithm);

    // Event listeners
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void onDropdownEvent(ofxDatGuiDropdownEvent e);

    // GUI Elements
    ofxDatGui* gui; // GUI Element
    ofxDatGuiDropdown* tessellationTypeDropdown;
    ofxDatGuiSlider* populationSizeSlider;
    ofxDatGuiDropdown* mutationDropdown;
    ofxDatGuiDropdown* crossoverDropdown;
    ofxDatGuiDropdown* fitnessFunctionsDropdown;
    ofxDatGuiToggle* showCenterPointsToggle;
    ofxDatGuiToggle* showTessellationMeshToggle;
    ofxDatGuiLabel* bestFitnessLabel;
    ofxDatGuiLabel* avgFitnessLabel;
    ofxDatGuiLabel* currentGenerationNumberLabel;
    ofxDatGuiButton* startButton;

    // Variables
    class Voronoi* voronoi; // Voronoi pointer
    EvolutionaryAlgorithm* evolutionaryAlgorithm; // Pointer to evolutionary algorithm
    
    
};

#endif /* GUI_hpp */
