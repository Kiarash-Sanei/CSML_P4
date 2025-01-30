#include "class.h"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
    SetTargetFPS(FPS);

    char username[100] = "";
    char password[100] = "";
    int usernameLength = 0;
    int passwordLength = 0;
    bool isUsernameSelected = true;
    bool loginSuccessful = false;

    Rectangle usernameBox = {SCREEN_WIDTH / 2 - 100, 190, 200, 30};
    Rectangle passwordBox = {SCREEN_WIDTH / 2 - 100, 290, 200, 30};
    Rectangle loginButton = {SCREEN_WIDTH / 2 - 50, 390, 100, 30};

    while (!WindowShouldClose() && !loginSuccessful)
    {
        int key = GetCharPressed();
        while (key > 0)
        {
            if (isUsernameSelected && usernameLength < 99)
            {
                username[usernameLength] = (char)key;
                username[usernameLength + 1] = '\0';
                usernameLength++;
            }
            else if (!isUsernameSelected && passwordLength < 99)
            {
                password[passwordLength] = (char)key;
                password[passwordLength + 1] = '\0';
                passwordLength++;
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            if (isUsernameSelected && usernameLength > 0)
            {
                usernameLength--;
                username[usernameLength] = '\0';
            }
            else if (!isUsernameSelected && passwordLength > 0)
            {
                passwordLength--;
                password[passwordLength] = '\0';
            }
        }

        if (IsKeyPressed(KEY_TAB))
        {
            isUsernameSelected = !isUsernameSelected;
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            if (isUsernameSelected)
            {
                isUsernameSelected = false;
            }
            else if (!isUsernameSelected)
            {
                if (usernameLength != 0 && passwordLength != 0)
                {
                    loginSuccessful = true;
                }
                else
                {
                    isUsernameSelected = true;
                }
            }
        }
        

        Vector2 mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(mousePoint, loginButton))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (usernameLength != 0 && passwordLength != 0)
                {
                    loginSuccessful = true;
                }
                else
                {
                    isUsernameSelected = true;
                }
            }
        }
        else if (CheckCollisionPointRec(mousePoint, usernameBox))
        {
            isUsernameSelected = true;
        }
        else if (CheckCollisionPointRec(mousePoint, passwordBox))
        {
            isUsernameSelected = false;
        }


        BeginDrawing();
        ClearBackground(CAROLINA_BLUE);

        DrawText("LOGIN", SCREEN_WIDTH / 2 - MeasureText("LOGIN", 30) / 2, 100, 30, PANTONE);
        DrawText("Username", SCREEN_WIDTH / 2 - MeasureText("Username", 20), 170, 20, LAPIS_LAZULI);
        DrawText("Password", SCREEN_WIDTH / 2 - MeasureText("Password", 20), 270, 20, LAPIS_LAZULI);

        DrawRectangleRec(usernameBox, WHITE);
        DrawRectangleRec(passwordBox, WHITE);
        DrawRectangleLines(usernameBox.x, usernameBox.y, usernameBox.width, usernameBox.height,
                           isUsernameSelected ? ORANGE : BLUE);
        DrawRectangleLines(passwordBox.x, passwordBox.y, passwordBox.width, passwordBox.height,
                           isUsernameSelected ? BLUE : ORANGE);

        DrawRectangleRec(loginButton, BLUE);
        DrawRectangleLines(loginButton.x, loginButton.y, loginButton.width, loginButton.height, LAPIS_LAZULI);
        DrawText("Login",
                 loginButton.x + (loginButton.width - MeasureText("Login", 20)) / 2,
                 loginButton.y + 5, 20, LAPIS_LAZULI);

        DrawText(username, usernameBox.x + 5, usernameBox.y + 5, 20, LAPIS_LAZULI);
        char hiddenPassword[100] = "";
        for (int i = 0; i < passwordLength; i++)
            hiddenPassword[i] = '*';
        hiddenPassword[passwordLength] = '\0';
        DrawText(hiddenPassword, passwordBox.x + 5, passwordBox.y + 5, 20, LAPIS_LAZULI);

        EndDrawing();
    }

    CloseWindow();

    if (loginSuccessful)
    {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
        SetTargetFPS(FPS);

        Ball ball;
        LeftPaddle leftPaddle(0, SCREEN_HEIGHT / 2);
        RightPaddle rightPaddle(SCREEN_WIDTH, SCREEN_HEIGHT / 2);
        Player player1(username);
        Player player2("Player 2");

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
    }

    return 0;
}
