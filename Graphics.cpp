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

/*
======================================
Applies a color to the Renderer for drawing on the screen

Parameters:
>> color: color to be applied to renderer
======================================
*/
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

/*
======================================
Creates a new instance of Graphics
======================================
*/
Graphics * Graphics::Instance() {
    if(sInstance == NULL){
        sInstance = new Graphics();
    }

    return sInstance;
}

/*
======================================
Destroys current instance of Graphics
======================================
*/
void Graphics::Release(){
    delete sInstance;
    sInstance = NULL;
    sInitialized = false;
}

/*
======================================
Returns true if Graphics is initialized, false otherwise
======================================
*/
bool Graphics::Initialized() {
    return sInitialized;
}

/*
======================================
Constructor for Graphics
======================================
*/
Graphics::Graphics() {
    mPreWindow = NULL;
    sInitialized = Init();
}

/*
======================================
Destructor for Graphics
======================================
*/
Graphics::~Graphics() {
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;

    SDL_Quit;
}

/*
======================================
Initializes new window and surface (called preWindow)
======================================
*/
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

/*
======================================
Updates window with preWindow (the surface for the current window)
======================================
*/
void Graphics::UpdateScreen(){
    SDL_UpdateWindowSurface(mWindow);
}
/*
======================================
Draws a rectangle onto the window with the specified location and color

Parameters:
>> x1: x-position of top left corner of rectangle 
>> y1: y-position of top left corner of rectangle
>> x2: x-position of bottom right corner of rectangle
>> y2: y-position of bottom right corner of rectangle
>> color: color of the rectangle
======================================
*/
void Graphics::DrawRectangle(int x1, int y1, int x2, int y2, color color){

    SDL_Rect rect;
    rect.x = x1;
    rect.y = y1;
    rect.w = x2-x1;
    rect.h = y2-y1;

    Uint32 colorVal = SetColor(color);

    SDL_FillRect(mPreWindow, &rect, colorVal);
}
/*
======================================
Clears preWindow by setting prewindow to all black
======================================
*/
void Graphics::ClearScreen(){
    Uint32 colorVal = SetColor(BLACK);
    SDL_FillRect(mPreWindow, NULL, colorVal);
}
/*
======================================
Gets key input from user
======================================
*/
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
/*
======================================
Checks if a certain key is pressed

Parameters:
>> pKey: checks if this key is pressed
======================================
*/
int Graphics::IsKeyDown (int pKey)
{
	const Uint8* mKeytable;
	int mNumkeys;
	SDL_PumpEvents();
	mKeytable = SDL_GetKeyboardState(&mNumkeys);
	return mKeytable[pKey];
}
/*
======================================
Returns the current key being pressed
======================================
*/
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
/*
======================================
Return height of screen
======================================
*/
int Graphics::GetScreenHeight(){
    return SCREEN_HEIGHT;
}
