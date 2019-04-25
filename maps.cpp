#include <iostream>

using namespace std;

int main() {
  unsigned int map_board[3][3][3];
  map_board[0][0][0] = 18;
  map_board[1][0][0] = 23;
  map_board[2][0][0] = 24;

  map_board[0][1][0] = 19;
  map_board[1][1][0] = 22;
  map_board[2][1][0] = 25;

  map_board[0][2][0] = 20;
  map_board[1][2][0] = 21;
  map_board[2][2][0] = 26;


  map_board[0][0][1] = 17;
  map_board[1][0][1] = 12;
  map_board[2][0][1] = 11;

  map_board[0][1][1] = 16;
  map_board[1][1][1] = 13;
  map_board[2][1][1] = 10;

  map_board[0][2][1] = 15;
  map_board[1][2][1] = 14;
  map_board[2][2][1] = 9;


  map_board[0][0][2] = 0;
  map_board[1][0][2] = 5;
  map_board[2][0][2] = 6;

  map_board[0][1][2] = 1;
  map_board[1][1][2] = 4;
  map_board[2][1][2] = 7;

  map_board[0][2][2] = 2;
  map_board[1][2][2] = 3;
  map_board[2][2][2] = 8;
  cout << "Board: " << "\n";
  for (unsigned char z = 0; z <= 2; z++) {
      for (unsigned char y = 0; y <= 2 ; y++) {
          for (unsigned char x = 0; x <= 2; x++ ) {
              cout << map_board[x][y][z] << "\t";
          }
          cout << "\n";
      }
      cout << "\n\n";
  }
  cout << "\n";
}
