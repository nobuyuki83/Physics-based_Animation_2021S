
#include "delfem2/glfw/viewer3.h"
#include "delfem2/mshprimitive.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <Eigen/Core>
#include <Eigen/Eigenvalues>

/**
 *
 * @param cg
 * @param aXYZ
 * @param aTri
 * @return
 */
double MassCenterofgravity_MeshTri3(
    double cg[3],
    std::vector<double>& aXYZ,
    std::vector<unsigned int>& aTri)
{ // offset the center of the gravity
  Eigen::Vector3d ecg = Eigen::Vector3d::Zero();
  double M = 0.;
  for(unsigned int it=0;it<aTri.size()/3;++it){
    const Eigen::Vector3d& p0 = Eigen::Map<Eigen::Vector3d>(aXYZ.data()+aTri[it*3+0]*3);
    const Eigen::Vector3d& p1 = Eigen::Map<Eigen::Vector3d>(aXYZ.data()+aTri[it*3+1]*3);
    const Eigen::Vector3d& p2 = Eigen::Map<Eigen::Vector3d>(aXYZ.data()+aTri[it*3+2]*3);
    double area = (p1-p0).cross(p2-p0).norm()/2;
    ecg += area*(p0+p1+p2)/3;
    M += area;
  }
  cg[0] = ecg(0) / M;
  cg[1] = ecg(1) / M;
  cg[2] = ecg(2) / M;
  return M;
}

/**
 *
 * @param Imat
 * @param aXYZ
 * @param aTri
 */
void InertiaTensor(
    Eigen::Matrix3d& Imat,
    std::vector<double>& aXYZ,
    std::vector<unsigned int>& aTri)
{
  // zero clear Imat
  Imat = 1.0e-5*Eigen::Matrix3d::Identity();
  for(unsigned int it=0;it<aTri.size()/3;++it){
    const Eigen::Vector3d ap[3] = {
        Eigen::Map<Eigen::Vector3d>(aXYZ.data()+aTri[it*3+0]*3),
        Eigen::Map<Eigen::Vector3d>(aXYZ.data()+aTri[it*3+1]*3),
        Eigen::Map<Eigen::Vector3d>(aXYZ.data()+aTri[it*3+2]*3)
    };
    const double area = (ap[1]-ap[0]).cross(ap[2]-ap[0]).norm()/2;
    // write some code below to compute inertia tensor
  }
}

/**
 * Read 3D mesh file in Alias *.Obj format
 * @tparam REAL
 * @param path_file
 * @param aXYZ
 * @param aTri
 */
template <typename REAL>
void Read_Obj(
    const std::string& path_file,
    std::vector<REAL>& aXYZ,
    std::vector<unsigned int>& aTri)
{
  std::ifstream fin;
  fin.open(path_file.c_str());
  if (fin.fail()){
    std::cout<<"File Read Fail"<<std::endl;
    return;
  }
  aXYZ.clear();
  aTri.clear();
  aXYZ.reserve(256*16);
  aTri.reserve(256*16);
  const int BUFF_SIZE = 256;
  char buff[BUFF_SIZE];
  while (fin.getline(buff, BUFF_SIZE)){
    if (buff[0]=='#'){ continue; }
    if (buff[0]=='v' && buff[1]==' '){
      char str[256]; REAL x, y, z;
      {
        std::istringstream is(buff);
        is >> str >> x >> y >> z;
      }
      aXYZ.push_back(x);
      aXYZ.push_back(y);
      aXYZ.push_back(z);
    }
    if (buff[0]=='f'){
      char str[256]; int i0, i1, i2;
      {
        std::istringstream is(buff);
        is >> str >> i0 >> i1 >> i2;
      }
      aTri.push_back(i0-1);
      aTri.push_back(i1-1);
      aTri.push_back(i2-1);
    }
  }
}

// print out error
static void error_callback(int error, const char* description){
  fputs(description, stderr);
}

int main()
{
  std::vector<unsigned int> aTri;
  std::vector<double> aXYZ;
  Read_Obj(
      std::string(PATH_SOURCE)+"/fertility.obj",
      aXYZ,aTri);
  { // offset the center of gravity to the origin of the coordinate
    double cg[3];
    double M = MassCenterofgravity_MeshTri3(cg,aXYZ,aTri);
    std::cout << "total mass: " << M << std::endl;
    std::cout << "center of gravity before offset: " << cg[0] << " " << cg[1] << " " << cg[2] << std::endl;
    for(unsigned int ip=0;ip<aXYZ.size()/3;++ip){
      aXYZ[ip*3+0] -= cg[0];
      aXYZ[ip*3+1] -= cg[1];
      aXYZ[ip*3+2] -= cg[2];
    }
    M = MassCenterofgravity_MeshTri3(cg,aXYZ,aTri);
    std::cout << "center of gravity after offset: " << cg[0] << " " << cg[1] << " " << cg[2] << std::endl;
  }

  // compute rotation inertia tensor
  Eigen::Matrix3d Imat;
  InertiaTensor(
      Imat,
      aXYZ,aTri);

  std::cout << "assymmetric components of inertia tensor (should be very small): ";
  std::cout << Imat(0,1)-Imat(1,0) << " ";
  std::cout << Imat(1,2)-Imat(2,1) << " ";
  std::cout << Imat(2,0)-Imat(0,2) << std::endl;

  // eigen decomposition of inertia tensor
  Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> es(Imat);
  std::cout << "eivenvalues of inertia tensor: " << es.eigenvalues().transpose() << std::endl;
  const Eigen::Vector3d ev0 = es.eigenvectors().col(0);
  const Eigen::Vector3d ev1 = es.eigenvectors().col(1);
  const Eigen::Vector3d ev2 = es.eigenvectors().col(2);

  delfem2::glfw::CViewer3 viewer;
  {
    viewer.camera.view_height = 100.0;
    viewer.camera.trans[0] = -0.5;
    viewer.camera.trans[1] = -0.5;
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
    ::glDisable(GL_LIGHTING);
    {
      ::glLineWidth(1);
      ::glColor3d(0, 0, 0);
      ::glBegin(GL_LINES);
      for (unsigned int itri = 0; itri < aTri.size() / 3; ++itri) {
        unsigned int i0 = aTri[itri * 3 + 0];
        unsigned int i1 = aTri[itri * 3 + 1];
        unsigned int i2 = aTri[itri * 3 + 2];
        ::glVertex3dv(aXYZ.data() + i0 * 3);
        ::glVertex3dv(aXYZ.data() + i1 * 3);
        ::glVertex3dv(aXYZ.data() + i1 * 3);
        ::glVertex3dv(aXYZ.data() + i2 * 3);
        ::glVertex3dv(aXYZ.data() + i2 * 3);
        ::glVertex3dv(aXYZ.data() + i0 * 3);
      }
      ::glEnd();
      //
      ::glLineWidth(3);
      const double len = 100;
      ::glBegin(GL_LINES);
      ::glColor3d(1, 0, 0);
      ::glVertex3d(+len*ev0.x(), +len*ev0.y(), +len*ev0.z());
      ::glVertex3d(-len*ev0.x(), -len*ev0.y(), -len*ev0.z());
      ::glColor3d(0, 1, 0);
      ::glVertex3d(+len*ev1.x(), +len*ev1.y(), +len*ev1.z());
      ::glVertex3d(-len*ev1.x(), -len*ev1.y(), -len*ev1.z());
      ::glColor3d(0, 0, 1);
      ::glVertex3d(+len*ev2.x(), +len*ev2.y(), +len*ev2.z());
      ::glVertex3d(-len*ev2.x(), -len*ev2.y(), -len*ev2.z());
      ::glEnd();

    }
    viewer.SwapBuffers();
    glfwPollEvents();
  }
  glfwDestroyWindow(viewer.window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
