#include <iostream>
#include <stdlib.h>
#include <string>

/*
    This is frowned upon by most c++ devs
    Its okay to have a using namespace decl
    but it is much safer to use it in a .cpp file

    Reason:
    if I included this file [#include "tictactoe.h"]
    and I had my own Chris::cout it will conflict with std::cout
*/
//using namespace std;

/*
    Global variables are bad, global variables in header files
    are worse. This will cause linker errors (multiple definitions of 
    same object) if you had >1 .cpp files including this file.

    This is actually a pretty tough topic to explain over txt so read
    these:
        1) constexpr: https://stackoverflow.com/questions/51939692/c-extern-constant-int-for-array-size
        2) extern: https://stackoverflow.com/questions/19929681/c-global-variable-declaration


    But just fyi, this is still bad imo. Why not move these into the class
    as variables? Make them const static so you can use them in your array
    decl --> char grid[LEN][LEN];
*/
//const int NUM_PLAYERS = 2;
//const int LEN = 3;
//const char playerMark[] = {'*', 'x'};
constexpr int NUM_PLAYERS = 2;
constexpr int LEN = 3;
extern const char playerMark[];


//Excuse the formatting, my IDE does this automatically
class TicTacToe
{
//private:
    ///* You could have done this instead*/
    //static const int LEN;

private:
    char grid[LEN][LEN];
    bool player;
    //I frown on this
    //Each line should only have 1 consistent type, since playerNames is array and notifications is not
    std::string playerNames[NUM_PLAYERS], notifications;
    //This is fine but some devs may not like this
    int plays, lastLocation;

public:
    TicTacToe();
    void playGame();
    void printGrid();
    void play(bool player_, int loc_);
    bool continueGame();
};