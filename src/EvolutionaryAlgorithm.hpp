//
//  EvolutionaryAlgorithm.hpp
//  Bachelor
//
//  Created by Frederik Tollund Juutilainen on 13/04/16.

#ifndef EvolutionaryAlgorithm_hpp
#define EvolutionaryAlgorithm_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Genome.hpp"
#include "ofxCsv.h"
#include "Defines.h"
#include "Voronoi.hpp"

class EvolutionaryAlgorithm{
public:
    // Methods
    EvolutionaryAlgorithm(Voronoi* voronoi);
    void initializePopulation();
    void evaluatePopulation();
    void produceNextGeneration();
    void startEvolution();
    bool evolutionRunning = false;
    bool evolutionStarted = false;
    void exportToCsv();
    
    // Variables
    int populationSize = 30;
    int generationCount = 0;
    int genomeSize = 25;
    int eliteCount = 2; //
    float crossoverProbability = 0.90;
    vector<Genome> population;
    int fitnessType = 0;
    float getAverageFitness();
    int mutationType = 0;
    float mutationRate = 0.15;
    int crossoverType = 0;
    float mutationProbability = 0.05;
    Voronoi* voronoi;
    vector<double> bestFitnessVector;
    vector<double> avgFitnessVector;
    
    // Dimensions
    ofVec3f dimensions = ofVec3f(615,820,15);
    
    //CSV
    ofxCsv csv;
};

#endif /* EvolutionaryAlgorithm_hpp */
