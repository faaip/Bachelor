//
//  EvolutionaryAlgorithm.cpp
//  Bachelor
//
//  Created by Frederik Tollund Juutilainen on 13/04/16.
//
//

#include "EvolutionaryAlgorithm.hpp"
#include <cmath>

EvolutionaryAlgorithm::EvolutionaryAlgorithm(Voronoi* voronoi){
    this->voronoi = voronoi;
}

void EvolutionaryAlgorithm::initializePopulation(){
    // Initializes the population with random genomes
    population.clear();
    for(int i = 0; i<populationSize; i++ ){
        Genome genome = Genome(genomeSize,dimensions);
        genome.randomizeChromosome();
        population.push_back(genome);
    }
}

void EvolutionaryAlgorithm::startEvolution(){
    evolutionRunning = true;
    evolutionStarted = true;
    
    // Initialisaasi
    initializePopulation();
    // Evaluate
    evaluatePopulation();
}

void EvolutionaryAlgorithm::evaluatePopulation(){
    // Evaluates each genome at sets fitness accordingly
    for (vector<Genome>::iterator g= population.begin(); g!=population.end(); g++){
        calculateFitness(&(*g));
    }
}


void EvolutionaryAlgorithm::produceNextGeneration(){
    // http://geneticalgorithms.ai-depot.com/Tutorial/Overview.html - roulette wheel selection
    // http://www.codeproject.com/Articles/707505/Genetic-Algorithms-Demystified
    // Kilde om forskellige selektioner: http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.140.3747
    
    vector<Genome> newPopulation;
    evaluatePopulation();
    
    // Sort according to fitness
    std::sort(population.begin(),population.end());
    
    // Save best and average fitness for exporting to csv
    bestFitnessVector.push_back(population.front().fitness);
    avgFitnessVector.push_back(getAverageFitness());
    
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
            Genome child(genomeSize,dimensions);
            switch ( crossoverType ) {
                case 0:
                    // Singlepoint
                    child = mother->singlePointCrossover(father);
                    if(ofRandom(1)<mutationProbability)child.mutate(mutationRate);
                    newPopulation.push_back(child);
                    break;
                case 1:
                    // Two-point crossover
                    child = mother->twoPointCrossover(father);
                    if(ofRandom(1)<mutationProbability)child.mutate(mutationRate);
                    newPopulation.push_back(child);
                    break;
                case 2:
                    // Uniform crossover
                    child = mother->uniformCrossover(father);
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
    g->fitness = voronoi->calculateFitness(g,fitnessType);
}

float EvolutionaryAlgorithm::getAverageFitness(){
    double sum = 0;
    
    for(auto & genome : population){
        sum += genome.fitness;
    }
    
    return sum/population.size();
}

void EvolutionaryAlgorithm::exportToCsv(){
    csv.createFile("createfile.csv");
    
    ofxCsvRow infoRow;
    infoRow.setString(0, "Population size: " + ofToString(populationSize));
    infoRow.setString(1, "Dimensions size: " + ofToString(dimensions.x) + " " + ofToString(dimensions.y) + " "+ ofToString(dimensions.z));
    infoRow.setString(2, "Genome size: " + ofToString(genomeSize));
    infoRow.setString(3, "Fitness type: " + ofToString(fitnessType));
    infoRow.setString(4, "Crossover %: " + ofToString(crossoverProbability*100));
    infoRow.setString(5, "Crossover type: " + ofToString(crossoverType));
    infoRow.setString(6, "Mutation rate: " + ofToString(mutationRate));
    infoRow.setString(6, "Mutation probability: " + ofToString(mutationProbability*100));
    csv.addRow(infoRow);
    
    ofxCsvRow emptyRow;
    csv.addRow(emptyRow);
    
    ofxCsvRow moreInfoRow;
    moreInfoRow.setString(0, "Avg fitness:");
    moreInfoRow.setString(1, "Best fitness:");
    csv.addRow(moreInfoRow);
    
    // Add avg and best fitness
    for(int i = 0; i < generationCount; i++){
        ofxCsvRow row;
        row.insertFloat(0, avgFitnessVector.at(i));
        row.insertFloat(1, bestFitnessVector.at(i));
        csv.addRow(row);
    }
    
    csv.save(ofToString(ofToString((int) ofRandom(10000)) + "_savefile.csv"));
    cout << "Exported to csv" << endl;
}