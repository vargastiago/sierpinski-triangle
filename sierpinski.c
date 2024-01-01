#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600

void createWindow(SDL_Window **window, SDL_Renderer **renderer);
void destroyWindow(SDL_Window *window, SDL_Renderer *renderer);
void sierpinskiTriangles(SDL_Renderer *renderer, unsigned level);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("%s\n", "You must enter only one positive integer argument");
        exit(EXIT_FAILURE);
    }

    char *strPtr = NULL;
    int level = strtol(argv[1], &strPtr, 10);

    if (strcmp(strPtr, "") || level < 0) {
        printf("%s\n", "Argument must be a positive integer");
        exit(EXIT_FAILURE);
    }

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    createWindow(&window, &renderer);
    sierpinskiTriangles(renderer, level);

    SDL_Event event;

    // wait until close the window
    while (1) {
        if (SDL_WaitEvent(&event)) {
            if (event.type == SDL_QUIT) {
                destroyWindow(window, renderer);
                break;
            }
        }
    }
}

void createWindow(SDL_Window **window, SDL_Renderer **renderer) {
    if (SDL_Init(SDL_INIT_VIDEO < 0)) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    *window = SDL_CreateWindow(
        "Sierpinski Triangle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (*window == NULL) {
        printf("Window could not be created: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_SOFTWARE);

    if (*renderer == NULL) {
        printf("Renderer could not be created: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetRenderDrawColor(*renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(*renderer);
    SDL_RenderPresent(*renderer);
}

void destroyWindow(SDL_Window *window, SDL_Renderer *renderer) {
    if (renderer)
        SDL_DestroyRenderer(renderer);

    if (window)
        SDL_DestroyWindow(window);

    SDL_Quit();
}

SDL_Point middlePoint(SDL_Point p1, SDL_Point p2) {
    SDL_Point mid;

    mid.x = (p1.x + p2.x) / 2;
    mid.y = (p1.y + p2.y) / 2;
    return mid;
}

void displayTriangles(SDL_Renderer *renderer, unsigned level,
                      SDL_Point p1, SDL_Point p2, SDL_Point p3) {

    if (level == 0) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
        SDL_RenderDrawLine(renderer, p2.x, p2.y, p3.x, p3.y);
        SDL_RenderDrawLine(renderer, p3.x, p3.y, p1.x, p1.y);
        SDL_RenderPresent(renderer);
    } else {
        SDL_Point p12 = middlePoint(p1, p2);
        SDL_Point p23 = middlePoint(p2, p3);
        SDL_Point p31 = middlePoint(p3, p1);

        displayTriangles(renderer, level - 1, p1, p12, p31);
        displayTriangles(renderer, level - 1, p12, p2, p23);
        displayTriangles(renderer, level - 1, p31, p23, p3);
    }
}

void sierpinskiTriangles(SDL_Renderer *renderer, unsigned level) {
    SDL_Point p1 = {WIDTH / 2, 0};
    SDL_Point p2 = {0, HEIGHT};
    SDL_Point p3 = {WIDTH, HEIGHT};

    displayTriangles(renderer, level, p1, p2, p3);
}
