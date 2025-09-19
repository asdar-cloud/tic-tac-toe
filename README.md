# Ultimate tic tac toe
## Instalation
```bash
git clone https://github.com/asdar-cloud/tic-tac-toe
```
## Usage
After instalation you need to enter into project directory
```bash
cd tic-tac-toe
```
Then you can just launch compiled file
```bash
./tic-tac-toe # for Linux operating system
```

## Rules
The Ultimate Tic-Tac-Toe rules are fairly simple. The game consists of a large 3×3 grid. Within each cell or big square there is a small square with a smaller 3×3 Tic-Tac-Toe board. Just like the original Tic-Tac-Toe game there are two players, X and O. 
The goal of Ultimate Tic Tac Toe is to win three small boards in a row (horizontally, vertically, or diagonally) on the large board. Basically you are playing 10 games of tic-tac-toe all at once. That means you have to really use some strategy and think ahead. 
The first player starts by marking any cell in any of the 9 smaller boards with their X or O.

The opponent’s previous move determines each player’s next move. The position of the move in the small board determines which small board the opponent must play in for their next move. For example, if Player X places their mark in the top right cell of a small board, Player O must play in the top right small board. If that small board is already won or full, the player can choose any cell in any of the remaining small boards.
Winning a Small Board:  A player wins a small board just like in the traditional game by getting three in a row horizontally, vertically, or diagonally within that small board. When a small board is won, it is marked as won by that player by writing a large X or O over the top of it.

Winning the Whole Game:  The game is won by the first player to win three small boards in a row horizontally, vertically, or diagonally on the large board.
Tied Game: If all small boards are filled and no player has won three in a row, the game is a draw. We used to call it Cats and draw a big C cross out tic-tac-toe boards as kids. I only just learned why.  Cats cannot catch their own tail, just like nobody can win a tied game. Also Cat is Tac spelled backwards. Cats scratch and it is a “scratch” game. 
