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
        ofPoint newCell = ofPoint(ofRandom(-_width*0.5,_width*0.5),
                                  ofRandom(-_height*0.5,_height*0.5),
                                  ofRandom(-_deep*0.25,_deep*0.25));
        chromosome.push_back(newCell);
    }
}

Genome Genome::reproduce(Genome otherParent){
    // Reproducing using single-point crossover
    Genome child = Genome();
    
    int r = ofRandom(0,NUMBER_OF_POINTS);
    
    for(int i = 0; i < r; i++){
        child.chromosome.push_back(chromosome.at(i));
    }
    
    for(int i = r; i < NUMBER_OF_POINTS; i++){
        child.chromosome.push_back(otherParent.chromosome.at(i));
    }
    
//    if(ofRandom(1)>mutationProbability){
        child.mutate();
//    }
    
    return child;
}

void Genome::mutate(){
    for (vector<ofPoint>::iterator c= chromosome.begin(); c!=chromosome.end(); c++){
        if(ofRandom(1)>mutationRate){
            c->set((ofRandom(-_width,_width),
                    ofRandom(-_height,_height),
                    ofRandom(-_deep,_deep)));
            cout << "MUTATION" << endl;
        }
    }
    randomizeChromosome();
}
