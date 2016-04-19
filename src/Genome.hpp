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
    float fitness;
    vector<ofPoint> chromosome;
  
    // Overload < operator
    bool operator<(const Genome& b)
    {
        return this->fitness < b.fitness;
    }
    
};

#endif /* Genome_hpp */
