#include <stdio.h>
#include <string.h>
#include <time.h> 
#include <stdlib.h> 

void easybot(char board[3][3][3][3], int GRow, int GCol, int *LRow, int *LCol); 
void botfield(int *row, int *col); 
void mediumbot(char board[3][3][3][3], int GRow, int GCol, int *LRow, int *LCol);
void hardbot(char board[3][3][3][3], int GRow, int GCol, int *LRow, int *LCol);

void initboard();
void drawboard();
int localwin(int glbrow, int glbcol);
int globalwin();
int setlang();
void setfield(int plr, int *row, int *col);
int setbot();
int gameplay(int GRow, int GCol, int plr);
int botplay(int GRow, int GCol, int plr);
int wincond(int GRow, int GCol);

const int RC = 3; // quantity of rows and columns

int GDraw = 0; // For detecting draw on entire field
char board[3][3][3][3] = {'N'}; // this contain information about board ('O' 'X')
int lang; // This will contain information about chosen language of the game (0 - ru; 1 - en)
int draw[3][3] = {0};
int win[3][3] = {0}; // (0 - none, 1 - X, 2 - O) assigning a default value (0) to localwin means that none of the mini-boards have been won yet
int bot; // This will contain information about chosen version of bot
int wincon[3][3] = {0}; // this will contain information about victoryy condition on the local board
int main()
{
    int GRow = -1, GCol = -1, plr = 1;
    initboard();
    drawboard();
    lang = setlang();
    bot = setbot(); printf("\n");
    setfield(plr, &GRow, &GCol);
    if (bot == 0) gameplay(GRow, GCol, plr);
    else botplay(GRow, GCol, plr);
    return 0;
}

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
   for (int globalrow = 0; globalrow < 3; globalrow++)                                    //-
   {                                                                                      // |
    switch (globalrow)                                                                    // |
    {                                                                                     // |
        case 1: case 2: printf("=========================================\n");     // |
    }                                                                                      //  >  drawing global board
    for (int localrow = 0; localrow < 5; localrow++)                                      // |
    {                                                                                     // |
        for (int globalcol = 0; globalcol < 3; globalcol++)                               // |
        {                                                                                 // |
            if (globalcol != 0)                                                           //-
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
    return 1;
}

void setfield(int plr, int *row, int *col) // This function is responsible for selecting the board at the start of the game and in the event of a win or draw.
{
    switch (lang) // asks player to choose field
    {
        case 0: printf("%d-й игрок, выберите поле, в котором будете играть -> ", plr); break;
        case 1: printf("Player %d, you have to choose board you will play in -> ", plr); break;
    }
    scanf("%d %d", row, col); printf("\n"); (*row)--; (*col)--; // assigning player`s choice to row and col
    if (*row >= 0 && *row < 3 && *col >= 0 && *col < 3 && draw[*row][*col] != 1 && win[*row][*col] == 0) // check if this valid values
    {
        return;
    }
    else (*row) = -1;
}

int setbot()
{
    int bot;
    switch(lang) // asks player to choose game format
    {
        case 0: printf("Выберите вариант игры: 0 - два игрока; 1 - бот лёгкой сложности; 2 - бот средней сложности; 3 - бот высокой сложности\n"); break;
        case 1: printf("Choose game mode: 0 - 2p mode; 1 - with easy bot; 2 - with medium bot; 3 - with hard bot\n"); break;
    }
    while (1)
    {
        scanf("%d", &bot);
        if (bot >= 0 && bot <= 3)
        {
            return bot;
        }
        else 
        {
            switch (lang)
            {
                case 0: printf("Вы можете выбрать только один из предложенных вариантов\n"); break;
                case 1: printf("You have to choose only one of existing variants\n"); break;
            }
        }
    }
}

int gameplay(int GRow, int GCol, int plr)
{
    int LRow = -1, LCol = -1, tm[3][3] = {0}; // tm will count how many moves the player has made in each local board (I need it to detect draw on the board)
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
            drawboard();
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
    
}

int botplay(int GRow, int GCol, int plr)
{
    int LRow = -1, LCol = -1, tm[3][3] = {0}; // tm will count how many moves the player has made in each local board (I need it to detect draw on the board)
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
        if (GDraw == 9) 
        {
            switch (lang)
            {
                case 0: printf("Ничья. На этом всё.\n"); break;
                case 1: printf("Draw. That`s all for now.\n"); break;
            }
            return 0;
        }
        if (draw[GRow][GCol] == 1 || win[GRow][GCol] != 0)
        {
            if (plr == 1)
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
            else
            {
                botfield(&GRow, &GCol);
            }
        }
        if (plr == 1)
        {
            switch (lang)
            {
                case 0: printf("Игрок, выберите клетку (строку и колонку), которую желаете занять. Координаты вашего поля: %d %d. -> ", (GRow + 1), (GCol + 1)); break;
                case 1: printf("Player, choose cell (row and collumn) you wish to occupy. You board located at %d %d coordinates. -> ", (GRow + 1), (GCol + 1)); break;
            }
            scanf("%d %d", &LRow, &LCol); printf("\n"); LRow--; LCol--;
        }
        else
        {
            switch (bot)
            {
                case 1: easybot(board, GRow, GCol, &LRow, &LCol); break;
                case 2: mediumbot(board, GRow, GCol, &LRow, &LCol); break;
            }
        }

        if (LRow >= 0 && LRow < 3 && LCol >= 0 && LCol < 3 && board[GRow][GCol][LRow][LCol] == ' ') // check if this step is possible
        {
            board[GRow][GCol][LRow][LCol] = (plr == 1) ? 'X' : 'O';
            tm[GRow][GCol]++;
            if (localwin(GRow, GCol) == 1)
            {
                win[GRow][GCol] = (plr == 1) ? 1 : 2;
            }
            drawboard();
            if (globalwin() == 1)
            {
                switch (lang)
                {
                    case 0: printf("Поздравляю с победой, игрок! \n"); break;
                    case 1: printf("Congratulations, player, you won! \n"); break;
                }
                drawboard();
                return 0;
            }
            if (tm[GRow][GCol] == 9)
            {
                draw[GRow][GCol] = 1;
                GDraw++;
            }

            wincon[GRow][GCol] = wincond(GRow, GCol);

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
}

void easybot(char board[3][3][3][3], int GRow, int GCol, int *LRow, int *LCol) 
{
    srandom(time(0)); 
    while (1)
    {
        int row = rand() % 3;
        int col = rand() % 3;
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[GRow][GCol][row][col] == ' ')
        {
            *LRow = row; *LCol = col;
            switch (lang)
            {
                case 0: printf("А мы вот так! (%d %d)\n\n", row++, col++); break;
                case 1: printf("Here we go (%d %d)\n\n", row++, col++); break;
            }
            return;
        }
    }

}

void mediumbot(char board[3][3][3][3], int GRow, int GCol, int *LRow, int *LCol)
{
    srandom(time(0));   
    while (1)
    {
        switch (wincon[GRow][GCol])
        {
            case 1: *LRow = 0; *LCol = 2; return; break;
            case 2: *LRow = 0; *LCol = 0; return; break;
            case 3: *LRow = 0; *LCol = 1; return; break;

            case 11: *LRow = 1; *LCol = 2; return; break;
            case 12: *LRow = 1; *LCol = 0; return; break;
            case 13: *LRow = 1; *LCol = 1; return; break;

            case 21: *LRow = 2; *LCol = 2; return; break;
            case 22: *LRow = 2; *LCol = 0; return; break;
            case 23: *LRow = 2; *LCol = 1; return; break;

            case 31: *LRow = 2; *LCol = 2; return; break;
            case 32: *LRow = 0; *LCol = 0; return; break;
            case 33: *LRow = 1; *LCol = 1; return; break;

            case 41: *LRow = 0; *LCol = 2; return; break;
            case 42: *LRow = 2; *LCol = 0; return; break;
            case 43: *LRow = 1; *LCol = 1; return; break;

            case 51: *LRow = 2; *LCol = 0; return; break;
            case 52: *LRow = 0; *LCol = 0; return; break;
            case 53: *LRow = 1; *LCol = 0; return; break;

            case 61: *LRow = 2; *LCol = 1; return; break;
            case 62: *LRow = 0; *LCol = 1; return; break;
            case 63: *LRow = 1; *LCol = 1; return; break;

            case 71: *LRow = 2; *LCol = 2; return; break;
            case 72: *LRow = 0; *LCol = 2; return; break;
            case 73: *LRow = 1; *LCol = 2; return; break;
        }
        int row = rand() % 3;
        int col = rand() % 3;
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[GRow][GCol][row][col] == ' ')
        {
            *LRow = row; *LCol = col;
            switch (lang)
            {
                case 0: printf("А мы вот так! (%d %d)\n\n", row++, col++); break;
                case 1: printf("Here we go (%d %d)\n\n", row++, col++); break;
            }
            return;
        }
    }

}

void hardbot(char board[3][3][3][3], int GRow, int GCol, int *LRow, int *LCol)
{
    //TODO
}

void botfield(int *row, int *col)
{
    if (bot == 2 || bot == 3)
    {
        for (int i = 0; i < RC; i++)
        {
            for (int j = 0; j < RC; i++)
            {
                if (wincon[i][j] != 0 && win[i][j] == 0)
                {
                    *row = i; *col = j;
                    return;
                }
            }
        }
    }
    srandom(time(0));
    while (1)
    {
        *row = rand() % 3;
        *col = rand() % 3;
        if (*row >= 0 && *row < 3 && *col >= 0 && *col < 3 && draw[*row][*col] != 1 && win[*row][*col] == 0)
        {
            return;
        }
    }
}

int wincond(int GRow, int GCol)
{
    if (board[GRow][GCol][0][0] == 'O' && board[GRow][GCol][0][1] == 'O' && board[GRow][GCol][0][2] == 'N') // O O -
    {
        return 1;
    }
    else if (board[GRow][GCol][0][0] == 'N' && board[GRow][GCol][0][1] == 'O' && board[GRow][GCol][0][2] == 'O') // - O O
    {
        return 2;
    }
    else if (board[GRow][GCol][0][0] == 'O' && board[GRow][GCol][0][1] == 'N' && board[GRow][GCol][0][2] == 'O') // O - O
    {
        return 3;
    }
    // second row
    else if (board[GRow][GCol][1][0] == 'O' && board[GRow][GCol][1][1] == 'O' && board[GRow][GCol][1][2] == 'N')
    {
        return 11;
    }
    else if (board[GRow][GCol][1][0] == 'N' && board[GRow][GCol][1][1] == 'O' && board[GRow][GCol][1][2] == 'O')
    {
        return 12;
    }
    else if (board[GRow][GCol][1][0] == 'O' && board[GRow][GCol][1][1] == 'N' && board[GRow][GCol][1][2] == 'O')
    {
        return 13;
    }
    //third row
    else if (board[GRow][GCol][2][0] == 'O' && board[GRow][GCol][2][1] == 'O' && board[GRow][GCol][2][2] == 'N')
    {
        return 21;
    }
    else if (board[GRow][GCol][2][0] == 'N' && board[GRow][GCol][2][1] == 'O' && board[GRow][GCol][2][2] == 'O')
    {
        return 22;
    }
    else if (board[GRow][GCol][2][0] == 'O' && board[GRow][GCol][2][1] == 'N' && board[GRow][GCol][2][2] == 'O')
    {
        return 23;
    }
    // first diagonal
    else if (board[GRow][GCol][0][0] == 'O' && board[GRow][GCol][1][1] == 'O' && board[GRow][GCol][2][2] == 'N')
    {
        return 31;
    }
    else if (board[GRow][GCol][0][0] == 'N' && board[GRow][GCol][1][1] == 'O' && board[GRow][GCol][2][2] == 'O')
    {
        return 32;
    }
    else if (board[GRow][GCol][0][0] == 'O' && board[GRow][GCol][1][1] == 'N' && board[GRow][GCol][2][2] == 'O')
    {
        return 33;
    }
    // second diagonal
    else if (board[GRow][GCol][2][0] == 'O' && board[GRow][GCol][1][1] == 'O' && board[GRow][GCol][0][2] == 'N')
    {
        return 41;
    }
    else if (board[GRow][GCol][2][0] == 'N' && board[GRow][GCol][1][1] == 'O' && board[GRow][GCol][0][2] == 'O')
    {
        return 42;
    }
    else if (board[GRow][GCol][2][0] == 'O' && board[GRow][GCol][1][1] == 'N' && board[GRow][GCol][0][2] == 'O')
    {
        return 43;
    }
    // first column
    else if (board[GRow][GCol][0][0] == 'O' && board[GRow][GCol][1][0] == 'O' && board[GRow][GCol][2][0] == 'N')
    {
        return 51;
    }
    else if (board[GRow][GCol][0][0] == 'N' && board[GRow][GCol][1][0] == 'O' && board[GRow][GCol][2][0] == 'O')
    {
        return 52;
    }
    else if (board[GRow][GCol][0][0] == 'O' && board[GRow][GCol][1][0] == 'N' && board[GRow][GCol][2][0] == 'O')
    {
        return 53;
    }
    // seconf column
    else if (board[GRow][GCol][0][1] == 'O' && board[GRow][GCol][1][1] == 'O' && board[GRow][GCol][2][1] == 'N')
    {
        return 61;
    }
    else if (board[GRow][GCol][0][1] == 'N' && board[GRow][GCol][1][1] == 'O' && board[GRow][GCol][2][1] == 'O')
    {
        return 62;
    }
    else if (board[GRow][GCol][0][1] == 'O' && board[GRow][GCol][1][1] == 'N' && board[GRow][GCol][2][1] == 'O')
    {
        return 63;
    }
    // third column
    else if (board[GRow][GCol][0][2] == 'O' && board[GRow][GCol][1][2] == 'O' && board[GRow][GCol][2][2] == 'N')
    {
        return 71;
    }
    else if (board[GRow][GCol][0][2] == 'N' && board[GRow][GCol][1][2] == 'O' && board[GRow][GCol][2][2] == 'O')
    {
        return 72;
    }
    else if (board[GRow][GCol][0][2] == 'O' && board[GRow][GCol][1][2] == 'N' && board[GRow][GCol][2][2] == 'O')
    {
        return 73;
    }
    return 0;
}
