
#include "delfem2/glfw/viewer2.h"
#include "delfem2/dtri2_v2dtri.h" // triangle mesh generation
#include "delfem2/mshuni.h" // point surrounding point array generation
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <random>
#include <cstdio>

/**
 * Optimize the position of the mesh to reduce the energy
 * energy is defined as the sum of squared lengths of the edges of the mesh
 * @param[in,out] aXY array of coordinates
 * @param[in] aPsupInd array of index for jagged array
 * @param[in] aPsup array of neighbouring index for jagged array
 * @param[in] aBCFlag if BCFlag is not 0, that point needs to be fixed.
 */
void GaussSeidelRelaxation(
    std::vector<double>& aXY,
    const std::vector<unsigned int>& aPsupInd,
    const std::vector<unsigned int>& aPsup,
    const std::vector<int>& aBCFlag)
{
  const auto np = aXY.size() / 2;
  for (auto ip = 0; ip < np; ++ip) { // loop over all the point
    if( aBCFlag[ip] != 0 ){ continue; }
    const unsigned int nneighbour = aPsupInd[ip + 1] - aPsupInd[ip]; // number of points neighbouring ip
    if( nneighbour == 0 ){ continue; }
    double pos_new[2] = {0., 0.}; // new coordinate. Put it at the center of gravity of the neighbouring points
    for (auto ipsup = aPsupInd[ip]; ipsup < aPsupInd[ip + 1]; ++ipsup) {
      const unsigned int jp = aPsup[ipsup]; // index of point neighbouring ip
      // write something here
      // write something here
    }
    // write something here
    // un-comment below
    // aXY[ip*2+0] = pos_new[0]; // update the x-coordinate of ip
    // aXY[ip*2+1] = pos_new[1]; // update the y-coordinate of ip
  }
}

/**
 * Compute the energy that is defined as the sum of squared lengths of the edges of the mesh
 * @param[in] aXY array of coordinates
 * @param[in] aPsupInd array of index for jagged array
 * @param[in] aPsup array of neighbouring index for jagged array
 * @return energy
 */
double Energy(
    const std::vector<double>& aXY,
    const std::vector<unsigned int>& aPsupInd,
    const std::vector<unsigned int>& aPsup)
{
  const auto np = aXY.size() / 2;
  double W = 0.0;
  for (auto ip = 0; ip < np; ++ip) {
    const double* p0 = aXY.data()+ip*2;
    for (auto ipsup = aPsupInd[ip]; ipsup < aPsupInd[ip + 1]; ++ipsup) {
      const unsigned int jp = aPsup[ipsup];
      const double* p1 = aXY.data()+jp*2;
      W += (p0[0]-p1[0])*(p0[0]-p1[0]) + (p0[1]-p1[1])*(p0[1]-p1[1]);
    }
  }
  return W;
}

void SettingUpSimulation(
    std::vector<double>& aXY,
    std::vector<unsigned int>& aPsupInd,
    std::vector<unsigned int>& aPsup,
    std::vector<int>& aBCFlag)
{
  // generating mesh inside input polygon (aLoop)
  double Lx = 1;
  double Ly = 1;
  const std::vector< std::vector<double> > aLoop = { {-Lx,-Ly, +Lx,-Ly, +Lx,+Ly, -Lx,+Ly} };
  std::vector<delfem2::CDynPntSur> aPo2D;
  std::vector<delfem2::CDynTri> aETri;
  std::vector<delfem2::CVec2d> aVec2;
  delfem2::GenMesh(
      aPo2D, aETri, aVec2,
      aLoop, 0.03, 0.03);
  std::vector<unsigned int> aTri;
  delfem2::CMeshTri2D(
      aXY, aTri,
      aVec2, aETri);
  delfem2::JArray_PSuP_MeshElem(
      aPsupInd,aPsup,
      aTri.data(), aTri.size()/3, 3, aXY.size()/2);
  // setting up boundry condition (fixing the both ends of the rectangle)
  aBCFlag.resize(aXY.size()/2,0);
  for(unsigned int ip=0;ip<aXY.size()/2;++ip){
    if( aXY[ip*2+0] < -Lx*0.99
    || aXY[ip*2+0] > +Lx*0.99
//    || aXY[ip*2+1] < -Ly*0.99
    || aXY[ip*2+1] > +Ly*0.99 ) {
      aBCFlag[ip] = 1;
    }
  }
}

// =============================================

// print out error
static void error_callback(int error, const char* description){
  fputs(description, stderr);
}

void DrawMesh2_Psup(
    const std::vector<double> &aXY,
    const std::vector<unsigned int>& aPsupInd,
    const std::vector<unsigned int>& aPsup)
{
  glBegin(GL_LINES);
  const auto np = aXY.size()/2;
  for(auto ip=0;ip<np;++ip){
    for(auto ipsup=aPsupInd[ip];ipsup<aPsupInd[ip+1];++ipsup) {
      const unsigned int jp = aPsup[ipsup];
      ::glVertex2dv(aXY.data() + ip * 2);
      ::glVertex2dv(aXY.data() + jp * 2);
    }
  }
  glEnd();
}

int main()
{
  std::vector<double> aXY;
  std::vector<unsigned int> aPsupInd;
  std::vector<unsigned int> aPsup;
  std::vector<int> aBCFlag;
  SettingUpSimulation(aXY,aPsupInd,aPsup,aBCFlag);
  {
    std::mt19937 rndeng(std::random_device{}());
    std::uniform_real_distribution<double> dist_m1p1(-1.,+1.);
    for(auto ip=0;ip<aXY.size()/2;++ip){
      if( aBCFlag[ip] != 0 ){ continue; }
      aXY[ip*2+0] += 0.5*dist_m1p1(rndeng);
      aXY[ip*2+1] += 0.5*dist_m1p1(rndeng);
    }
  }
  //
  delfem2::glfw::CViewer2 viewer;
  {
    viewer.view_height = 1.2;
    viewer.title = "task5: Solving Large Linear System";
  }
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
    std::cout << "number of points: " << aXY.size()/2 << ",  energy: " << Energy(aXY,aPsupInd,aPsup) << std::endl;
    GaussSeidelRelaxation(
        aXY,
        aPsupInd, aPsup,aBCFlag);
    //----
    viewer.DrawBegin_oldGL();
    glColor3f(0.f, 0.f, 0.f);
    DrawMesh2_Psup(aXY, aPsupInd, aPsup);
    viewer.SwapBuffers();
    glfwPollEvents();
  }
  glfwDestroyWindow(viewer.window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
