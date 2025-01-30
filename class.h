#include "raylib.h"
#include <string.h>
#include <stdio.h>

#define CHARCOAL {47, 72, 88, 255}
#define LAPIS_LAZULI {51, 101, 138, 255}
#define CAROLINA_BLUE {134, 187, 216, 255}
#define HUNYADI_YELLOW {246, 174, 45, 255}
#define PANTONE {242, 100, 25, 255}
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800
#define GAME_NAME "PONG"
#define FPS 60

class Paddle
{
protected:
    int positionX;
    int positionY;
    int velocityY;
    int accelerationY;
    int width;
    int height;
    int padding;
    Color color;

protected:
    Paddle(int posX, int posY);

    void limitCheck();

public:
    int getPositionX();

    int getPositionY();

    int getWidth();

    int getHeight();
};

class Player
{
private:
    char username[20];
    int score;

public:
    Player(char name[20]);

    void updateScore(int delta);

    int getScore();

    char *getName();

    void setName(char name[20]);
};

class Ball
{
private:
    int positionX;
    int positionY;
    int velocityX;
    int velocityY;
    int accelerationX;
    int accelerationY;
    float radius;
    Color color;

public:
    Ball();

    void draw();

    void update(Player &player1, Player &player2);

    int getPositionY();

    void collision(Paddle paddle);

    void reset();
};

class RightPaddle : public Paddle
{
public:
    RightPaddle(int posX, int posY);

    void draw();

    void update(Ball ball);
};

class LeftPaddle : public Paddle
{
public:
    LeftPaddle(int posX, int posY);

    void draw();

    void update();
};

