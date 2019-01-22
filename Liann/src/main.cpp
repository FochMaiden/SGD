//
//  main.cpp
//  Liann
//
//  Created by Gosia Zdybel on 20/01/2019.
//  Copyright © 2019 Liann. All rights reserved.
//

#include <iostream>
#include "Game.h"

Game *game = nullptr;

int main(int argc, const char * argv[]) {

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    
    Uint32 frameStart;
    int frameTime;
    
    
    game = new Game();
    
    game->init("Its a boy", 800, 640, false);
    
    while (game->running()) {
        
        frameStart = SDL_GetTicks();
        
        //do stuffs
        game->handleEvents();
        game->update();
        game->render();
        
        frameTime = SDL_GetTicks() - frameStart;
        
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
        
    }
    
    game -> clean();
    
    return 0;
}
