#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Surface *screen = SDL_GetWindowSurface(window);
    SDL_Rect pl1 = (SDL_Rect) {40, 40, 20, 100};
    SDL_Rect pl2 = (SDL_Rect) {540, 200, 20, 100};
    SDL_Rect ball = (SDL_Rect) {320, 240, 20, 20};
    
    Uint32 color = 0xff0000ff;
    int running = 1;
    int pl1_speed = 5;
    int ai_speed = 3;
    int ball_dx = 4, ball_dy = 4;


    int score1 = 0, score2 = 0;

    if (TTF_Init() == -1) {
    printf("Failed to initialize SDL_ttf: %s\n", TTF_GetError());
    return 1;
}

    TTF_Font *font = TTF_OpenFont("arial.ttf", 20);
    if (!font){
        printf("Error loading font!!!: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Color textcolor = {255, 255, 255, 255};


    while (running) {
        // int x=40,y=40;
        SDL_FillRect(screen, NULL, 0x00000000);

        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT){
            running = 0;
        }

        //BAD CODE
        // if (event.type == SDL_KEYDOWN){
        //     printf("Keydown pressed: %d\n", event.key.keysym.scancode);
        //     if (event.key.keysym.scancode == 82){
        //         SDL_FillRect(screen, &pl1, 0x00000000);
        //         pl1.y -= 5;
        //         SDL_FillRect(screen, &pl1, color);
        //     }
        //     if (event.key.keysym.scancode == 81){
        //         SDL_FillRect(screen, &pl1, 0x00000000);
        //         pl1.y += 5;
        //         SDL_FillRect(screen, &pl1, color);
        //     }  
        // }
        // if (event.type == SDL_KEYUP){
        //     printf("Keyup pressed: %d\n", event.key.keysym.scancode);
        // }

        const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        if(keystate[SDL_SCANCODE_UP] && pl1.y > 0) pl1.y -= pl1_speed;
        if(keystate[SDL_SCANCODE_DOWN] && pl1.y < 480) pl1.y += pl1_speed;

        ball.x -= ball_dx;
        ball.y += ball_dy;

        if (ball.y <= 0 || ball.y >= 480 - ball.h) {
            ball_dy = -ball_dy;
        }
        if (ball.x <= pl1.x + pl1.w && ball.y + ball.h > pl1.y && ball.y < pl1.y + pl1.h) {
            
            if (ball.y + ball.h - ball_dy > pl1.y && ball.y - ball_dy < pl1.y + pl1.h) {
                ball_dx = -ball_dx; 
                ball.x = pl1.x + pl1.w;
                ball_dy += (rand() % 3 - 1);
            } else {
                ball_dy = -ball_dy; 
            }
        }

        if (ball.x + ball.w >= pl2.x && ball.y + ball.h > pl2.y && ball.y < pl2.y + pl2.h) {
            if (ball.y + ball.h - ball_dy > pl2.y && ball.y - ball_dy < pl2.y + pl2.h) {
                ball_dx = -ball_dx; 
                ball.x = pl2.x - ball.w; 
                ball_dy += (rand() % 3 - 1);
            } else {
                ball_dy = -ball_dy; 
            }
        }
        //BAD COLLISION CODE
        // if (ball.y <=0 || ball.y >=480 - ball.h) ball_dy = -ball_dy;
        // if (ball.x <= pl1.x + pl1.w && ball.y + ball.h > pl1.y && ball.y < pl1.y + pl1.h) ball_dx = -ball_dx;
        // if (ball.x + ball.w >= pl2.x && ball.y + ball.h > pl2.y && ball.y < pl2.y + pl2.h) ball_dx = -ball_dx;



        if (ball.x <=0 ){
            score2++;
            ball.x = 320;
            ball.y = 240;
            ball_dx = (rand() % 2 == 0 ? 3 : -3);
            ball_dy = (rand() % 2 == 0 ? 3 : -3);
            printf("Player 1 score: %d\n", score1);
            printf("Player 2 score: %d\n\n", score2);
        
        }
        if (ball.x + ball.w >=640){
            score1++;
            ball.x = 320;
            ball.y = 240;
            ball_dx = (rand() % 2 == 0 ? 3 : -3);
            ball_dy = (rand() % 2 == 0 ? 3 : -3);
            printf("Player 1 score: %d\n", score1);
            printf("Player 2 score: %d\n\n", score2);
        }


        if (ball.y < pl2.y) {
            pl2.y -= ai_speed;
        } else if (ball.y > pl2.y + pl2.h) {
            pl2.y += ai_speed;
        }

        if (pl2.y < 0) pl2.y = 0;
        if (pl2.y > 480 - pl2.h) pl2.y = 480 - pl2.h;

        SDL_FillRect(screen, &pl1, color);
        SDL_FillRect(screen, &pl2, color);
        SDL_FillRect(screen, &ball, 0xffffffff);


        char scoreText1[100];
        sprintf(scoreText1, "Player 1 - Sumir score: %d", score1);
        SDL_Surface *scoreSurface1 = TTF_RenderText_Solid(font, scoreText1, textcolor);
        SDL_Rect scoreRect1 = {100, 15, scoreSurface1->w, scoreSurface1->h};
        SDL_BlitSurface(scoreSurface1, NULL, screen, &scoreRect1);
        SDL_FreeSurface(scoreSurface1);

        char scoreText2[100];
        sprintf(scoreText2, "Player 2 - AI score: %d", score2); 
        SDL_Surface *scoreSurface2 = TTF_RenderText_Solid(font, scoreText2, textcolor);
        SDL_Rect scoreRect2 = {400, 15, scoreSurface2->w, scoreSurface2->h};
        SDL_BlitSurface(scoreSurface2, NULL, screen, &scoreRect2);
        SDL_FreeSurface(scoreSurface2);


        SDL_UpdateWindowSurface(window);
        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}