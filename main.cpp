#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
//#include <allegro5/allegro_primitives.h>				//Our primitive header file
#include "snake.h"

enum KEYS{ UP, DOWN, LEFT, RIGHT};

const int width = 500;
const int height = 500;
const int speed = 60;

Snake *snake;
SFood *food;
bool keys[4] = {false, false, false, false};
bool at_start = true;
bool lock_move = false;

ALLEGRO_FONT *font;

void restart()
{
    delete snake;
    keys[UP] = false;
    keys[DOWN] = false;
    keys[LEFT] = false;
    keys[RIGHT] = false;
    at_start = true;
    lock_move = false;
    int fx, fy;
    fx = (rand()%48)*10 + 10;
    fy = (rand()%48)*10 + 10;
    while ((fx == snake->getSnakeHead().getX())&&(fy == snake->getSnakeHead().getY()))
    {
        fx = (rand()%48)*10 + 10;
        fy = (rand()%48)*10 + 10;
    }
    food->setCoords(fx, fy);

    snake = new Snake(width/2, height/2);
}

void showScore()
{
    al_draw_text(font, al_map_rgb(255, 255, 255), 10, 10, NULL, "azaza");
}

void drawFunc()
{
    showScore();
    snake->draw();
    food->drawIt();

    al_flip_display();
    al_clear_to_color(al_map_rgb(0,0,0));
}

bool snakeEnd()
{
    if ((snake->getSnakeHead().getX() < 0) || (snake->getSnakeHead().getX() > width)
            || snake->getSnakeHead().getY() < 0 || snake->getSnakeHead().getY() > height)
        return true;
    return false;
}

void update()//uint time)
{
    snake->moveDown(keys[DOWN]);
    snake->moveUp(keys[UP]);
    snake->moveLeft(keys[LEFT]);
    snake->moveRight(keys[RIGHT]);
    if (keys[DOWN] || keys[UP] || keys[LEFT] || keys[RIGHT])
    {
        at_start = false;
    }
}

void updateFunc(uint gtime)
{
    if (!at_start)
        for (uint i = 0; i < snake->getSnakeBody().size(); i++)
        {
            if ((snake->getSnakeHead().getX() == snake->getSnakeBody().at(i).getX())
                    &&(snake->getSnakeHead().getY() == snake->getSnakeBody().at(i).getY()))
                restart();
        }
    if ((snake->getSnakeHead().getX() == food->getX())
            && (snake->getSnakeHead().getY() == food->getY()))
    {
        snake->eatFood();
        bool re_food = true;
        while (re_food)
        {
            food->setCoords((rand()%48)*10 + 10, (rand()%48)*10 + 10);
            re_food = false;
            for (uint i = 0; i < snake->getSnakeBody().size(); i++)
            {
                if ((food->getX() == snake->getSnakeBody().at(i).getX())
                        &&(food->getY() == snake->getSnakeBody().at(i).getY()))
                {
                    re_food = true;
                    break;
                }
            }
        }
    }
    if (gtime % snake->getSpeed() == 0)
    {
        update();
        lock_move = false;
    }
}

int main(void)
{
    bool done = false;
    bool redraw = true;
    snake = new Snake(width/2, height/2);
    food = new SFood((rand()%50)*10, (rand()%50)*10);

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;

    if(!al_init())										//initialize Allegro
        return -1;

    display = al_create_display(width, height);			//create our display object

    if(!display)										//test display object
        return -1;

    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();

    font = al_load_ttf_font("/usr/share/fonts/truetype/freefont/FreeMono.ttf", 18, NULL);

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / speed);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_start_timer(timer);
    while(!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        /*if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:
                    keys[UP] = true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    keys[DOWN] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = true;
                    break;
            }
        }
        else */if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (!lock_move)
                switch(ev.keyboard.keycode)
                {
                    case ALLEGRO_KEY_UP:
                        if (!keys[DOWN]){
                            keys[UP] = true;
                            keys[DOWN] = false;
                            keys[LEFT] = false;
                            keys[RIGHT] = false;
                        }
                        break;
                    case ALLEGRO_KEY_DOWN:
                        if (!keys[UP])
                        {
                            keys[UP] = false;
                            keys[DOWN] = true;
                            keys[LEFT] = false;
                            keys[RIGHT] = false;
                        }
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        if (!keys[LEFT])
                        {
                            keys[UP] = false;
                            keys[DOWN] = false;
                            keys[LEFT] = false;
                            keys[RIGHT] = true;
                        }
                        break;
                    case ALLEGRO_KEY_LEFT:
                        if (!keys[RIGHT])
                        {
                            keys[UP] = false;
                            keys[DOWN] = false;
                            keys[LEFT] = true;
                            keys[RIGHT] = false;
                        }
                        break;
                    case ALLEGRO_KEY_ESCAPE:
                        done = true;
                        break;
                }
            lock_move = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        else if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            updateFunc(ev.timer.count);

            redraw = true;
        }

        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            drawFunc();
        }
        if (snakeEnd() && (!at_start))
        {
            //done = true;
            restart();
        }
    }

    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_display(display);						//destroy our display object
    al_destroy_font(font);
    delete snake;
    delete food;

    return 0;
}
