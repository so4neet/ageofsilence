#include <kos.h>
#include <raylib.h>
#include <pthread.h>
#include <oggvorbis/sndoggvorbis.h>
#include "components/input.h"
#include "components/menus.h"

const int scrWidth = 640;
const int scrHeight = 480;
// Set enums for scene manager and maps
enum GameState {SPLASH, MENU, LOADING, INGAME };
enum MapToLoad {TESTMAP, DESERT};
bool startGame = false;
bool startLoadThread = false;
bool doneLoading = false;
KOS_INIT_FLAGS(INIT_DEFAULT | INIT_MALLOCSTATS);

void *loadAssets();
void *playSnd();

int main() {
    pthread_t loadThread;
    enum GameState currentState = SPLASH;
    enum MapToLoad mapToLoad;

    int splashTimer = 0;
    int volume = 100;
    int rotSquare = 0;
    float fadeOpacity = 1.0f;
    bool unloadSplash = false;
    bool startFade = false;

    InitWindow(scrWidth, scrHeight, "Age Of Silence");
    SetTargetFPS(60);

    Image splImg = LoadImage("/cd/assets/tex/ogresden.png");
    Texture2D splTex = LoadTextureFromImage(splImg);
    UnloadImage(splImg);
    snd_stream_init();
    sndoggvorbis_init();
    sndoggvorbis_start("/cd/assets/snd/splash_aos.ogg", 0);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        // Switch for Logic
        switch(currentState){
            case SPLASH: {
                // Splash screen timer
                Color fade = Fade(BLACK, fadeOpacity);
                DrawTexturePro(splTex, (Rectangle){0, 0, splTex.width, splTex.height}, (Rectangle){64, 0, scrWidth-128, scrHeight}, (Vector2){0, 0}, 0.0f, WHITE);
                DrawRectangle(0, 0, scrWidth, scrHeight, fade);
                int startState = GetStartState();
                if(splashTimer == 300 || startState == 1){
                    unloadSplash = true;
                    fadeOpacity = 1.0f;
                    sndoggvorbis_stop();
                    currentState = MENU;
                }
                if(splashTimer < 60) {
                    fadeOpacity -= 0.016f;
                }
                if(splashTimer > 240) {
                    fadeOpacity += 0.016f;
                }
                splashTimer++;
                break;
            }
            case MENU: {
                // Grab user input
                if(unloadSplash){
                    UnloadTexture(splTex);
                    unloadSplash = false;
                }
                if(!sndoggvorbis_isplaying()){
                    sndoggvorbis_start("/cd/assets/snd/aos_menu.ogg", 1);
                }
                DrawMenu();
                DrawRectangle(0,0,scrWidth,scrHeight, Fade(BLACK, fadeOpacity));
                if(startGame){
                    startFade = true;
                }
                if(!startFade){
                    if(fadeOpacity > 0.0f){
                        fadeOpacity -= 0.016f;
                    }
                } else {
                    if(fadeOpacity < 1.0f){
                        fadeOpacity += 0.016f;
                        volume -= 1;
                        sndoggvorbis_volume(volume);
                    } else {
                        fadeOpacity = 1.0f;
                        startFade = false;
                        startLoadThread = true;
                        sndoggvorbis_stop();
                        currentState = LOADING;
                    }
                }
                break;
            }
            case LOADING: {
                // Load all used ingame assets
                if(startGame){
                    mapToLoad = DESERT; // start level
                } else {
                    // Get random number to pick a level etc
                }
                switch(mapToLoad){
                    case DESERT: {
                        DrawText("Loading [wasteland planet name]", 40, 20, 20, WHITE);
                        DrawRectanglePro((Rectangle){20, 30, 20, 20}, (Vector2){10, 10}, rotSquare, WHITE);
                        rotSquare = rotSquare+4;
                        break;
                    }
                    case TESTMAP: {
                        break;
                    }
                }

                if(startLoadThread){
                    pthread_create(&loadThread, NULL, loadAssets, NULL);
                    startLoadThread = false;
                }

                if(doneLoading){
                    pthread_join(loadThread, NULL);
                    currentState = INGAME;
                }
                break;
            }
            case INGAME: {
                // Handle game logic
                DrawText("Done Loading!", 10, 10, 10, WHITE);
                break;
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void *loadAssets() {
    Image t1 = LoadImage("/cd/assets/tex/ts_bg.png");
    Texture2D tt1 = LoadTextureFromImage(t1);
    UnloadImage(t1);
    UnloadTexture(tt1);
    Image t2 = LoadImage("/cd/assets/tex/ts_bg.png");
    Texture2D tt2 = LoadTextureFromImage(t1);
    UnloadImage(t2);
    UnloadTexture(tt2);
    Image t3 = LoadImage("/cd/assets/tex/ts_bg.png");
    Texture2D tt3 = LoadTextureFromImage(t1);
    UnloadImage(t3);
    UnloadTexture(tt3);
    Image t4 = LoadImage("/cd/assets/tex/ts_bg.png");
    Texture2D tt4 = LoadTextureFromImage(t1);
    UnloadImage(t4);
    UnloadTexture(tt4);
    int volume = 255;
    sndoggvorbis_volume(volume);
    sndoggvorbis_start("/cd/assets/snd/aos_ambiance.ogg", 1);
    doneLoading = true;
    return NULL;
}
