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

class EvolutionaryAlgorithm{
public:
    // Methods
    EvolutionaryAlgorithm();
    void initializePopulation();
    void evaluatePopulation();
    void produceNextGeneration();
    void calculateFitness(Genome g);
    bool hasHigherFitness(Genome x, Genome y);
    
    
    // Variables
    int populationSize;
    vector<Genome> population;
};

#endif /* EvolutionaryAlgorithm_hpp */
