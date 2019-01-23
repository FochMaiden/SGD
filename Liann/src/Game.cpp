//
//  Game.cpp
//  Liann
//
//  Created by Gosia Zdybel on 20/01/2019.
//  Copyright © 2019 Liann. All rights reserved.
//

#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Collision.h"
#include "AssetManager.h"


Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera{0,0,800,640};

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

//auto& player(manager.addEntity());

Game::Game(){}

Game::~Game(){}

void Game::init(const char *title, int width, int height, bool fullscreen){
    int flags = 0;
    
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        
        std::cout << "Initialized..." << std::endl;
        
        window =  SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        
        if (window) {
            std::cout << "Widnow created" << std::endl;
        }
        
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer creted" << std::endl;
        }
        
        isRunning = true;
    }
    assets->AddTexture("terrain", "res/terrain_ss.png");
    assets->AddTexture("player", "res/player_anims.png");
    assets->AddTexture("projectile", "res/proj.png");
    
    map = new Map("terrain", 3, 32);
    map->LoadMap("res/map2.txt", 25, 20);
    
    assets->CreatePlayer("player");
    
    assets->CreateProjectile(Vector2D(600, 600),Vector2D(2,0), 200, 2, "projectile");
    assets->CreateProjectile(Vector2D(600, 600),Vector2D(2,0), 200, 2, "projectile");
    
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
//auto& monsters(manager.getGroup(Game::groupMonsters));

void Game::handleEvents(){
   
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
            
        default:
            break;
    }
}
void Game::update(){
    for(auto& p :players){
        SDL_Rect playerCol = p->getComponent<ColliderComponent>().collider;
        Vector2D playerPos = p->getComponent<TransformComponent>().position;
        
        manager.refresh();
        manager.update();
        
        for(auto& c : colliders){
            SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
            if (Collision::AABB(cCol, playerCol)) {
                p->getComponent<TransformComponent>().position = playerPos;
            }
        }
        for (auto& pr : projectiles) {
            if(Collision::AABB(p->getComponent<ColliderComponent>().collider, pr->getComponent<ColliderComponent>().collider)){
                std::cout << "Hit player" << std::endl;
                pr->destroy();
            }
        }
    
        camera.x = p->getComponent<TransformComponent>().position.x - 400;
        camera.y = p->getComponent<TransformComponent>().position.y - 320;
        
    //    std::cout << "x:" << player.getComponent<TransformComponent>().position.x  << "y:" << player.getComponent<TransformComponent>().position.y <<std::endl;
        std::cout << "x:" << camera.w  << "y:" << camera.h <<std::endl;
        
        if (camera.x < 0) {
            camera.x = 0;
        }
        if (camera.y < 0) {
            camera.y = 0;
        }
        if (camera.x > camera.w*2) {
            camera.x = camera.w*2;
        }
        if (camera.y  > camera.h*2) {
            camera.y = camera.h;
        }
    }

}

//auto& tiles(manager.getGroup(groupMap));


void Game::render(){
    SDL_RenderClear(renderer);
    
    //stuff to render
    for (auto& t : tiles){
        t->draw();
    }
    for (auto& c : colliders) {
        c->draw();
    }
    for (auto& p : players){
        p->draw();
    }
    for(auto& p : projectiles){
        p->draw();
    }

//    for (auto& m : monsters){
//        m->draw();
//    }
    
    SDL_RenderPresent(renderer);
}
void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    
    std::cout << "Cleaned" << std::endl;
}




