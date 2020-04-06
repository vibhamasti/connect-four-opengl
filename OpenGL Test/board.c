//
//  board.c
//  Connect Four
//


#ifndef BOARD_C
#define BOARD_C


#include "board.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int IN_GAME = 1;
static int cur_col = 0;
static int cur_player = 1;


int getCol() {
    return cur_col;
}

char getPlayer() {
    if (cur_player == 1) return 'r';
    else return 'y';
}

GLchar getBoard(int x, int y) {
    return BOARD[y][x];
}

// Callback
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        if (cur_col != 0) {
            --cur_col;
        }
        
    }
    
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        if (cur_col != COLUMNS-1) {
            ++cur_col;
        }
    }
    
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
    
        if (!update(cur_player, cur_col)) return;
        
        if (cur_player == 1) {
            cur_player = 2;
        }
        else {
            cur_player = 1;
        }
        
        check();
        if (!game()) return;
        
        cur_col = 0;
        
    }
}

// Method to draw a circle
void drawCircle(GLfloat abs_x, GLfloat abs_y, GLfloat abs_radius, GLint numberOfSides, GLchar color) {
    GLfloat x, y;

    x = abs_x/(BOARD_WIDTH/2);
    y = abs_y/(BOARD_HEIGHT/2);
    
    
    
    abs_radius *= 0.95;
    GLfloat xRadius, yRadius;
    
    xRadius = abs_radius/(BOARD_WIDTH/2);
    yRadius = abs_radius/(BOARD_HEIGHT/2);
    
    GLint numberOfVertices = numberOfSides + 2;
    
    
    
    GLfloat doublePi = 2.0f * M_PI;
    GLfloat circleVerticesX[numberOfVertices];
    GLfloat circleVerticesY[numberOfVertices];
    
    // Central point of circle
    circleVerticesX[0] = x;
    circleVerticesY[0] = y;
    
    
    // Creating common array
    for (int i=1; i<numberOfVertices; ++i) {
        circleVerticesX[i] = x + (xRadius*cos(i*doublePi/numberOfSides));
        circleVerticesY[i] = y + (yRadius*sin(i*doublePi/numberOfSides));
        
    }
    
    GLfloat allCircleVertices[numberOfVertices*2];
    
    for (int i=0; i<numberOfVertices; ++i) {
        allCircleVertices[i*2] = circleVerticesX[i];
        allCircleVertices[i*2 + 1] = circleVerticesY[i];
    }
    
    // Colours
    
    GLfloat circleColors[3];
    

    switch (color) {
        // Red
        case 'r': {
            circleColors[0] = 1.0f;
            circleColors[1] = 0.0f;
            circleColors[2] = 0.0f;
            break;
        }
            
        // Grey
        case 'e': {
            circleColors[0] = 0.760f;
            circleColors[1] = 0.760f;
            circleColors[2] = 0.760f;
            break;
        }
        
        // Yellow
        case 'y': {
            circleColors[0] = 0.941f;
            circleColors[1] = 0.811f;
            circleColors[2] = 0.058f;
            break;
        }
        default: {
            circleColors[0] = 1.0f;
            circleColors[1] = 1.0f;
            circleColors[2] = 1.0f;
        }
    }
    
    
    
    
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glColor3fv(circleColors);
    
    glVertexPointer(2, GL_FLOAT, 0, allCircleVertices);
    glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
    

    glDisableClientState(GL_VERTEX_ARRAY);
    
}


void drawBoardBack(GLfloat boardVertices[], GLint numberOfVertices, GLfloat boardColours[]) {
    
    // Dealing with vertex array
    glEnableClientState(GL_VERTEX_ARRAY);
    
    // Enable colours
    glEnableClientState(GL_COLOR_ARRAY);
    
    // Axes = 2, stride = 0
    glVertexPointer(2, GL_FLOAT, 0, boardVertices);
    
    //glColor3fv(boardColours);
    glColorPointer(3, GL_FLOAT, 0, boardColours);
    
    // Draw polygon
    glDrawArrays(GL_POLYGON, 0, numberOfVertices);
    
    glDisableClientState(GL_COLOR_ARRAY);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    
    // End board
}


// To check if game in play
int game() {
    return IN_GAME;
}



// Reset the board to empty
void reset_board() {
    for (int i=0; i<ROWS; ++i) {
        for (int j=0; j<COLUMNS; ++j) {
            // 'e' represents empty
            BOARD[i][j] = 'e';
        }
    }

}


// Returns input validity
int inp_validity(int col) {
    if (BOARD[0][col] != 'e') {
        return col_full;
    }

    return valid;
}


// Returns the first empty row of the column (not index)
int empty_row(int col) {
    for (int i=ROWS-1; i>=0; --i) {
        if (BOARD[i][col] == 'e')
            return i;
    }
    return -1;
}

int update(int p, int col) {
    
    if (inp_validity(col) == col_full) return 0;
    
    // Player 1 = r
    if (p == 1) {
        BOARD[empty_row(col)][col] = 'r';
    }
    // Player 2 = y
    else {
        BOARD[empty_row(col)][col] = 'y';
    }
    
    return 1;
    
}

// Check for 4
void check() {
    // Vertical lines of 4
    for (int i=ROWS-1; i>=3; --i) {
        for (int j=0; j<COLUMNS; ++j) {
            if (BOARD[i][j] == 'e') {
                continue;

            }

            if (BOARD[i][j] == BOARD[i-1][j] &&
            BOARD[i-1][j] == BOARD[i-2][j] &&
            BOARD[i-2][j] == BOARD[i-3][j]) {

                IN_GAME = 0;

                if (BOARD[i][j] == 'r') {
                    printf("Player 1 wins!!\n");
                }
                else {
                    printf("Player 2 wins!!\n");
                }
                return;
            }

        }
    } // End of vertical

    // Horizontal lines of 4
    for (int j=COLUMNS-1; j>=3; --j) {
        for (int i=0; i<ROWS; ++i) {
            if (BOARD[i][j] == 'e') {
                continue;

            }

            if (BOARD[i][j] == BOARD[i][j-1] &&
            BOARD[i][j-1] == BOARD[i][j-2] &&
            BOARD[i][j-2] == BOARD[i][j-3]) {

                IN_GAME = 0;

                if (BOARD[i][j] == 'r') {
                    printf("Player 1 wins!!\n");
                }
                else {
                    printf("Player 2 wins!!\n");
                }
                return;
            }

        }
    } // End of horizontal

    // Main diagonal lines of 4
    for (int i=0; i<=ROWS-4; ++i) {
        for (int j=0; j<=COLUMNS-4; ++j) {
            if (BOARD[i][j] == 'e') {
                continue;

            }

            if (BOARD[i][j] == BOARD[i+1][j+1] &&
            BOARD[i+1][j+1] == BOARD[i+2][j+2] &&
            BOARD[i+2][j+2] == BOARD[i+3][j+3]) {

                IN_GAME = 0;

                if (BOARD[i][j] == 'r') {
                    printf("Player 1 wins!!\n");
                }
                else {
                    printf("Player 2 wins!!\n");
                }
                return;
            }

        }
    } // End of main diagonal

    // Secondary diagonal lines of 4
    for (int i=0; i<=ROWS-4; ++i) {
        for (int j=COLUMNS-1; j>=3; --j) {
            if (BOARD[i][j] == 'e') {
                continue;

            }

            if (BOARD[i][j] == BOARD[i+1][j-1] &&
            BOARD[i+1][j-1] == BOARD[i+2][j-2] &&
            BOARD[i+2][j-2] == BOARD[i+3][j-3]) {

                IN_GAME = 0;

                if (BOARD[i][j] == 'r') {
                    printf("Player 1 wins!!\n");
                }
                else {
                    printf("Player 2 wins!!\n");
                }
                return;
            }

        }
    } // End of secondary diagonal


}


#endif
