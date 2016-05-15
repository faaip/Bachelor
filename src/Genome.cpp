//
//  Genome.cpp
//  Bachelor
//
//  Created by Frederik Tollund Juutilainen on 13/04/16.
//
//

#include "Genome.hpp"

Genome::Genome(int genomeSize, ofVec3f d){
    this->genomeSize = genomeSize;
    this->dimensions = d;
}

void Genome::randomizeChromosome(){
    chromosome.clear();
    for(int i = 0; i < genomeSize;i++){
        ofPoint newCell = ofPoint(ofRandom(-dimensions.x,dimensions.x),
                                  ofRandom(-dimensions.y,dimensions.y),
                                  ofRandom(-dimensions.z,dimensions.z));
        chromosome.push_back(newCell);
    }
}

Genome Genome::singlePointCrossover(Genome* otherParent){
    // Crossover using single-point crossover
    Genome child = Genome(genomeSize,this->dimensions);
    
    int r = ofRandom(0,genomeSize); // random single point
    
    for(int i = 0; i < r; i++){
        child.chromosome.push_back(chromosome.at(i)); // from mother
    }
    
    for(int i = r; i < genomeSize; i++){
        child.chromosome.push_back(otherParent->chromosome.at(i)); // from other parent
    }
    return child;
}

Genome Genome::twoPointCrossover(Genome* otherParent){
    // Reproducing using two-point crossover
    Genome child = Genome(genomeSize,this->dimensions);
    
    int r1 = ofRandom(0,genomeSize);
    int r2 = ofRandom(0,genomeSize);
    
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
        child.chromosome.push_back(otherParent->chromosome.at(i));
    }
    
    // From mother (again)
    for(int i = r2; i < genomeSize; i++){
        child.chromosome.push_back(this->chromosome.at(i));
    }
    
    
    return child;
}

Genome Genome::uniformCrossover(Genome* otherParent){
    // Crossover using uniform crossover
    Genome child = Genome(genomeSize,this->dimensions);
    
    for(int i = 0; i < genomeSize;i++){
        if(ofRandom(1)>0.5){
            child.chromosome.push_back(this->chromosome.at(i));
        }else{
            child.chromosome.push_back(otherParent->chromosome.at(i));
        }
    }
   
    return child;
    
}

void Genome::mutate(float mutationRate){
    for(auto & p : this->chromosome){
        if(ofRandom(1)<mutationRate){
            p.x =ofRandom(-dimensions.x,dimensions.x);
        }
        if(ofRandom(1)<mutationRate){
            p.y =ofRandom(-dimensions.y,dimensions.y);
        }
        if(ofRandom(1)<mutationRate){
            p.z =ofRandom(-dimensions.z,dimensions.z);
        }
    }
}
