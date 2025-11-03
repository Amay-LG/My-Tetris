/*****************************************************************************************
* File: Game.h
* Desc: defines the general gameplay loop and actions
*
* gametuto.com - Javier L�pez L�pez (javilop.com)
* 
* Author - Amay Lokesh Galappa
*
*****************************************************************************************/

#include "Game.h"



Game::Game (Board *pBoard, Pieces *pPieces, int pScreenHeight)
{
    mBoard = pBoard;
    mPieces = pPieces;
    mIO = Graphics::Instance();
    mScreenHeight = pScreenHeight;
    InitGame();
}

/*
======================================
Get a random int between to integers

Parameters:
>> pA: First number
>> pB: Second number
======================================
*/
int Game::GetRand (int pA, int pB)
{
    return rand() % (pB - pA + 1) + pA;
}

/*
======================================
Initial parameters of the game
======================================
*/
void Game::InitGame()
{
    srand ((unsigned int) time(NULL));

    //Current block
    mPiece = GetRand(0,6);
    mRotation = GetRand(0, 3);
    mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
    mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

    //Next Block
    mNextPiece = GetRand(0,6);
    mNextRotation = GetRand(0,3);
    mNextPosX = (BOARD_WIDTH + 5);
    mNextPosY = 5;
}

/*
======================================
Create a random piece
======================================
*/
void Game::CreateNewPiece()
{
    //Update current piece
    mPiece = mNextPiece;
    mRotation = mNextRotation;
    mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
    mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

    //Create next Piece
    mNextPiece = GetRand(0, 6);
    mNextRotation = GetRand(0, 3);
}

/*
======================================
Draw piece

Parameters:

>> pX: Horizontal position in blocks
>> pY: Vertical position in blocks
>> pPiece: Piece to draw
>> pRotation: 1 of the 4 possible rotations
======================================
*/
void Game::DrawPiece (int pX, int pY, int pPiece, int pRotation)
{
    color mColor = BLACK;

    // Obtain the position in pixel in the screen of the block we want to draw
    int mPixelsX = mBoard->GetXPosInPixels (pX);
    int mPixelsY = mBoard->GetYPosInPixels (pY);

    for (int i = 0; i < PIECE_BLOCKS; i++){
        for (int j = 0; j < PIECE_BLOCKS; j++){
            switch (mPieces->GetBlockType(pPiece, pRotation, j, i)){
                case 1: mColor = GREEN; break;
                case 2: mColor = BLUE; break;
            }
            if (mPieces->GetBlockType (pPiece, pRotation, j, i) != 0){
                mIO->DrawRectangle(mPixelsX + i*BLOCK_SIZE,  //Top left X
                                mPixelsY + j*BLOCK_SIZE,     //Top left Y
                                (mPixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1, //Bottom Right X
                                (mPixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, //Bottom Right Y
                                mColor);
            }
        }
    }
}

/*
======================================
Draw board

Draw the two lines that delimit the board
======================================
*/
void Game::DrawBoard ()
{
    int mX1 = BOARD_POSITION - (BOARD_WIDTH/2)*BLOCK_SIZE -1;
    int mX2 = BOARD_POSITION + (BOARD_WIDTH/2)*BLOCK_SIZE;
    int mY = mScreenHeight - (BLOCK_SIZE*BOARD_HEIGHT);

    // Check that the vertical margin is not to small
    assert (mY > MIN_VERTICAL_MARGIN);

    mIO->DrawRectangle(mX1 - BOARD_LINE_WIDTH, mY, mX1, mScreenHeight - 1, BLUE);
    mIO->DrawRectangle(mX2, mY, mX2 + BOARD_LINE_WIDTH, mScreenHeight - 1, BLUE);

    // Check that the horizontal margin is not to small
    assert(mX1 > MIN_HORIZONTAL_MARGIN);

    mX1++;
    for(int i = 0; i < BOARD_WIDTH; i++){
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            if(!(mBoard->IsFreeBlock(i, j))){
                mIO->DrawRectangle (mX1+(i*BLOCK_SIZE), mY + (j*BLOCK_SIZE),
                                    mX1+(i*BLOCK_SIZE) + BLOCK_SIZE - 1,
                                    mY + (j*BLOCK_SIZE) + BLOCK_SIZE - 1,
                                    RED);
            }
        }
    }
}

/*
======================================
Draw scene

Draw all the objects of the scene
======================================
*/
void Game::DrawScene()
{
    DrawBoard();
    DrawPiece(mPosX, mPosY, mPiece, mRotation);
    DrawPiece(mNextPosX, mNextPosY, mNextPiece, mNextRotation);
}


