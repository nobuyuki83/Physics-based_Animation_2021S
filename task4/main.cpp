#include "delfem2/glfw/viewer2.h"
#include "delfem2/color.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstdio>
#include <random>

// print out error
static void error_callback(int error, const char* description){
  fputs(description, stderr);
}


class CParticle{
public:
  float pos[2] = {0.f, 0.f};
  float velo[2] = {0.f, 0.f};
  float color[3] = {0.f, 0.f, 0.f};
};

void draw(
    const std::vector<CParticle>& aParticle,
    float rad)
{
  ::glLineWidth(2);

  // draw boundary
  ::glBegin(GL_LINE_LOOP);
  ::glColor3f(0.f, 0.f, 0.f);
  ::glVertex2f(0.f, 0.f);
  ::glVertex2f(1.f, 0.f);
  ::glVertex2f(1.f, 1.f);
  ::glVertex2f(0.f, 1.f);
  ::glEnd();

  // draw points
  const int ndiv = 64;
  const float dr = 2.f*M_PI/ndiv;
  ::glPointSize(10);
  for(const auto & ip : aParticle){
    ::glColor3fv(ip.color);
    ::glBegin(GL_TRIANGLE_FAN);
    for(int idiv=0;idiv<ndiv;++idiv){
      ::glVertex2f(
          ip.pos[0]+rad*cos(dr*idiv),
          ip.pos[1]+rad*sin(dr*idiv) );
    }
    ::glEnd();
  }
}

void simulate(
    std::vector<CParticle>& aParticle,
    float rad,
    float dt)
{
  for(auto & p : aParticle) {
    p.pos[0] += dt*p.velo[0];
    p.pos[1] += dt*p.velo[1];
    if( p.pos[0] < rad ){ // left wall
      p.pos[0] = 2*rad-p.pos[0];
      p.velo[0] = -p.velo[0];
    }
    if( p.pos[1] < rad ){ // bottom wall
      p.pos[1] = 2*rad-p.pos[1];
      p.velo[1] = -p.velo[1];
    }
    if( p.pos[0] > 1-rad ){ // left wall
      p.pos[0] = (1-rad)*2-p.pos[0];
      p.velo[0] = -p.velo[0];
    }
    if( p.pos[1] > 1-rad ){ // top wall
      p.pos[1] = (1-rad)*2-p.pos[1];
      p.velo[1] = -p.velo[1];
    }
  }
}

int main()
{
  const unsigned int N = 40; // number of points
  const float rad = 0.03;
  const float dt = 0.01;
  std::vector<CParticle> aParticle;
  { // initialize particle
    std::mt19937 rndeng(std::random_device{}());
    std::uniform_real_distribution<float> dist01(0,1);
    aParticle.resize(N);
    for(auto & p : aParticle){
      // set position
      p.pos[0] = dist01(rndeng);
      p.pos[1] = dist01(rndeng);
      // set color
      delfem2::GetRGB_HSV(
          p.color[0], p.color[1], p.color[2],
          dist01(rndeng), 1.f, 1.f);
      // set velocity
      p.velo[0] = dist01(rndeng)*2.f-1.f;
      p.velo[1] = dist01(rndeng)*2.f-1.f;
      const float lenvelo = sqrt(p.velo[0]*p.velo[0]+p.velo[1]*p.velo[1]);
      p.velo[0] /= lenvelo;
      p.velo[1] /= lenvelo;
    }
  }
  delfem2::glfw::CViewer2 viewer;
  {
    viewer.view_height = 0.75;
    viewer.trans[0] = -0.5;
    viewer.trans[1] = -0.5;
    viewer.title = "task4";
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
    simulate(aParticle,rad,dt);
    draw(aParticle,rad);
    viewer.SwapBuffers();
    glfwPollEvents();
  }
  glfwDestroyWindow(viewer.window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
