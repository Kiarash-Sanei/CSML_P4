#include "kgh.h"

Shape::Shape(int posX, int posY) : positionX(posX), positionY(posY) {}

int Shape::getX()
{
    return positionX;
}

int Shape::getY()
{
    return positionY;
}

RectangularShape::RectangularShape(int posX, int posY, int wid, int hei) : Shape(posX, posY), width(wid), height(hei) {}

int RectangularShape::getWidth()
{
    return width;
}

int RectangularShape::getHeight()
{
    return height;
}

bool RectangularShape::checkCollision(Vector2 mousePoint)
{
    return CheckCollisionPointRec(mousePoint, Rectangle{(float)positionX, (float)positionY, (float)width, (float)height});
}

Ball::Ball(GameMode gM, double *cT)
    : Shape(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), gameMode(gM), calculationTime(cT)
{
    choose();
    round = 0;
    radius = 10;
    color1 = NEON_GREEN;
    color2 = TERMINAL_GREEN;
    color3 = LIGHT_GREEN;
    reset();
}

Ball::Ball(double *cT)
    : Shape(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), velocityX(300), velocityY(300), accelerationX(0), accelerationY(0), calculationTime(cT)
{
    int random = GetRandomValue(1, 3);
    gameMode.path = (random == 1 ? Path::Regular : random == 2 ? Path::Sin
                                                               : Path::Curve);
    gameMode.difficulty = Difficulty::Easy;
    round = 0;
    radius = 10;
    color1 = NEON_GREEN;
    color2 = TERMINAL_GREEN;
    color3 = LIGHT_GREEN;
    reset();
}

void Ball::draw()
{
    float rotationAngle = round * 0.1f;

    double temporaryTime = time(NULL);

    for (int i = 0; i < 6; i++)
    {
        float segment;
        float startAngle;
        float endAngle;
        float endX;
        float endY;

        if (gameMode.program == Program::Cpp)
        {
            segment = i * PI / 3;
            startAngle = rotationAngle + segment;
            endAngle = rotationAngle + segment + PI / 3;
            endX = (float)positionX + radius * cos(startAngle);
            endY = (float)positionY + radius * sin(startAngle);
        }
        else
        {
            segment = SE(i);
            startAngle = SA(rotationAngle, segment);
            endAngle = EA(rotationAngle, segment);
            endX = EX(positionX, radius, startAngle);
            endY = EY(positionY, radius, startAngle);
        }

        Vector2 start = {(float)positionX, (float)positionY};
        Vector2 end = {endX, endY};

        DrawCircleSector(
            Vector2{(float)positionX, (float)positionY},
            radius,
            startAngle * RAD2DEG,
            endAngle * RAD2DEG,
            32,
            (i % 2 == 0 ? color1 : color2));
        DrawLineEx(start, end, 1.0f, color3);
    }

    *calculationTime += time(NULL) - temporaryTime;
}

void Ball::update(Player *player1, Player *player2)
{
    path();

    if (positionX - radius <= 0)
    {
        player2->updateScore(1);
        reset();
    }
    else if (positionX + radius >= SCREEN_WIDTH)
    {
        player1->updateScore(1);
        reset();
    }
    if (positionY - radius <= 0)
    {
        positionY = radius;
        velocityY *= -1;
    }
    else if (positionY + radius >= SCREEN_HEIGHT)
    {
        positionY = SCREEN_HEIGHT - radius;
        velocityY *= -1;
    }

    if (conrner())
    {
        reset();
        choose();
    }
}

void Ball::update()
{
    path();

    if (positionX - radius <= 0)
    {
        positionX = radius;
        velocityX *= -1;
    }
    else if (positionX + radius >= SCREEN_WIDTH)
    {
        positionX = SCREEN_WIDTH - radius;
        velocityX *= -1;
    }
    if (positionY - radius <= 0)
    {
        positionY = radius;
        velocityY *= -1;
    }
    else if (positionY + radius >= SCREEN_HEIGHT)
    {
        positionY = SCREEN_HEIGHT - radius;
        velocityY *= -1;
    }

    if (conrner())
    {
        reset();
        choose();
    }
}

void Ball::path()
{
    double temporaryTime = time(NULL);
    velocityX += accelerationX / FPS;
    velocityY += accelerationY / FPS;

    float deltaX;
    float deltaY;

    switch (gameMode.path)
    {
    case Path::Regular:
        deltaX = regularPath(velocityX, &gameMode);
        deltaY = regularPath(velocityY, &gameMode);
        break;

    case Path::Sin:
        deltaX = regularPath(velocityX, &gameMode);
        deltaY = sinPath(velocityY, round, &gameMode);
        break;

    case Path::Curve:
        accelerationY += curvePath(positionX, positionY, &gameMode);
        deltaX = regularPath(velocityX, &gameMode);
        deltaY = regularPath(velocityY, &gameMode);
        break;

    default:
        break;
    }

    positionX += deltaX;
    positionY += deltaY;
    round++;

    *calculationTime += time(NULL) - temporaryTime;
}

void Ball::collision(Paddle paddle)
{
    if (CheckCollisionCircleRec(Vector2{(float)positionX, (float)positionY},
                                radius,
                                Rectangle{(float)paddle.getX(), (float)paddle.getY(), (float)paddle.getWidth(), (float)paddle.getHeight()}))
    {
        velocityX *= -1;
    }
}

void Ball::reset()
{
    positionX = SCREEN_WIDTH / 2;
    positionY = SCREEN_HEIGHT / 2;
}

void Ball::choose()
{
    switch (gameMode.difficulty)
    {
    case Difficulty::Easy:
        velocityX = 300;
        velocityY = 300;
        accelerationX = 20;
        accelerationY = 20;
        break;
    case Difficulty::Meduim:
        velocityX = 350;
        velocityY = 350;
        accelerationX = 30;
        accelerationY = 30;
        break;
    case Difficulty::Hard:
        velocityX = 400;
        velocityY = 400;
        accelerationX = 40;
        accelerationY = 40;
        break;
    default:
        break;
    }

    int random[2] = {-1, 1};
    velocityX *= random[GetRandomValue(0, 1)];
    velocityY *= random[GetRandomValue(0, 1)];
}

bool Ball::conrner()
{
    return (positionX - radius <= 0 || positionX + radius >= SCREEN_WIDTH) &&
           (positionY - radius <= 0 || positionY + radius >= SCREEN_HEIGHT);
}

Paddle::Paddle(int posX, int posY)
    : RectangularShape(posX, posY - 50, 20, 100), velocityY(5), accelerationY(0)
{
    padding = 5;
    color = NEON_GREEN;
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

RightPaddle::RightPaddle(int posX, int posY, bool AI)
    : Paddle(posX, posY), isAI(AI)
{
    positionX -= padding;
    positionX -= width;
}

void RightPaddle::draw()
{
    DrawRectangleRounded(Rectangle{(float)positionX, (float)positionY, (float)width, (float)height}, 0.8, 0, color);
}

void RightPaddle::update(Ball ball)
{
    if (isAI && ball.getX() > SCREEN_WIDTH / 2)
    {
        if (positionY + height / 2 > ball.getY())
        {
            positionY -= velocityY;
        }
        else if (positionY + height / 2 < ball.getY())
        {
            positionY += velocityY;
        }
    }
    else
    {
        if (IsKeyDown(KEY_UP))
        {
            positionY -= velocityY;
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            positionY += velocityY;
        }
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
    DrawRectangleRounded(Rectangle{(float)positionX, (float)positionY, (float)width, (float)height}, 0.8, 0, color);
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

Player::Player(const char *name) : score(0)
{
    strncpy(username, name, sizeof(username) - 1);
    username[sizeof(username) - 1] = '\0';
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

Clickable::Clickable(Color foc, Color nor) : isFocus(false), focus(foc), normal(nor) {}

void Clickable::toggleFocus()
{
    isFocus = !isFocus;
}

void Clickable::setFocus(bool status)
{
    isFocus = status;
}

bool Clickable::getFocus()
{
    return isFocus;
}

TextBox::TextBox(int posX, int posY, const char *titleName, bool passwordStatus)
    : RectangularShape(posX, posY, 200, 30),
      Clickable(TERMINAL_GREEN, DARK_GREEN),
      fill(MATRIX_BLACK), textColor(NEON_GREEN), length(0), isPassword(passwordStatus)
{
    strcpy(title, titleName);
    text[0] = '\0';
}

void TextBox::addChar(int key)
{
    if (isFocus && length < 99)
    {
        text[length] = (char)key;
        length++;
        text[length] = '\0';
    }
}

void TextBox::deleteChar()
{
    if (isFocus && length > 0)
    {
        length--;
        text[length] = '\0';
    }
}

char *TextBox::getText()
{
    char *textCopy = (char *)malloc(100 * sizeof(char));
    strcpy(textCopy, text);
    return textCopy;
}

int TextBox::getLength()
{
    return length;
}

void TextBox::draw()
{
    DrawText(title, positionX - MeasureText(title, 20) / 2, positionY - 25, 20, textColor);
    DrawRectangleRec(Rectangle{(float)positionX - width / 2, (float)positionY, (float)width, (float)height}, fill);
    DrawRectangleLines(positionX - width / 2, positionY, width, height, isFocus ? focus : normal);
    if (isPassword)
    {
        char hiddenPassword[100] = "";
        for (int i = 0; i < length; i++)
            hiddenPassword[i] = '*';
        hiddenPassword[length] = '\0';
        DrawText(hiddenPassword, positionX - MeasureText(hiddenPassword, 20) / 2, positionY + 5, 20, textColor);
    }
    else
    {
        DrawText(text, positionX - MeasureText(text, 20) / 2, positionY + 5, 20, textColor);
    }
}

Button::Button(int posX, int posY, const char *titleName)
    : RectangularShape(posX, posY, 100, 30),
      Clickable(TERMINAL_GREEN, DARK_GREEN),
      fill(DARK_GREEN), textColor(NEON_GREEN)
{
    strcpy(title, titleName);
}

void Button::draw()
{
    DrawRectangleRec(Rectangle{(float)positionX - width / 2, (float)positionY, (float)width, (float)height}, fill);
    DrawRectangleLines(positionX - width / 2, positionY, width, height, isFocus ? focus : normal);
    DrawText(title, positionX - MeasureText(title, 20) / 2, positionY + 5, 20, textColor);
}

Text::Text(const char *txt, Color col, int posX, int posY) : Shape(posX, posY), color(col)
{
    strncpy(text, txt, sizeof(text) - 1);
    text[sizeof(text) - 1] = '\0';
}

void Text::draw()
{
    DrawText(text, positionX - MeasureText(text, 20) / 2, positionY, 20, color);
}

void Text::updateText(char *txt)
{
    strncpy(text, txt, sizeof(text) - 1);
    text[sizeof(text) - 1] = '\0';
}

CheckBox::CheckBox(int posX, int posY, const char *titleName)
    : RectangularShape(posX, posY, 30, 30),
      Clickable(TERMINAL_GREEN, DARK_GREEN),
      unChecked(DARK_GREEN),
      checked(NEON_GREEN),
      textColor(NEON_GREEN),
      isChecked(false)
{
    strcpy(title, titleName);
}

void CheckBox::draw()
{
    DrawRectangleRec(Rectangle{(float)positionX - width / 2, (float)positionY, (float)width, (float)height}, isChecked ? checked : unChecked);
    DrawRectangleLines(positionX - width / 2, positionY, width, height, isFocus ? focus : normal);
    DrawText(title, positionX + width + 5, positionY + 5, 20, textColor);
}

void CheckBox::toggleCheck()
{
    isChecked = !isChecked;
}

void CheckBox::setCheck(bool status)
{
    isChecked = status;
}

bool CheckBox::getCheck()
{
    return isChecked;
}