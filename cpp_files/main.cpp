#include "raylib.h"
#include "raymath.h"
#include "../header_files/rcamera.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../header_files/labirynth.h"
#include <vector>

float distance_view=80.f;

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

        if((distance<10.f) || (distance<distance_view && fabs(Vector2Angle(v1,v2))<M_PI_2)){
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
    unsigned size;
    unsigned long long hashed_value;
    // printf("Podaj ziarno do generatora: ");
    // scanf("%s", seed);
    strcpy(seed, "7a83lhj2p");
    hashed_value=hash(seed);
    // printf("Podaj rozmiar labiryntu: ");
    // scanf("%u", &size);
    size=400;
    size|=1;
    srand(hashed_value);

    Labirynth *labirynth=createLabirynth(size);

    int width=1080;
    int height=720;

    InitWindow(width, height, "Maze Game");
    SetTargetFPS(60);

    Camera camera={0};
    camera.position=(Vector3){labirynth->start_point_x+0.5f, 2.0f, labirynth->start_point_y+0.5f};
    camera.target=(Vector3){0.0f, 2.0f, 0.0f};
    camera.up=(Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy=60;
    camera.projection=CAMERA_PERSPECTIVE;

    std::vector<Vector3> positions;
    Vector3 start_pos;
    Vector3 end_pos;

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

    DisableCursor();

    while(!WindowShouldClose()){
        UpdateCameraCustom(&camera, CAMERA_FIRST_PERSON, labirynth);

        if(IsKeyDown(KEY_O)){
            distance_view+=1.f;
        }
        if(IsKeyDown(KEY_I)){
            distance_view-=1.f;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);

        drawWalls(camera, positions, start_pos, end_pos);

        // DrawPlane((Vector3){0.f, 0.f, 0.f}, (Vector2){128.f, 128.f}, BLACK);
        // DrawPlane((Vector3){30.f, 30.f, 30.f}, (Vector2){128.f, 128.f}, BLACK);

        EndMode3D();

        EndDrawing();
    }

    CloseWindow();

    deleteLabirynth(labirynth);
    return 0;
}