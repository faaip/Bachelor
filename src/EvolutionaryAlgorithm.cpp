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
    
    for(int i = 0; i<populationSize; i++ ){
        
        Genome genome = Genome();
        genome.randomizeChromosome();
        population.push_back(genome);
    
    }
}

void EvolutionaryAlgorithm::evaluatePopulation(){
    // Evaluates each genome at sets fitness accordingly
    for(auto genome : population){
        calculateFitness(genome);
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

void EvolutionaryAlgorithm::calculateFitness(Genome g){

//TODO:Calculate fitness

}