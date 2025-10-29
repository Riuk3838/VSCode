#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#define filas 10
#define columnas 10

#define death 0
#define alive 1

int contarvecinos(int grid[filas][columnas], int x, int y) {
    int conteo = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < filas && ny >= 0 && ny < columnas) {
                conteo += grid[nx][ny];
            }
        }
    }
    return conteo;
}

void nextgeneration(int grid[filas][columnas]) {
    int nuevo[filas][columnas];

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            int vecinos = contarvecinos(grid, i, j);

            if (grid[i][j] == alive) {
                nuevo[i][j] = (vecinos == 2 || vecinos == 3) ? alive : death;
            } else {
                nuevo[i][j] = (vecinos == 3) ? alive : death;
            }
        }
    }

    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            grid[i][j] = nuevo[i][j];
}

void imprimir(int grid[filas][columnas]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%c ", grid[i][j] ? '#' : '.');
        }
        printf("\n");
    }
}

void limpiarPantalla() {
    // Limpia la pantalla según el sistema operativo
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void draw(int grid[filas][columnas], int gen) {
    printf("Generación %d:\n", gen);
    imprimir(grid);
    printf("\n");
}

int main() { 
    int grid[filas][columnas];
    srand(time(NULL));

    // Inicialización aleatoria
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            grid[i][j] = rand() % 2;
        }
    }

    // Simulación
    for (int gen = 0; gen < 50; gen++) {
        draw(grid, gen);
        nextgeneration(grid);

        #ifdef _WIN32
            Sleep(300);
        #else
            usleep(3000000);
        #endif
    }

    return 0;
}
