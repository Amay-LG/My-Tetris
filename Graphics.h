#ifndef _GRAPHICS_
#define _GRAPHICS_

#include <SDL.h>

enum color {BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE}; // Colors

class Graphics {

public:
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;

private:
    static Graphics * sInstance;
    static bool sInitialized;

    SDL_Window * mWindow;
    SDL_Surface * mPreWindow;

public:
    static Graphics * Instance();
    static void Release();
    static bool Initialized();
    void UpdateScreen();
    void DrawRectangle(int x1, int y1, int x2, int y2, color color);
    void ClearScreen();

    int Pollkey();
    int Getkey();
    int IsKeyDown(int key);
    int GetScreenHeight();

private:
    Graphics();
    ~Graphics();
    Uint32 SetColor(color color);
    bool Init();

};

#endif