#include "lib/PumpkinSpice.h"

#include "ShaderLoader.h"
#include <GLFW/glfw3.h>

PumpkinSpiceComponentObject* pumpkinSpiceComponentObject;
GLuint basicShader;
int vertIn;
GLuint vao;
int textCIn;
int textureIn;
PumpkinSpice pumpkinSpiceCompiler;

int WIDTH = 400, HEIGHT = 400;
int helloCounter = 0;

void error_callback(int error, const char* description);

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
   if (action == GLFW_PRESS) {
      switch (key) {
         case 256:
         case 81:
            glfwSetWindowShouldClose(window, true);
            break;
         default:
            std::cout << "KEY: " << key << "\n";
            break;
      }
   }
}


void display(GLFWwindow* window) {
   float ratio;
   int width, height;
   glfwGetFramebufferSize(window, &width, &height);
   ratio = width / (float) height;
   glViewport(0, 0, width, height);
   glClearColor(0.0, 0.0, 0.0, 0.0);    
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen

   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);
   
   glUseProgram(basicShader);
   
   vertIn = glGetAttribLocation(basicShader,"vertexPosition");
   glEnableVertexAttribArray(vertIn);

   textCIn = glGetAttribLocation(basicShader,"vTextureCoordinate");
   glEnableVertexAttribArray(textCIn);

   textureIn = glGetUniformLocation(basicShader,"image");

   std::vector<PumpkinSpiceObject*> pumpkinSpiceRenderObjects = pumpkinSpiceComponentObject->getPumpkinSpiceRenderObjects();
   for (uint objectIterator = 0; objectIterator != pumpkinSpiceRenderObjects.size(); objectIterator++) {
      PumpkinSpiceObject* pumpkinSpiceObject = pumpkinSpiceRenderObjects.at(objectIterator);
      GLuint* buffer = new GLuint[pumpkinSpiceObject->meshes.size()];
      GLuint* textureObj = new GLuint[pumpkinSpiceObject->meshes.size()];

      glGenBuffers(pumpkinSpiceObject->meshes.size(), buffer);
      glGenTextures(pumpkinSpiceObject->meshes.size(), textureObj);
      // Load it.
      for (uint i = 0; i != pumpkinSpiceObject->meshes.size(); i++) {
         std::vector<glm::vec3> mesh = pumpkinSpiceObject->meshes.at(i);
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
         glVertexAttribPointer(textCIn,3,GL_FLOAT,GL_FALSE,0, &bufferVertSize);

         Texture* texture = pumpkinSpiceObject->textures.at(i);

         // texture->saveAsBitmapImage("/home/laurie/test.bmp"); // add full path.

         glBindTexture(GL_TEXTURE_2D, textureObj[i]);
         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->getWidth(), texture->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
         glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      }

      for (uint i = 0; i != pumpkinSpiceObject->meshes.size(); i++) {
         glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
         std::vector<glm::vec3> mesh = pumpkinSpiceObject->meshes.at(i);

         // Textures
         glBindTexture(GL_TEXTURE_2D, textureObj[i]);
         // think about buffering

         glDrawArrays(GL_TRIANGLES, 0 , mesh.size());
      }
   }
}

int main(int argc, char** argv) {
   pumpkinSpiceCompiler = PumpkinSpice(WIDTH, HEIGHT);
   pumpkinSpiceCompiler.addFont("external/font/Bangers-Regular.ttf", "Bangers-Regular");

   PumpkinSpiceInput pumpkinSpiceInput;
   pumpkinSpiceInput.basePumkinFileName = "examples/HelloWorldExample/test.xml";
   pumpkinSpiceInput.baseSpiceFileName = "examples/HelloWorldExample/style.spice";

   pumpkinSpiceCompiler.compileComponents(pumpkinSpiceInput);
   pumpkinSpiceComponentObject = pumpkinSpiceCompiler.getPumpkinSpiceComponentObject();

   PumpkinSpiceComponentObject* pumpkinSpiceComponentObject = pumpkinSpiceCompiler.getPumpkinSpiceComponentObject();
   
   GLFWwindow* window;

   if (!glfwInit()) {
      exit(EXIT_FAILURE);
   }
   glfwSetErrorCallback(error_callback);

   window = glfwCreateWindow(640, 480, "Basic Component", NULL, NULL);
   if (!window) {
      glfwTerminate();
      exit(EXIT_FAILURE);
   }

   glfwMakeContextCurrent(window);
   glfwSetKeyCallback(window, keyCallback);
   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
   glewExperimental = GL_TRUE;
   glewInit();

   basicShader = initShader( "examples/shaders/standardVertexShader.glsl", "examples/shaders/standardFragmentShader.glsl");

   glEnable(GL_BLEND);
   glEnable(GL_DEPTH);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   glEnable(GL_PROGRAM_POINT_SIZE);

   while (!glfwWindowShouldClose(window)) {
      display(window);
      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   glfwDestroyWindow(window);
   glfwTerminate();
   return 0;
}


void error_callback(int error, const char* description) {
    fputs(description, stderr);
}
