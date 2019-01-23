//
//  KeyboardController.hpp
//  Liann
//
//  Created by Gosia Zdybel on 21/01/2019.
//  Copyright © 2019 Liann. All rights reserved.
//

#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "ColliderComponent.h"

class KeybardController : public Component {
    
public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    
    bool jumping = false;
    int jumpingTime = 0;
    
    void init() override{
        transform = &entity->getComponent<TransformComponent>();
        sprite= &entity->getComponent<SpriteComponent>();
    }
    
    void update() override{
        
//        Vector2D pos = transform-> position;
        Vector2D vel = transform-> velocity;
        
//        std::cout << "pos x" << pos.x << "pos y" << pos.y << std::endl;
//        std::cout << "pos x" << vel.x << "vel y" << vel.y << std::endl;
//        std::cout << jumpingTime << std::endl;
        
        if (Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym) {
                case SDLK_w:
                    transform-> velocity.y = -1;
                    sprite->Play("Walk");
                    break;
                case SDLK_a:
                    transform-> velocity.x = -1;
                    sprite->Play("Walk");
                    sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                    break;
                case SDLK_d:
                    transform-> velocity.x = 1;
                    sprite->Play("Walk");
                    break;
                case SDLK_s:
                    transform-> velocity.y = 1;
                    sprite->Play("Walk");
                    break;
                case SDLK_SPACE:
                    
//                    if (!jumping) {
//                        jumping = true;
                        transform-> velocity.y = -12.0f;
                   // }
                default:
                    break;
            }
        }
        if(Game::event.type == SDL_KEYUP){
            switch (Game::event.key.keysym.sym) {
                case SDLK_w:
                    transform-> velocity.y = 0;
                    sprite->Play("Idle");
                    break;
                case SDLK_a:
                    transform-> velocity.x = 0;
                    sprite->Play("Idle");
                    sprite->spriteFlip = SDL_FLIP_NONE;
                    break;
                case SDLK_d:
                    transform-> velocity.x = 0;
                    sprite->Play("Idle");
                    break;
                case SDLK_s:
                    transform-> velocity.y = 0;
                    sprite->Play("Idle");
                    break;
                case SDLK_SPACE:
//                    if (vel.y > 1) {
//                        jumpingTime ++;
//                    }
                    if (vel.y < -6.0f) {
                        transform->velocity.y = 6.0f;
                    };
//                    if (jumpingTime == 16 || vel.y ==0){
//                        transform->velocity.y = 0;
//                        jumpingTime = 0;
//                        jumping = false;
//                    }
                    sprite->Play("Idle");
                    break;
                case SDLK_ESCAPE:
                    Game::isRunning = false;
                default:
                    break;
            }
        }
    }
};

