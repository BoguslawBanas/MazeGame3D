#include "../header_files/button.h"
#include <stdio.h>

GameButton::GameButton(Rectangle rec, Color color1, Color color2, const char *s){
    this->rectangle=rec;
    this->c1=color1;
    this->c2=color2;
    this->current_mode=0;
    strcpy(this->name, s);
}

GameButton::GameButton(const float x, const float y, const float width, const float height, Color color1, Color color2, const char *s){
    // this->rectangle=Rectangle{x, y, width, height};
    this->rectangle.x=x;
    this->rectangle.y=y;
    this->rectangle.width=width;
    this->rectangle.height=height;

    this->c1=color1;
    this->c2=color2;
    this->current_mode=0;
    strcpy(this->name, s);
    printf("%f\n", this->rectangle.x);
}

GameButton::~GameButton()=default;

Rectangle GameButton::getRectangle(){
    printf("%f\n", this->rectangle.x);
    return this->rectangle;
}

bool GameButton::isMouseOn(){
    Vector2 mousePoint=GetMousePosition();
    if(CheckCollisionPointRec(mousePoint, this->rectangle)){
        this->current_mode=1;
        return true;
    }
    this->current_mode=0;
    return false;
}

bool GameButton::isButtonClicked(){
    return true;
}

void GameButton::drawButton(){
    if(current_mode==0){
        DrawRectangle(this->rectangle.x, this->rectangle.y, this->rectangle.width, this->rectangle.height, this->c1);
        // DrawRectangleRec(this->rectangle, this->c1);
    }
    else{
        DrawRectangle(this->rectangle.x, this->rectangle.y, this->rectangle.width, this->rectangle.height, this->c2);
        // DrawRectangleRec(this->rectangle, this->c2);
    }
    DrawText(this->name, this->rectangle.x+20, this->rectangle.y+5, 40, GRAY);
}