#include "kgh.h"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
    SetTargetFPS(FPS);

    GameMode gameMode;
    gameMode.numberOfPlayer = 1;
    gameMode.path = 1;
    gameMode.difficulty = 1;

    Player player1("");
    bool loginStatus = loginMenu(&player1);
    bool start;
    if (loginStatus)
    {
        start = mainMenu(&gameMode);
    }

    Player player2("AI");
    if (!start)
    {
        loginStatus = loginMenu(&player2);
    }

    game(&player1, &player2, &gameMode);

    CloseWindow();

    return 0;
}
