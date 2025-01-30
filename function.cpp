#include "kgh.h"

bool checkLogin(TextBox *username, TextBox *password, Button *login)
{
    if (username->getLength() != 0 && password->getLength() != 0)
    {
        return true;
    }
    else
    {
        username->setFocus(true);
        password->setFocus(false);
        login->setFocus(false);
        return false;
    }
}
bool loginMenu(Player *player)
{
    Text title("LOGIN MENU", PANTONE, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200);
    TextBox username(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, "USERNAME");
    TextBox password(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "PASSWORD", true);
    Button login(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, "Login");
    username.setFocus(true);
    password.setFocus(false);
    login.setFocus(false);

    bool loginStatus = false;

    Ball ball1;
    Ball ball2;

    while (!WindowShouldClose() && !loginStatus)
    {
        int key = GetCharPressed();
        while (key > 0)
        {
            username.addChar(key);
            password.addChar(key);
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            username.deleteChar();
            password.deleteChar();
        }

        if (IsKeyPressed(KEY_TAB))
        {
            if (username.getFocus())
            {
                username.setFocus(false);
                password.setFocus(true);
            }
            else if (password.getFocus())
            {
                password.setFocus(false);
                login.setFocus(true);
            }
            else if (login.getFocus())
            {
                login.setFocus(false);
                username.setFocus(true);
            }
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            if (username.getFocus())
            {
                username.toggleFocus();
                password.toggleFocus();
            }
            else
            {
                loginStatus = checkLogin(&username, &password, &login);
            }
        }

        Vector2 mousePoint = GetMousePosition();
        if (login.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            loginStatus = checkLogin(&username, &password, &login);
        }
        else if (username.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            username.setFocus(true);
            password.setFocus(false);
        }
        else if (password.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            username.setFocus(false);
            password.setFocus(true);
        }

        BeginDrawing();
        ClearBackground(ASH_GRAY);
        ball1.update();
        ball1.draw();
        ball2.update();
        ball2.draw();

        title.draw();
        username.draw();
        password.draw();
        login.draw();

        EndDrawing();
    }

    player->setName(username.getText());
    return loginStatus;
}

bool checkStart(CheckBox *multiPlayer, CheckBox *singlePlayer, CheckBox *regular, CheckBox *sin, CheckBox *curve)
{
    return (multiPlayer->getCheck() || singlePlayer->getCheck()) && (regular->getCheck() || sin->getCheck() || curve->getCheck());
}

bool mainMenu()
{
    Text title("MAIN MENU", PANTONE, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200);
    Text guide("Choose the game mode:", LAPIS_LAZULI, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100);
    Text ballPath("Choose the ball's path:", LAPIS_LAZULI, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100);

    CheckBox multiPlayer(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2, "MULTIPLAYER");
    CheckBox singlePlayer(SCREEN_WIDTH / 2 + 200, SCREEN_HEIGHT / 2, "SINGLEPLAYER");

    CheckBox regular(SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 + 200, "REGULAR");
    CheckBox sin(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200, "SIN");
    CheckBox curve(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 + 200, "CURVE");

    Button startGame(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300, "Start");

    bool start = false;

    while (!WindowShouldClose() && !start)
    {
        if (IsKeyPressed(KEY_TAB))
        {
            if (multiPlayer.getFocus())
            {
                multiPlayer.setFocus(false);
                singlePlayer.setFocus(true);
            }
            else if (singlePlayer.getFocus())
            {
                singlePlayer.setFocus(false);
                regular.setFocus(true);
            }
            else if (regular.getFocus())
            {
                regular.setFocus(false);
                sin.setFocus(true);
            }
            else if (sin.getFocus())
            {
                sin.setFocus(false);
                curve.setFocus(true);
            }
            else if (curve.getFocus())
            {
                curve.setFocus(false);
                startGame.setFocus(true);
            }
            else if (startGame.getFocus())
            {
                startGame.setFocus(false);
                multiPlayer.setFocus(true);
            }
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            if (multiPlayer.getFocus())
            {
                multiPlayer.toggleCheck();
                if (multiPlayer.getCheck())
                {
                    singlePlayer.setCheck(false);
                }
            }
            else if (singlePlayer.getFocus())
            {
                singlePlayer.toggleCheck();
                if (singlePlayer.getCheck())
                {
                    multiPlayer.setCheck(false);
                }
            }
            else if (regular.getFocus())
            {
                regular.toggleCheck();
                if (regular.getCheck())
                {
                    sin.setCheck(false);
                    curve.setCheck(false);
                }
            }
            else if (sin.getFocus())
            {
                sin.toggleCheck();
                if (sin.getCheck())
                {
                    regular.setCheck(false);
                    curve.setCheck(false);
                }
            }
            else if (curve.getFocus())
            {
                curve.toggleCheck();
                if (curve.getCheck())
                {
                    regular.setCheck(false);
                    sin.setCheck(false);
                }
            }
            else if (startGame.getFocus())
            {
                start = checkStart(&multiPlayer, &singlePlayer, &regular, &sin, &curve);
                if (!start)
                {
                    startGame.setFocus(false);
                    multiPlayer.setFocus(true);
                }
            }
        }

        Vector2 mousePoint = GetMousePosition();
        if (startGame.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            start = checkStart(&multiPlayer, &singlePlayer, &regular, &sin, &curve);
        }
        else if (multiPlayer.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            multiPlayer.setFocus(true);
            multiPlayer.setCheck(true);
            singlePlayer.setFocus(false);
            singlePlayer.setCheck(false);
            regular.setFocus(false);
            sin.setFocus(false);
            curve.setFocus(false);
        }
        else if (singlePlayer.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            multiPlayer.setFocus(false);
            multiPlayer.setCheck(false);
            singlePlayer.setFocus(true);
            singlePlayer.setCheck(true);
            regular.setFocus(false);
            sin.setFocus(false);
            curve.setFocus(false);
        }
        else if (regular.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            multiPlayer.setFocus(false);
            singlePlayer.setFocus(false);
            regular.setFocus(true);
            regular.setCheck(true);
            sin.setFocus(false);
            sin.setCheck(false);
            curve.setFocus(false);
            curve.setCheck(false);
        }
        else if (sin.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            multiPlayer.setFocus(false);
            singlePlayer.setFocus(false);
            regular.setFocus(false);
            regular.setCheck(false);
            sin.setFocus(true);
            sin.setCheck(true);
            curve.setFocus(false);
            curve.setCheck(false);
        }
        else if (curve.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            multiPlayer.setFocus(false);
            singlePlayer.setFocus(false);
            regular.setFocus(false);
            regular.setCheck(false);
            sin.setFocus(false);
            sin.setCheck(false);
            curve.setFocus(true);
            curve.setCheck(true);
        }

        BeginDrawing();
        ClearBackground(CAROLINA_BLUE);

        title.draw();
        guide.draw();
        ballPath.draw();
        multiPlayer.draw();
        singlePlayer.draw();
        regular.draw();
        sin.draw();
        curve.draw();
        startGame.draw();
        
        EndDrawing();
    }

    return singlePlayer.getCheck();
}