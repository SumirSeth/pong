#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Surface *screen = SDL_GetWindowSurface(window);
    SDL_Rect rect = (SDL_Rect) {20, 20, 100, 100};
    SDL_FillRect(screen, &rect, 0xffffffff);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(5000);
    return 0;
}
