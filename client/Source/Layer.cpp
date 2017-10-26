//
//  Layer.cpp
//  GP
//
//  Created by Ronei Berlezi on 07/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#include "Layer.h"

Layer::Layer(int sizeX, int sizeY)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    
    //layer = (int **)calloc(sizeX, sizeof(int *));
    //for (unsigned int i = 0; i < sizeX; i++)
    //	layer[i] = (int *)calloc(sizeY, sizeof(int));
    
    layer = new int*[sizeX];
    for (int i = 0; i < sizeX; ++i)
        layer[i] = new int[sizeY];
    
    for (int x = 0; x < sizeX; x++){
        for (int y = 0; y < sizeY; y++)
            layer[x][y] = 0;
    }
}


Layer::~Layer()
{
    for (int i = 0; i < sizeX; ++i) {
        delete [] layer[i];
    }
    delete [] layer;
}

