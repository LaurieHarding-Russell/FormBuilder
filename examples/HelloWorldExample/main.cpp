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
float textC[]={
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

    glClearColor(0.0, 1.0, 0.0, 0.0);    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    int vertIn=glGetAttribLocation(basicShader,"vertexPosition");
    glEnableVertexAttribArray(vertIn);

    int textCIn=glGetAttribLocation(basicShader,"vTextureCoordinate");
    glEnableVertexAttribArray(textCIn);

    int textureIn= glGetUniformLocation(basicShader,"image");

    GLuint* buffer = new GLuint[pumpkinSpiceObject->meshes.size()];
    GLuint* textureObj = new GLuint[pumpkinSpiceObject->meshes.size()];

    glGenBuffers(pumpkinSpiceObject->meshes.size(), buffer);
    glGenTextures(pumpkinSpiceObject->meshes.size(), textureObj);

    for (uint i = 0; i != pumpkinSpiceObject->meshes.size(); i++) {
        std::vector<Point> mesh = pumpkinSpiceObject->meshes.at(i);
        std::cout << mesh[0] << "," << mesh[1] << "," << mesh[2] << "," << mesh[3] << "\n";
        float* meshFloat = pointsToFloats(mesh);
        float* uvVerts = pointsToFloats(pumpkinSpiceObject->textureMap);
        
        int size = mesh.size() * 3;
        int bufferVertSize = size * sizeof(float);
        int uvMapSize = pumpkinSpiceObject->textureMap.size() * 3 * sizeof(float);

        glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
        glBufferData(GL_ARRAY_BUFFER, bufferVertSize + uvMapSize, NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, bufferVertSize, meshFloat);
        glBufferSubData(GL_ARRAY_BUFFER, bufferVertSize, uvMapSize, uvVerts);

        // Textures
        glBindTexture(GL_TEXTURE_2D, textureObj[i]);
        // FIXME, oh so hacky... so very very hacky :)  
        Texture* texture = pumpkinSpiceObject->textures.at(i);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // think about buffering

        glVertexAttribPointer(vertIn,3,GL_FLOAT,GL_FALSE,0,0);
        glVertexAttribPointer(textCIn,3,GL_FLOAT,GL_FALSE,0,(GLvoid*)sizeof(verts));
        glUniform1i(textureIn,0);

        glDrawArrays(GL_TRIANGLES, 0 , size);
    }


    glutSwapBuffers();

}

int main(int argc, char** argv) {
    PumpkinSpiceCompiler pumpkinSpiceCompiler = PumpkinSpiceCompiler();
    pumpkinSpiceCompiler.addFont("external/font/Bangers-Regular.ttf", "Bangers-Regular");
    pumpkinSpiceObject = pumpkinSpiceCompiler.compilePumpkinSpice("examples/HelloWorldExample/test.xml", "examples/HelloWorldExample/style.spice");

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
    glUseProgram(basicShader);

    GLuint vectorIn = glGetAttribLocation(basicShader, "vectorIn");
	glEnableVertexAttribArray(vectorIn);
	glVertexAttribPointer(vectorIn, 3, GL_FLOAT, GL_FALSE, 0, 0);
   
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glutDisplayFunc(display); 
    glutKeyboardFunc (keyboard);

    glutMainLoop();

    return 0;
}
