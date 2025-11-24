#include "raylib.h"
#include <stdbool.h>

#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED  1

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

    // --------------------------------------------------------------------
    //                       SPRITE DEL JUGADOR
    // --------------------------------------------------------------------
    Texture2D texture = LoadTexture("Cat_player_images/Cat_sheets/Cat_walk_1.png");
    Rectangle frameRec = { 0.0f, 0.0f, (float)texture.width/3, (float)texture.height };
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 2;

    // --------------------------------------------------------------------
    //                        DATOS DEL JUGADOR
    // --------------------------------------------------------------------
    Player player = {0};
    player.rect = (Rectangle){350, 280, frameRec.width, frameRec.height};
    player.velocity = (Vector2){0, 0};
    player.onGround = false;

    // --------------------------------------------------------------------
    //                     PLATAFORMAS Y FÍSICAS
    // --------------------------------------------------------------------
    Rectangle floor = (Rectangle){0, 400, 800, 50};
    Rectangle platform = (Rectangle){300, 300, 150, 20};

    const float gravity = 600.0f;
    const float speed = 200.0f;
    const float jumpForce = -300.0f;

    // --------------------------------------------------------------------
    //                         GAME LOOP
    // --------------------------------------------------------------------
    while (!WindowShouldClose()) {

        float dt = GetFrameTime();

        // ANIMACIÓN del spritesheet
        framesCounter++;
        if (framesCounter >= (60/framesSpeed)) {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;

            frameRec.x = frameRec.width * currentFrame;
        }

        // Control de velocidad de animación (debug)
        if (IsKeyPressed(KEY_RIGHT)) framesSpeed++;
        if (IsKeyPressed(KEY_LEFT)) framesSpeed--;
        if (framesSpeed > MAX_FRAME_SPEED) framesSpeed = MAX_FRAME_SPEED;
        if (framesSpeed < MIN_FRAME_SPEED) framesSpeed = MIN_FRAME_SPEED;

        // ---------------------------------------------------------
        //                INPUT
        // ---------------------------------------------------------
        player.velocity.x = 0;
        if (IsKeyDown(KEY_D)) player.velocity.x = speed;
        if (IsKeyDown(KEY_A)) player.velocity.x = -speed;

        if (IsKeyPressed(KEY_SPACE) && player.onGround) {
            player.velocity.y = jumpForce;
            player.onGround = false;
        }

        // ---------------------------------------------------------
        //                FÍSICAS
        // ---------------------------------------------------------
        player.velocity.y += gravity * dt;
        player.rect.x += player.velocity.x * dt;
        player.rect.y += player.velocity.y * dt;

        // Resetear estado
        player.onGround = false;

        // Colisión con suelo
        if (CheckCollisionRecs(player.rect, floor)) {
            player.rect.y = floor.y - player.rect.height;
            player.velocity.y = 0;
            player.onGround = true;
        }

        // Colisión con plataforma
        if (CheckCollisionRecs(player.rect, platform)) {
            if (player.velocity.y > 0) {
                player.rect.y = platform.y - player.rect.height;
                player.velocity.y = 0;
                player.onGround = true;
            }
        }

        // ---------------------------------------------------------
        //                DRAW
        // ---------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleRec(floor, DARKGRAY);
        DrawRectangleRec(platform, GRAY);

        // Dibujar el sprite animado
        DrawTextureRec(texture, frameRec, (Vector2){player.rect.x, player.rect.y}, WHITE);

        DrawText("Plataformero en C + Raylib", 10, 10, 20, BLACK);
        DrawText("A/D para moverte, SPACE para saltar", 10, 35, 18, DARKBLUE);

        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();
    return 0;
}
