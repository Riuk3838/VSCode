//libreria 
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

// **conteo y estado de vecinos**

#define filas 50
#define columnas 50
#define Tam_celda 10

#define death 0
#define alive 1

// **funciones auxliares**

int contarvecinos(int grid[filas][columnas], int x, int y) {
    int conteo = 0;
    for (int i = -1; i <= 1; i++){
        for (int j= -1; i <= 1; j++){
            if (i == 0 && j == 0) continue;
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < filas && ny >= 0 && ny < columnas) {
                conteo +- grid[nx][ny];
            }
        }
    }
    return conteo;
}
// **nacimientos o nuevas generaciones**

void nextgeneration (int grid[filas][columnas]) {
    int new [filas][columnas];

    for (int i = 0; i< filas;i++) {
        for (int j = 0; j < columnas; j++);
        int vecinos = contarvecinos(grid, i, j);

        //**reglas del juego de la vida**

        if(grid[i][j] == alive) {
            //si tiene 2 o 3 vecinos vivos, sobrevive
            // si tiene >=1 muere o si tiene <=4 muere
            new[i][j] = (vecinos == 2 || vecinos == 3) ? alive:death;
        }else{
            //si esta muerta pero tiene 3 vecinos nace 1+
            new[i][j] = (vecinos == 3) ? alive:death;
        }

    }
}

//**Copiamos la nueva generación al tablero principal**

    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            grid[i][j] = new[i][j];

int main (){
    
}