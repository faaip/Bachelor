//
//  Genome.hpp
//  Bachelor
//
//  Created by Frederik Tollund Juutilainen on 13/04/16.

#ifndef Genome_hpp
#define Genome_hpp

#include <stdio.h>
#include "Defines.h"
#include "Genome.hpp"
#include "ofMain.h"

class Genome{
public:
    // Methods
    Genome(int genomeSize, ofVec3f d);
    void randomizeChromosome();
    Genome reproduce(Genome otherParent);
    void mutate(float mutationRate);
    
    // Variables
    double fitness = 0;
    vector<ofPoint> chromosome;
    int genomeSize = 0;

    // Overload < operator
    bool operator<(Genome other) const
    {
        return fitness > other.fitness;
    };
    
    // Crossover
    Genome singlePointCrossover(Genome otherParent);
    Genome twoPointCrossover(Genome otherParent);
    
    // Mutation
    
    // Dimensions size
    ofVec3f dimensions;
    
};

#endif /* Genome_hpp */
