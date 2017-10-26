//
//  Layer.h
//  GP
//
//  Created by Ronei Berlezi on 07/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#ifndef __GP__Layer__
#define __GP__Layer__

#include <string>

class Layer
{
public:
    int** layer;
    Layer(int sizeX, int sizeY);
    ~Layer();
private:
    int sizeX;
    int sizeY;
};

#endif /* defined(__GP__Layer__) */
