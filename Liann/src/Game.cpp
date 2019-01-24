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
#include <sstream>

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera{0,0,800,640};

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& label(manager.addEntity());

int counter=0;
int i=0;

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
    
    if(TTF_Init() == -1){
        std::cout << "Error : SDL_TTF" << std::endl;
    }
    
    assets->AddTexture("terrain", "res/terrain_ss.png");
    assets->AddTexture("player", "res/player_anims.png");
    assets->AddTexture("projectile", "res/proj.png");
    assets->AddTexture("monster", "res/monster2.png");
    
    assets->AddFont("font", "res/font.ttf", 20);
    
    map = new Map("terrain", 5, 32);
    map->LoadMap("res/map.txt", 25, 20);
    
    player.addComponent<TransformComponent>(1600, 1800, 32, 32, 3);
    player.addComponent<SpriteComponent>("player", true);
    player.addComponent<KeybardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);
    
    SDL_Color white = {255,255,255,255};
    label.addComponent<UILabel>(10, 10, "counter", "font", white);
    
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
    
    std::stringstream ss;
    ss << "Player points " << counter << "000";
    label.getComponent<UILabel>().SetLabelText(ss.str(), "font");
    
    manager.refresh();
    manager.update();
    
    for(auto& c : colliders){
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCol)) {
            //std::cout << "Hit" << playerPos << std::endl;
            
            player.getComponent<TransformComponent>().position = playerPos;
            player.getComponent<TransformComponent>().onGround = true;
        }
    }

    for (auto& m : monsters) {
        if(Collision::AABB(m->getComponent<ColliderComponent>().collider, player.getComponent<ColliderComponent>().collider)){
           // std::cout << "Player hit" << std::endl;
            counter++;
            m->destroy();
        }
    }
    
    if (Game::event.type == SDL_KEYDOWN) {
        switch (Game::event.key.keysym.sym) {
            case SDLK_z:
                assets->CreateProjectile(Vector2D(playerPos.x-20, playerPos.y),Vector2D(-2,-2), 80, 2, "projectile");
                break;
            case SDLK_c:
                assets->CreateProjectile(Vector2D(playerPos.x+80, playerPos.y),Vector2D(2,-2), 80, 2, "projectile");
                break;
            default:
                break;
        }
    }

    
    for(auto& monster : monsters){
        for(auto& projectile : projectiles){
            if (Collision::AABB(monster->getComponent<ColliderComponent>().collider, projectile->getComponent<ColliderComponent>().collider)) {
                monster->destroy();
                projectile->destroy();
                counter++;
            }
        }
    }

    for (i ; i<20; i++) {
        Vector2D vec;
        vec.x = rand() % 2000 + 100;
        vec.y = rand() % 2000 + 100;
        
        assets->CreateMonster(Vector2D(vec.x,vec.y),"monster");
    }
    
    camera.x = player.getComponent<TransformComponent>().position.x - 400;
    camera.y = player.getComponent<TransformComponent>().position.y - 320;
    
    
    if (camera.x < 0) {
        camera.x = 0;
    }
    if (camera.y < 0) {
        camera.y = 0;
    }
    if (camera.x > camera.w*4) {
        camera.x = camera.w*4;
    }
    if (camera.y  > camera.h*4) {
        camera.y = camera.h*4;
    }

}



void Game::render(){
    
    SDL_RenderClear(renderer);
    
    for (auto& t : tiles){
        t->draw();
    }
//    for (auto& c : colliders) {
//        c->draw();
//    }

    for(auto& pr : projectiles){
        pr->draw();
    }
    
   for (auto& m : monsters){
       m->draw();
    }
    
    for (auto& p : players){
        p->draw();
    }
    
    label.draw();
    
    SDL_RenderPresent(renderer);
}
void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    
    std::cout << "Cleaned" << std::endl;
}




