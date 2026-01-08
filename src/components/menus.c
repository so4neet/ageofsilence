#include <raylib.h>
#include <raymath.h>
#include "input.h"
#include "../main.h"

enum MenuState {MAIN, CONNECT, SETTINGS, CREDITS};
enum MenuState menuState;
bool firstOpen = true;
#define STAR_COUNT 150
Vector3 stars[STAR_COUNT] = {0};
Vector2 starsScrPos[STAR_COUNT] = {0};
void DrawMenu() {
    float delta = GetFrameTime();
    Color bgColor = {0,0,25,255};
    ClearBackground(bgColor);
    for (int i=0; i<STAR_COUNT; i++){
        stars[i].z -= delta*1.0f;

        starsScrPos[i] = (Vector2){
            640*0.5f + stars[i].x/stars[i].z,
            480*0.5f + stars[i].y/stars[i].z,
        };
        if ((stars[i].z < 0.0) || (starsScrPos[i].x < 0.0) || (starsScrPos[i].y < 0.0f) || (starsScrPos[i].x > 645) || (starsScrPos[i].y > 485)){
            stars[i].x = GetRandomValue(-640*0.5f, 640*0.5f);
            stars[i].y = GetRandomValue(-480*0.5f, 480*0.5f);
            stars[i].z = 1.0f;
        }
    }
    for (int i=0; i<STAR_COUNT; i++){
        float t = Clamp(stars[i].z + 1.0f/32.0f, 0.0f, 1.0f);
        if ((t-stars[i].z) > 1e-3){
            Vector2 startPos = (Vector2){640*0.5f + stars[i].x/t, 480*0.5f + stars[i].y/t};
            DrawLineV(startPos, starsScrPos[i], LIGHTGRAY);
        }
    }
    DrawText("AGE OF SILENCE", 20, 20, 60, WHITE);
    switch(menuState){
        case MAIN: {
            HandleMenuInput(3);

            if(menuChoice == 0){
                DrawText("-Connect-", 45, 200, 30, WHITE);
            } else {
                DrawText("Connect", 40, 200, 30, WHITE);
            }
            if(menuChoice == 1){
                DrawText("-Settings-", 45, 240, 30, WHITE);
            } else {
                DrawText("Settings", 40, 240, 30, WHITE);
            }
            if(menuChoice == 2){
                DrawText("-Credits-", 45, 280, 30, WHITE);
            } else {
                DrawText("Credits", 40, 280, 30, WHITE);
            }
            if(aPressed == true){
                if(menuChoice == 0){
                    menuState = CONNECT;
                }
                if(menuChoice == 1){
                    menuState = SETTINGS;
                }
                if(menuChoice == 2){
                    menuState = CREDITS;
                }
            }
            break;
        }
        case CONNECT: {
            HandleMenuInput(0);
            DrawText("will add later, press (A) to start game, (B) to go back.", 10, 10, 10, WHITE);
            if(aPressed){
                startGame = true;
            }
            if(bPressed){
                menuState = MAIN;
            }
            break;
        }
        case SETTINGS: {
            HandleMenuInput(0);
            DrawText(" - Settings - ", 10, 4, 20, WHITE);
            DrawText("(B) To Return", 20, 470, 10, WHITE);
            if(bPressed == true){
                menuState = MAIN;
            }
            break;
        }
        case CREDITS: {
            HandleMenuInput(0);
            DrawText(" - CREDITS - ", 10, 4, 20, WHITE);
            DrawText("Created by: ", 20, 180, 30, WHITE);
            DrawText("Blaire McArthur - Developer/Music", 30, 210, 20, PURPLE);
            DrawText("Gwen Warren - Story/Lore", 30, 230, 20, PURPLE);
            DrawText("Software Used: ", 20, 280, 30, WHITE);
            DrawText("KallistiOS - Raylib - FL Studio", 30, 310, 20, PURPLE);
            DrawText("(B) To Return", 20, 470, 10, WHITE);
            if(bPressed == true){
                menuState = MAIN;
            }
        }
    }
}
