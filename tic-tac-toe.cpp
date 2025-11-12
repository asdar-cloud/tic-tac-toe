#include <cstring>
#include <random>

const int RC{3}; // quantity of rows and columns
char board[3][3][3][3] = {' '}; // this contain information about board ('O' 'X')
int draw[3][3] = {0}; // this will contain information about draw existance in some field
int GDraw = 0; // For detecting draw on entire field
int lang{}; // This will contain information about chosen language of the game (0 - ru; 1 - en)
int win[3][3] = {0}; // (0 - none, 1 - X, 2 - O) assigning a default value (0) to localwin means that none of the mini-boards have been won yet


// function's prototypes
void initboard();
void drawboard();
int setlang();
int setbot();
void setfield(int plr, int *row, int *col);
int localwin(int glbrow, int glbcol);
int globalwin();
int gameplay(int GRow, int GCol, int plr, int bot);
void setcell(int GRow, int GCol, int plr, int *LRow, int *LCol);
void ebot(int GRow, int GCol, int *LRow, int *LCol);
void mbot(int GRow, int GCol, int *LRow, int *LCol);
void hbot(int GRow, int GCol, int *LRow, int *LCol);
int randcell();
void winpos(int *lrow, int *lcol, int GRow, int GCol);


int main()
{
    int GRow{-1}, GCol{-1}, plr{1};
    int bot{}; // This will contain information about chosen version of bot
    initboard();
    drawboard();
    lang = setlang();
    bot = setbot();
    gameplay(GRow, GCol, plr, bot);
    return 0;
}


void initboard() // asigning standard value (space) for every parts of field
{
    for (int GRow{0}; GRow < 3; GRow++)
    {
        for (int GCol{0}; GCol < 3; GCol++)
        {
            for (int LRow{0}; LRow < 3; LRow++)
            {
                for (int LCol{0}; LCol < 3; LCol++)
                {
                    board[GRow][GCol][LRow][LCol] = ' ';
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
        case 1: case 2: printf("=========================================\n");            // |
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

int setlang()
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

int setbot()
{
    int bot{};
    switch(lang)
    {
        case 0: printf("Выберите вариант игры: 0 - два игрока; 1 - бот лёгкой сложности; 2 - бот средней сложности; 3 - бот высокой сложности -> "); break;
        case 1: printf("Choose game mode: 0 - 2p mode; 1 - with easy bot; 2 - with medium bot; 3 - with hard bot -> "); break;
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

void setfield(int plr, int *row, int *col) // This function is responsible for selecting the board at the start of the game and in the event of a win or draw.
{
    switch (lang) // asks player to choose field
    {
        case 0: printf("%d-й игрок, выберите поле, в котором будете играть -> ", plr); break;
        case 1: printf("Player %d, you have to choose board you will play in -> ", plr); break;
    }
    scanf("%d %d", row, col); (*row)--; (*col)--; // assigning player`s choice to row and col
    if (*row >= 0 && *row < 3 && *col >= 0 && *col < 3 && draw[*row][*col] != 1 && win[*row][*col] == 0) // check if this valid values
    {
        return;
    }
    else (*row) = -1;
    return;
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

int gameplay(int GRow, int GCol, int plr, int bot)
{
    int LRow = -1, LCol = -1, tm[3][3] = {0}; // tm will count how many moves the player has made in each local board (I need it to detect draw on the board)
    while (1)
    {
        plr = (plr % 2) ? 1 : 2;
        if (GDraw == 9) 
        {
            switch (lang)
            {
                case 0: printf("Ничья! Какая досада (или нет?)\n"); break;
                case 1: printf("Draw! What a shame (or not?)\n"); break;
            }
            return 0;
        }
        if (GRow == -1 || draw[GRow][GCol] == 1 || win[GRow][GCol] != 0)
        {
            if (bot == 0 || (bot != 0 && plr == 1))
            {
                setfield(plr, &GRow, &GCol);
                while (GRow == -1)
                {
                    switch (lang)
                    {
                        case 0: printf("Не выйдет. Попробуйте снова. \n"); break;
                        case 1: printf("You can't do that. Try again. \n"); break;
                    }
                    setfield(plr, &GRow, &GCol);
                }
            }
            else if (bot != 0 && plr == 2)
            {
                while (1)
                {
                    GRow = randcell(); GCol = randcell();
                    if (draw[GRow][GCol] == 0 && win[GRow][GCol] == 0)
                    {
                        break;
                    }
                }
            }
        }
        if (bot == 0 || (bot != 0 && plr == 1))
        {
            switch (lang)
            {
                case 0: printf("%d-й игрок, выберите клетку (строку и колонку), которую желаете занять. Координаты вашего поля: %d %d. -> ", plr, (GRow + 1), (GCol + 1)); break;
                case 1: printf("Player %d, choose cell (row and collumn) you wish to occupy. You board located at %d %d coordinates. -> ", plr, (GRow + 1), (GCol + 1)); break;
            }
            setcell(GRow, GCol, plr, &LRow, &LCol);
        }
        else if (bot != 0 && plr == 2)
        {
            switch (bot)
            {
                case 1: ebot(GRow, GCol, &LRow, &LCol); break;
                case 2: mbot(GRow, GCol, &LRow, &LCol); break;
                case 3: hbot(GRow, GCol, &LRow, &LCol); break;
            }
        }

        if (localwin(GRow, GCol) == 1)
        {
            win[GRow][GCol] = (plr == 1) ? 1 : 2;
            GDraw++;
        }
        drawboard();

        if (globalwin() == 1)
        {
            if (bot == 0 || (bot != 0 && plr == 1))
            {
                switch (lang)
                {
                    case 0: printf("Поздравляю с победой, %d-й игрок! \n", plr); break;
                    case 1: printf("Congratulations, player number %d, you won! \n", plr); break;
                }
            }
            else if (bot != 0 && plr == 2)
            {
                switch (lang)
                {
                    case 0: printf("Бот: Хехехе. Я умнее тебя, у меня памяти 16 мегабайт :)\n"); break;
                    case 1: printf("Player, you've lost the game, but you always can come back and try again!\n"); break;
                } 
            }    
            return 0;
        }
        tm[GRow][GCol]++;
        if (tm[GRow][GCol] == 9)
        {
            draw[GRow][GCol] = 1;
            GDraw++;
        }
        GRow = LRow; GCol = LCol; plr++;
    }
    
}

void setcell(int GRow, int GCol, int plr, int *LRow, int *LCol)
{
    while (1)
    {
        scanf("%d %d", LRow, LCol); *LRow -= 1; *LCol -= 1;
        if (*LRow >= 0 && *LRow < 3 && *LCol >= 0 && *LCol < 3 && board[GRow][GCol][*LRow][*LCol] == ' ') // check if this step is possible
        {
            board[GRow][GCol][*LRow][*LCol] = (plr == 1) ? 'X' : 'O';
            printf("\n");
            return;
        }
        else 
        {
            switch (lang)
            {
                case 0: printf("Этот ход невозможен. Попробуйте ещё раз. \n"); break;
                case 1: printf("This is impossible. Try again. \n"); break;
            }
        } 
    }
}

// easy bot (working just with random)
void ebot(int GRow, int GCol, int *LRow, int *LCol)
{
    while (1)
    {
        int row = randcell();
        int col = randcell();
        if (board[GRow][GCol][row][col] == ' ')
        {
            *LRow = row; *LCol = col;

            board[GRow][GCol][*LRow][*LCol] = 'O';
            printf("\n");

            switch (lang)
            {
                case 0: printf("А мы вот так! (%d %d)\n\n", row + 1, col + 1); break;
                case 1: printf("Here we go (%d %d)\n\n", row + 1, col + 1); break;
            }
            return;
        }
    }
}

// medium bot (in case of possible win in 1 step, do it to gane victory. If there is not such step, just uses random)
void mbot(int GRow, int GCol, int *LRow, int *LCol)
{
    int row{-1}, col{-1};
    winpos(&row, &col, GRow, GCol);
    if (row == -1)
    {
        ebot(GRow, GCol, &row, &col);
        *LRow = row; *LCol = col;
        return;
    }

    *LRow = row; *LCol = col;
    board[GRow][GCol][*LRow][*LCol] = 'O';
    printf("\n");
    
    switch (lang)
    {
        case 0: printf("А мы вот так! (%d %d)\n\n", row + 1, col + 1); break;
        case 1: printf("Here we go (%d %d)\n\n", row + 1, col + 1); break;
    }
    return;
}

// hard bot ...
void hbot(int GRow, int GCol, int *LRow, int *LCol)
{
    //TODO
}

// function for random generation of cell based on random_device for TRUE random
int randcell() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, 2);
    
    return dist(gen);
}

// function for detecting step, that will bring local win for bot
void winpos(int *lrow, int *lcol, int GRow, int GCol)
{
    int wincount{0};
    int dotzero[2] = {-1};

    // looking for the win position at all rows in the loclal field
    for (int row{0}; row < RC; row++)
    {
        for (int col{0}; col > RC; col++)
        {
            if (board[GRow][GCol][row][col] == 'O')
            {
                wincount++;
            }
            else if (board[GRow][GCol][row][col] == ' ')
            {
                dotzero[0] = row; dotzero[1] = col;
            }
        }
        if (wincount == 2)
        {
            *lrow = dotzero[0]; *lcol = dotzero[1];
            return;
        }
        wincount = 0;
    }

    //looking for the win position at all collumns in the local field
    for (int col{0}; col < RC; col++)
    {
        for (int row{0}; row < RC; row++)
        {
            if (board[GRow][GCol][row][col] == 'O')
            {
                wincount++;
            }
            else if (board[GRow][GCol][row][col] == ' ')
            {
                dotzero[0] = row; dotzero[1] = col;
            }
        }
        if (wincount == 2)
        {
            *lrow = dotzero[0]; *lcol = dotzero[1];
            return;
        }
        wincount = 0;
    }

    // looking for the win position at diagonals
    for (int rc{0}; rc < RC; rc++)
    {
        if (board[GRow][GCol][rc][rc] == 'O')
        {
            wincount++;
        }
        else if (board[GRow][GCol][rc][rc] == ' ')
        {
            dotzero[0] = rc; dotzero[1] = rc;
        }
    }
    if (wincount == 2)
    {
        *lrow = dotzero[0]; *lcol = dotzero[1];
        return;
    }
    for (int rc{3}; rc > 0; rc--)
    {
        if (board[GRow][GCol][rc][rc] == 'O')
        {
            wincount++;
        }
        else if (board[GRow][GCol][rc][rc] == ' ')
        {
            dotzero[0] = rc; dotzero[1] = rc;
        }
    }
    if (wincount == 2)
    {
        *lrow = dotzero[0]; *lcol = dotzero[1];
        return;
    }
}
