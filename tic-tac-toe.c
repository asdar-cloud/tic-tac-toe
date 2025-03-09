#include <stdio.h>

/*
1) Board initialization (initboard)
2) Drawing board (drawboard)
3) Separate functions for check global and local wins
4) Main game pocess, including moves and victory checks
*/

int localwin[3][3] = {0}; // assigning a default value (none, 1 - X, 2 - O) to localwin means that none of the mini-boards have been won yet
char board[3][3][3][3];
int lang; // This will contain information about chosen language of the game (0 - ru; 1 - en)

void initboard() // asigning standard value (space) for every parts of field
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    board[i][j][k][l] = ' ';
                }
            }
        }
    }
}

void drawboard() // Here you can see drawing process
{
    int lclrow = 0;
   for (int globalrow = 0; globalrow < 3; globalrow++)                             //-
   {                                                                               // |
    switch (globalrow)                                                             // |
    {                                                                              // |
        case 1: case 2: printf("=========================================\n");     // |
    }                                                                              //  >  drawing global board
    for (int localrow = 0; localrow < 5; localrow++)                               // |
    {                                                                              // |
        for (int globalcol = 0; globalcol < 3; globalcol++)                        // |
        {                                                                          // |
            if (globalcol != 0)                                                    //-
                printf("|| ");
            if (localwin[globalrow][globalcol] == 0) // drawing local boards
            {
                switch (localrow)
                {
                case 0: lclrow = 0; case 4: lclrow = 1; case 2: lclrow = 2;
                 printf(" %c | %c | %c  ", board[globalrow][globalcol][lclrow][0], board[globalrow][globalcol][lclrow][1], board[globalrow][globalcol][lclrow][2]); break;
                case 1: case 3: printf("---+---+--- "); break;
                }
            }
            else if (globalwin[globalrow][globalcol] == 1)
            {
                switch (localrow)
                {
                    case 0: printf("  _      _  "); break;
                    case 1: printf("   \\_  _/   "); break;
                    case 2: printf("     \\/     "); break;
                    case 3: printf("    _/\\_    "); break;
                    case 4: printf("  _/    \\_  "); break;
                }
            }
            else if (globalwin[globalrow][globalcol] == 2)
            {
                switch (localrow)
                {
                    case 0: case 4: printf("   OOOO     "); break;
                    case 1: case 2: case 3: printf("  O    O    "); break;
                }
            }
        }
        printf("\n");
    }
   }
   printf("\n");
}

int localwin()
{

}
int globalwin()
{

}

int main()
{
    int GRow, GCol, LRow, LCol, plr = 1, tm[3][3] = {0};
    printf("You can read the rules in README file on github\n"); // not existing yet
    initboard();
    drawboard();
    printf("Choose language (en/ru) -> ");
    if (scanf("%s", input) == 1) 
    {
        if (strcmp(input, "en") == 0) 
        {
            lang = 1;
            printf("Language set to English.\n");
        } else if(strcmp(input, "ru") == 0)
        {
            lang = 0;
            printf("Language set to Russian.\n");
        }
    } else {
        printf("This isn't absolute democracy. You can choose only one of this two languages.\n");
    }
    switch (lang)
    {
        case 0: printf("1-й игрок, выберите поле, с которого вы начнёте -> "); break;
        case 1: printf("Player 1, you have to choose board you will start with -> "); break;
    }
    scanf("%d %d", GRow, GCol); printf("\n");
    while (1)
    {
        plr = (plr % 2) ? 1 : 2;
        switch (lang)
        {
            case 0: printf("%d-й игрок, выберите клетку (строку и колонку), которую желаете занять. Координаты вашего поля: %d %d. -> ", plr, GRow, GCol); break;
            case 1: printf("Player %d, choose cell (row and collumn) you wish to occupy. You board located at %d %d coordinates. -> ", plr, GRow, GCol); break;
        }
        scanf("%d %d", LRow, LCol); printf("\n"); LRow--; LCol--;
        if (LRow >= 0 && LRow < 3 && LCol >= 0 && LCol < 3 && board[GRow][GCol][LRow][LCol] == ' ')
        {
            board[GRow][GCol][LRow][LCol] = (plr == 1) ? 'X' : 'O';
            tm[GRow][GCol]++;
            drawboard();
            
        }        
    }
    return 0;
}