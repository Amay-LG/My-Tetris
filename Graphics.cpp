/*****************************************************************************************
* File: Graphics.cpp
* Desc: Contains all the Graphics Functions; directly interacts with window.
*
* Author - Amay Lokesh Galappa: Updated to use SDL2
*
*****************************************************************************************/
#include "Graphics.h"
Graphics * Graphics::sInstance = NULL;
bool Graphics::sInitialized = false;

Uint32 Graphics::SetColor(color color){
    switch(color) {
        case (BLACK):{
            return SDL_MapRGB(mPreWindow->format, 0, 0, 0);
        }
        case (RED):{
            return SDL_MapRGB(mPreWindow->format, 255, 0, 0);
        }
        case (GREEN):{
            return SDL_MapRGB(mPreWindow->format, 0, 255, 0);
        }
        case (BLUE):{
            return SDL_MapRGB(mPreWindow->format, 0, 0, 255);
        }
        case (CYAN):{
            return SDL_MapRGB(mPreWindow->format, 0, 255, 255);
        }
        case (MAGENTA):{
            return SDL_MapRGB(mPreWindow->format, 255, 0, 255);
        }
        case (YELLOW):{
            return SDL_MapRGB(mPreWindow->format, 255, 255, 0);
        }
        case (WHITE):{
            return SDL_MapRGB(mPreWindow->format, 255, 255, 255);
        }
    }
    return -1;
}

Graphics * Graphics::Instance() {
    if(sInstance == NULL){
        sInstance = new Graphics();
    }

    return sInstance;
}

void Graphics::Release(){
    delete sInstance;
    sInstance = NULL;
    sInitialized = false;
}

bool Graphics::Initialized() {
    return sInitialized;
}

Graphics::Graphics() {
    mPreWindow = NULL;
    sInitialized = Init();
}

Graphics::~Graphics() {
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;

    SDL_Quit;
}

bool Graphics::Init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL Initialization Error: %s\n", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("Tetris (kinda)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(mWindow == NULL){
        printf("Window Creation Error: %s\n", SDL_GetError());
        return false;
    }

    mPreWindow = SDL_GetWindowSurface(mWindow);

    return true;
}

void Graphics::UpdateScreen(){
    SDL_UpdateWindowSurface(mWindow);
}

void Graphics::DrawRectangle(int x1, int y1, int x2, int y2, color color){

    SDL_Rect rect;
    rect.x = x1;
    rect.y = y1;
    rect.w = x2-x1;
    rect.h = y2-y1;

    Uint32 colorVal = SetColor(color);

    SDL_FillRect(mPreWindow, &rect, colorVal);
}

void Graphics::ClearScreen(){
    Uint32 colorVal = SetColor(BLACK);
    SDL_FillRect(mPreWindow, NULL, colorVal);
}

int Graphics::Pollkey(){
    SDL_Event event;
	while ( SDL_PollEvent(&event) ) 
	{
		switch (event.type) {
			case SDL_KEYDOWN:
				return event.key.keysym.sym;
			case SDL_QUIT:
				exit(3);
		}
	}
	return -1;
}

int Graphics::IsKeyDown (int pKey)
{
	const Uint8* mKeytable;
	int mNumkeys;
	SDL_PumpEvents();
	mKeytable = SDL_GetKeyboardState(&mNumkeys);
	return mKeytable[pKey];
}

int Graphics::Getkey()
{
	SDL_Event event;
	while (true)
	{
	  SDL_WaitEvent(&event);
	  if (event.type == SDL_KEYDOWN)
		  break;
      if (event.type == SDL_QUIT)
		  exit(3);
	};
	return event.key.keysym.sym;
}

int Graphics::GetScreenHeight(){
    return SCREEN_HEIGHT;
}