//
//  main.c
//  Connect Four


#include <stdio.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include <stdlib.h>

#include "board.h"

//void drawBoard(void);

int main(void) {
    
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(BOARD_WIDTH, BOARD_HEIGHT, "Connect Four", NULL, NULL);
    
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    
    
    glfwSetKeyCallback(window, keyCallback);

    // Make the window's context current
    glfwMakeContextCurrent(window);

    
    
    // Vertices 
    GLfloat boardVertices[] = {
        -0.8f,  (0.8f)*APPARENT_BOARD_HEIGHT/BOARD_HEIGHT,   // Vertex 1 (X, Y)
        0.8f,  0.8f*APPARENT_BOARD_HEIGHT/BOARD_HEIGHT,    // Vertex 2 (X, Y)
        0.8f, -0.8f*APPARENT_BOARD_HEIGHT/BOARD_HEIGHT,    // Vertex 3 (X, Y)
        -0.8f, -0.8f*APPARENT_BOARD_HEIGHT/BOARD_HEIGHT    // Vertex 4 (X, Y)
    };
    
    GLfloat boardColours[] = {
        0.01, 0.3, 1,
        0.01, 0.3, 1,
        0.01, 0.3, 1,
        0.01, 0.3, 1
    };
    

    // GL_FILL, GL_LINE, GL_POINT
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    reset_board();
    
    printf("Player: 1, column: 0\n");
    
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        
        // Board
        drawBoardBack(boardVertices, 4, boardColours);

                
        
        // Circle
        int coinRadius = (BOARD_WIDTH/2)*(0.8f/7);
    
        
        int xstart = (int) ((-0.8f*BOARD_WIDTH)/2);
        int ystart = (int) ((0.8f*APPARENT_BOARD_HEIGHT)/2);
       
        
        // Draw all the slots and coins
        for (int j=ystart-coinRadius, ycount=0; ycount<6 && j>=(-ystart); j-=2*coinRadius, ++ycount) {
                
            for (int i=xstart+coinRadius, xcount=0; xcount<7 && i<=(-xstart); i+=2*coinRadius, ++xcount) {
                GLchar c = getBoard(xcount, ycount);
                 
                drawCircle(i, j, coinRadius, 360, c);
               
            }

        }
        
        // Stop if game ends
        if (game()) {
            drawCircle(xstart+coinRadius + getCol()*2*coinRadius, ((0.8f*BOARD_HEIGHT)/2), coinRadius, 360, getPlayer());
        }
    

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}



