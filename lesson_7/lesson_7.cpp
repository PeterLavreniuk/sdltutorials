//
// Created by lavreniuk on 07.09.2020.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


//install sdl images sudo apt-get install libsdl2-image-dev

//sdl lesson 7
//texture loading and rendering
//https://lazyfoo.net/tutorials/SDL/07_texture_loading_and_rendering/index.php

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

    auto imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & IMG_INIT_PNG)){
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    return true;
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
    gTexture = loadTexture("lesson7_texture.png");
    if(gTexture == nullptr){
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

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


int lesson7_main(){
    if(!init()){
        std::cout << "init failed" << std::endl;
        clear();
        return 0;
    }

    if(!loadMedia()){
        std::cout << "loadMedia failed" << std::endl;
        clear();
        return 0;
    }

    auto quit = false;
    SDL_Event e;

    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
        }

        SDL_RenderClear(gRenderer);
        SDL_RenderCopy(gRenderer, gTexture, nullptr, nullptr);
        SDL_RenderPresent(gRenderer);
    }

    clear();
    return 0;
}

