//
// Created by lavreniuk on 15.09.2020.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//sdl lesson 9
//The Viewport
//https://lazyfoo.net/tutorials/SDL/09_the_viewport/index.php

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Texture* gTexture = nullptr;

bool init(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << SDL_GetError();
        return false;
    }

    gWindow = SDL_CreateWindow("SDL TUTORIAL",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH,
                               SCREEN_HEIGHT,
                               SDL_WINDOW_SHOWN);

    if(gWindow == nullptr){
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if(gRenderer == nullptr){
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return true;
}

void clear(){
    SDL_DestroyTexture(gTexture);
    gTexture = nullptr;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture(std::string path){
    SDL_Texture* newTexture = nullptr;
    auto loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == nullptr){
        std::cout << SDL_GetError() << std::endl;
        return nullptr;
    }

    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if(newTexture == nullptr){
        std:: cout << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_FreeSurface(loadedSurface);

    return newTexture;
}
bool loadMedia(){
    gTexture = loadTexture("lesson9_texture.png");
    if(gTexture == nullptr){
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}


void RenderLeftTopViewport(SDL_Texture* texture, SDL_Renderer* renderer){
    SDL_Rect viewPort;
    viewPort.x = 0;
    viewPort.y = 0;
    viewPort.w = SCREEN_WIDTH / 2;
    viewPort.h = SCREEN_HEIGHT / 2;

    SDL_RenderSetViewport(renderer, &viewPort);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}

void RenderRightTopViewport(SDL_Texture* texture, SDL_Renderer* renderer){
    SDL_Rect viewPort;
    viewPort.x = SCREEN_WIDTH / 2;
    viewPort.y = 0;
    viewPort.w = SCREEN_WIDTH / 2;
    viewPort.h = SCREEN_HEIGHT / 2;

    SDL_RenderSetViewport(renderer, &viewPort);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}

void RenderBottomViewport(SDL_Texture* texture, SDL_Renderer* renderer){
    SDL_Rect viewPort;
    viewPort.x = 0;
    viewPort.y = SCREEN_HEIGHT / 2;
    viewPort.w = SCREEN_WIDTH;
    viewPort.h = SCREEN_HEIGHT / 2;

    SDL_RenderSetViewport(renderer, &viewPort);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}

int main(){
    if(!init()){
        std::cout << "init failed" << std::endl;
        clear();
        return 0;
    }

    if(!loadMedia()){
        std::cout << "load media failed" << std::endl;
        clear();
        return 0;
    }

    RenderRightTopViewport(gTexture, gRenderer);
    RenderLeftTopViewport(gTexture, gRenderer);
    RenderBottomViewport(gTexture, gRenderer);

    auto quit = false;
    SDL_Event e;

    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
        }


        SDL_RenderPresent(gRenderer);
    }

    clear();
    return 0;
}
