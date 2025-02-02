#include "kgh.h"

double executionTime = 0;
double calculationTime = 0;

int main()
{
    double temporaryTime = time(NULL);

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
    loginStatus = loginMenu(&player1, &calculationTime);
    if (loginStatus)
    {
        start = mainMenu(&gameMode);

        if (!start && gameMode.numberOfPlayer == 2)
        {
            loginStatus = loginMenu(&player2, &calculationTime);
        }
    }

    if (loginStatus)
    {
        game(&player1, &player2, &gameMode, &calculationTime);
    }

    CloseWindow();

    double executionTime = time(NULL) - temporaryTime;

    FILE *logFile = fopen("log.txt", "a");
    fprintf(logFile, "Execution time is %.0f seconds.\nCalculation time while using %s is %.9f nano seconds.\n", executionTime, (gameMode.program == Program::Assembly ? "ASSEMBLY" : "C++"), calculationTime * 1000000000);
    fclose(logFile);

    return 0;
}
