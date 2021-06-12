
#include "delfem2/glfw/viewer3.h"
#include "delfem2/opengl/old/mshuni.h" // point surrounding point array generation
#include "delfem2/opengl/old/funcs.h"
#include "delfem2/mshuni.h"
#include "delfem2/points.h"
#include "delfem2/mshio.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <random>
#include <cstdio>
#include <Eigen/Core>
#include <Eigen/Geometry>

#ifndef M_PI
  #define M_PI 3.14159265359
#endif

/**
 * generating random points
 * @param[out] aPosSrc source points to be rotated
 * @param[out] aPosTrg target points fixed
 */
void InitializeProblem(
    std::vector<double>& aPosSrc,
    std::vector<double>& aPosTrg)
{
  std::mt19937 rndeng(std::random_device{}());
  std::uniform_real_distribution<double> dist_m1p1(-1,+1);
  for (int i = 0; i < 100; ++i) { // make random points on the unit sphere
    const double p[3] = { dist_m1p1(rndeng), dist_m1p1(rndeng), dist_m1p1(rndeng) };
    const double li0 = 1.0/sqrt(p[0]*p[0]+p[1]*p[1]+p[2]*p[2]);
    aPosSrc.push_back(p[0]*li0);
    aPosSrc.push_back(p[1]*li0);
    aPosSrc.push_back(p[2]*li0);
  }
  Eigen::Matrix3d R0;
  { // random rotation matrix
    R0 = Eigen::AngleAxis<double>(dist_m1p1(rndeng) * M_PI, Eigen::Vector3d::UnitX());
    R0 = R0 * Eigen::AngleAxis<double>(dist_m1p1(rndeng) * M_PI, Eigen::Vector3d::UnitY());
    R0 = R0 * Eigen::AngleAxis<double>(dist_m1p1(rndeng) * M_PI, Eigen::Vector3d::UnitZ());
  }
  for(unsigned int ip=0;ip<aPosSrc.size()/3;++ip){ //
    const Eigen::Vector3d& x = Eigen::Map<Eigen::Vector3d>(aPosSrc.data()+ip*3);
    const Eigen::Vector3d y = 2*R0*x;
    aPosTrg.push_back(y(0));
    aPosTrg.push_back(y(1));
    aPosTrg.push_back(y(2));
  }
}

/**
 * energy ||Rp-q||^2 and its gradient and hessian
 * @param[out] W energy
 * @param[out] dW gradient of energy
 * @param[out] ddW hessian of energy
 * @param[in] p source point before rotation
 * @param[in] q target point
 * @param[in] R rotation
 */
void WdWddW_Rotation(
    double& W,
    Eigen::Vector3d& dW,
    Eigen::Matrix3d& ddW,
    const Eigen::Vector3d& p,
    const Eigen::Vector3d& q,
    const Eigen::Matrix3d& R)
{
  const Eigen::Vector3d Rp = R*p;
  W = (Rp-q).squaredNorm();
  // compute gradient and hessian of the energy below.
  // dW =
  // ddW =
}

/**
 * optimize the rotation matrix such that the sum of squared distance
 * between rotated source points and target points are minimized
 * @param[out] R rotation matrix
 * @param[in] aPosSrc source points
 * @param[in] aPosTrg target points
 */
void OptimizeRotation(
    Eigen::Matrix3d& R,
    const std::vector<double>& aPosSrc,
    const std::vector<double>& aPosTrg)
{
  assert( aPosSrc.size() == aPosTrg.size() ); // the number of points should be the same
  assert( aPosSrc.size() % 3 == 0 );
  double W = 0.; // total energy
  Eigen::Vector3d dW = Eigen::Vector3d::Zero(); // gradient of total energy
  Eigen::Matrix3d ddW = Eigen::Matrix3d::Zero(); // hessian of total energy
  for(unsigned int ip=0;ip<aPosSrc.size()/3;++ip){ // loop over points
    const Eigen::Vector3d p = Eigen::Map<const Eigen::Vector3d>(aPosSrc.data()+ip*3); // source point
    const Eigen::Vector3d q = Eigen::Map<const Eigen::Vector3d>(aPosTrg.data()+ip*3); // target point
    double w0;
    Eigen::Vector3d dw0; dw0.setZero();
    Eigen::Matrix3d ddw0; ddw0.setZero();
    WdWddW_Rotation(
        w0,dw0,ddw0,
        p,q,R);
    W += w0;
    dW += dw0;
    ddW += ddw0;
  }
  ddW += 5.e+3*Eigen::Matrix3d::Identity(); // damp for animation
  std::cout << "total energy: " << W << std::endl;
  Eigen::Vector3d dt = (-ddW.inverse())*dW; // rotation vector for update computed by Newton method
  Eigen::Matrix3d dR;
  dR = Eigen::AngleAxis<double>(dt.norm(), dt.normalized());
  R = dR*R; // update rotation matrix
}

// =============================================

// print out error
static void error_callback(int error, const char* description){
  fputs(description, stderr);
}

void DrawProblem(
    const std::vector<double>& aPosSrc,
    const std::vector<double>& aPosTrg,
    const Eigen::Matrix3d& R)
{
  ::glDisable(GL_LIGHTING);
  ::glPointSize(5);
  ::glBegin(GL_POINTS);
  glColor3f(1.f, 0.f, 0.f);
  for(unsigned int ip=0;ip<aPosSrc.size()/3;++ip){
    Eigen::Vector3d Rp = R*Eigen::Map<const Eigen::Vector3d>(aPosSrc.data()+ip*3);
    ::glVertex3d(Rp(0), Rp(1), Rp(2));
  }
  glColor3f(0.f, 0.f, 1.f);
  for(unsigned int ip=0;ip<aPosSrc.size()/3;++ip){
    ::glVertex3d(aPosTrg[ip*3+0], aPosTrg[ip*3+1], aPosTrg[ip*3+2]);
  }
  ::glEnd();
  ::glBegin(GL_LINES);
  glColor3f(0.f, 0.f, 0.f);
  for(unsigned int ip=0;ip<aPosSrc.size()/3;++ip){
    Eigen::Vector3d Rp = R*Eigen::Map<const Eigen::Vector3d>(aPosSrc.data()+ip*3);
    ::glVertex3d(Rp(0), Rp(1), Rp(2));
    ::glVertex3d(aPosTrg[ip*3+0], aPosTrg[ip*3+1], aPosTrg[ip*3+2]);
  }
  ::glEnd();
}

int main()
{
  std::vector<double> aPosSrc, aPosTrg; // source position and target position
  InitializeProblem(aPosSrc,aPosTrg);

  // rotatation matrix to be optimized
  Eigen::Matrix3d R = Eigen::Matrix3d::Identity();
  //
  delfem2::glfw::CViewer3 viewer;
  viewer.camera.view_height = 2.0;
  //
  glfwSetErrorCallback(error_callback);
  if ( !glfwInit() ) { exit(EXIT_FAILURE); }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); // legacy OpenGL
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  // ------
  viewer.InitGL();

  double time_last_update = 0.0;
  const double dt = 1.0/60.0;
  while (!glfwWindowShouldClose(viewer.window)) {
    { // frame rate control
      const double time_now = glfwGetTime();
      if (time_now - time_last_update < dt) {
        glfwPollEvents();
        continue;
      }
      time_last_update = time_now;
    }
    //
    OptimizeRotation(
        R,
        aPosSrc,aPosTrg);
    //
    viewer.DrawBegin_oldGL();
    DrawProblem(
        aPosSrc,aPosTrg,R);
    viewer.SwapBuffers();
    glfwPollEvents();
  }
  glfwDestroyWindow(viewer.window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
