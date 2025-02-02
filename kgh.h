#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

#define CHARCOAL {47, 72, 88, 255}
#define LAPIS_LAZULI {51, 101, 138, 255}
#define CAROLINA_BLUE {134, 187, 216, 255}
#define HUNYADI_YELLOW {246, 174, 45, 255}
#define PANTONE {242, 100, 25, 255}
#define PALE_AZURE {99, 210, 255, 255}
#define STEEL_BLUE {32, 129, 195, 255}
#define TIFFANY_BLUE {120, 213, 215, 255}
#define ASH_GRAY {190, 216, 212, 255}
#define SEASALT {247, 249, 249, 255}

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800
#define GAME_NAME "PONG"
#define FPS 60

typedef struct GameMode
{
    int numberOfPlayer;
    int path;
    int difficulty;
    int program;
} GameMode;

class Shape
{
protected:
    int positionX;
    int positionY;
    Shape(int posX, int posY);

public:
    int getX();
    int getY();
};

class RectangularShape : public Shape
{
protected:
    int width;
    int height;
    RectangularShape(int posX, int posY, int wid, int hei);

public:
    int getWidth();
    int getHeight();
    bool checkCollision(Vector2 mousePoint);
};

class Paddle : public RectangularShape
{
protected:
    int velocityY;
    int accelerationY;
    int padding;
    Color color;

    Paddle(int posX, int posY);
    void limitCheck();
};

class Player
{
private:
    char username[20];
    int score;

public:
    Player(const char *name);
    void updateScore(int delta);
    int getScore();
    char *getName();
    void setName(char name[20]);
};

class Ball : public Shape
{
private:
    int velocityX;
    int velocityY;
    int accelerationX;
    int accelerationY;
    float radius;
    Color color;
    GameMode gameMode;

public:
    Ball(GameMode gM);
    Ball();
    void draw();
    void update(Player *player1, Player *player2, double time);
    void update();
    void collision(Paddle paddle);
    void reset();
};

class RightPaddle : public Paddle
{
private:
    bool isAI;

public:
    RightPaddle(int posX, int posY, bool AI);
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

class Clickable
{
protected:
    bool isFocus;
    Color focus;
    Color normal;
    Clickable(Color foc, Color nor);

public:
    void toggleFocus();
    void setFocus(bool status);
    bool getFocus();
};

class TextBox : public RectangularShape, public Clickable
{
private:
    char title[20];
    int length;
    char text[100];
    Color fill;
    Color textColor;
    bool isPassword;

public:
    TextBox(int posX, int posY, const char *titleName, bool passwordStatus = false);
    void addChar(int key);
    void deleteChar();
    char *getText();
    int getLength();
    void draw();
};

class Button : public RectangularShape, public Clickable
{
private:
    char title[20];
    Color fill;
    Color textColor;

public:
    Button(int posX, int posY, const char *titleName);
    void draw();
};

class Text : public Shape
{
private:
    char text[100];
    Color color;

public:
    Text(const char *txt, Color col, int posX, int posY);
    void draw();
    void updateText(char *txt);
};

class CheckBox : public RectangularShape, public Clickable
{
private:
    char title[20];
    Color unChecked;
    Color checked;
    Color textColor;
    bool isChecked;

public:
    CheckBox(int posX, int posY, const char *titleName);
    void draw();
    void toggleCheck();
    void setCheck(bool status);
    bool getCheck();
};

bool checkLogin(TextBox *username, TextBox *password, Button *login);
bool loginMenu(Player *player);
bool mainMenu(GameMode *gameMode);
bool game(Player *player1, Player *player2, GameMode *gameMode);
float regularPath(int velocity);
float sinPath(int velocity, double time);
float curvePath(int positionX, int positionY);
