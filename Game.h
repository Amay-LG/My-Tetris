/*****************************************************************************************
* File: Game.h
* Desc: defines the general gameplay loop and actions
*
* gametuto.com - Javier L�pez L�pez (javilop.com)
* 
* Author - Amay Lokesh Galappa
*
*****************************************************************************************/

#ifndef _GAME_
#define _GAME_

#include "Board.h"
#include "Pieces.h"
#include "Graphics.h"
#include <time.h>
#include <cassert>

#define WAIT_TIME 700

// ——————————————————————————–
// Game
// ——————————————————————————–

class Game
{
    public:
        Game (Board *pBoard, Pieces *pPieces, int pScreenHeight);

        void DrawScene ();
        void CreateNewPiece ();

        int mPosX, mPosY;
        int mPiece, mRotation;
    
    private:
        int mScreenHeight; // Screen height in pixels
        int mNextPosX, mNextPosY; // Position of the next piece
        int mNextPiece, mNextRotation; // Kind and rotation of the next piece

        Board *mBoard;
        Pieces *mPieces;

        Graphics *mIO;

        int GetRand (int pA, int pB);
        void InitGame();
        void DrawPiece (int pX, int pY, int pPiece, int pRotation);
        void DrawBoard ();
};

#endif