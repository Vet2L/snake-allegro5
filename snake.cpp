#include "snake.h"

Snake::Snake(int nx, int ny)
{
    //head
    this->head.setCoords(nx, ny);
    //body
    for (int i=0; i<5; i++)
    {
        this->body.push_back(SBody(nx, ny));
    }
    this->speed = 5; // 1 - ultra fast, 10 - slow
    this->score = 0;
}

void SBody::drawIt()
{
    al_draw_filled_rectangle(this->x - 5, this->y - 5, this->x + 5, this->y + 5, al_map_rgb(0, 255, 0));
}

void SHead::drawIt()
{
    al_draw_filled_rectangle(this->x - 5, this->y - 5, this->x + 5, this->y + 5, al_map_rgb(255, 0, 0));
}

void Snake::moveUp(bool d)
{
    if (d)
    {
        int lx, ly;
        lx = this->head.getX();
        ly = this->head.getY();
        int lx1, ly1;

        this->head.setCoords(lx, ly - 10);
        for (uint i=0; i<this->body.size(); i++)
        {
            lx1 = this->body[i].getX();
            ly1 = this->body[i].getY();
            this->body[i].setCoords(lx, ly);
            lx = lx1;
            ly = ly1;
        }
    }
}

void Snake::moveDown(bool d)
{
    if (d)
    {
        int lx, ly;
        lx = this->head.getX();
        ly = this->head.getY();
        int lx1, ly1;

        this->head.setCoords(lx, ly + 10);
        for (uint i=0; i<this->body.size(); i++)
        {
            lx1 = this->body[i].getX();
            ly1 = this->body[i].getY();
            this->body[i].setCoords(lx, ly);
            lx = lx1;
            ly = ly1;
        }
    }
}

void Snake::moveLeft(bool d)
{
    if (d)
    {
        int lx, ly;
        lx = this->head.getX();
        ly = this->head.getY();
        int lx1, ly1;

        this->head.setCoords(lx - 10, ly);
        for (uint i=0; i<this->body.size(); i++)
        {
            lx1 = this->body[i].getX();
            ly1 = this->body[i].getY();
            this->body[i].setCoords(lx, ly);
            lx = lx1;
            ly = ly1;
        }
    }
}

void Snake::moveRight(bool d)
{
    if (d)
    {
        int lx, ly;
        lx = this->head.getX();
        ly = this->head.getY();
        int lx1, ly1;

        this->head.setCoords(lx + 10, ly);
        for (uint i=0; i<this->body.size(); i++)
        {
            lx1 = this->body[i].getX();
            ly1 = this->body[i].getY();
            this->body[i].setCoords(lx, ly);
            lx = lx1;
            ly = ly1;
        }
    }
}

void Snake::draw()
{
    head.drawIt();
    for (uint i=0; i<body.size(); i++)
        body[i].drawIt();
}

void Snake::eatFood()
{
    this->body.push_back(SBody(body.at(0).getX(), body.at(0).getY()));
    this->score++;
}

SHead Snake::getSnakeHead()
{
    return this->head;
}

std::vector<SBody> Snake::getSnakeBody()
{
    return this->body;
}

uint Snake::getSpeed()
{
    return this->speed;
}

uint Snake::getScore()
{
    return this->score;
}


SFood::SFood(int nx, int ny)
{
    this->setCoords(nx, ny);
}

void SFood::drawIt()
{
    al_draw_filled_circle(this->x, this->y, 5, al_map_rgb(0, 0, 255));
}
