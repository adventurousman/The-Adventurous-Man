//
// Created by hoang on 12/9/15.
//
#include "CApp.h"

int CApp::showMenu(SDL_Surface *screen) {
    int x, y;
    bool isRunning = true;
    const int menuNumber = 3;
    const char *menuOptions[menuNumber] = {"Continue", "Map creator", "Exit"};
    SDL_Surface *menu[menuNumber];
    bool options[menuNumber] = {0, 0};
    SDL_Color colors[2] = {{255, 255, 255},
                           {255, 0,   0}};

    for (int i = 0; i < menuNumber; i++)
        menu[i] = TTF_RenderText_Solid(font, menuOptions[i], colors[0]);

    SDL_Rect menuPosition[menuNumber];
    for (int i = 0; i < menuNumber; i++) {
        menuPosition[i].x = screen->clip_rect.w / 2 - menu[i]->clip_rect.w / 2;
        menuPosition[i].y = screen->clip_rect.h / 2 + i * (menu[i]->clip_rect.h);
    }
    SDL_Event menuEvent;

    SDL_Surface *menuDisplay = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, screen->w, screen->h, 32,
                                              screen->format->Rmask, screen->format->Gmask,
                                              screen->format->Bmask, screen->format->Amask);

    SDL_FillRect(menuDisplay, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
    SDL_SetAlpha(menuDisplay, SDL_SRCALPHA, 129);
    SDL_BlitSurface(menuDisplay, NULL, screen, NULL);
    SDL_FreeSurface(menuDisplay);
    while (isRunning) {
        SDL_WaitEvent(&menuEvent);

        switch (menuEvent.type) {
            case SDL_QUIT:
                for (int i = 0; i < menuNumber; i++)
                    SDL_FreeSurface(menu[i]);
                return 2;
            case SDL_MOUSEMOTION:
                x = menuEvent.motion.x;
                y = menuEvent.motion.y;
                for (int i = 0; i < menuNumber; i++) {
                    if (x >= menuPosition[i].x
                        && x <= (menuPosition[i].x + menu[i]->clip_rect.w)
                        && y >= menuPosition[i].y
                        && y <= (menuPosition[i].y + menu[i]->clip_rect.h)) {
                        if (! options[i]) {
                            SDL_FreeSurface(menu[i]);
                            menu[i] = TTF_RenderText_Solid(font, menuOptions[i], colors[1]);
                            options[i] = 1;
                        }
                    } else {
                        if (options[i]) {
                            SDL_FreeSurface(menu[i]);
                            menu[i] = TTF_RenderText_Solid(font, menuOptions[i], colors[0]);
                            options[i] = 0;
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = menuEvent.button.x;
                y = menuEvent.button.y;
                for (int i = 0; i < menuNumber; i++) {
                    if (x >= menuPosition[i].x
                        && x <= (menuPosition[i].x + menu[i]->clip_rect.w)
                        && y >= menuPosition[i].y &&
                        y <= (menuPosition[i].y + menu[i]->clip_rect.h)) {
                        for (int j = 0; j < menuNumber; j++)
                            SDL_FreeSurface(menu[j]);
                        return i;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (menuEvent.key.keysym.sym == SDLK_ESCAPE) {
                    for (int i = 0; i < menuNumber; i++)
                        SDL_FreeSurface(menu[i]);
                    return 0;
                }
                break;
        }
        for (int i = 0; i < menuNumber; i++)
            SDL_BlitSurface(menu[i], NULL, screen, &menuPosition[i]);
        SDL_Flip(screen);
    }
}
