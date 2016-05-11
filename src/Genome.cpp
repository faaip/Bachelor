//
//  Genome.cpp
//  Bachelor
//
//  Created by Frederik Tollund Juutilainen on 13/04/16.
//
//

#include "Genome.hpp"

Genome::Genome(){
    
}

void Genome::randomizeChromosome(){
    chromosome.clear();
    for(int i = 0; i < NUMBER_OF_POINTS;i++){
        ofPoint newCell = ofPoint(ofRandom(0,_width),
                                  ofRandom(0,_height),
                                  ofRandom(0,_deep));
        chromosome.push_back(newCell);
    }
}

Genome Genome::singlePointCrossover(Genome otherParent){
    // Reproducing using single-point crossover
    Genome child = Genome();
    
    int r = ofRandom(0,NUMBER_OF_POINTS); // random single point
    
    for(int i = 0; i < r; i++){
        child.chromosome.push_back(chromosome.at(i)); // from mother
    }
    
    for(int i = r; i < NUMBER_OF_POINTS; i++){
        child.chromosome.push_back(otherParent.chromosome.at(i)); // from other parent
    }
    return child;
}

Genome Genome::twoPointCrossover(Genome otherParent){
    // Reproducing using two-point crossover
    Genome child = Genome();
    
    int r1 = ofRandom(0,NUMBER_OF_POINTS);
    int r2 = ofRandom(0,NUMBER_OF_POINTS);
    
    if (r1>r2)//sure that 2>1
    {
        std::swap(r1,r2);
    }
    
    // From mother
    for(int i = 0; i < r1; i++){
        child.chromosome.push_back(this->chromosome.at(i));
    }
    
    // From father
    for(int i = r1; i < r2; i++){
        child.chromosome.push_back(otherParent.chromosome.at(i));
    }
    
    // From mother (again)
    for(int i = r2; i < NUMBER_OF_POINTS; i++){
        child.chromosome.push_back(this->chromosome.at(i));
    }
    
    
    return child;
}

void Genome::mutate(){
    for (vector<ofPoint>::iterator c= chromosome.begin(); c!=chromosome.end(); c++){
        if(ofRandom(1)>mutationRate){
            c->set((ofRandom(0,_width),
                    ofRandom(0,_height),
                    ofRandom(0,_deep)));
        }
    }
    randomizeChromosome();
}
