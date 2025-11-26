#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1
#define MAX_PLATFORMS 10

float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

typedef struct Player {
    Rectangle rect;
    Vector2 velocity;
} Player;

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Plataformero con Raylib");
    SetTargetFPS(60);

    srand(time(NULL));

    // ---------------- PLAYER ----------------
    Texture2D texture = LoadTexture("Cat_player_images/Cat_sheets/Cat_walk_1.png");
    Rectangle frameRec = {0.0f, 0.0f, (float)texture.width/3, (float)texture.height};
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 6;

    Player player = {0};
    player.rect = (Rectangle){350, 280, frameRec.width, frameRec.height};
    player.velocity = (Vector2){0, 0};

    // ---------------- PLATFORMS ----------------
    Rectangle floor = {0, 400, 800, 50};
    Rectangle platforms[MAX_PLATFORMS];

    for (int i = 0; i < MAX_PLATFORMS; i++) {
        platforms[i] = (Rectangle){
            (float)(rand() % 700),
            (float)(rand() % 350),
            (float)(50 + rand() % 100),
            20
        };
    }

    const float gravity = 600.0f;
    const float speed = 200.0f;
    const float jumpForce = -300.0f;

    // ---------------- CAMERA ----------------
    Camera2D camera = {0};
    camera.target = (Vector2){player.rect.x, player.rect.y};
    camera.offset = (Vector2){screenWidth/2, screenHeight/2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // ---------------- GAME LOOP ----------------
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // ---- Animación ----
        framesCounter++;
        if (framesCounter >= (60/framesSpeed)) {
            framesCounter = 0;
            currentFrame++;
            if (currentFrame > 2) currentFrame = 0;
            frameRec.x = frameRec.width * currentFrame;
        }

        // ---- Input ----
        if (IsKeyDown(KEY_D)) player.velocity.x = speed;
        else if (IsKeyDown(KEY_A)) player.velocity.x = -speed;
        else player.velocity.x = 0;

        if (IsKeyPressed(KEY_SPACE)) player.velocity.y = jumpForce;

        if (IsKeyDown(KEY_SPACE) && player.velocity.y < 0)
            player.velocity.y += gravity * dt * 0.3f;

        if (IsKeyReleased(KEY_SPACE) && player.velocity.y < 0)
            player.velocity.y += gravity * dt * 1.5f;

        // ---- Físicas ----
        player.velocity.y += gravity * dt;
        player.rect.x += player.velocity.x * dt;
        player.rect.y += player.velocity.y * dt;

        // ---- Colisiones ----
        if (CheckCollisionRecs(player.rect, floor)) {
            player.rect.y = floor.y - player.rect.height;
            player.velocity.y = 0;
        }

        for (int i = 0; i < MAX_PLATFORMS; i++) {
            if (CheckCollisionRecs(player.rect, platforms[i]) && player.velocity.y > 0) {
                player.rect.y = platforms[i].y - player.rect.height;
                player.velocity.y = 0;
            }
        }

        // ---- Cámara ----
        float smooth = 8.0f;
        Vector2 targetPos = {player.rect.x + player.rect.width/2, player.rect.y + player.rect.height/2};
        camera.target.x = lerp(camera.target.x, targetPos.x, smooth * dt);
        camera.target.y = lerp(camera.target.y, targetPos.y, smooth * dt);

        // ---- DRAW ----
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        DrawRectangleRec(floor, DARKGRAY);
        for (int i = 0; i < MAX_PLATFORMS; i++)
            DrawRectangleRec(platforms[i], GRAY);

        DrawTextureRec(texture, frameRec, (Vector2){player.rect.x, player.rect.y}, WHITE);
        EndMode2D();

        DrawText("Saltos infinitos + plataformas random", 10, 10, 20, BLACK);
        DrawText("A/D para moverte, SPACE para saltar", 10, 35, 18, DARKBLUE);

        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();
    return 0;
}
