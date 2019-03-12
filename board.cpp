//#ifndef BOARD_H
//#define BOARD_H

#include <random>
#include <iostream>

using namespace std;

unsigned int board[3][3][3];

unsigned char moveOnce( unsigned char x, unsigned char y, unsigned char z, bool h, bool v, bool hv, bool vv, bool noMerge );

bool moveUp();
bool moveLeft();
bool moveDown();
bool moveRight();
bool moveFront();
bool moveBack();

unsigned char getStatus();

unsigned int getLargestTile();

bool isCoordValid( unsigned char x, unsigned char y, unsigned char z );

/* moveOnce
   moves a tile in a direction by a tile, and returns 1 if
   moved to a empty space, 2 if merged with another tile, 0 if not
   moved at all.

   if noMerge is true, the function refuses to join tiles.
*/
unsigned char moveOnce( unsigned char x, unsigned char y, unsigned char z, bool h, bool v, bool d, bool hv, bool vv, bool dv, bool noMerge ) {
	unsigned char tx = x, ty = y, tz = z;
	if ( h ) {
		if ( hv ) tx += 1;
		else tx -= 1;
	}
	if ( v ) {
		if ( vv	) ty += 1;
		else ty -= 1;
	}
    if ( d ) {
        if ( dv ) tz += 1;
        else tz -= 1;
    }

	if ( !isCoordValid( x, y, z ) || !isCoordValid( tx, ty, tz ) ) // illegal tile
		return 0;
	else if ( board[x][y][z] == 0 ) return 0; // empty tile
	else if ( board[tx][ty][tz] == 0 ) { // the target tile is empty
		board[tx][ty][tz] = board[x][y][z];
		board[x][y][z] = 0;
		return 1; // done!
	} else if ( !noMerge && board[tx][ty][tz] == board[x][y][z] ) { // the target tile can be merged
		board[tx][ty][tz] = 2 * board[tx][ty][tz];
		board[x][y][z] = 0;
		return 2; //done!
	}
	return 0;
}

/* moveVerticallyOnce, moveHorizontallyOnce
   Wrappers of moveOnce() for convenience.
*/
#define moveVerticallyOnce( x, y, z, dir, noMerge ) moveOnce( x, y, z, false, true, false, false, dir, false, noMerge )
#define moveHorizontallyOnce( x, y, z, dir, noMerge ) moveOnce( x, y, z, true, false, false, dir, false, false, noMerge )
#define moveDepthwiseOnce( x, y, z, dir, noMerge ) moveOnce( x, y, z, false, false, true, false, false, dir, noMerge )

/* moveUp, moveLeft, moveDown, moveRight, moveFront, moveBack
   move everything to a direction, returns true if
   any tile is moved.
*/

bool moveUp() {
	unsigned char x, y, z, ly, lyMargin, result = 0;
	bool moved = false;
	bool noMerge = false;
    for ( z = 0; z <= 2; z++ ) {
        // now we are at a new page
        for ( x = 0; x <= 2; x++ ) {
    		// now we are at a new col
    		lyMargin = 0; // reset the margin
    		for ( y = 1; y <= 2; y++ ) {
    			// now we are at a new row
    			noMerge = false; // reset the noMerge flag
    			for ( ly = y; ly > lyMargin; ly-- ) {
    				result = moveVerticallyOnce( x, ly, z, false, noMerge );
    				if ( result )
    					moved = true;
    				if ( result == 2 ) {
    					noMerge = true;
    					lyMargin = ly;
    				}
    				if ( result == 0 ) break; // move complete
    			}
    		}
    	}
    }
    return moved;
}

bool moveLeft() {
	unsigned char x, y, z, lx, lxMargin, result = 0;
	bool moved = false;
	bool noMerge = false;
    for ( z = 0; z <= 2; z ++ ) {
    	for ( y = 0; y <= 2; y++ ) {
    		lxMargin = 0;
    		for ( x = 1; x <= 2; x++ ) {
    			noMerge = false;
    			for ( lx = x; lx > lxMargin; lx-- ) {
    				result = moveHorizontallyOnce( lx, y, z, false, noMerge );
    				if ( result )
    					moved = true;
    				if ( result == 2 ) {
    					noMerge = true;
    					lxMargin = lx;
    				}
    				if ( result == 0 ) break; // move complete
    			}
    		}
    	}
    }
	return moved;
}

bool moveDown() {
	unsigned char x, y, z, ly, lyMargin, result = 0;
	bool moved = false;
	bool noMerge = false;
    for (z = 0; z <= 2; z++ ) {
    	for ( x = 0; x <= 2; x++ ) {
    		lyMargin = 2;
    		for ( y = 2; y >= 0; y-- ) {
    			noMerge = false;
    			for ( ly = y; ly < lyMargin; ly++ ) {
    				result = moveVerticallyOnce( x, ly, z, true, noMerge );
    				if ( result )
    					moved = true;
    				if ( result == 2 ) {
    					noMerge = true;
    					lyMargin = ly;
    				}
    				if ( result == 0 ) break;
    			}
    			if ( y == 0 ) break; // fix the mind-bogging infinite loop
    		}
    	}
    }
	return moved;
}

bool moveRight() {
	unsigned char x, y, z, lx, lxMargin, result = 0;
	bool moved = false;
	bool noMerge = false;
    for ( z = 0; z <= 2; z++ ) {
    	for ( y = 0; y <= 2; y++ ) {
    		lxMargin = 2;
    		for ( x = 2; x >= 0; x-- ) {
    			noMerge = false;
    			for ( lx = x; lx < lxMargin; lx++ ) {
    				result = moveHorizontallyOnce( lx, y, z, true, noMerge );
    				if ( result )
    					moved = true;
    				if ( result == 2 ) {
    					noMerge = true;
    					lxMargin = lx;
    				}
    				if ( result == 0 ) break; // move complete
    			}
    			if ( x == 0 ) break;
    		}
    	}
    }
	return moved;
}

bool moveFront() {
	unsigned char x, y, z, lz, lzMargin, result = 0;
	bool moved = false;
	bool noMerge = false;
    for ( y = 0; y <= 2; y++ ) {
        // now we are at a new row
        for ( x = 0; x <= 2; x++ ) {
    		// now we are at a new col
    		lzMargin = 0; // reset the margin
    		for ( z = 1; z <= 2; z++ ) {
    			// now we are at a new page
    			noMerge = false; // reset the noMerge flag
    			for ( lz = z; lz > lzMargin; lz-- ) {
    				result = moveDepthwiseOnce( x, y, lz, false, noMerge );
    				if ( result )
    					moved = true;
    				if ( result == 2 ) {
    					noMerge = true;
    					lzMargin = lz;
    				}
    				if ( result == 0 ) break; // move complete
    			}
    		}
    	}
    }
    return moved;
}

bool moveBack() {
    unsigned char x, y, z, lz, lzMargin, result = 0;
	bool moved = false;
	bool noMerge = false;
    for ( y = 0; y <= 2; y++ ) {
        // now we are at a new row
        for ( x = 0; x <= 2; x++ ) {
    		// now we are at a new col
    		lzMargin = 2; // reset the margin
    		for ( z = 2; z >= 0; z-- ) {
    			// now we are at a new page
    			noMerge = false; // reset the noMerge flag
    			for ( lz = z; lz < lzMargin; lz++ ) {
    				result = moveDepthwiseOnce( x, y, lz, true, noMerge );
    				if ( result )
    					moved = true;
    				if ( result == 2 ) {
    					noMerge = true;
    					lzMargin = lz;
    				}
    				if ( result == 0 ) break; // move complete
    			}
                if ( z == 0 ) break;
    		}
    	}
    }
    return moved;
}

unsigned char getStatus() {
	bool moveable = false;
	unsigned char x, y, z;
    for ( z = 0; z<= 2; z++ ) {
    	for ( y = 0; y <= 2; y++ ) {
    		for ( x = 0; x <= 2; x++ ) {
    			if ( board[x][y][z] == 0 ) { // vacant tile
    				return 0; // board not full
    			}
    			// let's check if the player can move further
    			if ( x <= 1 ) {
    				if ( board[x][y][z] == board[x+1][y][z] )
    					moveable = true;
    			}
    			if ( y <= 1 ) {
    				if ( board[x][y][z] == board[x][y+1][z] )
    					moveable = true;
    			}
                if ( z <= 1 ) {
                    if ( board[x][y][z] == board[x][y][z+1] )
    					moveable = true;
                }
    		}
    	}
    }
	// board full
	if ( moveable ) return 1; // board full, but still moveable
	else return 2; // game over!
}

bool isCoordValid( unsigned char x, unsigned char y, unsigned char z ) {
	return x <= 2 && y <= 2 && z <= 2;
}

void initializeBoard() {
    for (unsigned char z = 0; z <= 2; z++) {
        for (unsigned char y = 0; y <= 2 ; y++) {
            for (unsigned char x = 0; x <= 2; x++ ) {
                board[x][y][z] = 0;
            }
        }
    }
}

void printBoard() {
    cout << "Board: " << "\n";
    for (unsigned char z = 0; z <= 2; z++) {
        for (unsigned char y = 0; y <= 2 ; y++) {
            for (unsigned char x = 0; x <= 2; x++ ) {
                cout << board[x][y][z] << "\t";
            }
            cout << "\n";
        }
        cout << "\n\n";
    }
    cout << "\n";
}

int rng(int upper) {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, upper);
    return dist(mt);
}

void placeNewTile() {
    if ( getStatus() == 0 ) {
        while ( true ) {
            unsigned char x = rng(2);
            unsigned char y = rng(2);
            unsigned char z = rng(2);
            if( board[x][y][z] == 0 ) {
                if ( rng(9) == 0 ) {
                    board[x][y][z] = 4;
                }
                else {
                    board[x][y][z] = 2;
                }
                return;
            }
        }
    }
}

int main() {
    initializeBoard();
    while (getStatus() != 2) {
        placeNewTile();
        printBoard();
        bool validMove = false;
        while (!validMove) {
            char move;
            cin >> move;
            if (move == 'w') {
                validMove = moveUp();
            }
            else if (move == 'a') {
                validMove = moveLeft();
            }
            else if (move == 's') {
                validMove = moveDown();
            }
            else if (move == 'd') {
                validMove = moveRight();
            }
            else if (move == 'q') {
                validMove = moveFront();
            }
            else if (move == 'e') {
                validMove = moveBack();
            }
        }
    }
    printBoard();
    cout << "Game over!";
}

//#endif
