
#include "delfem2/glfw/viewer2.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstdio>
#include <random>

// print out error
static void error_callback(int error, const char* description){
  fputs(description, stderr);
}

void Draw(
    std::vector<float>& aXY)
{
  glBegin(GL_LINE_LOOP);
  glColor3f(0.f, 0.f, 0.f);
  for(int ixy=0;ixy<aXY.size()/2;++ixy){
    ::glVertex2fv(aXY.data()+ixy*2);
  }
  glEnd();
  //
  ::glPointSize(5);
  glBegin(GL_POINTS);
  glColor3f(0.f, 0.f, 0.f);
  for(int ixy=0;ixy<aXY.size()/2;++ixy){
    ::glVertex2fv(aXY.data()+ixy*2);
  }
  glEnd();
}

int main()
{
  std::vector<float> aXY;
  {
    std::mt19937 rndeng( std::random_device{}() );
    std::uniform_real_distribution<float> dist01(0,1);
    const unsigned int N = 20;
    aXY.resize(N*2);
    for(int i=0;i<N;++i){
      aXY[i*2+0] = dist01(rndeng);
      aXY[i*2+1] = dist01(rndeng);
    }
  }
  delfem2::glfw::CViewer2 viewer;
  {
    viewer.view_height = 0.75;
    viewer.trans[0] = -0.5;
    viewer.trans[1] = -0.5;
    viewer.title = "task6: Optimization with Constraints";
  }
  glfwSetErrorCallback(error_callback);
  if ( !glfwInit() ) { exit(EXIT_FAILURE); }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  // ------
  viewer.InitGL();

  while (!glfwWindowShouldClose(viewer.window))
  {
    viewer.DrawBegin_oldGL();
    Draw(aXY);
    viewer.SwapBuffers();
    glfwPollEvents();
  }
  glfwDestroyWindow(viewer.window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
