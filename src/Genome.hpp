//
//  Genome.hpp
//  Bachelor
//
//  Created by Frederik Tollund Juutilainen on 13/04/16.
//
//

#ifndef Genome_hpp
#define Genome_hpp

#include <stdio.h>
#include "Defines.h"
#include "Genome.hpp"
#include "ofMain.h"

class Genome{
public:
    // Methods
    Genome();
    void randomizeChromosome();
    Genome reproduce(Genome otherParent);
    void mutate();
    
    // Variables
    float fitness = 0;
    vector<ofPoint> chromosome;
    float probability = 0;
  
    // Overload < operator
    bool operator<(Genome other) const
    {
        return fitness > other.fitness;
    };

    
};

#endif /* Genome_hpp */
