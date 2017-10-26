//
//  Collidable.h
//  GP
//
//  Created by Ronei Berlezi on 29/10/14.
//  Copyright (c) 2014 Ronei Berlezi. All rights reserved.
//

#ifndef GP_Collidable_h
#define GP_Collidable_h

class Collidable{
public:
    static bool checkCollision( SDL_Rect A, SDL_Rect B )
    {
        //The sides of the rectangles
        int leftA, leftB;
        int rightA, rightB;
        int topA, topB;
        int bottomA, bottomB;
        
        //Calculate the sides of rect A
        leftA = A.x;
        rightA = A.x + A.w;
        topA = A.y;
        bottomA = A.y + A.h;
        
        //Calculate the sides of rect B
        leftB = B.x;
        rightB = B.x + B.w;
        topB = B.y;
        bottomB = B.y + B.h;
        
        //If any of the sides from A are outside of B
        if( bottomA <= topB )
        {
            return false;
        }
        
        if( topA >= bottomB )
        {
            return false;
        }
        
        if( rightA <= leftB )
        {
            return false;
        }
        
        if( leftA >= rightB )
        {
            return false;
        }
        
        //If none of the sides from A are outside B
        return true;
    }
};

#endif
