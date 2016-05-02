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
    light.setPosition(100,500, 100);
    cam.setAutoDistance(true);
    
    
}

void Voronoi::update(){
    
}

void Voronoi::draw(){
    ofBackgroundGradient(ofColor(255), ofColor(170), OF_GRADIENT_CIRCULAR);
    ofPushMatrix();
    cam.begin();
    light.enable();
    ofEnableLighting();
    glEnable(GL_DEPTH_TEST);
    
    // Draw center spheres
    if(isShowingPoints){
        for (int i = 0; i < cellCentroids.size(); i++){
            ofSetColor(0,190);
            ofDrawSphere(cellCentroids[i], cellRadius[i]*0.15);
            ofSetColor(255);
            ofDrawBitmapString(ofToString(cellRadius[i]), 15+cellCentroids[i].x, cellCentroids[i].y);
        }
    }
    
    // Draw middle point
    ofSetColor(255,0,0);
    ofDrawSphere(ofPoint(_width/2,_height/2,_deep/2), 10);
    
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

void Voronoi::createPhenotype(Genome genome){
    //  Fresh begining
    cellMeshes.clear();
    cellCentroids.clear();
    cellRadius.clear();
    
    //  Define a container
    voro::container con(-_width*0.5,_width*0.5,
                        -_height*0.5,_height*0.5,
                        -_deep*0.5,_deep*0.5,
                        1,1,1,
                        true,true,true,
                        8);
    
    
    // Add walls depending on choice in GUI
    if(tessellationType == 0){
        voro::wall_cylinder cyl(0,0,0,0,0,20, min(_width*0.5, _height*0.5));
        con.add_wall(cyl);
    }else if (tessellationType == 1){
        voro::wall_sphere sph(0, 0, 0, min(_width*0.5, _height*0.5) );
        con.add_wall(sph);
    }else if (tessellationType == 2){
        voro::wall_cone cone(0,0,min(_width*0.5, _height*0.5),0,0,-1,atan(0.5));
        con.add_wall(cone);
    }
    
    int i = 0;
    for(auto cell : genome.chromosome){
        addCellSeed(con, cell, i, true);
        i++;
    }
            
    cellMeshes = getCellsFromContainer(con,0.0);
    cellMeshWireframes = getCellsFromContainer(con,0.0,true);
    cellRadius = getCellsRadius(con);
    cellCentroids = getCellsCentroids(con);
}