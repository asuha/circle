#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

// Window dimensions
const GLint WIDTH=800, HEIGHT=600;

void drawCircle( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides );

int main() {
    // Init GLFW
    glfwInit();
    
    // Create a GLFWwindow object that we can use for GLFW`s functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Circle", nullptr, nullptr );
    
    int screenWidth, screenHeight;
    
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    if ( nullptr == window) {
        glfwTerminate();
        
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    glViewport( 0, 0, screenWidth, screenHeight);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    glOrtho( 0, WIDTH, 0, HEIGHT, 0, 1 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    
    //while the window is not closed
    while (!glfwWindowShouldClose(window)) {
        glClear( GL_COLOR_BUFFER_BIT );
        
        drawCircle(WIDTH / 2, HEIGHT / 2, 0, 120, 360);
        
        glfwSwapBuffers( window );
        
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    return 0;
}

void drawCircle( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides ) {
    GLint numberOfVertices = numberOfSides + 2;
    
    GLfloat twicePi = 2.0f * M_PI;
    
    GLfloat circleVerticesX[numberOfVertices];
    GLfloat circleVerticesY[numberOfVertices];
    GLfloat circleVerticesZ[numberOfVertices];
    
    circleVerticesX[0] = x;
    circleVerticesY[0] = y;
    circleVerticesZ[0] = z;
    
    for ( int i = 0; i < numberOfVertices; i++) {
        circleVerticesX[i] = x + ( radius * cos( i * twicePi / numberOfSides ) );
        circleVerticesY[i] = y + ( radius * sin( i * twicePi / numberOfSides ) );
        circleVerticesZ[i] = z;
    }
    
    GLfloat allCircleVertices[numberOfVertices * 3];
    
    for ( int i = 0; i < numberOfVertices; i++) {
        allCircleVertices[i*3] = circleVerticesX[i];
        allCircleVertices[(i*3) + 1] = circleVerticesY[i];
        allCircleVertices[(i*3) + 2] = circleVerticesZ[i];
    }
    
    glEnableClientState( GL_VERTEX_ARRAY );
    
    glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
    glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
    
    glDisableClientState( GL_VERTEX_ARRAY );
}
