#include <iostream>
#include <SDL2/SDL.h>

//sdl lesson 1
//hello sdl your first graphics window
//https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index2.php

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main() {
    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not initialize! SDL internal error : " << SDL_GetError();
    }
    else{
        window = SDL_CreateWindow("SDL TUTORIAL",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH,
                                  SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if(window == nullptr){
            std::cout << "Window could not created! SDL internal error : " << SDL_GetError();
        }
        else{
            screenSurface = SDL_GetWindowSurface(window);

            SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface -> format, 0xFF, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
        }

        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    return 0;
}
