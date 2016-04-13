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
#include "ofxDatGui.h"

class GUI{
public:
    // Methods
    GUI();

    // Event listeners
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);

    // GUI Elements
    ofxDatGui* gui; // GUI Element
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

};

#endif /* GUI_hpp */
