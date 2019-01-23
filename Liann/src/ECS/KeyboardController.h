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
#include "ProjectileComponent.h"

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
                    transform-> velocity.y = -13;
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
                    transform-> velocity.y = 13;
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

