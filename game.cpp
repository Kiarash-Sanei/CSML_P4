#include "kgh.h"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
    SetTargetFPS(FPS);

    GameMode gameMode = {
        .numberOfPlayer = 1,
        .path = Path::Regular,
        .difficulty = Difficulty::Easy,
        .program = Program::Cpp};

    Player player1("Player1");
    Player player2("AI");

    bool loginStatus = false;
    bool start = false;
    loginStatus = loginMenu(&player1);
    if (loginStatus)
    {
        start = mainMenu(&gameMode);

        if (!start && gameMode.numberOfPlayer == 2)
        {
            loginStatus = loginMenu(&player2);
        }
    }

    if (loginStatus)
    {
        game(&player1, &player2, &gameMode);
    }

    CloseWindow();
    return 0;
}
