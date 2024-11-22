#include <stdio.h>
// Made by Mr.Quantum (Darshan Patel)

// What feature I wanna add : - One block contains names, time,Who win,etc
// input every time a game is played
// after certain number of games history delete the history
int entry_Number = 1;
struct entry
{
  char playerNames[2][20];
  char whoWins[20];
  // int player1_Score;
  // int player2_Score;
};

int main()
{
  // int entry_Number = 1;

  struct entry game[50]; // This is array of structures, Structure variables, I am setting maximum history for 50 games

   // entry_Number++ used to inc it by 1 for next entry
  return 0;
}