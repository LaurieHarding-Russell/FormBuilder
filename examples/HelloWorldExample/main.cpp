#include "lib/PumpkinSpiceFactory.h"

#include "ShaderLoader.h"
#include <GL/freeglut.h>

PumpkinSpiceObject* pumpkinSpiceObject;
PumpkinSpiceCompiler* pumpkinSpiceCompiler;

GLuint basicShader;

void keyboard(unsigned char key, int x, int y) {
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

void display() {

    glClearColor(0.0, 0.0, 0.0, 0.0);    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen



    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glUseProgram(basicShader);
    
    int vertIn = glGetAttribLocation(basicShader,"vertexPosition");
    glEnableVertexAttribArray(vertIn);

    int textCIn = glGetAttribLocation(basicShader,"vTextureCoordinate");
    glEnableVertexAttribArray(textCIn);

    int textureIn = glGetUniformLocation(basicShader,"image");

    GLuint* buffer = new GLuint[pumpkinSpiceObject->meshes.size()];
    GLuint* textureObj = new GLuint[pumpkinSpiceObject->meshes.size()];

    glGenBuffers(pumpkinSpiceObject->meshes.size(), buffer);
    glGenTextures(pumpkinSpiceObject->meshes.size(), textureObj);
    // Load it.
    for (uint i = 0; i != pumpkinSpiceObject->meshes.size(); i++) {
        std::vector<Point> mesh = pumpkinSpiceObject->meshes.at(i);
        int size = mesh.size() * 3;

        float* meshFloat = pointsToFloats(mesh);
        float* uvVerts = pointsToFloats(pumpkinSpiceObject->textureMap);
        
        int bufferVertSize = size * sizeof(float);
        int uvMapSize = pumpkinSpiceObject->textureMap.size() * 3 * sizeof(float);

        glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
        glBufferData(GL_ARRAY_BUFFER, bufferVertSize + uvMapSize, NULL, GL_STATIC_DRAW);

        glBufferSubData(GL_ARRAY_BUFFER, 0, bufferVertSize, meshFloat);
        glVertexAttribPointer(vertIn,3,GL_FLOAT,GL_FALSE,0,0);
        
        glBufferSubData(GL_ARRAY_BUFFER, bufferVertSize, uvMapSize, uvVerts);
        glVertexAttribPointer(textCIn,3,GL_FLOAT,GL_FALSE,0,(GLvoid*)bufferVertSize);

        Texture* texture = pumpkinSpiceObject->textures.at(i);

        glBindTexture(GL_TEXTURE_2D, textureObj[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    for (uint i = 0; i != pumpkinSpiceObject->meshes.size(); i++) {
        glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
        std::vector<Point> mesh = pumpkinSpiceObject->meshes.at(i);
        int size = mesh.size() * 3;

        // Textures
        glBindTexture(GL_TEXTURE_2D, textureObj[i]);
        // think about buffering

        glDrawArrays(GL_TRIANGLES, 0 , size);
    }


    glutSwapBuffers();

}

int main(int argc, char** argv) {
    pumpkinSpiceCompiler = new PumpkinSpiceCompiler(); 

    PumpkinSpiceInput basicComponentInput;
    basicComponentInput.basePumkinFileName = "examples/HelloWorldExample/test.xml";
    basicComponentInput.baseSpiceFileName = "examples/HelloWorldExample/style.spice";

    pumpkinSpiceCompiler->addFont("external/font/Bangers-Regular.ttf", "Bangers-Regular");
    pumpkinSpiceCompiler->compileComponents(basicComponentInput);
    pumpkinSpiceObject = pumpkinSpiceCompiler->getPumpkinSpiceComponentObject()->pumpkinSpiceObjects[0];

    glutInit(&argc, argv);

    glutInitContextVersion( 3, 0 );
	glutInitContextProfile( GLUT_CORE_PROFILE );
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowSize (400, 400); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Hello World");
    glewExperimental = GL_TRUE;
    glewInit();
    
    basicShader = initShader( "examples/shaders/standardVertexShader.glsl", "examples/shaders/standardFragmentShader.glsl");
   
	// glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glutDisplayFunc(display); 
    glutKeyboardFunc (keyboard);

    glutMainLoop();

    return 0;
}
