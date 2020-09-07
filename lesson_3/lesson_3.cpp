//
// Created by lavreniuk on 06.09.2020.
//

#include <iostream>
#include <SDL2/SDL.h>

//sdl lesson 3
//event drive programming
//https://lazyfoo.net/tutorials/SDL/03_event_driven_programming/index.php

SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gImageSurface = nullptr;
SDL_Surface* gXOutSurface = nullptr;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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

    gScreenSurface = SDL_GetWindowSurface(gWindow);

    return true;
}

bool loadMedia(){
    gImageSurface = SDL_LoadBMP("image.bmp");
    if(gImageSurface == nullptr){
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    gXOutSurface = SDL_LoadBMP("lesson3_out.bmp");
    if(gXOutSurface == nullptr){
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void close(){
    //free gImageSurface
    SDL_FreeSurface(gImageSurface);
    gImageSurface = nullptr;

    //free gXOutSurface
    SDL_FreeSurface(gXOutSurface);
    gXOutSurface = nullptr;

    //destroy sdl window. window surface will free too
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    SDL_Quit();
}

int lesson3_main(){
    if(init() == false){
        std::cout << "init failed" << std::endl;
        return 0;
    }

    if(!loadMedia()){
        std::cout << "loadMedia failed" << std::endl;
        return 0;
    }

    SDL_BlitSurface(gImageSurface, nullptr, gScreenSurface, nullptr);
    SDL_UpdateWindowSurface(gWindow);

    auto quit = false;
    SDL_Event e;

    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            //in the original tutorial - we waiting for "X" window key press
            quit = (SDL_GetScancodeFromKey(e.key.keysym.sym) == SDL_SCANCODE_X);
        }
    }

    SDL_BlitSurface(gXOutSurface, nullptr, gScreenSurface, nullptr);
    SDL_UpdateWindowSurface(gWindow);
    SDL_Delay(4000);

    close();

    return 0;
}