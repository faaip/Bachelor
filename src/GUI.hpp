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
#include "Genome.hpp"

class GUI{
public:
    // Methods
    GUI();
    void disableElements();
    void updateGraph(float average, float max);
    void setupStartGUI(Voronoi* voronoi, EvolutionaryAlgorithm* evolutionaryAlgorithm);
    void setupRunGUI();


    // Event listeners
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void onToggleEvent(ofxDatGuiToggleEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void onDropdownEvent(ofxDatGuiDropdownEvent e);

    // Start GUI Elements
    ofxDatGui* guiStart; // GUI Element for start choices
    ofxDatGuiSlider* populationSizeSlider;
    ofxDatGuiSlider* genomeSizeSlider;
    ofxDatGuiDropdown* fitnessFunctionsDropdown;
    ofxDatGuiDropdown* crossoverDropdown;
    ofxDatGuiSlider* crossoverProbability;
    ofxDatGuiFolder* dimensionConstraints;
    ofxDatGuiToggle* widthConstraintToggle;
    ofxDatGuiToggle* heightConstraintToggle;
    ofxDatGuiToggle* depthConstraintToggle;
    ofxDatGuiFolder* mutationFolder;
    ofxDatGuiSlider* mutationRate;
    ofxDatGuiSlider* mutationProbability;
    ofxDatGuiButton* startButton;
    ofxDatGuiButton* resetButton;
    
    ofxDatGuiFolder* dimensionsFolder;
    ofxDatGuiSlider* widthSlider;
    ofxDatGuiSlider* heightSlider;
    ofxDatGuiSlider* depthSlider;
    
    // Run GUI elements
    ofxDatGui* guiRun; // GUI while running algorithm
    ofxDatGuiFolder* parametersFolder;
    ofxDatGuiLabel* populationSizelabel;
    ofxDatGuiLabel* genomeSizeLabel;
    ofxDatGuiLabel* fitnessTypeLabel;
    ofxDatGuiLabel* crossoverLabel;
    ofxDatGuiLabel* crossoverProbabilityLabel;
    ofxDatGuiLabel* mutationRateLabel;
    ofxDatGuiLabel* mutationProbabilityLabel;
    
    ofxDatGuiLabel* bestFitnessLabel;
    ofxDatGuiLabel* avgFitnessLabel;
    ofxDatGuiLabel* currentGenerationNumberLabel;
    ofxDatGuiButton* pauseButton;
    ofxDatGuiValuePlotter* averageValuePlotter;
    ofxDatGuiFolder* renderFolder;
    ofxDatGuiToggle* renderingToggle;
    ofxDatGuiToggle* showCenterPointsToggle;
    ofxDatGuiToggle* showTessellationMeshToggle;
    ofxDatGuiButton* exportToCsvButton;
    
   
    
    // Variables
    class Voronoi* voronoi; // Voronoi pointer
    EvolutionaryAlgorithm* evolutionaryAlgorithm; // Pointer to evolutionary algorithm
    
    vector<string> crossover = {"Single point crossover", "Two point crossover", "Uniform crossover"};
    vector<string> mutations = {"Bit string mutation"};
    vector<string> fitnessFunctionChoices = {"Faces / Dist to middle","Long edge length", "Faces * dist to middle", "Faces * edge length", "Number of faces", "Away from smallest", "Dist. to middle"};
    vector<string> tessellationTypes = {"Flat surface","Cylinder","Sphere","Cone"};
};

#endif /* GUI_hpp */
