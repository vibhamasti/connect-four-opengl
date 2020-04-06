//
//  board.h
//  Connect Four
//


#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

// Validity enum values
enum validity {
    col_full,
    valid
};


static const int ROWS=6, COLUMNS=7;
static char BOARD[ROWS][COLUMNS] = {'e'};

#define BOARD_WIDTH 700
#define BOARD_HEIGHT 700
#define APPARENT_BOARD_HEIGHT 600

// OpenGL headers
void drawCircle(GLfloat, GLfloat, GLfloat, GLint, GLchar);

// Draws rectangle back of the board
void drawBoardBack(GLfloat [], GLint, GLfloat []);

// Callback function for key presses
void keyCallback(GLFWwindow *, int, int, int, int);


GLchar getBoard(int, int);  // Returns char in pos (x,y)
int getCol(void);           // Returns current column number
char getPlayer(void);       // Returns current player


int inp_validity(int);      // Checks validity of input
int update(int, int);       // Updates board square to O or X
int empty_row(int);         // Returns the first empty row
void reset_board(void);     // Resets board to empty
void print_board(void);     // Prints the board

void check(void);           // Checks for 4
int game(void);             // Returns if game is still in play

#endif

