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

bool checkMainMenuSelections(CheckBox *singlePlayer, CheckBox *multiPlayer,
                             CheckBox *regular, CheckBox *sin, CheckBox *curve,
                             CheckBox *easy, CheckBox *medium, CheckBox *hard,
                             CheckBox *cpp, CheckBox *assembly)
{
    bool hasGameMode = singlePlayer->getCheck() || multiPlayer->getCheck();
    bool hasPath = regular->getCheck() || sin->getCheck() || curve->getCheck();
    bool hasDifficulty = easy->getCheck() || medium->getCheck() || hard->getCheck();
    bool hasLanguage = cpp->getCheck() || assembly->getCheck();
    return hasGameMode && hasPath && hasDifficulty && hasLanguage;
}

bool mainMenu(GameMode *gameMode)
{
    Text title("MAIN MENU", PANTONE, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 375);
    Text guide("Choose the game mode:", LAPIS_LAZULI, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 325);
    Text ballPath("Choose the ball's path:", LAPIS_LAZULI, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 175);
    Text difficulty("Choose game's difficulty:", LAPIS_LAZULI, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 25);
    Text hotPart("Choose the language used in hot patrs:", LAPIS_LAZULI, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 125);

    CheckBox singlePlayer(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 250, "SINGLEPLAYER");
    CheckBox multiPlayer(SCREEN_WIDTH / 2 + 200, SCREEN_HEIGHT / 2 - 250, "MULTIPLAYER");
    singlePlayer.setCheck(true);
    singlePlayer.setFocus(true);

    CheckBox regular(SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 - 100, "REGULAR");
    CheckBox sin(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, "SIN");
    CheckBox curve(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 100, "CURVE");
    regular.setCheck(true);

    CheckBox easy(SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 + 50, "EASY");
    CheckBox medium(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, "MEDIUM");
    CheckBox hard(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 + 50, "HARD");
    easy.setCheck(true);

    CheckBox cpp(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 + 200, "C++");
    CheckBox assembly(SCREEN_WIDTH / 2 + 200, SCREEN_HEIGHT / 2 + 200, "ASSEMBLY");
    cpp.setCheck(true);

    Button startGame(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 275, "Start");

    bool start = false;

    while (!WindowShouldClose() && !start)
    {
        if (IsKeyPressed(KEY_TAB))
        {
            if (singlePlayer.getFocus())
            {
                singlePlayer.setFocus(false);
                multiPlayer.setFocus(true);
            }
            else if (multiPlayer.getFocus())
            {
                multiPlayer.setFocus(false);
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
                easy.setFocus(true);
            }
            else if (easy.getFocus())
            {
                easy.setFocus(false);
                medium.setFocus(true);
            }
            else if (medium.getFocus())
            {
                medium.setFocus(false);
                hard.setFocus(true);
            }
            else if (hard.getFocus())
            {
                hard.setFocus(false);
                cpp.setFocus(true);
            }
            else if (cpp.getFocus())
            {
                cpp.setFocus(false);
                assembly.setFocus(true);
            }
            else if (assembly.getFocus())
            {
                assembly.setFocus(false);
                startGame.setFocus(true);
            }
            else if (startGame.getFocus())
            {
                startGame.setFocus(false);
                singlePlayer.setFocus(true);
            }
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            if (singlePlayer.getFocus())
            {
                singlePlayer.toggleCheck();
                if (singlePlayer.getCheck())
                {
                    multiPlayer.setCheck(false);
                }
            }
            else if (multiPlayer.getFocus())
            {
                multiPlayer.toggleCheck();
                if (multiPlayer.getCheck())
                {
                    singlePlayer.setCheck(false);
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
            else if (easy.getFocus())
            {
                easy.toggleCheck();
                if (easy.getCheck())
                {
                    medium.setCheck(false);
                    hard.setCheck(false);
                }
            }
            else if (medium.getFocus())
            {
                medium.toggleCheck();
                if (medium.getCheck())
                {
                    easy.setCheck(false);
                    hard.setCheck(false);
                }
            }
            else if (hard.getFocus())
            {
                hard.toggleCheck();
                if (hard.getCheck())
                {
                    easy.setCheck(false);
                    medium.setCheck(false);
                }
            }
            else if (cpp.getFocus())
            {
                cpp.toggleCheck();
                if (cpp.getCheck())
                {
                    assembly.setCheck(false);
                }
            }
            else if (assembly.getFocus())
            {
                assembly.toggleCheck();
                if (assembly.getCheck())
                {
                    cpp.setCheck(false);
                }
            }
            else if (startGame.getFocus())
            {
                start = checkMainMenuSelections(&singlePlayer, &multiPlayer,
                                                &regular, &sin, &curve,
                                                &easy, &medium, &hard,
                                                &cpp, &assembly);
            }
        }

        Vector2 mousePoint = GetMousePosition();
        if (startGame.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            start = checkMainMenuSelections(&singlePlayer, &multiPlayer,
                                            &regular, &sin, &curve,
                                            &easy, &medium, &hard,
                                            &cpp, &assembly);
        }
        else if (singlePlayer.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            singlePlayer.setFocus(true);
            singlePlayer.setCheck(true);
            multiPlayer.setFocus(false);
            multiPlayer.setCheck(false);
            regular.setFocus(false);
            sin.setFocus(false);
            curve.setFocus(false);
            easy.setFocus(false);
            medium.setFocus(false);
            hard.setFocus(false);
        }
        else if (multiPlayer.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            singlePlayer.setFocus(false);
            singlePlayer.setCheck(false);
            multiPlayer.setFocus(true);
            multiPlayer.setCheck(true);
            regular.setFocus(false);
            sin.setFocus(false);
            curve.setFocus(false);
            easy.setFocus(false);
            medium.setFocus(false);
            hard.setFocus(false);
        }
        else if (regular.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            singlePlayer.setFocus(false);
            multiPlayer.setFocus(false);
            regular.setFocus(true);
            regular.setCheck(true);
            sin.setFocus(false);
            sin.setCheck(false);
            curve.setFocus(false);
            curve.setCheck(false);
            easy.setFocus(false);
            medium.setFocus(false);
            hard.setFocus(false);
        }
        else if (sin.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            singlePlayer.setFocus(false);
            multiPlayer.setFocus(false);
            regular.setFocus(false);
            regular.setCheck(false);
            sin.setFocus(true);
            sin.setCheck(true);
            curve.setFocus(false);
            curve.setCheck(false);
            easy.setFocus(false);
            medium.setFocus(false);
            hard.setFocus(false);
        }
        else if (curve.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            singlePlayer.setFocus(false);
            multiPlayer.setFocus(false);
            regular.setFocus(false);
            regular.setCheck(false);
            sin.setFocus(false);
            sin.setCheck(false);
            curve.setFocus(true);
            curve.setCheck(true);
            easy.setFocus(false);
            medium.setFocus(false);
            hard.setFocus(false);
        }
        else if (easy.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            singlePlayer.setFocus(false);
            multiPlayer.setFocus(false);
            regular.setFocus(false);
            sin.setFocus(false);
            curve.setFocus(false);
            easy.setFocus(true);
            easy.setCheck(true);
            medium.setFocus(false);
            medium.setCheck(false);
            hard.setFocus(false);
            hard.setCheck(false);
        }
        else if (medium.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            singlePlayer.setFocus(false);
            multiPlayer.setFocus(false);
            regular.setFocus(false);
            sin.setFocus(false);
            curve.setFocus(false);
            easy.setFocus(false);
            easy.setCheck(false);
            medium.setFocus(true);
            medium.setCheck(true);
            hard.setFocus(false);
            hard.setCheck(false);
        }
        else if (hard.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            singlePlayer.setFocus(false);
            multiPlayer.setFocus(false);
            regular.setFocus(false);
            sin.setFocus(false);
            curve.setFocus(false);
            easy.setFocus(false);
            easy.setCheck(false);
            medium.setFocus(false);
            medium.setCheck(false);
            hard.setFocus(true);
            hard.setCheck(true);
        }
        else if (cpp.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            singlePlayer.setFocus(false);
            multiPlayer.setFocus(false);
            regular.setFocus(false);
            sin.setFocus(false);
            curve.setFocus(false);
            easy.setFocus(false);
            medium.setFocus(false);
            hard.setFocus(false);
            cpp.setFocus(true);
            cpp.setCheck(true);
            assembly.setFocus(false);
            assembly.setCheck(false);
        }
        else if (assembly.checkCollision(mousePoint) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            singlePlayer.setFocus(false);
            multiPlayer.setFocus(false);
            regular.setFocus(false);
            sin.setFocus(false);
            curve.setFocus(false);
            easy.setFocus(false);
            medium.setFocus(false);
            hard.setFocus(false);
            cpp.setFocus(false);
            cpp.setCheck(false);
            assembly.setFocus(true);
            assembly.setCheck(true);
        }

        BeginDrawing();
        ClearBackground(CAROLINA_BLUE);

        title.draw();
        guide.draw();
        ballPath.draw();
        difficulty.draw();
        hotPart.draw();
        singlePlayer.draw();
        multiPlayer.draw();
        regular.draw();
        sin.draw();
        curve.draw();
        easy.draw();
        medium.draw();
        hard.draw();
        cpp.draw();
        assembly.draw();
        startGame.draw();

        EndDrawing();
    }

    if (multiPlayer.getCheck())
    {
        gameMode->numberOfPlayer = 2;
    }

    if (sin.getCheck())
    {
        gameMode->path = Path::Sin;
    }
    else if (curve.getCheck())
    {
        gameMode->path = Path::Curve;
    }

    if (medium.getCheck())
    {
        gameMode->difficulty = Difficulty::Meduim;
    }
    else
    {
        gameMode->difficulty = Difficulty::Hard;
    }

    if (assembly.getCheck())
    {
        gameMode->program = Program::Assembly;
    }

    return singlePlayer.getCheck();
}

bool game(Player *player1, Player *player2, GameMode *gameMode)
{
    Ball ball(*gameMode);
    LeftPaddle leftPaddle(0, SCREEN_HEIGHT / 2);
    RightPaddle rightPaddle(SCREEN_WIDTH, SCREEN_HEIGHT / 2, gameMode->numberOfPlayer == 1);

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
        DrawText(player1->getName(), 10, 10, 20, LAPIS_LAZULI);
        DrawText(player2->getName(), SCREEN_WIDTH - 100, 10, 20, LAPIS_LAZULI);
        DrawText(TextFormat("%i", player1->getScore()), 10, 40, 20, LAPIS_LAZULI);
        DrawText(TextFormat("%i", player2->getScore()), SCREEN_WIDTH - 100, 40, 20, LAPIS_LAZULI);
        EndDrawing();
    }

    return true;
}

float regularPath(int velocity, GameMode *gameMode)
{
    if (gameMode->program == Program::Cpp)
    {
        return velocity / (float)FPS;
    }
    else
    {
        return R(velocity);
    }
}

float sinPath(int velocity, double time, GameMode *gameMode)
{
    const float frequency = 0.05f;
    float baseMovement = velocity / FPS;
    float sineComponent = sin(frequency * time);
    return baseMovement * sineComponent;
}

float curvePath(int positionX, int positionY, GameMode *gameMode)
{
    const float constant = 1000;
    positionX -= SCREEN_WIDTH / 2;
    positionY -= SCREEN_HEIGHT / 2;
    float norm = positionX * positionX + positionY * positionY;
    if (norm < 25)
    {
        return 0;
    }
    else
    {
        return constant * positionY / norm;
    }
}