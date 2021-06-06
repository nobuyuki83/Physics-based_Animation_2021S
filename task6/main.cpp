
#include "delfem2/glfw/viewer2.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstdio>
#include <random>
#include <Eigen/Core>
#include <Eigen/LU>

/**
* Area of the triangle connecting given two points and the origin, together with gradient and hessian of area.
* @param[out] W area
* @param[out] dW gradient of W. dW[inode][idim]: differentiation of W w.r.t. aP[inode][idim]
* @param[out] ddW hessian of W. ddW[inode][jnode][idim][jdim]: differentiation of W w.r.t. aP[inode][idim] and aP[jnode][jdim]
* @param[in] aP coordinates of two points. aP[inode][idim]: idim-th coordinate of inode-th point
*/
void WdWddW_Area2(
    double& W,
    double dW[2][2],
    double ddW[2][2][2][2],
    const double aP[2][2])
{
  W = 0.5*(aP[0][0] * aP[1][1] - aP[0][1] * aP[1][0]);
  dW[0][0] = +0.5 * aP[1][1];
  dW[0][1] = -0.5 * aP[1][0];
  dW[1][0] = -0.5 * aP[0][1];
  dW[1][1] = +0.5 * aP[0][0];
  std::fill_n(&ddW[0][0][0][0],2*2*2*2,0.0);
  ddW[0][1][0][1] = +0.5;
  ddW[0][1][1][0] = -0.5;
  ddW[1][0][0][1] = -0.5;
  ddW[1][0][1][0] = +0.5;
}

/**
 * Squared distance of the two points and its gradient and hessian
 * @param[out] W squared distance
 * @param[out] dW gradient of W. dW[inode][idim]: differentiation of W w.r.t. aP[inode][idim]
 * @param[out] ddW hessian of W. ddW[inode][jnode][idim][jdim]: differentiation of W w.r.t. aP[inode][idim] and aP[jnode][jdim]
 * @param[in] aP coordinates of two points. aP[inode][idim]: idim-th coordinate of inode-th point
 */
void WdWddW_SquaredDistance2(
    double& W,
    double dW[2][2],
    double ddW[2][2][2][2],
    const double aP[2][2])
{
  const double dx = aP[1][0] - aP[0][0];
  const double dy = aP[1][1] - aP[0][1];
  W = dx*dx+dy*dy;
  dW[0][0] = -dx;
  dW[0][1] = -dy;
  dW[1][0] = +dx;
  dW[1][1] = +dy;
  std::fill_n(&ddW[0][0][0][0],2*2*2*2,0.0);
  ddW[0][0][0][0] = +1;
  ddW[0][0][1][1] = +1;
  ddW[0][1][0][0] = -1;
  ddW[0][1][1][1] = -1;
  ddW[1][0][0][0] = -1;
  ddW[1][0][1][1] = -1;
  ddW[1][1][0][0] = +1;
  ddW[1][1][1][1] = +1;
}


/**
 * Optimize points to minimize the sum of squared distance of polygon edges while keeping the area of polygon 1
 * @param[in,out] aXY Coordinates of points of the polygon
 * @param[in,out] lambda lagrange multiplier
 * @param[in] damping damping factor to make animation slow enough to see
 */
void Optimize(
    std::vector<double>& aXY,
    double& lambda,
    double damping)
{
  const unsigned int np = aXY.size()/2; // number of points
  Eigen::MatrixXd matA(np*2+1,np*2+1); // coeff. matrix for coordinates and lagrange multiplier
  Eigen::VectorXd vecB(np*2+1);
  matA.setZero();
  vecB.setZero();
  double W_sum = 0.0; // sum of squared distance of edges
  double G_sum = 0.0; // area of polygon (sum of triangle areas)
  for(auto ie=0;ie<np;++ie){
    const unsigned int ip0 = ie;
    const unsigned int ip1 = (ie+1)%np;
    const double aP[2][2] = { // coordinates of two end points
        {aXY[ip0*2+0],aXY[ip0*2+1]},
        {aXY[ip1*2+0],aXY[ip1*2+1]} };
    // compute squared distance between two points
    double W, dW[2][2], ddW[2][2][2][2];
    WdWddW_SquaredDistance2(
        W, dW, ddW,
        aP);
    W_sum += W;
    // compute area of triangle connecting two points and the origin, together with gradient and hessian
    double G, dG[2][2], ddG[2][2][2][2];
    WdWddW_Area2(
        G, dG, ddG,
        aP);
    G_sum += G;
    // making corff. matrix and rhs vector
    // ---------------
    // write some codes below
    for(int idim=0;idim<2;++idim) {
      for(int jdim=0;jdim<2;++jdim) {
        matA(ip0 * 2 + idim, ip0 * 2 + jdim) += ddW[0][0][idim][jdim];
        matA(ip0 * 2 + idim, ip1 * 2 + jdim) += ddW[0][1][idim][jdim];
        matA(ip1 * 2 + idim, ip0 * 2 + jdim) += ddW[1][0][idim][jdim];
        matA(ip1 * 2 + idim, ip1 * 2 + jdim) += ddW[1][1][idim][jdim];
      }
      vecB(ip0*2+idim) += dW[0][idim];
      vecB(ip1*2+idim) += dW[1][idim];
      // write something around here to put the areal constraint
    }
  }

  // no further modification below
  // ---------------

  // damp the update by adding diagonal
  for(unsigned int ip=0;ip<np;++ip) {
    matA(ip*2+0,ip*2+0) += damping;
    matA(ip*2+1,ip*2+1) += damping;
  }
  matA(np*2,np*2) -= damping*1.0e-5;

  Eigen::FullPivLU<Eigen::MatrixXd> lu(matA);
  Eigen::VectorXd vecX = lu.solve(vecB);

  std::cout << "square sum of distance: " << W_sum << "   area of polygon: " << G_sum << std::endl;
  for(unsigned int ip=0;ip<np;++ip){
    aXY[ip*2+0] -= vecX(ip*2+0);
    aXY[ip*2+1] -= vecX(ip*2+1);
  }
  lambda -= vecX(np*2);
}


// -------------------------
// below: opengl dependency

// print out error
static void error_callback(int error, const char* description){
  fputs(description, stderr);
}

/**
 * Draw Polygon and constraint forces
 * black: polygon, blue: energy gradient, red: constraints gradient
 * @param[in] aXY
 */
void Draw(
    const std::vector<double>& aXY)
{
  const unsigned int np = aXY.size()/2;
  ::glLineWidth(1);
  ::glBegin(GL_LINE_LOOP);
  ::glColor3f(0.f, 0.f, 0.f);
  for (int ixy = 0; ixy<np; ++ixy) {
    ::glVertex2dv(aXY.data() + ixy * 2);
  }
  ::glEnd();
  //
  ::glPointSize(5);
  ::glBegin(GL_POINTS);
  ::glColor3f(0.f, 0.f, 0.f);
  for (int ixy = 0; ixy < np; ++ixy) {
    ::glVertex2dv(aXY.data() + ixy * 2);
  }
  ::glEnd();
  //
  { //
    std::vector<double> dWsum(np*2,0.0);
    for(auto ie=0;ie<np;++ie) {
      const unsigned int ip0 = ie;
      const unsigned int ip1 = (ie + 1) % np;
      const double aP[2][2] = { // coordinates of two end points
          {aXY[ip0 * 2 + 0], aXY[ip0 * 2 + 1]},
          {aXY[ip1 * 2 + 0], aXY[ip1 * 2 + 1]}};
      // compute squared distance between two points
      double W, dW[2][2], ddW[2][2][2][2];
      WdWddW_SquaredDistance2(
          W, dW, ddW,
          aP);
      dWsum[ip0*2+0] += dW[0][0];
      dWsum[ip0*2+1] += dW[0][1];
      dWsum[ip1*2+0] += dW[1][0];
      dWsum[ip1*2+1] += dW[1][1];
    }
    ::glLineWidth(2);
    ::glColor3f(0.f, 0.f, 1.f);
    ::glBegin(GL_LINES);
    for (int ixy = 0; ixy < np; ++ixy) {
      ::glVertex2d(aXY[ixy*2+0], aXY[ixy*2+1]);
      ::glVertex2d(aXY[ixy*2+0]+dWsum[ixy*2+0], aXY[ixy*2+1]+dWsum[ixy*2+1]);
    }
    ::glEnd();
  }
  { //
    std::vector<double> dGsum(np*2,0.0);
    for(auto ie=0;ie<np;++ie) {
      const unsigned int ip0 = ie;
      const unsigned int ip1 = (ie + 1) % np;
      const double aP[2][2] = { // coordinates of two end points
          {aXY[ip0 * 2 + 0], aXY[ip0 * 2 + 1]},
          {aXY[ip1 * 2 + 0], aXY[ip1 * 2 + 1]}};
      // compute squared distance between two points
      double G, dG[2][2], ddG[2][2][2][2];
      WdWddW_Area2(
          G, dG, ddG,
          aP);
      dGsum[ip0*2+0] += dG[0][0];
      dGsum[ip0*2+1] += dG[0][1];
      dGsum[ip1*2+0] += dG[1][0];
      dGsum[ip1*2+1] += dG[1][1];
    }
    ::glLineWidth(4);
    glColor3f(1.f, 0.f, 0.f);
    glBegin(GL_LINES);
    for (int ixy = 0; ixy < np; ++ixy) {
      ::glVertex2d(aXY[ixy*2+0], aXY[ixy*2+1]);
      ::glVertex2d(aXY[ixy*2+0]+dGsum[ixy*2+0], aXY[ixy*2+1]+dGsum[ixy*2+1]);
    }
    glEnd();
  }
}

int main()
{
  std::vector<double> aXY;
  { // make random points
    std::mt19937 rndeng( std::random_device{}() );
    std::uniform_real_distribution<double> dist01(0,1);
    const unsigned int N = 20;
    aXY.resize(N*2);
    for(int i=0;i<N;++i){
      aXY[i*2+0] = dist01(rndeng);
      aXY[i*2+1] = dist01(rndeng);
    }
  }
  double lambda = 0.0;
  //
  delfem2::glfw::CViewer2 viewer;
  { // set up camera for 2D view
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
  double time_last_update = 0.0;
  const double dt = 1.0/60.0;
  while (!glfwWindowShouldClose(viewer.window))
  {
    // control of the frame rate
    const double time_now = glfwGetTime();
    if(time_now - time_last_update < dt ){
      glfwPollEvents();
      continue;
    }
    time_last_update = time_now;
    //
    Optimize(
        aXY,lambda,
        30.0);
    // draw from here
    viewer.DrawBegin_oldGL();
    Draw(aXY); // black: polygon, blue: energy gradient, red: constraints gradient
    viewer.SwapBuffers();
    glfwPollEvents();
  }
  glfwDestroyWindow(viewer.window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
