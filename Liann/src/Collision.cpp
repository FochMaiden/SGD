//
//  Collision.cpp
//  Liann
//
//  Created by Gosia Zdybel on 21/01/2019.
//  Copyright © 2019 Liann. All rights reserved.
//

#include "Collision.h"
#include "ECS/ColliderComponent.h"

bool Collision::CircleCircle(const SDL_Rect &recA, const SDL_Rect &recB){
    
    int circleAx, circleBx;
    int circleAy, circleBy;
    int circleAr, circleBr;
    int totalR;
    int deltaX, deltaY, distanceSquared;
    
    circleAx = recA.x;
    circleAy = recA.y;
    circleAr = recA.h/2;
    
    circleBx = recB.x;
    circleBy = recB.y;
    circleBr = recB.h/2;
    
    totalR = circleBr + circleAr;
    totalR = totalR * totalR;
    
    deltaX = circleBx - circleAx;
    deltaY = circleBy - circleAy;
    
    distanceSquared = deltaX * deltaX + deltaY * deltaY;
    
    if (distanceSquared < totalR) {
        std::cout << "dotklem" << std::endl;
        return true;
    }
    return false;
}

bool Collision::CircleSquare(const SDL_Rect& recA, const SDL_Rect& recB){
  
    int circleAx, circleAy, circleAr;
    int cX, cY;
    int deltaX, deltaY, distanceSquared;
    
    circleAx = recA.x;
    circleAy = recA.y;
    circleAr = recA.h/2;
    
    if (circleAx < recB.x) {
        cX = recB.x;
    }else if (circleAx > recB.x + recB.w){
        cX = recB.x + recB.w;
    }
    else {cX = circleAx;}
    
    if (circleAy < recB.y) {
        cY = recB.y;
    }else if (circleAy > recB.y + recB.h){
        cY = recB.y +recB.h;
    }
    else {cY = circleAy;}
    
    deltaX = cX - circleAx;
    deltaY = cY - circleAy;
    
    distanceSquared = deltaX * deltaX + deltaY * deltaY;
    
    if (distanceSquared < circleAr * circleAr) {
        std::cout << "dotklemcos" << std::endl;
        return true;
    }
    
    
    return false;
};

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB){
    

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = recA.x;
    rightA = recA.x + recA.w;
    topA = recA.y;
    bottomA = recA.y + recA.h;

    leftB = recB.x;
    rightB = recB.x + recB.w;
    topB = recB.y;
    bottomB = recB.y + recB.h;

    if (bottomA <= topB) {
        return false;
    } if (topA >= bottomB) {
        return false;
    } if (rightA <= leftB) {
        return false;
    } if (leftA >= rightB) {
        return false;
    } else return true;
    
    // rightA >= leftB
    // rightB >= leftA
    // bottomnA >= topB
    // bottomnB >= topA
//    if (recA.x + recA.w >= recB.x  &&
//        recB.x + recB.w >= recA.x  &&
//        recA.y + recA.h >= recB.y  &&
//        recB.y + recB.h >= recA.y) {
//        return true;
//    } else {return false;}
//
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB){
    
    std::cout << colA.tag << " hit: " << colB.tag << std::endl;
    
    if (AABB(colA.collider, colB.collider)) {
        return true;
    }
    if (CircleCircle(colA.collider, colB.collider)) {
        //std::cout << colA.tag << " hit: " << colB.tag << std::endl;
        return true;
    }
    if (CircleSquare(colA.collider, colB.collider)) {
        return true;
    }
    
     else {return false;}
}
