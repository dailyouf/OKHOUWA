#include <stdlib.h>
#include <stdio.h>

#define L 100
#define H 100

void point(char car, int y, int x, char image[L][H]);
void trait(char car, int X1, int X2, int Y, char image[L][H]);
void rectangle(char car, int X1, int X2, int Y1, int Y2, char image[L][H]);

int main() {
    char image[L][H];
    int i, j;
    char car = '#';

    for (i = 0; i < L; i++) {
        for (j = 0; j < H; j++) {
            image[i][j] = '.';
        }
    }
    
    trait('-', 5, 12, 2, image);
    trait('-', 5, 12, 6, image);
    trait_vertical('|', 5, 2, 6, image);
    trait_vertical('|', 12, 2, 6, image);
    
    point('+', 5, 2, image);
    point('+', 5, 6, image);
    point('+', 12, 2, image);
    point('+', 12, 6, image);
    
    for (i = 0; i < L; i++) {
        for (j = 0; j < H; j++) {
            printf("%c", image[j][i]);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}

void point(char car, int X, int Y, char image[L][H]) {
    if (X >= 0 && X < L && Y >= 0 && Y < H) {
        image[X][Y] = car;
    }
}

void trait(char car, int X1, int X2, int Y, char image[L][H]) {
    int i;
    for (i = X1; i < X2; i++) {
        point(car, i, Y, image);
    }
}

void trait_vertical(char car, int X, int Y1, int Y2, char image[L][H]) {
    int j;
    for (j = Y1; j < Y2; j++) {
        point(car, X, j, image);
    }
}



void rectangle(char car, int X1, int X2, int Y1, int Y2, char image[L][H]) {
    trait(car, X1, X2, Y1, image);
    trait(car, X1, X2, Y2, image);
    trait_vertical(car, X1, Y1, Y2, image);
    trait_vertical(car, X2, Y1, Y2, image);
}

