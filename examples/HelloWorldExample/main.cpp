#include "lib/PumpkinSpiceFactory.h"

#include "ShaderLoader.h"
#include <GL/freeglut.h>

PumpkinSpiceObject* pumpkinSpiceObject;

void keyboard(unsigned char key, int x, int y) {
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

void display() {
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen

    // GLuint assetBuffer;
    // glGenBuffers(1, &assetBuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, assetBuffer);
    // glBufferData(GL_ARRAY_BUFFER, pumpkinSpiceObject->vertexCount, NULL, GL_STATIC_DRAW);
    // glBufferSubData(GL_ARRAY_BUFFER, 0, pumpkinSpiceObject->vertexCount * 2, pumpkinSpiceObject->mesh);

    // glDrawArrays(GL_TRIANGLES, 0 , (pumpkinSpiceObject->vertexCount/3)/3);

    glutSwapBuffers();

}

int main(int argc, char** argv) {
    PumpkinSpiceCompiler pumpkinSpiceCompiler = PumpkinSpiceCompiler();
    pumpkinSpiceObject = pumpkinSpiceCompiler.compilePumpkinSpice("examples/HelloWorldExample/test.xml", "examples/HelloWorldExample/style.spice");

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize (400, 400); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Hello World");
    glewInit();

    GLuint basicShader = initShader( "examples/shaders/standardVertexShader.glsl", "examples/shaders/standardFragmentShader.glsl");
    glUseProgram(basicShader);

    GLuint vectorIn = glGetAttribLocation(basicShader, "vectorIn");
	glEnableVertexAttribArray(vectorIn);
	glVertexAttribPointer(vectorIn, 3, GL_FLOAT, GL_FALSE, 0, 0);
   
	glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display); 
    glutKeyboardFunc (keyboard);

    glutMainLoop();

    return 0;
}
