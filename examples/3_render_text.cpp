// g++ 3_render_text.cpp -framework SDL2 -framework SDL2_image -framework SDL2_ttf


#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>


#include "SDL.h"
#include "SDL_ttf.h"

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT (WINDOW_WIDTH)

/*
- x, y: upper left corner.
- texture, rect: outputs.
*/
void render_text(SDL_Renderer *renderer, int x, int y, char *text,
        TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};
    SDL_Color backgroundColor = {0,0,0,0};

    // surface = TTF_RenderText_Solid(font, text, textColor);
    surface=TTF_RenderText_Shaded(font, text, textColor, backgroundColor);

    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}

int main(int argc, char **argv) {
    SDL_Event event;
    SDL_Rect rect1, rect2;
    SDL_Renderer *renderer;
    SDL_Texture *texture1, *texture2;
    SDL_Window *window;
    int quit;

    char font_path[100];
    sprintf(font_path, "../data/Sans.ttf");
    if (argc == 2) {
        sprintf(font_path, "%s", argv[1]);
    } else {
        printf("usage: render_text <font.ttf>\n");

    }

    /* Inint TTF. */
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    TTF_Init();
    TTF_Font *font = TTF_OpenFont(font_path, 24);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }

    char lines[2][100] = { "Hello", "world" };
    render_text(renderer, 0, 0, (char*)lines[0], font, &texture1, &rect1);
    render_text(renderer, 0, rect1.y + rect1.h, (char*)lines[1], font, &texture2, &rect2);

    quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        /* Use TTF textures. */
        SDL_RenderCopy(renderer, texture1, NULL, &rect1);
        SDL_RenderCopy(renderer, texture2, NULL, &rect2);

        SDL_RenderPresent(renderer);
    }

    /* Deinit TTF. */
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    free(font_path);
    return EXIT_SUCCESS;
}
