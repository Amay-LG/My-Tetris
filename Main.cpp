/*****************************************************************************************
* File: Main.cpp
* Desc: Runs game and gameplay loop
*
* gametuto.com - Javier L�pez L�pez (javilop.com)
* 
* Author - Amay Lokesh Galappa
*
*****************************************************************************************/
#include "Game.h"
#include "Timer.h"
#ifndef LINUX
//#include <windows.h>
#endif

#define FRAME_RATE 60 // Frame rate of game

/*
Main
*/
// int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
int main(int argc, char* argv[])
{
    // —– Vars —–

    // Class for drawing stuff, it uses SDL for the rendering.
    Graphics * mIO = Graphics::Instance();
    int mScreenHeight = mIO->GetScreenHeight();

    // Pieces
    Pieces mPieces;

    // Board
    Board mBoard (&mPieces, mScreenHeight);

    // Game
    Game mGame (&mBoard, &mPieces, mScreenHeight);

    // Get the actual clock milliseconds (SDL)
    unsigned long mTime1 = SDL_GetTicks();

    Timer * mTimer = Timer::Instance();

    while (!mIO->IsKeyDown(SDLK_q))
    {
        
        mTimer->Update();
        

        if(mTimer->DeltaTime() >= 1.0f / FRAME_RATE){
            mIO->ClearScreen();
            mGame.DrawScene();
            mIO->UpdateScreen();
            
            mTimer->Reset();
        }
        

        int mKey = mIO->Pollkey();
        switch (mKey) {
            case (SDLK_q):
            {
                goto end_game;
            }
            case (SDLK_RIGHT):
            {
                if(mBoard.IsPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation)){
                    mGame.mPosX++;
                }
                break;
            }
            case (SDLK_LEFT):
            {
                if(mBoard.IsPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation)){
                    mGame.mPosX--;    
                }
                break;
            }
            case (SDLK_DOWN):
            {
                if(mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation)){
                    mGame.mPosY++;
                }
                break;
            }
            case (SDLK_x):
            {   
                while(mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation)){
                    mGame.mPosY++;
                }

                if(mBoard.IsGameOver()){
                    mIO->Getkey();
                    exit(0);
                }

                mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);
                mBoard.DeletePossibleLines();
                mGame.CreateNewPiece();
                mTime1 = SDL_GetTicks();
                break;
            }
            case (SDLK_z):
            {
                if(mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation+1) % 4)){
                    mGame.mRotation = (mGame.mRotation+1) % 4;
                }
                break;
            }
        }
        
        // Periodically move down
        unsigned long mTime2 = SDL_GetTicks();
        

        if(mTime2 - mTime1 > WAIT_TIME){
            if(mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation)){
                mGame.mPosY++;
            } else {

                if (mBoard.IsGameOver()){
                    mIO->Getkey();
                    exit(0);
                }

                mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);
                mBoard.DeletePossibleLines();
                mGame.CreateNewPiece();
            }
            
            mTime1 = SDL_GetTicks();
        }

    }
    end_game:;
    return 0;
}