#include <stdio.h>

#define root 3
#define square root*root

int gameboard[square][square] = {
    {1, 2, 3, 4, 5, 6, 7, 8, 9},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}};

int main()
{
    for(int y = 0; y < square; y++)
    {
        for(int x = 0; x < square; x++)
        {
            printf("%i, ", gameboard[y][x]);
        }
        printf("\n");
    }

    
    return 0;
}