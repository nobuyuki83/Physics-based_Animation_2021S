
#include "delfem2/glfw/viewer2.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstdio>
#include <random>

// print out error
static void error_callback(int error, const char* description){
  fputs(description, stderr);
}

/**
 * compute inverse of 2x2 matrix
 * @tparam T floating point number (e.g, double or float)
 * @param[out] a_inv  2x2 invesed matrix
 * @param[in] a 2x2 matrix to be inversed
 */
template <typename T>
void inverse_matrix2(
    T a_inv[2][2],
    const T a[2][2])
{
  const T det_inv = 1/(a[0][0]*a[1][1] - a[0][1]*a[1][0]);
  a_inv[0][0] = +a[1][1]*det_inv;
  a_inv[0][1] = -a[0][1]*det_inv;
  a_inv[1][0] = -a[1][0]*det_inv;
  a_inv[1][1] = +a[0][0]*det_inv;
}

/**
 * compute matrix-vector product
 * @tparam nrow number of rows
 * @tparam ncol number of columns
 * @tparam T floating point number (e.g., float or double)
 * @param y left hand side vector
 * @param A matrix
 * @param x right hand side vector
 */
template <int nrow, int ncol, typename T>
void matrix_vector_product(
    T y[nrow],
    const T A[nrow][ncol],
    const T x[ncol])
{
  for(int i=0;i<nrow;++i){
    y[i] = 0;
    for(int j=0;j<ncol;++j){
      y[i] += A[i][j] * x[j];
    }
  }
}

/**
 * compute energy that is sum of the squared distance between input point and sample points
 * @param[in] pos input points
 * @param[in] aXY coordinates of sample points
 * @return energy
 */
float energy(
    const float pos[2],
    const std::vector<float>& aXY)
{
  float W = 0.f;
  for(unsigned int ixy=0;ixy<aXY.size()/2;++ixy) {
    const float dx = pos[0] - aXY[ixy * 2 + 0];
    const float dy = pos[1] - aXY[ixy * 2 + 1];
    W += dx * dx + dy * dy;
  }
  return W;
}

/**
 * optimize the location of input point based on the Newton-Raphson method
 * @param[in,out] input point
 * @param[in] aXY XY-coordinates of sample points
 */
void optimization_newton(
    float *pos,
    const std::vector<float>& aXY)
{
  float gradW[2] = {0.f, 0.f}; // gradient of energy
  float hessW[2][2] = {{0.f, 0.f}, {0.f, 0.f}}; // hessian of energy
  // adding small value to diagonal for stabilization
  hessW[0][0] += 1.0e-10;
  hessW[1][1] += 1.0e-10;
  for(unsigned int ixy=0;ixy<aXY.size()/2;++ixy){
    const float dx = pos[0] - aXY[ixy * 2 + 0];
    const float dy = pos[1] - aXY[ixy * 2 + 1];
    // write some codes below to compute gradient and hessian of the energy defined in line #60.
//    gradW[0] +=
//    gradW[1] +=
//    hessW[0][0] +=
//    hessW[0][1] +=
//    hessW[1][0] +=
//    hessW[1][1] +=
  }
  // below: Newton-Raphson method
  // compute inverse of hessian: (ddW)^{-1}
  float hessW_inv[2][2]; inverse_matrix2(hessW_inv,hessW);
  // compute matrix vector product: u=(ddW)^{-1}*dW
  float upd[2]; matrix_vector_product<2,2>(upd,hessW_inv,gradW);
  // update positions
  pos[0] -= upd[0];
  pos[1] -= upd[1];
}


/**
 * optimize the location of input point based on stochastic optimization
 * @param[in,out] input point
 * @param[in] aXY XY-coordinates of sample points
 * @param dist distribution of the update to the next optimized point
 * @param randeng random number generator
 */
void optimization_random(
    float pos[2],
    const std::vector<float>& aXY,
    std::normal_distribution<float>& dist,
    std::mt19937& randeng)
{
  const float W0 = energy(pos, aXY); // current energy
  const float pos_new[2] = { // suggestion for new position
      pos[0] + dist(randeng),
      pos[1] + dist(randeng),
  };
  const float W1 = energy(pos_new, aXY); // new energy
  if( W1 < W0 ){ // take the suggestion to update position if it decrease the energy
    pos[0] = pos_new[0];
    pos[1] = pos_new[1];
  }
}

/**
 * draw input point and edges between sample points
 * @param[in] aXY sample points
 * @param[in] pos optimized point
 */
void draw_optimized_point(
    const std::vector<float>& aXY,
    const float pos[2])
{
  ::glBegin(GL_POINTS);
  ::glPointSize(1);
  ::glVertex2fv(pos);
  ::glEnd();
  //
  ::glBegin(GL_LINES);
  for(unsigned int ixy=0;ixy<aXY.size()/2;++ixy){
    ::glVertex2fv(aXY.data()+ixy*2);
    ::glVertex2fv(pos);
  }
  glEnd();
}


int main()
{
  std::mt19937 rndeng(std::random_device{}());
  std::vector<float> aXY; // sample points
  { // initialize positions
    const unsigned int N = 100;
    std::uniform_real_distribution<float> dist01(0,1);
    aXY.resize(N*2);
    for(unsigned int ixy=0;ixy<aXY.size()/2;++ixy){
      aXY[ixy*2+0] = dist01(rndeng);
      aXY[ixy*2+1] = dist01(rndeng);
    }
  }
  float pos_optrand[2] = {0.f, 0.f}; // points for stochastic optimization(red)
  float pos_optnewton[2] = {1.f, 1.f}; // points for newton optimizatoin(brue)
  // -----------
  delfem2::glfw::CViewer2 viewer;
  { // set up camera parameters
    viewer.view_height = 0.6;
    viewer.trans[0] = -0.5;
    viewer.trans[1] = -0.5;
    viewer.title = "task2: Optimization";
  }
  glfwSetErrorCallback(error_callback);
  if ( !glfwInit() ) { exit(EXIT_FAILURE); }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  // ------
  viewer.InitGL();

  const double dt = 1.0/60.0; // frame-rate is fixed to 60FPS.
  double time_last_update = 0.0;
  while (!glfwWindowShouldClose(viewer.window))
  {
    // control of the frame rate
    const double time_now = glfwGetTime();
    if(time_now - time_last_update < dt ){
      glfwPollEvents();
      continue;
    }
    time_last_update = time_now;
    std::cout << "energy for stochastic optimization: " << energy(pos_optrand,aXY) << ",  ";
    std::cout << "energy for newton optimization: " << energy(pos_optnewton,aXY) << std::endl;
    { // optimize
      std::normal_distribution<float> distN(0, 0.005);
      optimization_random(
          pos_optrand,
          aXY,
          distN,
          rndeng);
    }
    optimization_newton(pos_optnewton,aXY);
    // start draw
    viewer.DrawBegin_oldGL();
    { // draw black sample points
      ::glColor3f(0.f, 0.f, 0.f);
      ::glPointSize(5);
      ::glBegin(GL_POINTS);
      for (unsigned int ixy = 0; ixy < aXY.size() / 2; ++ixy) {
        ::glVertex2fv(aXY.data() + ixy * 2);
      }
      ::glEnd();
    }
    // draw point for random optimization (red)
    ::glLineWidth(1);
    ::glColor3f(1.f, 0.f, 0.f); // red color
    draw_optimized_point(aXY,pos_optrand);
    // draw point for Newton-Raphson optimization (blue)
    ::glLineWidth(2);
    ::glColor3f(0.f, 0.f, 1.f);
    draw_optimized_point(aXY,pos_optnewton);
    // end draw
    viewer.SwapBuffers();
    glfwPollEvents();
  }
  glfwDestroyWindow(viewer.window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
