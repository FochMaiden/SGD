//
//  PositionComponent.hpp
//  Liann
//
//  Created by Gosia Zdybel on 21/01/2019.
//  Copyright © 2019 Liann. All rights reserved.
//

#pragma once

#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component {

    
public:
    
    Vector2D position;
    Vector2D velocity;
    
    int height = 32;
    int width = 32;
    int scale = 1;
    
    int speed = 3;
    
    bool onGround = false;
    
    TransformComponent(){
        position.Zero();
    }
    TransformComponent(int sc){
        position.Zero();
        scale = sc;
    }
    TransformComponent(float x, float y){
        position.Zero();
    }
    TransformComponent(bool og){
        onGround = og;
    }
    TransformComponent(float x, float y, int h, int w, int sc){
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = sc;
    }
    
    void init() override{
        velocity.Zero();
    }
    void update() override{
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};
