#include "tictactoe.h"

const char playerMark[] = {'*', 'x'};


//Remember what I said about `using namespace` in the header files?
//This is a good place to place it instead
using namespace std;

TicTacToe::TicTacToe()
{
    // Initialise grid
    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            grid[i][j] = '0' + ((j + 1) + LEN * i);
        }
    }

    // Initialise other variables
    player = false;
    notifications = "";
    plays = 0;
    char tmp[11];

    // Welcome message
    system("clear");
    cout << "Welcome. The younger player starts first." << endl;

    // First player
    for (int i = 0; i < NUM_PLAYERS; i++) {
        cout << "Enter Player " << i+1 << "'s name: ";
        scanf("%10s", tmp);
        playerNames[i] = tmp;
        cout << "Hi " + playerNames[0] + ".\n" << endl;
    }

    // Wait until both players are ready
    cout << "Press ENTER to start playing" << endl;
    system("read");
}

void TicTacToe::playGame()
{
    // Play game for as long as nobody wins
    do {
        char tmp[2];

        // Read inputsƒ
        system("clear");
        cout << notifications << endl;
        cout << "[" << playerMark[0] << "] - " << playerNames[0] << endl;
        cout << "[" << playerMark[1] << "] - " << playerNames[1] + "\n" << endl;

        // Print grid
        this->printGrid();

        // Instructions and input
        cout << playerNames[player] + "\'s turn. Select cell: ";
        scanf("%1s", tmp);
        lastLocation = tmp[0] - 48;

        // Update arrays
        this->play(player, lastLocation);

    } while (continueGame() && plays < 9);

    // Once game stops
    if (plays == 9 && continueGame()) {
        // Nobody wins
        system("clear");
        this->printGrid();
        cout << "Nobody won. Game ends. Bye!" << endl;
    } else {
        // Unswitch winner
        player = !player;

        // Output winning message
        system("clear");
        cout << "We have a winner." << endl;

        // Print board
        this->printGrid();

        // Congratulate
        cout << "Congrats " << playerNames[player] << "!" << endl;
    }
}

void TicTacToe::printGrid()
{
    cout << "-------" << endl;
    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            cout << "|" << grid[i][j];
        }
        cout << "|" << endl;
    }
    cout << "-------\n" << endl;
}

void TicTacToe::play(bool player_, int loc_)
{
    //I see this same line inside TicTacToe::continueGame()
    //Maybe you can refactor
    int i = (loc_-1) / LEN;
    int j = ((loc_ % LEN) + 2) % LEN;
    
    // Check validity
    if (!(loc_ >= 1 && loc_ <= 9)) {
        notifications = "Choose any number between 1 to 9 inclusive\n";
    } else if (grid[i][j] == 'o' || grid[i][j] == 'x') {
        notifications = "That cell has already been marked!\n";
    } else {
        grid[i][j] = playerMark[player_];
        notifications = "";
        // Switch turn
        player = !player;
        ++plays;
    }
}

bool TicTacToe::continueGame()
{
    //I see this same line inside TicTacToe::play
    //Maybe you can refactor
    int i = (lastLocation-1) / LEN;
    int j = ((lastLocation % LEN) + 2) % LEN;
    char c = grid[i][j];
    int countHorizontal, countVertical, countDiagonalLR, countDiagonalRL;

    countHorizontal = countVertical = countDiagonalLR = countDiagonalRL = 0;
    for (int i = 0; i < LEN; i++) {   

        // Diagonal counting
        if (c == grid[i][i]) { countDiagonalLR++; }
        if (c == grid[i][LEN-i-1]) { countDiagonalRL++; }
        if (i == LEN-1) { 
            if (countDiagonalRL == LEN || countDiagonalLR == LEN) {
                // ++plays;
                return false;
            }
        }

        // Horizontal and vertical counting
        for (int j = 0; j < LEN; j++) {
            if (c == grid[i][j]) { countHorizontal++; }
            if (c == grid[j][i]) { countVertical++; }
        }
        if (countHorizontal == LEN || countVertical == LEN) {
            // ++plays;
            return false;
        } else {
            countHorizontal = countVertical = 0;
        }
    }

    return true;
}