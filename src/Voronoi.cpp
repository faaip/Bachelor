//
//  Voronoi.cpp
//  Bachelor
//
//  Created by Frederik Tollund Juutilainen on 13/04/16.
//
//

#include "Voronoi.hpp"

Voronoi::Voronoi(){
    // Lights and cam setup
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    // light.setPosition(100,500, 100);
    cam.setDistance(1500);
}

void Voronoi::update(){
    
}

void Voronoi::clear(){
    cellMeshes.clear();
    cellCentroids.clear();
    cellRadius.clear();
}

void Voronoi::draw(){
    if(isRendering){
        ofBackgroundGradient(ofColor(255), ofColor(170), OF_GRADIENT_CIRCULAR);
        ofPushMatrix();
        cam.begin();
        //    light.enable();
        ofEnableLighting();
        glEnable(GL_DEPTH_TEST);
        
        // Draw center spheres
        if(isShowingPoints){
            for (int i = 0; i < cellCentroids.size(); i++){
                ofSetColor(0,190);
                ofDrawSphere(cellCentroids[i], cellRadius[i]*0.15);
                ofTrueTypeFont f;
                ofDrawBitmapString(ofToString(cellRadius[i]), 15+cellCentroids[i].x, cellCentroids[i].y);
            }
        }
        
        // Draw tessellation
        if(isShowingMesh) {
            for(int i = 0; i < cellMeshes.size(); i++){
                ofSetColor(100,30);
                cellMeshes[i].drawFaces();
                ofPushStyle();
                ofSetLineWidth(3);
                ofSetColor(255);
                cellMeshWireframes[i].draw();
                ofPopStyle();
            }
        }
        
        glDisable(GL_DEPTH_TEST);
        ofDisableLighting();
        light.disable();
        cam.end();
        ofPopMatrix();
    }
}

voro::container Voronoi::createPhenotype(Genome* genome){
    //  Fresh begining
    cellMeshes.clear();
    cellCentroids.clear();
    cellRadius.clear();
    
    //  Define a container
    voro::container con(-dimensions.x,dimensions.x,
                        -dimensions.y,dimensions.y,
                        -dimensions.z,dimensions.z,
                        1,1,1,
                        widthConstraint,heightConstraint,depthConstraint,
                        8);
    
    for(int i = 0; i < genome->chromosome.size(); i++){
        addCellSeed(con, genome->chromosome.at(i), i, true);
    }
    
    cellMeshes = getCellsFromContainer(con,0.0);
    cellMeshWireframes = getCellsFromContainer(con,0.0,true);
    cellRadius = getCellsRadius(con);
    cellCentroids = getCellsCentroids(con);
    
    return con;
}

double Voronoi::calculateFitness(Genome* genome, int fitnessType){
    if(fitnessType == 0){
        // Evenly sized radius for cells
        createPhenotype(genome);
        double sum = 0;
        for(auto & radius : cellRadius){
            sum+=radius;
        }
        return sum/cellRadius.size();
    }else if (fitnessType == 1){
        // Depth difference on z-axis
        voro::container con = createPhenotype(genome); // copy of container
        voro::c_loop_all cl(con); // Looping all cells
        voro::voronoicell_neighbor cellNeighbor; // auxilliary class for finding cell neighbors
        vector<int> neighborIds; // id's of all cell neighbors
        double x,y,z; // coordinates for current cell
        double fitness = 0; // fitness to return
        
        if(cl.start()) do if(con.compute_cell(cellNeighbor,cl)) { // Loop through all cells in container
            cl.pos(x,y,z); // position of cell currently being considered
            int id = cl.pid(); // Id of cell currently considered
            cellNeighbor.neighbors(neighborIds); // Adds neighbors to vector
            for(int i = 0; i< cellCentroids.size();i++){
            fitness +=  std::abs(cellCentroids.at(i).z+cellCentroids.at(id).z); // return distance on z-axis
            }
        }while (cl.inc());{}
        return fitness;
    }
    
}

