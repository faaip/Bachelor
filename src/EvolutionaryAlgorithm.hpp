//
//  EvolutionaryAlgorithm.hpp
//  Bachelor
//
//  Created by Frederik Tollund Juutilainen on 13/04/16.
//
//

#ifndef EvolutionaryAlgorithm_hpp
#define EvolutionaryAlgorithm_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Genome.hpp"
#include "Defines.h"

class EvolutionaryAlgorithm{
public:
    // Methods
    EvolutionaryAlgorithm();
    void initializePopulation();
    void evaluatePopulation();
    void produceNextGeneration();
    void calculateFitness(Genome* g);
    void startEvolution();
    bool hasHigherFitness(Genome x, Genome y);
    bool evolutionStarted = false;
    void setCrossoverType(int t);
    void setMutationType(int t);

    // Variables
    int populationSize = 30;
    int generationCount = 0;
    int eliteCount = 2; //
    float crossoverProbability = 0.7;
    vector<Genome> population;
    float getAverageFitness();
    int mutationType = 0;
    int crossoverType = 0;
    float mutationProbability = 0.1;

};

#endif /* EvolutionaryAlgorithm_hpp */
