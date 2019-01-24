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


class KeybardController : public Component {
    
public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    
    void init() override{
        transform = &entity->getComponent<TransformComponent>();
        sprite= &entity->getComponent<SpriteComponent>();
    }
    void update() override{
        
        if (Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym) {
                case SDLK_UP:
                    transform-> velocity.y = -2;
                    sprite->Play("Walk");
                    break;
                case SDLK_LEFT:
                    transform-> velocity.x = -2;
                    sprite->Play("Walk");
                    sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                    break;
                case SDLK_RIGHT:
                    transform-> velocity.x = 2;
                    sprite->Play("Walk");
                    break;
                case SDLK_DOWN:
                    transform-> velocity.y = 2;
                    sprite->Play("Walk");
                    break;
                default:
                    break;
            }
        }
        if(Game::event.type == SDL_KEYUP){
            switch (Game::event.key.keysym.sym) {
                case SDLK_UP:
                    transform-> velocity.y = 0;
                    sprite->Play("Idle");
                    break;
                case SDLK_LEFT:
                    transform-> velocity.x = 0;
                    sprite->Play("Idle");
                    sprite->spriteFlip = SDL_FLIP_NONE;
                    break;
                case SDLK_RIGHT:
                    transform-> velocity.x = 0;
                    sprite->Play("Idle");
                    break;
                case SDLK_DOWN:
                    transform-> velocity.y = 0;
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

