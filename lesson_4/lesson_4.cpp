//
// Created by lavreniuk on 06.09.2020.
//
#include <iostream>
#include <SDL2/SDL.h>

//sdl lesson 1
//key press
//https://lazyfoo.net/tutorials/SDL/04_key_presses/index.php

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL + 1];
SDL_Surface* gCurrentSurface = nullptr;

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

void close(){
    SDL_FreeSurface(gCurrentSurface);

    //destroy sdl window. window surface will free too
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    SDL_Quit();
}

SDL_Surface* loadSurface(std::string path){
    auto loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == nullptr){
        std::cout << SDL_GetError() << std::endl;
    }

    return loadedSurface;
}

bool loadMedia(){
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("lesson4_default.bmp");
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("lesson4_up.bmp");
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("lesson4_down.bmp");
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("lesson4_left.bmp");
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("lesson4_right.bmp");
    gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL] = loadSurface("lesson4_total.bmp");

    for(auto i = 0; i < (sizeof(gKeyPressSurfaces)/sizeof(*gKeyPressSurfaces)); ++i){
        if(gKeyPressSurfaces[i] == nullptr) {
            std::cout << KeyPressSurfaces(i) << "is not loaded" << std::endl;
            return false;
        }
    }

    return true;
}

int lesson4_main(){
    if(init() == false){
        std::cout << "init failed" << std::endl;
        return 0;
    }

    if(!loadMedia()){
        std::cout << "loadMedia failed" << std::endl;
        return 0;
    }

    auto quit = false;

    SDL_Event e;

    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
    SDL_BlitSurface(gCurrentSurface, nullptr, gScreenSurface, nullptr);

    SDL_UpdateWindowSurface(gWindow);

    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
                break;
            }

            if(e.type != SDL_KEYDOWN){
                break;
            }

            SDL_Surface* selectedSurface = nullptr;

            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    selectedSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                    break;
                case SDLK_DOWN:
                    selectedSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                    break;
                case SDLK_LEFT:
                    selectedSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                    break;
                case SDLK_RIGHT:
                    selectedSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                    break;
                case SDLK_KP_5:
                    if(e.key.keysym.mod != KMOD_NUM)
                        break;
                    selectedSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
                    break;
                default:
                    selectedSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                    break;
            }

            if(selectedSurface == nullptr) {
                break;
            }

            if(selectedSurface != gCurrentSurface){
                gCurrentSurface = selectedSurface;
                SDL_BlitSurface(gCurrentSurface, nullptr, gScreenSurface, nullptr);
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    close();

    return 0;
}


