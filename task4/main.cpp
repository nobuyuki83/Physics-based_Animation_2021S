
#include "delfem2/glfw/viewer2.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstdio>

// print out error
static void error_callback(int error, const char* description){
  fputs(description, stderr);
}

void Draw(){
  glBegin(GL_LINE_LOOP);
  glColor3f(0.f, 0.f, 0.f);
  glVertex2f(0.f, 0.f);
  glVertex2f(1.f, 0.f);
  glVertex2f(1.f, 1.f);
  glVertex2f(0.f, 1.f);
  glEnd();
}

int main()
{
  delfem2::glfw::CViewer2 viewer;
  {
    viewer.view_height = 1.0;
    viewer.trans[0] = -0.5;
    viewer.trans[1] = -0.5;
    viewer.title = "task4";
  }
  glfwSetErrorCallback(error_callback);
  if ( !glfwInit() ) { exit(EXIT_FAILURE); }
  // ------
  viewer.InitGL();

  while (!glfwWindowShouldClose(viewer.window))
  {
    viewer.DrawBegin_oldGL();
    Draw();
    viewer.SwapBuffers();
    glfwPollEvents();
  }
  glfwDestroyWindow(viewer.window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
