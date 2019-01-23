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

auto& player(manager.addEntity());

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
    
    assets->AddTexture("monster", "res/monster.png");
    
    map = new Map("terrain", 3, 32);
    map->LoadMap("res/map2.txt", 25, 20);
    
    player.addComponent<TransformComponent>(800, 640, 32, 32, 4);
    player.addComponent<SpriteComponent>("player", true);
    player.addComponent<KeybardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);
    
    assets->CreateMonster("monster");
    
    assets->CreateProjectile(Vector2D(600, 600),Vector2D(2,0), 200, 2, "projectile");
    assets->CreateProjectile(Vector2D(400, 400),Vector2D(2,2), 200, 2, "projectile");
    
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& monsters(manager.getGroup(Game::groupMonsters));

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
    
    SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = player.getComponent<TransformComponent>().position;
    
    manager.refresh();
    manager.update();
    
    for(auto& c : colliders){
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCol)) {
            std::cout << "Hit" << playerPos << std::endl;
            
            player.getComponent<TransformComponent>().position = playerPos;
            player.getComponent<TransformComponent>().onGround = true;
        }
    }
    if (Game::event.type == SDL_KEYDOWN) {
        switch (Game::event.key.keysym.sym) {
            case SDLK_q:
                 assets->CreateProjectile(Vector2D(playerPos.x-20, playerPos.y),Vector2D(-2,-2), 200, 2, "projectile");
                break;
            case SDLK_e:
                assets->CreateProjectile(Vector2D(playerPos.x+80, playerPos.y),Vector2D(2,-2), 200, 2, "projectile");
                break;
                
        }}
    for (auto& pr : projectiles) {
        if(Collision::AABB(pr->getComponent<ColliderComponent>().collider, player.getComponent<ColliderComponent>().collider)){
            std::cout << "Hit player" << std::endl;
          //  pr->destroy();
        }
    }
    for (auto& m : monsters) {
        if(Collision::AABB(m->getComponent<ColliderComponent>().collider, player.getComponent<ColliderComponent>().collider)){
            std::cout << "Player hit" << std::endl;
            m->destroy();
        }
    }
    
    for(auto& monster : monsters){
        for(auto& projectile : projectiles){
            if (Collision::AABB(monster->getComponent<ColliderComponent>().collider, projectile->getComponent<ColliderComponent>().collider)) {
                monster->destroy();
                projectile->destroy();
                int counter=0;
                counter++;
                
                std::cout << counter << std::endl;
            }
        }
    }
    
    camera.x = player.getComponent<TransformComponent>().position.x - 400;
    camera.y = player.getComponent<TransformComponent>().position.y - 320;
    
//   std::cout << "x:" << player.getComponent<TransformComponent>().position.x  << "y:" << player.getComponent<TransformComponent>().position.y <<std::endl;
//    std::cout << "x:" << camera.w  << "y:" << camera.h <<std::endl;
    
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
        camera.y = camera.h*2;
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
    for(auto& pr : projectiles){
        pr->draw();
    }
   for (auto& m : monsters){
       m->draw();
       
   }
    
    SDL_RenderPresent(renderer);
}
void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    
    std::cout << "Cleaned" << std::endl;
}




