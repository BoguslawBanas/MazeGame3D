#include "raylib.h"
#include "raymath.h"
#include "../header_files/rcamera.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../header_files/labirynth.h"
#include "../header_files/screen.h"
#include <vector>
#include <queue>
#include "../header_files/button.h"

#define MENU_START_FRAME_COUNTER 2048

float distance_view=1000.f;

unsigned long long hash(char s[]){
    int i=0;
    unsigned long long result=1;
    while(s[i]!='\0'){
        result*=(5*s[i])+37;
        ++i;
    }
    return result;
}

float calcDistance(Vector3 &v1, Vector3 &v2){
    return (v1.x-v2.x)*(v1.x-v2.x)+(v1.z-v2.z)*(v1.z-v2.z);
}

void drawWalls(Camera &camera, std::vector<Vector3>&positions, Vector3 &start_pos, Vector3 &end_pos){
    Vector2 v1{camera.target.x-camera.position.x, camera.target.z-camera.position.z};
    Vector2 v2;

    for(int i=0;i<positions.size();++i){
        v2.x=positions[i].x-camera.position.x;
        v2.y=positions[i].z-camera.position.z;
        float distance=calcDistance(camera.position, positions[i]);

        if(distance<30.f || (distance<distance_view && fabs(Vector2Angle(v1, v2))<M_PI_4+0.1f)){
            DrawCube(positions[i], 1.f, 5.f, 1.f, LIGHTGRAY);
            DrawCubeWires(positions[i], 1.f, 5.f, 1.f, MAGENTA);
        }
    }

    if(calcDistance(camera.position, start_pos)<distance_view){
        DrawCube(start_pos, 1.f, 0.2f, 1.f, RED);
    }
    if(calcDistance(camera.position, end_pos)<distance_view){
        DrawCube(end_pos, 1.f, 0.2f, 1.f, GREEN);
    }
}

int main(){
    char seed[64];
    seed[0]='\0';
    unsigned size;
    unsigned long long hashed_value;
    Screen screen=TitleScreen;
    int frame_counter=0;

    const int width=1080;
    const int height=720;

    InitWindow(width, height, "Maze Game");
    SetTargetFPS(60);
    Labirynth *labirynth=nullptr;

    std::vector<Vector3> positions;
    Vector3 start_pos;
    Vector3 end_pos;
    Camera camera={0};
    camera.position=(Vector3){0.0f, 6.0f, 0.0f};
    camera.target=(Vector3){10.0f, 2.0f, 10.0f};
    camera.up=(Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy=60;
    camera.projection=CAMERA_PERSPECTIVE;

    int indexKey=0;
    Rectangle inputBox={width/2 - 100, 180, 225, 50};

    FILE *f=fopen("example_maze.maz", "r");
    if(f){
        int x,y,z;
        fscanf(f, "%d %d %d", &x, &y, &z);
        while(!feof(f)){
            positions.push_back(Vector3{x+0.5f, y+0.5f, z+0.5f});
            fscanf(f, "%d %d %d", &x, &y, &z);
        }
    }
    fclose(f);

    GameButton *b1=new GameButton(width/3-300, 100, 225, 50, GREEN, RED, "New game");
    GameButton *b2=new GameButton(width*2/3-300, 100, 225, 50, GREEN, RED, "Load game");
    GameButton *b3=new GameButton(width-300, 100, 225, 50, GREEN, RED, "Credits");

    while(!WindowShouldClose()){
        switch(screen){
            case TitleScreen:{
                ++frame_counter;
                if(frame_counter>=MENU_START_FRAME_COUNTER){
                    frame_counter=0;
                }
                if(frame_counter<=MENU_START_FRAME_COUNTER/2){
                    camera.target.x+=0.05f;
                    camera.target.z+=0.05f;
                }
                else{
                    camera.target.x-=0.05f;
                    camera.target.z-=0.05f;
                }
                UpdateCameraCustom(&camera, CAMERA_ORBITAL, nullptr);

                if(b1->isMouseOn() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    screen=NewGameScreen;
                }
                b2->isMouseOn();
                b3->isMouseOn();
            }break;

            case NewGameScreen:{
                SetMouseCursor(MOUSE_CURSOR_IBEAM);
                int key=GetCharPressed();
                while(key>0){
                    if(key>=32 && key<=125 && indexKey<63){
                        seed[indexKey]=char(key);
                        seed[indexKey+1]='\0';
                        ++indexKey;
                    }
                    key=GetCharPressed();
                }
                if(IsKeyPressed(KEY_BACKSPACE)){
                    --indexKey;
                    if(indexKey<0){
                        indexKey=0;
                    }
                    seed[indexKey]='\0';
                }
                else if(IsKeyPressed(KEY_ENTER)){
                    if(seed!=""){
                        hashed_value=hash(seed);
                        srand(hashed_value);
                    }
                    else{
                        srand(time(0));
                    }
                    size=21;
                    size|=1;
                    screen=LoadingGameScreen;
                    distance_view=150.f;
                }
            }break;

            case LoadingGameScreen:{
                DisableCursor();
                labirynth=createLabirynth(size);
                camera.position=(Vector3){labirynth->start_point_x+0.5f, 2.0f, labirynth->start_point_y+0.5f};
                camera.target=(Vector3){0.0f, 2.0f, 0.0f};
                camera.up=(Vector3){0.0f, 1.0f, 0.0f};
                camera.fovy=60;
                camera.projection=CAMERA_PERSPECTIVE;

                positions.clear();
                for(int i=0;i<labirynth->size;++i){
                    for(int j=0;j<labirynth->size;++j){
                        if(labirynth->labirynth[j][i]=='#'){
                            positions.push_back((Vector3){i+0.5f, 2.5f, j+0.5f});
                        }
                        else if(labirynth->labirynth[j][i]=='P'){
                            start_pos=(Vector3){i+0.5f, 0.f, j+0.5f};
                        }
                        else if(labirynth->labirynth[j][i]=='E'){
                            end_pos=(Vector3){i+0.5f, 0.f, j+0.5f};
                        }
                    }
                }
                screen=MazeScreen;
            }break;

            case MazeScreen:{
                UpdateCameraCustom(&camera, CAMERA_FIRST_PERSON, labirynth);
                if(IsKeyDown(KEY_O)){
                    distance_view+=1.f;
                }
                if(IsKeyDown(KEY_I)){
                    distance_view-=1.f;
                }
            }break;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        switch(screen){
            case TitleScreen:{
                BeginMode3D(camera);
                drawWalls(camera, positions, start_pos, end_pos);
                EndMode3D();
                DrawText("Maze game", width/2+40, 15, 40, MAGENTA);
                b1->drawButton();
                b2->drawButton();
                b3->drawButton();
            }break;

            case NewGameScreen:{
                ClearBackground(WHITE);
                DrawRectangleRec(inputBox, LIGHTGRAY);
                DrawText(seed, (int)inputBox.x+5, (int)inputBox.y+8, 40, MAGENTA);
            }break;

            case LoadingGameScreen:{
            }break;

            case MazeScreen:{
                BeginMode3D(camera);

                drawWalls(camera, positions, start_pos, end_pos);

                EndMode3D();
                }break;
            }
        EndDrawing();
    }

    CloseWindow();

    deleteLabirynth(labirynth);
    delete b1;
    delete b2;
    delete b3;
    return 0;
}