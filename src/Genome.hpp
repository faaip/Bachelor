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
#include "ofMain.h"

class Genome{
public:
    // Methods
    Genome();
    void randomizeChromosome();
    Genome reproduce(Genome otherParent);
    void mutate();
    
    // Variables
    int fitness;
    vector<ofPoint> chromosome;
    
    
};

#endif /* Genome_hpp */
