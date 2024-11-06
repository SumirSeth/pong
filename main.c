#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Surface *screen = SDL_GetWindowSurface(window);
    SDL_Rect pl1 = (SDL_Rect) {40, 40, 50, 200};
    SDL_Rect pl2 = (SDL_Rect) {540, 200, 50, 200};
    Uint32 color = 0xff0000ff;
    SDL_FillRect(screen, &pl1, color);
    SDL_FillRect(screen, &pl2, color);
    int running = 1;
    while (running) {
        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT){
            running = 0;
        }
        if (event.type == SDL_KEYDOWN){
            printf("Keydown pressed: %d\n", event.key.keysym.scancode);
        }
        if (event.type == SDL_KEYUP){
            printf("Keyup pressed: %d\n", event.key.keysym.scancode);
        }
        SDL_UpdateWindowSurface(window);
    }
    return 0;

}