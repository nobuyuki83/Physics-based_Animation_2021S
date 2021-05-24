
#include "delfem2/glfw/viewer2.h"
#include "delfem2/dtri2_v2dtri.h" // triangle mesh generation
#include "delfem2/mshuni.h" // line mesh from triangle mesh
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstdio>

#include <Eigen/Core>
#include <Eigen/LU>

/**
 * compute distance between two points in 2D space
 * @tparam T
 * @param p0
 * @param p1
 * @return distancee
 */
template <typename T>
double distance2(const T* p0, const T* p1)
{
  return sqrt( (p0[0]-p1[0])*(p0[0]-p1[0]) + (p0[1]-p1[1])*(p0[1]-p1[1]) );
}

/**
 * Elastic potential energy of a spring and its gradient & hessian
 * @param[out] W elastic energy of a 2D spring
 * @param[out] dW differentiation of energy w.r.t. positions
 * @param[out] ddW 2nd-order differentiation of energy w.r.t. positions
 * @param[in] ap positions of the end points of an edge
 * @param[in] Len initial length of the spring
 * @param[in] stiffness stiffness of the spring
 */
DFM2_INLINE void WdWddW_Spring2(
    double& W,
    double dW[2][2],
    double ddW[2][2][2][2],
    const double ap[2][2],
    const double Len,
    double stiffness)
{
  constexpr unsigned nnode = 2;
  constexpr unsigned ndim = 2;
  const double len = distance2(ap[0],ap[1]); // distance between p0 and p1
  const double u01[ndim] = { // unit direction vector from p0 to p1
      (ap[1][0] - ap[0][0]) / len,
      (ap[1][1] - ap[0][1]) / len };
  const double C = (len-Len); // the length difference.
  const double dC[nnode][ndim]  = { // gradient of C
      {-u01[0], -u01[1]},
      {+u01[0], +u01[1]} };
  double ddC[nnode][nnode][ndim][ndim]; // hessian of C
  std::fill_n(&ddC[0][0][0][0], nnode*nnode*ndim*ndim, 0.0); // currently ddC is zet to zero.
  for(unsigned int idim=0;idim<ndim;++idim){
    for(unsigned int jdim=0;jdim<ndim;++jdim) {
      // write some code below to compute the ddC.
      // ddC[ino][jno][idim][jdim] means differentiation of C w.r.t. p[ino][idim] and then p[jno][jdim]

//      ddC[0][0][idim][jdim] =
//      ddC[0][1][idim][jdim] =
//      ddC[1][0][idim][jdim] =
//      ddC[1][1][idim][jdim] =
    }
  }
  //
  W = 0.5 * stiffness * C * C; // Hooke's law. energy is square of length difference W=1/2*k*C*C
  for(int ino=0; ino < nnode; ++ino){
    for(int idim=0;idim < ndim;++idim){
      dW[ino][idim] = stiffness * dC[ino][idim] * C; // dW = k*dC*C
    }
  }
  for(int ino=0; ino < nnode; ++ino){
    for (int jno = 0; jno < nnode; ++jno) {
      for (int idim = 0; idim < ndim; ++idim) {
        for (int jdim = 0; jdim < ndim; ++jdim) {
          ddW[ino][jno][idim][jdim] =
              + stiffness * dC[ino][idim] * dC[jno][jdim]
              + stiffness * C * ddC[ino][jno][idim][jdim]; // ddW = k*dC*dC + k*C*ddC
        }
      }
    }
  }
}


/**
 * One Newton iteration to solve deformation by energy minimization.
 * @param[in,out] aXY current position
 * @param[in] aXY0 position in the rest state
 * @param[in] aLine element index showing connectivity of points
 * @param[in] stiffness stiffness of the spring
 * @param[in] mass_point mass of point
 * @param[in] gravity gravitational acceleration
 * @param[in] aBCFlag array of flags showing which degree of freedom is free (0) or fixed(1)
 */
void EnergyMinimization(
    std::vector<double>& aXY,
    const std::vector<double>& aXY0,
    const std::vector<unsigned int>& aLine,
    double stiffness,
    double mass_point,
    const double gravity[2],
    const std::vector<int>& aBCFlag)
{ // simulation
  const unsigned int np = aXY.size()/2; // number of points
  const unsigned int nDof = aXY.size(); // total degree of freedom
  Eigen::MatrixXd hessW(nDof,nDof); // hessian matrix
  Eigen::VectorXd gradW(nDof); // gradient vector
  hessW.setZero();
  gradW.setZero();
  double W = 0.0;
  for(int il=0;il<aLine.size()/2;++il){ // loop over springs
    unsigned int ip0 = aLine[il*2+0]; // index of point0
    unsigned int ip1 = aLine[il*2+1]; // index of point1
    const double Len = distance2(aXY0.data()+ip0*2, aXY0.data()+ip1*2); // initial length
    const double ap[2][2] = {
        { aXY[ip0*2+0], aXY[ip0*2+1] },
        { aXY[ip1*2+0], aXY[ip1*2+1] } };
    double w, dw[2][2], ddw[2][2][2][2];
    WdWddW_Spring2(
        w,dw,ddw,
        ap,Len,stiffness);
    W += w;
    // merge gradient
    for(unsigned int ino=0;ino<2;++ino) {
      unsigned int ip = aLine[il*2+ino];
      gradW(ip*2+0) += dw[ino][0];
      gradW(ip*2+1) += dw[ino][1];
    }
    // merge hessian
    for(unsigned int ino=0;ino<2;++ino) {
      for(unsigned int jno=0;jno<2;++jno) {
        unsigned int ip = aLine[il*2+ino];
        unsigned int jp = aLine[il*2+jno];
        hessW(ip * 2 + 0, jp * 2 + 0) += ddw[ino][jno][0][0];
        hessW(ip * 2 + 0, jp * 2 + 1) += ddw[ino][jno][0][1];
        hessW(ip * 2 + 1, jp * 2 + 0) += ddw[ino][jno][1][0];
        hessW(ip * 2 + 1, jp * 2 + 1) += ddw[ino][jno][1][1];
      }
    }
  }
  // adding gradient of gravitational potential energy (hessian is zero for gravity energy)
  for(unsigned int ip=0;ip<np;++ip) {
    gradW(ip*2+0) -= mass_point*gravity[0];
    gradW(ip*2+1) -= mass_point*gravity[1];
    W -= mass_point*gravity[0]*aXY[ip*2+0] + mass_point*gravity[1]*aXY[ip*2+1];
  }
  std::cout << "energy of the system " << W << std::endl;
  // adding boundary condition
  for(unsigned int i=0;i<nDof;++i){
    if( aBCFlag[i] == 0 ){ continue; } // if this DoF is free, skip
    gradW[i] = 0;
    for(unsigned int j=0;j<nDof;++j) {
      hessW(i,j) = hessW(j,i) = 0.0;
    }
    hessW(i,i) = 1.0;
  }
  Eigen::FullPivLU< Eigen::MatrixXd > lu(hessW); // LU decomposition
  Eigen::VectorXd update = lu.solve(gradW); // solve matrix
  // update position
  for(unsigned int ip=0;ip<np;++ip){
    aXY[ip*2+0] -= update(ip*2+0);
    aXY[ip*2+1] -= update(ip*2+1);
  }
}

void SettingUpSimulation(
    std::vector<double>& aXY,
    std::vector<unsigned int>& aLine,
    std::vector<int>& aBCFlag)
{
  // generating mesh inside input polygon (aLoop)
  const std::vector< std::vector<double> > aLoop = { {-1,0, +1,0, +1,+0.3, -1,+0.3} };
  std::vector<delfem2::CDynPntSur> aPo2D;
  std::vector<delfem2::CDynTri> aETri;
  std::vector<delfem2::CVec2d> aVec2;
  delfem2::GenMesh(
      aPo2D, aETri, aVec2,
      aLoop, 0.07, 0.07);
  std::vector<unsigned int> aTri;
  delfem2::CMeshTri2D(
      aXY, aTri,
      aVec2, aETri);
  // convert triangle elements to line elements
  delfem2::MeshLine_MeshElem(
      aLine,
      aTri.data(),aTri.size()/3,delfem2::MESHELEM_TRI,aXY.size()/2);
  // setting up boundry condition (fixing the both ends of the rectangle)
  aBCFlag.resize(aXY.size(),0);
  for(unsigned int ip=0;ip<aXY.size()/2;++ip){
    if( aXY[ip*2+0] < -0.99 || aXY[ip*2+0] > +0.99 ){ // fix the both ends of rectangle
      aBCFlag[ip*2+0] = 1;
      aBCFlag[ip*2+1] = 1;
    }
  }
}

// =============================================

// print out error
static void error_callback(int error, const char* description){
  fputs(description, stderr);
}

void DrawMeshLine2(
    const std::vector<double>& aXY,
    const std::vector<unsigned int>& aLine)
{
  glBegin(GL_LINES);
  for(unsigned int it=0;it<aLine.size()/2;++it){
    ::glVertex2dv(aXY.data()+aLine[it*2+0]*2);
    ::glVertex2dv(aXY.data()+aLine[it*2+1]*2);
  }
  glEnd();
}

int main()
{
  std::vector<double> aXY;
  std::vector<unsigned int> aLine;
  std::vector<int> aBCFlag;
  SettingUpSimulation(aXY,aLine,aBCFlag);
  const std::vector<double> aXY0 = aXY; // initial position
  const double gravity[2] = {0., -10.0};
  const double stiffness = 1.0e+4;
  const double mass_point = 1.0;
  //
  delfem2::glfw::CViewer2 viewer;
  {
    viewer.view_height = 1.0;
    viewer.title = "task3: Mass-spring System";
  }
  glfwSetErrorCallback(error_callback);
  if ( !glfwInit() ) { exit(EXIT_FAILURE); }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  // ------
  viewer.InitGL();

  while (!glfwWindowShouldClose(viewer.window)) {
    EnergyMinimization(
        aXY,
        aXY0, aLine, stiffness, mass_point, gravity, aBCFlag);
    //
    viewer.DrawBegin_oldGL();
    // initial configuration (red)
    glColor3f(1.f, 0.f, 0.f);
    DrawMeshLine2(aXY0,aLine);
    // deformed configuration (black)
    glColor3f(0.f, 0.f, 0.f);
    DrawMeshLine2(aXY,aLine);
    viewer.SwapBuffers();
    glfwPollEvents();
  }
  glfwDestroyWindow(viewer.window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
