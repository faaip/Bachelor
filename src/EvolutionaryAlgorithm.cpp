//
//  EvolutionaryAlgorithm.cpp
//  Bachelor
//
//  Created by Frederik Tollund Juutilainen on 13/04/16.
//
//

#include "EvolutionaryAlgorithm.hpp"

EvolutionaryAlgorithm::EvolutionaryAlgorithm(){
    
    
    
}

void EvolutionaryAlgorithm::initializePopulation(){
    // Initializes the population with random genomes
    cout << "Initialising population with population size: " << populationSize << endl;
    
    for(int i = 0; i<populationSize; i++ ){
        Genome genome = Genome();
        genome.randomizeChromosome();
        population.push_back(genome);
    }
    
    evaluatePopulation();
}

void EvolutionaryAlgorithm::evaluatePopulation(){
    // Evaluates each genome at sets fitness accordingly
    for (vector<Genome>::iterator g= population.begin(); g!=population.end(); g++){
        calculateFitness(&(*g));
    }
    
    // Sort according to fitness
    std::sort(population.begin(),population.end());
}

bool EvolutionaryAlgorithm::hasHigherFitness(Genome x, Genome y){
    return x.fitness < y.fitness;
}

void EvolutionaryAlgorithm::produceNextGeneration(){
    // Producing the next generation
}

void EvolutionaryAlgorithm::calculateFitness(Genome* g){
    // TEMP FITNESS - FURTHES FROM MIDDLE:
    
    //TODO:Calculate fitness
    float f = 0;
    // Distance from middle
    ofPoint middle(_width/2,_height/2,_deep/2);
    
    for (vector<ofPoint>::iterator c= g->chromosome.begin(); c!=g->chromosome.end(); c++){
        f += middle.distance((*c));
    }
    
    g->fitness = f;

    
}