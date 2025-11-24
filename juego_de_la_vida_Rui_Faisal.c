#include "raylib.h"
#include <stdbool.h>

#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

typedef struct Player {
    Rectangle rect;
    Vector2 velocity;
    bool onGround;
} Player;

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Plataformero con Raylib");
    SetTargetFPS(60);

    // Jugador
    InitWindow(screenWidth,screenHeight,"raylib [textures] example - sprite animation");
    Texture2D scarfy = LoadTexture("cat_walk_1.png");}
    Vector2 position = { 350.0f, 280.0f}
    }

    // Plataforma principal (suelo)
    Rectangle floor = {0, 400, 800, 50};

    // Otra plataforma
    Rectangle platform = {300, 300, 150, 20};

    const float gravity = 600.0f; // gravedad en pixels/segundo^2
    const float speed = 200.0f;
    const float jumpForce = -300.0f;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // --------------------------
        //   INPUT DEL JUGADOR
        // --------------------------
        if (IsKeyDown(KEY_RIGHT)) player.velocity.x = speed;
        else if (IsKeyDown(KEY_LEFT)) player.velocity.x = -speed;
        else player.velocity.x = 0;

        if (IsKeyPressed(KEY_SPACE) && player.onGround) {
            player.velocity.y = jumpForce;
            player.onGround = false;
        }

        // --------------------------
        //        FÍSICA
        // --------------------------
        player.velocity.y += gravity * dt;
        player.rect.x += player.velocity.x * dt;
        player.rect.y += player.velocity.y * dt;

        // --------------------------
        //     COLISIONES
        // --------------------------
        player.onGround = false;

        // Suelo
        if (CheckCollisionRecs(player.rect, floor)) {
            player.rect.y = floor.y - player.rect.height;
            player.velocity.y = 0;
            player.onGround = true;
        }

        // Plataforma flotante
        if (CheckCollisionRecs(player.rect, platform)) {
            if (player.velocity.y > 0) { // cae desde arriba
                player.rect.y = platform.y - player.rect.height;
                player.velocity.y = 0;
                player.onGround = true;
            }
        }

        // --------------------------
        //     DIBUJO
        // --------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleRec(floor, DARKGRAY);
        DrawRectangleRec(platform, GRAY);

        DrawRectangleRec(player.rect, BLUE);

        DrawText("Plataformero en C + Raylib", 10, 10, 20, BLACK);
        DrawText("Flechas para moverte, SPACE para saltar", 10, 35, 18, DARKBLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
