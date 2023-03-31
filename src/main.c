#include <stdio.h>
#include <windows.h>

#define root 3
#define square root*root
#define spacing 3

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

typedef struct position2D
{
    int x;
    int y;
} position2D;

int gameboard[square*square] = {
    1, 4, 7, 2, 8, 6, 3, 5, 9,
    2, 5, 8, 3, 7, 9, 1, 4, 6,
    3, 6, 9, 1, 5, 4, 7, 2, 8,
    4, 7, 1, 6, 9, 5, 2, 8, 3,
    5, 8, 2, 7, 1, 3, 6, 9, 4,
    6, 9, 3, 4, 2, 8, 5, 7, 1,
    7, 1, 4, 8, 3, 2, 9, 6, 5,
    8, 2, 5, 9, 6, 1, 4, 3, 7,
    9, 3, 6, 5, 4, 7, 8, 1, 2};

static int gameboardIndex = 0;
char* pieceLetters = " 1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void print_row(char left_edge[4], char space[4], char content[4], char thin_divider[4], char thick_divider[4], char right_edge[4])
{
    printf("%s", left_edge);

        for(int i = 1; i <= root; i++)
        {
            for(int j = 1; j <= root; j++)
            {
                for(int s = 1; s <= spacing; s++)
                    if (s!=2)
                        printf("%s", space);
                    else
                        if(content[0] == '!')
                            printf("%c", pieceLetters[gameboard[(gameboardIndex++)%(square*square)]]);
                        else
                            printf("%s", content);
                if(j != root)
                    printf("%s", thin_divider);
            }
            if(i == root)
                printf("%s", right_edge);
            else
                printf("%s", thick_divider);
        }
        printf("\n");
}

void draw_gameboard()
{
    print_row("╔", "═", "═", "╤", "╦", "╗");
    for(int j = 1; j <= root; j++)
    {
        for(int i = 1; i <= root; i++)
        {
            print_row("║", " ", "!", "│", "║", "║");
            if(i!=root)
                print_row("╟", "─", "─", "┼", "╫", "╢");
        }
        if(j!=root)
            print_row("╠", "═", "═", "╪", "╬", "╣");
    }

    print_row("╚", "═", "═", "╧", "╩", "╝");
}

void fill_number(int x, int y, char c)
{
    gotoxy(x * 4 + 3, 2 * y + 2);
    printf("%c", c);
}

void fill_numbers()
{
    for (int y = 0; y < square; y++)
        for (int x = 0; x < square; x++)
            fill_number(x, y, pieceLetters[gameboard[x + y * square]]);
}

int* getColContains(int x)
{
    int *colContains = malloc(sizeof(int) * square);
        ZeroMemory(colContains, sizeof(int) * square);
        for(int y = 0; y < square; y++)
            colContains[gameboard[y * square + x]-1]++;
    return colContains;
}

int* getRowContains(int y)
{
    int *rowContains = malloc(sizeof(int) * square);
        ZeroMemory(rowContains, sizeof(int) * square);
        for(int x = 0; x < square; x++)
            rowContains[gameboard[y * square + x]-1]++;
    return rowContains;
}

int* getBoxContains(int boxx, int boxy)
{
    int *boxContains = malloc(sizeof(int) * square);
            ZeroMemory(boxContains, sizeof(int) * square);
            for(int x = boxx*root; x < (boxx+1)*root; x++)
                for(int y = boxy*root; y < (boxy+1)*root; y++)
                    boxContains[gameboard[y * square + x]-1]++;
    return boxContains;
}

_Bool is_solved()
{
    _Bool solved = 1;
    
    //Check columns
    for(int x = 0; x < square; x++)
    {
        int* colContains = getColContains(x);
    
        for(int i = 0; i < square; i++)
            if (colContains[i] != 1)
            {
                printf("Unsolved: Column %i contains %i instances of %c\n", x+1, colContains[i], pieceLetters[i+1]);
                solved = 0;
            }
    }

    //Check rows
    for(int y = 0; y < square; y++)
    {
        int* rowContains = getRowContains(y);
    
        for(int i = 0; i < square; i++)
            if (rowContains[i] != 1)
            {
                printf("Unsolved: Row %i contains %i instances of %c\n", y+1, rowContains[i], pieceLetters[i+1]);
                solved = 0;
            }
    }

    //Check boxes
    for(int boxx = 0; boxx < root; boxx++)
        for(int boxy = 0; boxy < root; boxy++)
        {
            int* boxContains = getBoxContains(boxx, boxy);

            for(int i = 0; i < square; i++)
                if (boxContains[i] != 1)
                {
                    printf("Unsolved: Box (%i, %i) contains %i instances of %c\n", boxx+1, boxy+1, boxContains[i], pieceLetters[i+1]);
                    solved = 0;
                } 
        }

    return solved;
}

int getEntropy(int x, int y)
{
    return -1;
}

position2D getSpaceWithLowestEntropy()
{
    int lowestEntropy = square + 1;
    position2D position;
    position.x = -1;
    position.y = -1;
    for(int x = 0; x < square; x++)
        for(int y = 0; y < square; y++)
            if(gameboard[y*square + x] == 0)
            {
                int entropy = getEntropy(x, y);
                
                if(entropy < lowestEntropy)
                {
                    lowestEntropy = entropy;
                    position.x = x;
                    position.y = y;
                }
            }

    if(lowestEntropy == 0 || lowestEntropy == square + 1)
        return position;

    return position;
}

_Bool makeAMove()
{
    position2D lowestEntropy = getSpaceWithLowestEntropy();

    printf("Lowest Entropy: (%i, %i)\n", lowestEntropy.x, lowestEntropy.y);
    return 1;
}

void solve()
{
    makeAMove();
    //while(!is_solved() && makeAMove()){}
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    draw_gameboard();
    
    printf("Press Enter to begin...");
    getchar();
    clear();
    draw_gameboard();

    solve();

    if(is_solved())
        printf("The puzzle is solved.\n");

    return 0;
}