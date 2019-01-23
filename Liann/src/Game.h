//
//  Game.hpp
//  Liann
//
//  Created by Gosia Zdybel on 20/01/2019.
//  Copyright © 2019 Liann. All rights reserved.
//

#pragma once

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include <iostream>
#include <vector>

class ColliderComponent;
class AssetManager;

class Game {
    public:
        Game();
        ~Game();
    
        void init(const char* title, int width, int height, bool fullscreen);
    
        void handleEvents();
        void update();
        bool running(){return isRunning;}
        void render();
        void clean();
    
        static AssetManager* assets;
        static SDL_Renderer *renderer;
        static SDL_Event event;
        static bool isRunning;
        static SDL_Rect camera;
    
    enum groupLables : std::size_t {
        groupMap,
        groupPlayers,
        //groupMonsters,
        groupColliders,
        groupProjectiles
    };
    
    private:
        int cnt = 0;
        SDL_Window *window;
};

