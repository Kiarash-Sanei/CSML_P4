#include "class.h"

Ball::Ball()
    : positionX(SCREEN_WIDTH / 2), positionY(SCREEN_HEIGHT / 2), velocityX(300), velocityY(300), accelerationX(0), accelerationY(0)
{
    radius = 10;
    color = CHARCOAL;
}

void Ball::draw()
{
    DrawCircle(positionX, positionY, radius, color);
}

void Ball::update(Player &player1, Player &player2)
{
    velocityX += accelerationX / FPS;
    velocityY += accelerationY / FPS;
    positionX += velocityX / FPS;
    positionY += velocityY / FPS;

    if (positionX - radius < 0)
    {
        player2.updateScore(1);
        reset();
    }
    else if (positionX + radius > SCREEN_WIDTH)
    {
        player1.updateScore(1);
        reset();
    }
    if (positionY - radius < 0)
    {
        positionY = radius;
        velocityY *= -1;
    }
    else if (positionY + radius > SCREEN_HEIGHT)
    {
        positionY = SCREEN_HEIGHT - radius;
        velocityY *= -1;
    }
}

int Ball::getPositionY()
{
    return positionY;
}

void Ball::collision(Paddle paddle)
{
    if (CheckCollisionCircleRec(Vector2{(float)positionX, (float)positionY},
                                radius,
                                Rectangle{(float)paddle.getPositionX(), (float)paddle.getPositionY(), (float)paddle.getWidth(), (float)paddle.getHeight()}))
    {
        velocityX *= -1;
    }
}

void Ball::reset()
{
    int random[2] = {-1, 1};

    positionX = SCREEN_WIDTH / 2;
    positionY = SCREEN_HEIGHT / 2;
    velocityX *= random[GetRandomValue(0, 1)];
}

Paddle::Paddle(int posX, int posY)
    : positionX(posX), positionY(posY - 50), velocityY(5), accelerationY(0)
{
    width = 20;
    height = 100;
    padding = 5;
    color = HUNYADI_YELLOW;
}

void Paddle::limitCheck()
{
    if (positionY < padding)
    {
        positionY = padding;
    }
    else if (positionY + height > SCREEN_HEIGHT - padding)
    {
        positionY = SCREEN_HEIGHT - height - padding;
    }
}

int Paddle::getPositionX()
{
    return positionX;
}

int Paddle::getPositionY()
{
    return positionY;
}

int Paddle::getWidth()
{
    return width;
}

int Paddle::getHeight()
{
    return height;
}

RightPaddle::RightPaddle(int posX, int posY)
    : Paddle(posX, posY)
{
    positionX -= padding;
    positionX -= width;
}

void RightPaddle::draw()
{
    DrawRectangle(positionX, positionY, width, height, color);
}

void RightPaddle::update(Ball ball)
{
    if (positionY + height / 2 > ball.getPositionY())
    {
        positionY -= velocityY;
    }
    else if (positionY + height / 2 < ball.getPositionY())
    {
        positionY += velocityY;
    }
    limitCheck();
}

LeftPaddle::LeftPaddle(int posX, int posY)
    : Paddle(posX, posY)
{
    positionX += padding;
}

void LeftPaddle::draw()
{
    DrawRectangle(positionX, positionY, width, height, color);
}

void LeftPaddle::update()
{
    if (IsKeyDown(KEY_W))
    {
        positionY -= velocityY;
    }
    else if (IsKeyDown(KEY_S))
    {
        positionY += velocityY;
    }
    limitCheck();
}

Player::Player(char name[20]) : score(0)
{
    strcpy(username, name);
}

void Player::updateScore(int delta)
{
    score += delta;
}

int Player::getScore()
{
    return score;
}

char *Player::getName()
{
    return username;
}

void Player::setName(char name[20])
{
    strcpy(username, name);
}