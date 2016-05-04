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
    cout << "Initialising population with population size: " << population.size() << endl;
}

void EvolutionaryAlgorithm::startEvolution(){
    evolutionStarted = true;
    
    
    // Initialisaasi
    initializePopulation();
    // Evaluate
    evaluatePopulation();
    
//    while(generationCount < 5000)
//    {
//        // Evaluate
//        evaluatePopulation();
//        produceNextGeneration();
//        generationCount++;
//    }
    
    // LOOP
    // SELECT
    // RECOMBINE
    // MUTATE
    // EVALUATE
    // SELECT
    
    
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
            newPopulation.push_back(mother->reproduce(*father));
        }else{
            if(ofRandom(1)<0.5){
                newPopulation.push_back(*mother);
            }else{
                newPopulation.push_back(*father);
            }
        }
    }
    
    population = newPopulation;
}

void EvolutionaryAlgorithm::calculateFitness(Genome* g){
    // TEMP FITNESS - FURTHEST FROM MIDDLE:
    float f = 0;
    // Distance from middle
    ofPoint middle(0,0,0);

    for (vector<ofPoint>::iterator c= g->chromosome.begin(); c!=g->chromosome.end(); c++){
        f += middle.distance((*c));
    }
    
    if(f <= 0 ){
        cout << "DET HER MÅ IKKE SKE!" << endl;
    }
    
    g->fitness = f;
}

float EvolutionaryAlgorithm::getAverageFitness(){
    double sum = 0;
    for (vector<Genome>::iterator g= population.begin(); g!=population.end(); g++){
        sum += g->fitness;
    }
    
    return sum/population.size();
    
}