# Physics-based Animation (物理ベースアニメーション)

ITC-LMS: 
- https://itc-lms.ecc.u-tokyo.ac.jp/lms/course?idnumber=20214860-10810F01



## Instructor

Dr. Nobuyuki Umetani 
- email: umetani@ci.i.u-tokyo.ac.jp
- url: http://www.nobuyuki-umetani.com/
- lab's website: https://cgenglab.github.io/labpage/en/

## Time

Time: Monday 3rd period, 13:00pm - 14:30pm

## Course Description

Abstract: Computer-generated images are everywhere in movies, video games, and VR. This course is an introduction to the techniques to animate objects in computer graphics based on the law of physics. The aim of the course is to get familiar with applied mathematics such as linear algebra, vector analysis, partial differential equations, variational principle, optimization, and numerical analysis through the animation techniques for particle systems, rigid bodies, elastic bodies. There are C++ programming assignments to acquire research-oriented graphics programming skills. 

Topics:
- mass-spring simulation
- rigid body simulation
- elastic body simulation
- cloth and hair modeling & simulation
- collision-detection using spatial hashing
- finite boundary method


## Lecture Schedule

| Day | Topic | Assignment | Scribble |
|:----|:---|:---|:---|
| (1) Apr. 5th | **Introduction**<br> data structure | task0 | |
| (2) Apr. 19th | **Time Integration**<br>  backward & forward Euler method,<br> particle system | task1 |  |
| (3) Apr. 26th | **Collision Detection**<br>  bounding volume hierarchy,<br> Kd-tree, N-tree | task2 | |
| (4) Mar. 10th | **Simple Deformation Energy**<br>  mass-spring system,<br> Eulear-Lagrange equation,<br> Lagrangian mechanics | ~~task2~~ | |
| (5) Mar. 17th | **Numerical Optimization**<br>  Newton-Raphson method,<br> Levenberg–Marquardt method | task3 | |
| (6) Mar. 24th | **Solving Large Linear System**<br>  matrix data structure,<br> conjugate gradient method | task4 | [[1]](https://www.dropbox.com/s/7fezkmqrz37tquw/linsol_cg.pdf?dl=0), [[2]](https://www.dropbox.com/s/aig0o766erjy41h/linsol_cgprecond.pdf?dl=0), [[3]](https://www.dropbox.com/s/k6vxthj7n27prc4/linsol_ludecomp.pdf?dl=0) |
| (7) Mar. 31st | **Optimization with Constraint**<br>  Lagrange multiplier method | task5 | |
| (8) Jun. 7th  | **Rigid Body Dynamics**<br>  inertia tensor, angular velocity | task6 | [[1]](https://www.dropbox.com/s/4ibh1l6ubdvie48/mech_rotation.pdf?dl=0),[[2]](https://www.dropbox.com/s/agiplv7a0rdm39d/mech_rigidbody.pdf?dl=0) |
| (9) Jun. 14th | **Collision and Friction**<br>  Coulomb friction, impulse based method | task7 | |
| (10) Jun. 21st | **Continuum Mechanics**<br>  mesh discretization, stress and strain | task8 | |
| (11) Jun. 28st | **Continuum Mechanics2**<br>  finite elemenet method | task9 | [[1]](https://www.dropbox.com/s/lbrznvk4j7dp577/fem_outline.pdf?dl=0) |
| (12) Jul. 5th  | **Non-physical Deformation**<br>  singular value decomposition,<br> shape matching method,<br> linear blend skinning,<br> as-rigid-as possible deformation | task10 | |
| (13) Jul. 12nd | **Finite Boundary Method**<br>  Green’s functions, thin-plate spline interpolation,<br> radial based function | task11 | [[1]](https://www.dropbox.com/s/50yjspzj79t3oos/bem_laplace.pdf?dl=0),[[2]](https://www.dropbox.com/s/9v8ld9f9kjd28vf/bem_helmholtz.pdf?dl=0) |

## Grading

- 20% lecture attendance
- 80% small assignemnts

There are many small programming assignments. These assignements needs to be submitted using **pull request** functionality of the GitHub. Let's assume you are looking at the repository `pba-<your GitHub account name>` (e.g., pba-nobuyuki83) and the  `task<task number>` is the assignment (e.g., task2). The submission is made by
1. create a branch of the name `task<task number>`
2. in that branch, go to the folder `\pba-<your GitHub account name>/task<task number>`
3. follow the instruction written in `\pba-<your GitHub account name>/task<task number>/README.md`
4. push the repository with the branch `task<task number>`
5. make a pull request 

Instructor will close the pull request after grading. 

*The submission of an assignment after its deadline is subject to point deduction.*


## Reading Material

[Physically Based Modeling: Principles and Practice, Siggraph '97 Course notes by Dr. Baraff](http://www.cs.cmu.edu/~baraff/sigcourse/index.html)

