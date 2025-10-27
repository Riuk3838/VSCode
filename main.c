#include "raylib.h"

//------------------------------------------------------------------------------------
// Variables globales
//------------------------------------------------------------------------------------
Vector2 playerposition = {50, 175};
Vector2 player2position = {730, 175};
Vector2 playersize = {20, 100};
Vector2 player2size = {20, 100};

int player1Score = 0;
int player2Score = 0;

//------------------------------------------------------------------------------------
// Función para reiniciar la pelota
//------------------------------------------------------------------------------------
void ResetBall(Vector2 *position, Vector2 *speed, int screenWidth, int screenHeight)
{
    *position = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };

    float dirX = (GetRandomValue(0, 1) == 0) ? -1.0f : 1.0f;
    float dirY = (GetRandomValue(0, 1) == 0) ? -1.0f : 1.0f;

    *speed = (Vector2){ dirX * 5.0f, dirY * 4.0f };
}

//------------------------------------------------------------------------------------
// Programa principal
//------------------------------------------------------------------------------------
int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "raylib - Pong");

    Vector2 ballPosition = { screenWidth / 2.0f, screenHeight / 2.0f };
    Vector2 ballSpeed = { 5.0f, 4.0f };
    int ballRadius = 20;
    float gravity = 0.2f;

    bool useGravity = true;
    bool pause = false;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        if (IsKeyPressed(KEY_G)) useGravity = !useGravity;
        if (IsKeyPressed(KEY_SPACE)) pause = !pause;

        if (!pause)
        {
            // Colisiones
            if (ballPosition.x - ballRadius <= playerposition.x + playersize.x &&
                ballPosition.y >= playerposition.y &&
                ballPosition.y <= playerposition.y + playersize.y)
            {
                ballSpeed.x *= -1.0f;
                ballPosition.x = playerposition.x + playersize.x + ballRadius;
            }

            if (ballPosition.x + ballRadius >= player2position.x &&
                ballPosition.y >= player2position.y &&
                ballPosition.y <= player2position.y + player2size.y)
            {
                ballSpeed.x *= -1.0f;
                ballPosition.x = player2position.x - ballRadius;
            }

            // Movimiento jugadores
            if (IsKeyDown(KEY_W) && playerposition.y > 0)
                playerposition.y -= 5;
            if (IsKeyDown(KEY_S) && (playerposition.y + playersize.y) < screenHeight)
                playerposition.y += 5;

            if (IsKeyDown(KEY_UP) && player2position.y > 0)
                player2position.y -= 5;
            if (IsKeyDown(KEY_DOWN) && (player2position.y + player2size.y) < screenHeight)
                player2position.y += 5;

            // Movimiento pelota
            ballPosition.x += ballSpeed.x;
            ballPosition.y += ballSpeed.y;

            if (ballSpeed.x > 14.0f) ballSpeed.x *= 0.7f;
            if (ballSpeed.y > 14.0f) ballSpeed.y *= 0.7f;

            if (useGravity) ballSpeed.y += gravity;

            // Rebotar en paredes
            if (ballPosition.y >= (screenHeight - ballRadius) || ballPosition.y <= ballRadius)
                ballSpeed.y *= -1.5f;

            // Puntos
            if (ballPosition.x < 0)
            {
                player2Score++;
                ResetBall(&ballPosition, &ballSpeed, screenWidth, screenHeight);
            }

            if (ballPosition.x > screenWidth)
            {
                player1Score++;
                ResetBall(&ballPosition, &ballSpeed, screenWidth, screenHeight);
            }
        }

        // Draw
        BeginDrawing();
            ClearBackground(BLACK);

            DrawCircleV(ballPosition, ballRadius, RED);
            DrawRectangleV(playerposition, playersize, BLUE);
            DrawRectangleV(player2position, player2size, GREEN);

            DrawText(TextFormat("%d", player1Score), screenWidth / 4 - 20, 20, 40, WHITE);
            DrawText(TextFormat("%d", player2Score), 3 * screenWidth / 4 - 20, 20, 40, WHITE);

            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
