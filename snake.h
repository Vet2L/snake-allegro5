#ifndef SNAKE_H
#define SNAKE_H

#include <allegro5/allegro_primitives.h>
#include <vector>

class SBody
{
public:
    SBody() {x=0; y=0;}
    SBody(int nx, int ny){ x = nx; y = ny; }
    int getX(){ return x; }
    int getY(){ return y; }
    void setCoords(int nx, int ny){ x = nx; y = ny; }
    void drawIt();
protected:
    int x;
    int y;
};

class SHead : public SBody
{
public:
    SHead() {x=0; y=0;}
    SHead(int nx, int ny){ this->x = nx; this->y = ny; }
    void drawIt();
};

class Snake
{
public:
    Snake(int nx, int ny);
    void moveRight(bool d);
    void moveLeft(bool d);
    void moveUp(bool d);
    void moveDown(bool d);
    void draw();

    void eatFood();

    SHead getSnakeHead();
    std::vector<SBody> &getSnakeBody();
    uint getSpeed();
    uint getScore();

private:
    SHead head;
    std::vector<SBody> body;

    uint speed;
    uint score;
};

class SFood : public SBody
{
public:
    SFood(int nx, int ny);
    void drawIt();
};

#endif // SNAKE_H
