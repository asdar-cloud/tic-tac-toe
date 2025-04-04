#include <stdio.h>
#include <string.h>

/*
1) Board initialization (initboard)
2) Drawing board (drawboard)
3) Separate functions for check global and local wins
4) Main game pocess, including moves and victory checks
*/
int GDraw = 0; // For detecting draw on entire field
char board[3][3][3][3]; // this contain information about board
int lang; // This will contain information about chosen language of the game (0 - ru; 1 - en)
int draw[3][3] = {0};
int win[3][3] = {0}; // assigning a default value (none, 1 - X, 2 - O) to localwin means that none of the mini-boards have been won yet

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
            if (win[globalrow][globalcol] == 0) // drawing local boards
            {
                if (localrow % 2 == 0) {  // rows with symbols 0, 2, 4
                    lclrow = localrow / 2;
                    printf(" %c | %c | %c  ",
                        board[globalrow][globalcol][lclrow][0],
                        board[globalrow][globalcol][lclrow][1],
                        board[globalrow][globalcol][lclrow][2]);
                } else {  // Separator lines (1, 3)
                    printf("---+---+--- ");
                }
            }
            else if (win[globalrow][globalcol] == 1) // printing 'X' instead of local board in case of victory X
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
            else if (win[globalrow][globalcol] == 2)  // printing 'O' instead of local board in case of victory 0
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

int localwin(int glbrow, int glbcol) // check if there's a victory in a small field
{
    for (int row = 0; row < 3; row++) // check if there horizontal wins
    { 
        if (board[glbrow][glbcol][row][0] == board[glbrow][glbcol][row][1] && board[glbrow][glbcol][row][0] == board[glbrow][glbcol][row][2] && board[glbrow][glbcol][row][0] != ' ')
            return 1;
    }
    for (int col = 0; col < 3; col++) // check if there vertical wins
    {
        if (board[glbrow][glbcol][0][col] == board[glbrow][glbcol][1][col] && board[glbrow][glbcol][0][col] == board[glbrow][glbcol][2][col] && board[glbrow][glbcol][0][col] != ' ')
            return 1;
    }
    // check if there diagonal wins
    if (board[glbrow][glbcol][0][0] == board[glbrow][glbcol][1][1] && board[glbrow][glbcol][0][0] == board[glbrow][glbcol][2][2] && board[glbrow][glbcol][0][0] != ' ')
        return 1;
    if (board[glbrow][glbcol][0][2] == board[glbrow][glbcol][1][1] && board[glbrow][glbcol][0][2] == board[glbrow][glbcol][2][0] && board[glbrow][glbcol][0][2] != ' ')
        return 1;
    return 0;
}

int globalwin() // check if there's a victory in the game
{
    for (int row = 0; row < 3; row++) // check if there horizontal wins
    {
        if (win[row][0] == win[row][1] && win[row][0] == win[row][2] && win[row][0] != 0)
            return 1;
    }
    for (int col = 0; col < 3; col++) // check if there vertical wins
    {
        if (win[0][col] == win[1][col] && win[0][col] == win[2][col] && win[0][col] != 0)
            return 1;
    }
    // check if there diagonal wins
    if (win[0][0] == win[1][1] && win[0][0] == win[2][2] && win[0][0] != 0)
        return 1;
    if (win[0][2] == win[1][1] && win[0][2] == win[2][0] && win[0][2] != 0)
        return 1;
    return 0;
}

int setlang() // This function is responsible for selecting the language of the game
{
    char input[3];
    printf("Choose language (en/ru) -> ");
    if (scanf("%2s", input) == 1) 
    {
        if (strcmp(input, "en") == 0) 
        {
            printf("Language set to English.\n");
            return 1;
        } 
        else if(strcmp(input, "ru") == 0)
        {
            printf("Language set to Russian.\n");
            return 0;
        }
        else 
        {
            printf("This isn't absolute democracy. You can choose only one of this two languages.\n");
            return setlang();
        }
    } 
    
}

void setfield(int plr, int *row, int *col) // This function is responsible for selecting the board at the start of the game and in the event of a win or draw.
{
    switch (lang)
    {
        case 0: printf("%d-й игрок, выберите поле, в котором будете играть -> ", plr); break;
        case 1: printf("Player %d, you have to choose board you will play in -> ", plr); break;
    }
    scanf("%d %d", row, col); printf("\n"); (*row)--; (*col)--;
    if (*row >= 0 && *row < 3 && *col >= 0 && *col < 3 && draw[*row][*col] != 1 && win[*row][*col] == 0)
    {
        return;
    }
    else (*row) = -1;
}

int main()
{
    int GRow = -1, GCol = -1, LRow = -1, LCol = -1, plr = 1, tm[3][3] = {0}; // tm will count how many moves the player has made in each local board (I need it to detect draw on the board)
    initboard();
    drawboard();
    lang = setlang();
    setfield(plr, &GRow, &GCol);
    while (GRow == -1) 
    {
            switch (lang)
            {
                case 0: printf("Не выйдет. Попробуйте снова \n"); break;
                case 1: printf("You can't do that. Try again \n"); break;
            }
            setfield(plr, &GRow, &GCol);
    }
    while (1)
    {
        plr = (plr % 2) ? 1 : 2;
        if (GDraw == 9) return 0;
        if (draw[GRow][GCol] == 1 || win[GRow][GCol] != 0)
        {
            while (1)
            {
                setfield(plr, &GRow, &GCol);
                if (GRow == -1)
                {
                    switch (lang)
                    {
                        case 0: printf("Не выйдет. Попробуйте снова. \n"); break;
                        case 1: printf("You can't do that. Try again. \n"); break;
                    }
                    setfield(plr, &GRow, &GCol);
                }
                else break;
            }
        }
        switch (lang)
        {
            case 0: printf("%d-й игрок, выберите клетку (строку и колонку), которую желаете занять. Координаты вашего поля: %d %d. -> ", plr, (GRow + 1), (GCol + 1)); break;
            case 1: printf("Player %d, choose cell (row and collumn) you wish to occupy. You board located at %d %d coordinates. -> ", plr, (GRow + 1), (GCol + 1)); break;
        }
        scanf("%d %d", &LRow, &LCol); printf("\n"); LRow--; LCol--;
        if (LRow >= 0 && LRow < 3 && LCol >= 0 && LCol < 3 && board[GRow][GCol][LRow][LCol] == ' ') // check if this step is possible
        {
            board[GRow][GCol][LRow][LCol] = (plr == 1) ? 'X' : 'O';
            tm[GRow][GCol]++;
            if (localwin(GRow, GCol) == 1)
            {
                win[GRow][GCol] = (plr == 1) ? 1 : 2;
            }
            if (globalwin() == 1)
            {
                switch (lang)
                {
                    case 0: printf("Поздравляю с победой, %d-й игрок! \n", plr); break;
                    case 1: printf("Congratulations, player number %d, you won! \n", plr); break;
                }
                drawboard();
                return 0;
            }
            if (tm[GRow][GCol] == 9)
            {
                draw[GRow][GCol] = 1;
                GDraw++;
            }
            drawboard();
            GRow = LRow; GCol = LCol; plr++;
        }
        else 
        {
            switch (lang)
            {
                case 0: printf("Этот ход невозможен. Попробуйте ещё раз. \n"); break;
                case 1: printf("This is impossible. Try again. \n"); break;
            }
            while (getchar() != '\n'); // Clearing the buffer
        }
    }
    return 0;
}