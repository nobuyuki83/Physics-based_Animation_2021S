#include "delfem2/glfw/viewer2.h"
#include "delfem2/color.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstdio>
#include <random> // for initial randome position & velocity
#include <algorithm> // for sort
#include <set> // for stack

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

// print out error
static void error_callback(int error, const char* description){
  fputs(description, stderr);
}

class CCircle{
public:
  float pos[2] = {0.f, 0.f};
  float velo[2] = {0.f, 0.f};
  bool is_collided = false;
};

void draw(
    const std::vector<CCircle>& aCircle,
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

  // draw circles
  const int ndiv = 64;
  const float dr = 2.f*M_PI/ndiv;
  ::glPointSize(10);
  for(const auto & circle : aCircle){
    if( circle.is_collided ){  // if it is collided, color is red
      ::glColor3f(1.f, 0.f, 0.f);
    }
    else {
      ::glColor3f(0.f, 0.f, 0.f);
    }
    ::glBegin(GL_TRIANGLE_FAN);
    for(int idiv=0;idiv<ndiv;++idiv){
      ::glVertex2f(
          circle.pos[0]+rad*cos(dr*float(idiv)),
          circle.pos[1]+rad*sin(dr*float(idiv)) );
    }
    ::glEnd();
  }
}

void move_circles(
    std::vector<CCircle>& aCircle,
    float rad,
    float dt)
{
  for(auto & circle : aCircle) {
    circle.pos[0] += dt * circle.velo[0];
    circle.pos[1] += dt * circle.velo[1];
    if(circle.pos[0] < rad ){ // left wall
      circle.pos[0] = 2 * rad - circle.pos[0];
      circle.velo[0] = -circle.velo[0];
    }
    if(circle.pos[1] < rad ){ // bottom wall
      circle.pos[1] = 2 * rad - circle.pos[1];
      circle.velo[1] = -circle.velo[1];
    }
    if(circle.pos[0] > 1 - rad ){ // right wall
      circle.pos[0] = (1 - rad) * 2 - circle.pos[0];
      circle.velo[0] = -circle.velo[0];
    }
    if(circle.pos[1] > 1 - rad ){ // top wall
      circle.pos[1] = (1 - rad) * 2 - circle.pos[1];
      circle.velo[1] = -circle.velo[1];
    }
  }
}

struct CPosIndex {
  //! definition of the order between to CPosIndex structures
  bool operator < (const CPosIndex& rhs) const {
    return p < rhs.p;
  }
  float p; //! projected position
  bool is_start;   //! true: enter  false: exit
  unsigned int icircle;   //! index of the circle
};

/**
 * @return true if two circles are collided
 */
bool is_collide(
    const CCircle& c0,
    const CCircle& c1,
    float rad)
{
  const float dx = c0.pos[0]-c1.pos[0];
  const float dy = c0.pos[1]-c1.pos[1];
  return 4 * rad * rad > dx * dx + dy * dy;
}

/**
 *
 * @param[in,out] aCircle array of particle
 * @param[in] rad radius of the circles
 */
void collision_detection(
    std::vector<CCircle>& aCircle,
    float rad)
{
  // reset all the circle as "not collided"
  for(auto& c : aCircle){ c.is_collided = false; }
  std::vector<CPosIndex> aPosIndex;
  aPosIndex.reserve(aCircle.size());
  for(unsigned int ic=0; ic < aCircle.size(); ++ic){
    aPosIndex.push_back({aCircle[ic].pos[0] - rad, true, ic}); // enter
    aPosIndex.push_back({aCircle[ic].pos[0] + rad, false, ic}); // exit
  }
  std::sort(aPosIndex.begin(),aPosIndex.end()); // sort array by quick sort
  std::set<unsigned int> stack;
  for(auto& pi : aPosIndex){
//    std::cout << pi.p << " " << pi.is_start << " " << pi.icircle << std::endl;
    if( pi.is_start ){ // enter the range of the circle
      unsigned int ic0 = pi.icircle;
      // ----------------------------------------------
      // write some codes here (probably 5 - 10 lines)
      // use the function "is_collide()" at line #102
      // ----------------------------------------------
      stack.insert(ic0);
    }
    else{ // exit the range of the circle
      stack.erase(pi.icircle);
    }
  }
}

int main()
{
  const unsigned int N = 40; // number of points
  const float rad = 0.03f; // radius of the circles
  const float dt = 1.f/60.f; // frame rate

  std::vector<CCircle> aCircle;

  { // initialize particle
    std::mt19937 rndeng(std::random_device{}());
    std::uniform_real_distribution<float> dist01(0,1);
    aCircle.resize(N);
    for(auto & p : aCircle){
      // set position
      p.pos[0] = dist01(rndeng);
      p.pos[1] = dist01(rndeng);
      // set velocity
      p.velo[0] = dist01(rndeng)*2.f-1.f;
      p.velo[1] = dist01(rndeng)*2.f-1.f;
      const float lenvelo = sqrt(p.velo[0]*p.velo[0]+p.velo[1]*p.velo[1]);
      p.velo[0] = p.velo[0]/lenvelo*0.2f;
      p.velo[1] = p.velo[1]/lenvelo*0.2f;
    }
  }
  delfem2::glfw::CViewer2 viewer;
  { // set up viewer
    viewer.view_height = 0.75;
    viewer.trans[0] = -0.5;
    viewer.trans[1] = -0.5;
    viewer.title = "task4: Sort & Seep method";
  }
  glfwSetErrorCallback(error_callback);
  if ( !glfwInit() ) { exit(EXIT_FAILURE); }
  // set legacy version of OpenGL
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  // ------
  viewer.InitGL();

  double time_last_update = 0.;
  while (!glfwWindowShouldClose(viewer.window))
  {
    // control of the frame rate
    const double time_now = glfwGetTime();
    if(time_now - time_last_update < dt ){
      glfwPollEvents();
      continue;
    }
    time_last_update = time_now;
    // simulation
    move_circles(aCircle, rad, dt);
    collision_detection(aCircle,rad);
    // draw circles on the window
    viewer.DrawBegin_oldGL();
    draw(aCircle,rad);
    viewer.SwapBuffers();
    glfwPollEvents();
  }
  glfwDestroyWindow(viewer.window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
