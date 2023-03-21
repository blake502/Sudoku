#include <stdio.h>
#include <windows.h>

#define root 3
#define square root*root
#define spacing 3

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

int gameboard[square*square] = {
    9, 8, 7, 6, 5, 4, 3, 2, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0};

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

_Bool is_solved()
{
    //Check columns
    for(int x = 0; x < square; x++)
    {
        int colContains[square];
        for(int y = 0; y < square; y++)
            colContains[y] = gameboard[x + y * square];
    
        for(int i = 0; i < square; i++)
        {
            printf("Col %i at %i: %i\n", x+1, i+1, colContains[i]);
        }
    }

    //Check rows
    for(int y = 0; y < square; y++)
    {
        int rowContains[square];
        for(int x = 0; x < square; x++)
            rowContains[x] = gameboard[x + y * square];
    
        for(int i = 0; i < square; i++)
        {
            printf("Row %i at %i: %i\n", y+1, i+1, rowContains[i]);
        }
    }

    return 1;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    draw_gameboard();
    
    printf("Press Enter to begin...");
    getchar();

    clear();
    draw_gameboard();

    is_solved();

    return 0;
    for(int i = 0; i < 2300; i++)
    {
        fill_numbers();
    }

    return 0;
}