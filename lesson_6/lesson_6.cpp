//
// Created by lavreniuk on 07.09.2020.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


//install sdl images sudo apt-get install libsdl2-image-dev

//sdl lesson 6
//extension libraries and loading other image formats
//https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index2.php

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow;
SDL_Surface* gScreenSurface;
SDL_Surface* gImageSurface;

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

    auto imgFlags = IMG_INIT_JPG;
    if(!(IMG_Init(imgFlags) & imgFlags)){
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);

    return true;
}

SDL_Surface* loadSurface(std::string path){
    SDL_Surface* optimizedSurface = nullptr;
    auto loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr){
        std::cout << "unable to load image" << SDL_GetError() << std::endl;
        return nullptr;
    }

    optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface -> format, 0);
    if(optimizedSurface == nullptr){
        std::cout << "unable to optimize surface" << SDL_GetError() << std::endl;
        SDL_FreeSurface(loadedSurface);
        return nullptr;
    }

    SDL_FreeSurface(loadedSurface);
    return optimizedSurface;
}

void clear(){
    SDL_FreeSurface(gImageSurface);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    IMG_Quit();
    SDL_Quit();
}

int lesson6_main(){
    if(!init()){
        std::cout << "init failed" << std::endl;
    }

    gImageSurface = loadSurface("lesson_6_img.png");

    if(gImageSurface == nullptr){
        std::cout << "gImageSurface is null" << std::endl;
        clear();
        return 0;
    }

    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;

    SDL_BlitScaled(gImageSurface, nullptr, gScreenSurface, &stretchRect);
    SDL_UpdateWindowSurface(gWindow);

    SDL_Delay(3000);

    clear();
    return 0;
}