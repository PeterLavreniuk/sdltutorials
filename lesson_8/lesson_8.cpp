//
// Created by lavreniuk on 07.09.2020.
//

#include <iostream>
#include <SDL2/SDL.h>

//sdl lesson 8
//Geometry rendering
//https://lazyfoo.net/tutorials/SDL/08_geometry_rendering/index.php

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

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
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;

    SDL_Quit();
}


int lesson_8_main(){
    if(!init()){
        std::cout << "init failed" << std::endl;
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

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH /2, SCREEN_HEIGHT / 2};
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(gRenderer, &fillRect);

        SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderDrawRect(gRenderer, &outlineRect);

        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

        SDL_RenderPresent(gRenderer);
    }

    clear();
    return 0;
}