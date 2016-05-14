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
    void disableElements();
    void updateGraph(float input);

    // Event listeners
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void onDropdownEvent(ofxDatGuiDropdownEvent e);

    // GUI Elements
    ofxDatGui* gui; // GUI Element
    ofxDatGuiSlider* populationSizeSlider;
    ofxDatGuiLabel* populationSizelabel;
    ofxDatGuiDropdown* crossoverDropdown;
    ofxDatGuiLabel* crossoverLabel;
    ofxDatGuiDropdown* fitnessFunctionsDropdown;
    ofxDatGuiToggle* showCenterPointsToggle;
    ofxDatGuiToggle* showTessellationMeshToggle;
    ofxDatGuiLabel* bestFitnessLabel;
    ofxDatGuiLabel* avgFitnessLabel;
    ofxDatGuiLabel* currentGenerationNumberLabel;
    ofxDatGuiButton* startButton;
    ofxDatGuiButton* pauseButton;
    ofxDatGuiValuePlotter* averageValuePlotter;

    // Variables
    class Voronoi* voronoi; // Voronoi pointer
    EvolutionaryAlgorithm* evolutionaryAlgorithm; // Pointer to evolutionary algorithm
    
    vector<string> crossover = {"Single point crossover", "Two point crossover"};
    vector<string> mutations = {"Bit string mutation"};
    vector<string> fitnessFunctionChoices = {"1","2","3"};
    vector<string> tessellationTypes = {"Flat surface","Cylinder","Sphere","Cone"};
};

#endif /* GUI_hpp */
