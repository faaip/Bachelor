//
//  EvolutionaryAlgorithm.cpp
//  Bachelor
//
//  Created by Frederik Tollund Juutilainen on 13/04/16.
//
//

#include "EvolutionaryAlgorithm.hpp"
#include <cmath>

EvolutionaryAlgorithm::EvolutionaryAlgorithm(){
    
    
    
}

void EvolutionaryAlgorithm::initializePopulation(){
    // Initializes the population with random genomes
    population.clear();
    for(int i = 0; i<populationSize; i++ ){
        Genome genome = Genome(genomeSize);
        genome.randomizeChromosome();
        population.push_back(genome);
    }
    cout << "Initialising population with population size: " << population.size() << endl;
}

void EvolutionaryAlgorithm::startEvolution(){
    evolutionRunning = true;
    evolutionStarted = true;
    
    // Initialisaasi
    initializePopulation();
    // Evaluate
}

void EvolutionaryAlgorithm::evaluatePopulation(){
    // Evaluates each genome at sets fitness accordingly
    for (vector<Genome>::iterator g= population.begin(); g!=population.end(); g++){
        calculateFitness(&(*g));
    }
    
    // Sort according to fitness
    std::sort(population.begin(),population.end());
}


void EvolutionaryAlgorithm::produceNextGeneration(){
    // http://geneticalgorithms.ai-depot.com/Tutorial/Overview.html - roulette wheel selection
    // http://www.codeproject.com/Articles/707505/Genetic-Algorithms-Demystified
    // Kilde om forskellige selektioner: http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.140.3747
    
    vector<Genome> newPopulation;
    
    
    evaluatePopulation();
    
    // Sort according to fitness
    std::sort(population.begin(),population.end());
    
    // Producing the next generation
    // Elite first
    for(int i = 0; i < eliteCount; i++){
        newPopulation.push_back(population.at(i));
    }
    
    // Roulette wheel selection
    // Sum all fitnesses
    int totalSum = 0;
    for (vector<Genome>::iterator g= population.begin(); g!=population.end(); g++){
        totalSum += g->fitness;
    }
    
    while(newPopulation.size() < populationSize){
        int rand = ofRandom(0, totalSum);
        int partialSum = 0;
        Genome* mother;
        Genome* father;
        
        // Find mother
        for (vector<Genome>::iterator g= population.begin(); g!=population.end(); g++){
            partialSum += g->fitness;
            if(partialSum >= rand){
                mother = &(*g);
                break;
            }
        }
        
        rand = ofRandom(0, totalSum);
        partialSum = 0;
        
        // Find father
        for (vector<Genome>::iterator g= population.begin(); g!=population.end(); g++){
            partialSum += g->fitness;
            if(partialSum >= rand){
                father = &(*g);
                break;
            }
        }
        
        // http://geneticalgorithms.ai-depot.com/Tutorial/Overview.html
        // Crossover only happens x % of the time
        if(ofRandom(1) < crossoverProbability){
            // switch case for different kinds of crossover
            Genome child(genomeSize);
            switch ( crossoverType ) {
                case 0:
                    // Singlepoint
                    child = mother->singlePointCrossover(*father);
                    if(ofRandom(1)<mutationProbability)child.mutate(mutationRate);
                    newPopulation.push_back(child);
                    break;
                case 1:
                    // Two-point crossover
                    child = mother->twoPointCrossover(*father);
                    if(ofRandom(1)<mutationProbability)child.mutate(mutationRate);
                    newPopulation.push_back(child);
                    break;
            }
        }else{
            // Parents enter the mix and are mutated
            if(ofRandom(1)<0.5){
                mother->mutate(mutationRate);
                newPopulation.push_back(*mother);
            }else{
                father->mutate(mutationRate);
                newPopulation.push_back(*father);
            }
        }
    }
    
    population = newPopulation;
}

void EvolutionaryAlgorithm::calculateFitness(Genome* g){
    // Reset fitness
    g->fitness = 0;
    
    
    for(int i = 0; i < g->chromosome.size();i++){
        for(int j = 0; j < g->chromosome.size();j++){
            if(!(i ==j)){
                g->fitness += std::abs(g->chromosome.at(i).squareDistance(g->chromosome.at(j))/1000000);
            }
        }
    }
}

float EvolutionaryAlgorithm::getAverageFitness(){
    double sum = 0;
    
    for(auto & genome : population){
        sum += genome.fitness;
    }
    
    return sum/population.size();
}