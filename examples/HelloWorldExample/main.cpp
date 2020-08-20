#include "lib/PumpkinSpiceFactory.h"

#include "ShaderLoader.h"
#include <GL/freeglut.h>

PumpkinSpiceObject* pumpkinSpiceObject;

float verts[]={
	// triangle 1
	-1.0f,-1.0f,						// bottom left
	-1.0f,1.0f,						// Top left
	1.0f,1.0f,						// top right
	// triangle 2
	-1.0f,-1.0f,						// bottom left
	1.0f,1.0f,						// top right
	1.0f,-1.0f						// bottom right
};
float textureMap[]={
    // triangle 1
    0.0f,0.0f,						// bottom left
    0.0f,1.0f,						// Top left
    1.0f,1.0f,						// top right
    // triangle 2
    0.0f,0.0f,						// bottom left
    1.0f,1.0f,						// top right
    1.0f,0.0f						// bottom right
};

GLuint basicShader;

void keyboard(unsigned char key, int x, int y) {
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen
    for (int i = 0; i != pumpkinSpiceObject->meshes.size(); i++) {
        std::vector<Point> mesh = pumpkinSpiceObject->meshes.at(i);
        float* meshFloat = pointsToFloats(mesh);
        int size = mesh.size() * 2;
        int bufferVertSize = size * sizeof(float);

        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        GLuint buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, bufferVertSize + sizeof(textureMap), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, bufferVertSize, meshFloat);
        glBufferSubData(GL_ARRAY_BUFFER, bufferVertSize, sizeof(textureMap), textureMap);


        // Textures
        GLuint textureObj;
        glGenTextures(1,&textureObj);
        glBindTexture(GL_TEXTURE_2D, textureObj);
        // FIXME, oh so hacky... so very very hacky :)  
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 500, 500, 0, GL_RGBA, GL_UNSIGNED_BYTE, pumpkinSpiceObject->textures.at(i));
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glActiveTexture(GL_TEXTURE0);
    	glBindTexture(GL_TEXTURE_2D, textureObj);


        int vertIn=glGetAttribLocation(basicShader,"vertexPosition");
        glEnableVertexAttribArray(vertIn);
        glVertexAttribPointer(vertIn,2,GL_FLOAT,GL_FALSE,0,0);
        
        int textCIn=glGetAttribLocation(basicShader,"vTextureCoordinate");
        glEnableVertexAttribArray(textCIn);
        glVertexAttribPointer(textCIn,2,GL_FLOAT,GL_FALSE,0,(GLvoid*)sizeof(verts));
        
        int textureIn= glGetUniformLocation(basicShader,"image");
        glUniform1i(textureIn,0);


        glClearColor(0.0, 1.0, 0.0, 0.0);    
        glClear(GL_COLOR_BUFFER_BIT); // clear the screen

        glDrawArrays(GL_TRIANGLES, 0 , size);
    }

    glutSwapBuffers();

}

int main(int argc, char** argv) {
    PumpkinSpiceCompiler pumpkinSpiceCompiler = PumpkinSpiceCompiler();
    pumpkinSpiceCompiler.addFont("external/font/Bangers-Regular.ttf", "Bangers-Regular");
    pumpkinSpiceObject = pumpkinSpiceCompiler.compilePumpkinSpice("examples/HelloWorldExample/test.xml", "examples/HelloWorldExample/style.spice");

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize (400, 400); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Hello World");
    glewInit();
    
    basicShader = initShader( "examples/shaders/standardVertexShader.glsl", "examples/shaders/standardFragmentShader.glsl");
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
