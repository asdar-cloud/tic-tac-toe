#include "bots.h"
#include <time.h>
#include <stdlib.h>

void easy(char board[3][3][3][3], int GRow, int GCol)
{
    srandom(time(NULL));
    int row = random() % 3;
    int col = random() % 3;
    board[GRow][GCol][row][col] = 'O';
}