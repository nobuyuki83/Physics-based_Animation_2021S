# Physics-based Animation (物理ベースアニメーション)

**this page is currently under development**

![under construction](doc/mole.png)


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
| (1)<br> Apr. 5 | **Introduction**<br> data structure | [task0](task0) | |
| (2)<br> Apr. 19 | **Time Integration**<br>  backward & forward Euler method,<br> particle system | [task1](task1) |  |
| (3)<br> Apr. 26 | **Collision Detection**<br>  bounding volume hierarchy,<br> Kd-tree, N-tree | [task2](task2) | |
| (4)<br> Mar. 10 | **Simple Deformation Energy**<br> mass-spring system,<br> Eulear-Lagrange equation,<br> Lagrangian mechanics | [task3](task3) | |
| (5)<br> Mar. 17 | **Numerical Optimization**<br>  Newton-Raphson method,<br> Levenberg–Marquardt method | [task4](task4) | |
| (6)<br> Mar. 24 | **Solving Large Linear System**<br> sparse matrix data structure,<br> conjugate gradient method | [task5](task5) | [[1]](http://www.nobuyuki-umetani.com/scribble/linsol_cg.pdf), [[2]](http://www.nobuyuki-umetani.com/scribble/linsol_cgprecond.pdf), [[3]](http://www.nobuyuki-umetani.com/scribble/linsol_ludecomp.pdf) |
| (7)<br> Mar. 31 | **Optimization with Constraint**<br> Lagrange multiplier method | [task6](task6) | |
| (8)<br> Jun. 7  | **Rigid Body Dynamics**<br>inertia tensor, <br>angular velocity | [task7](task7) | [[1]](http://www.nobuyuki-umetani.com/scribble/mech_rotation.pdf),[[2]](http://www.nobuyuki-umetani.com/scribble/mech_rigidbody.pdf) |
| (9)<br> Jun. 14 | **Collision and Friction**<br>Coulomb friction, <br>impulse based method | ~~task8~~ | |
| (10)<br> Jun. 21 | **Continuum Mechanics**<br> tensor, stress and strain | ~~task9~~ | |
| (11)<br> Jun. 28 | **Continuum Mechanics2**<br> finite elemenet method | [task10](task10) | [[1]](https://www.dropbox.com/s/lbrznvk4j7dp577/fem_outline.pdf?dl=0) |
| (12)<br> Jul. 5  | **Non-physical Deformation**<br> singular value decomposition,<br> shape matching method,<br> linear blend skinning,<br> as-rigid-as possible deformation | [task11](task11) | |
| (13)<br> Jul. 12 | **Finite Boundary Method**<br> Green’s functions,<br> thin-plate spline interpolation,<br> radial based function | [task12](task12) | [[1]](http://www.nobuyuki-umetani.com/scribble/bem_laplace.pdf),[[2]](http://www.nobuyuki-umetani.com/scribble/bem_helmholtz.pdf) |


## Grading

- 20% lecture attendance
- 80% small assignemnts

## Assignemnts

There are many small programming assignments. To do the assignments, you need to create your own copy of this repository through **GitHub Classroom**.  These assignements needs to be submitted using **pull request** functionality of the GitHub. Look at the following document. 

[How to Submit the Assignments](doc/submit.md)

### Policy

- Do the assignment by yourself. Don't share the assignments with others.

- Don't post the answers of the assignment on  Slack 

- Late submission of an assignment is subject to grade deduction

- Score each assignemnt will not be open soon (instructer needs to adjust the score later)

  


## Reading Material

[Physically Based Modeling: Principles and Practice, Siggraph '97 Course notes by Dr. Baraff](http://www.cs.cmu.edu/~baraff/sigcourse/index.html)

