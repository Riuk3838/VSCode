#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define FILAS 50
#define COLUMNAS 50
#define CELL_SIZE 10

#define DEAD 0
#define ALIVE 1

int contarVecinos(int grid[FILAS][COLUMNAS], int x, int y) {
    int conteo = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < FILAS && ny >= 0 && ny < COLUMNAS) {
                conteo += grid[nx][ny];
            }
        }
    }
    return conteo;
}

void nextGeneration(int grid[FILAS][COLUMNAS]) {
    int nuevo[FILAS][COLUMNAS];

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            int vecinos = contarVecinos(grid, i, j);

            if (grid[i][j] == ALIVE) {
                nuevo[i][j] = (vecinos == 2 || vecinos == 3) ? ALIVE : DEAD;
            } else {
                nuevo[i][j] = (vecinos == 3) ? ALIVE : DEAD;
            }
        }
    }

    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            grid[i][j] = nuevo[i][j];
}

void randomizarGrid(int grid[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            grid[i][j] = rand() % 2;
        }
    }
}

int main(void) {
    const int screenWidth = COLUMNAS * CELL_SIZE;
    const int screenHeight = FILAS * CELL_SIZE;

    InitWindow(screenWidth, screenHeight, "Juego de la Vida - Raylib");
    SetTargetFPS(60);

    srand(time(NULL));

    int grid[FILAS][COLUMNAS];
    randomizarGrid(grid);

    float timer = 0;
    float delay = 0.2f; // Tiempo entre generaciones
    bool paused = false;
    int generation = 0;

    while (!WindowShouldClose()) {
        // Controles
        if (IsKeyPressed(KEY_R)) {
            randomizarGrid(grid);
            generation = 0;
        }
        if (IsKeyPressed(KEY_SPACE)) {
            paused = !paused;
        }

        // Avanzar generaciones automáticamente
        if (!paused) {
            timer += GetFrameTime();
            if (timer >= delay) {
                nextGeneration(grid);
                generation++;
                timer = 0;
            }
        }

        // Dibujar
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS; j++) {
                Color color = (grid[i][j] == ALIVE) ? RAYWHITE : BLACK;
                DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, color);
            }
        }

        // Dibujar cuadrícula opcional
        for (int i = 0; i <= FILAS; i++) {
            DrawLine(0, i * CELL_SIZE, screenWidth, i * CELL_SIZE, DARKGRAY);
        }
        for (int j = 0; j <= COLUMNAS; j++) {
            DrawLine(j * CELL_SIZE, 0, j * CELL_SIZE, screenHeight, DARKGRAY);
        }

        DrawText(TextFormat("Generacion: %d", generation), 10, 10, 20, GREEN);
        DrawText(paused ? "Pausado (espacio para continuar)" : "Corriendo (espacio para pausar)", 10, 35, 20, YELLOW);
        DrawText("R para reiniciar", 10, 60, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
