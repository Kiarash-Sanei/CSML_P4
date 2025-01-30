#include "kgh.h"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
    SetTargetFPS(FPS);

    Player player1("");
    bool loginStatus = loginMenu(&player1);
    bool start;
    if (loginStatus)
    {
        start = mainMenu();
    }

    Player player2("AI");
    if (!start)
    {
        loginStatus = loginMenu(&player2);
    }

    Ball ball;
    LeftPaddle leftPaddle(0, SCREEN_HEIGHT / 2);
    RightPaddle rightPaddle(SCREEN_WIDTH, SCREEN_HEIGHT / 2);

    while (!WindowShouldClose())
    {
        ball.update(player1, player2);
        leftPaddle.update();
        rightPaddle.update(ball);
        ball.collision(leftPaddle);
        ball.collision(rightPaddle);

        BeginDrawing();
        ClearBackground(CAROLINA_BLUE);
        DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, PANTONE);
        ball.draw();
        leftPaddle.draw();
        rightPaddle.draw();
        DrawText(player1.getName(), 10, 10, 20, LAPIS_LAZULI);
        DrawText(player2.getName(), SCREEN_WIDTH - 100, 10, 20, LAPIS_LAZULI);
        DrawText(TextFormat("%i", player1.getScore()), 10, 40, 20, LAPIS_LAZULI);
        DrawText(TextFormat("%i", player2.getScore()), SCREEN_WIDTH - 100, 40, 20, LAPIS_LAZULI);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
