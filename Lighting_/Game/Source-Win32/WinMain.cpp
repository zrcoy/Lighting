#include "GamePCH.h"

#include "Game/Game.h"
#include <time.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 1024

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    srand(time(NULL));
    Framework* pFramework = new Framework();

    pFramework->Init( SCREEN_WIDTH, SCREEN_HEIGHT );

    GameCore* pGame = new Game( pFramework );

    pFramework->Run( pGame );
    pFramework->Shutdown();

    delete pGame;
    delete pFramework;

#if _DEBUG
    MyMemory_ValidateAllocations( true );
#endif
}
