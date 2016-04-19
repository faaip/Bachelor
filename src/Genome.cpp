//
//  Genome.cpp
//  Bachelor
//
//  Created by Frederik Tollund Juutilainen on 13/04/16.
//
//

#include "Genome.hpp"

Genome::Genome(){
    // Randomize at first
    randomizeChromosome();
    
}

void Genome::randomizeChromosome(){
    for(int i = 0; i < NUMBER_OF_POINTS;i++){
        ofPoint newCell = ofPoint(ofRandom(-_width*0.5,_width*0.5),
                                  ofRandom(-_height*0.5,_height*0.5),
                                  ofRandom(-_deep*0.25,_deep*0.25));
        chromosome.push_back(newCell);
    }
}