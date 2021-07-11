# Physics-based Animation 4860-1081 


| Linux | Windows |
| --- | --- |
| [![BuildTasks](https://github.com/PBA-2021S/pba/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/PBA-2021S/pba/actions/workflows/ubuntu.yml) | [![BuildTasks](https://github.com/PBA-2021S/pba/actions/workflows/windows.yml/badge.svg)](https://github.com/PBA-2021S/pba/actions/workflows/windows.yml) |


![under construction](doc/rep_image.png)

Lecture at graduate school of information science and technology in the university of Tokyo, spring semester, 2021

ITC-LMS (for Slack and GitHub Classroom invitaitons): 

- https://itc-lms.ecc.u-tokyo.ac.jp/lms/course?idnumber=20214860-10810F01



## Instructor

Dr. Nobuyuki Umetani 
- email: umetani@ci.i.u-tokyo.ac.jp
- url: http://www.nobuyuki-umetani.com/
- lab's website: https://cgenglab.github.io/labpage/en/

## Time

Monday 3rd period, 13:00pm - 14:30pm

## Course Description

Computer-generated images are everywhere in movies, video games, and VR. 
This course is an introduction to the techniques to animate objects in computer graphics based on the law of physics. 
The aim of the course is to get familiar with applied mathematics such as linear algebra, vector analysis, partial differential equations, variational principle, optimization, and numerical analysis through the animation techniques for particle systems, rigid bodies, elastic bodies. 
There are C++ programming assignments to acquire research-oriented graphics programming skills. 

Topics:
- mass-spring simulation
- rigid body simulation
- elastic body simulation
- cloth and hair modeling & simulation
- collision-detection using spatial hashing
- finite boundary method


## Lecture Schedule

| Day | Topic | Assignment | Scribble | Slide |
|:----|:---|:---|:---|-----|
| (1)<br> Apr. 5 | **Introduction**<br> |  | | [[1]](http://www.nobuyuki-umetani.com/pba2021s/introduction.pdf), [[2]](http://www.nobuyuki-umetani.com/pba2021s/data_structure.pdf) |
| (2)<br> Apr. 19 | **Data Structure**<br>data structure for simulation<br/>Implicit surface | [task0](task0)<br>deadline: Apr.22th|  | [[2]](http://www.nobuyuki-umetani.com/pba2021s/data_structure.pdf) |
| (3)<br> Apr. 26 | **Time Integration**<br/> Newtonian-mechanics<br/> backward & forward Euler method,<br/> particle system | [task1](task1)<br />deadline: Apr. 29th | | [[14]](http://www.nobuyuki-umetani.com/pba2021s/newtonian_mechanics.pdf), [[3]](http://www.nobuyuki-umetani.com/pba2021s/time_integration.pdf) |
| (4)<br> Mar. 10 | **Broad-phase Collision Detection**<br/>princepal component analysis<br>sort & sweep method <br/>bounding volume hierarchy | [task4](task4)<br>deadline: May. 13th | | [[18]](http://www.nobuyuki-umetani.com/pba2021s/pca.pdf), [[5]](http://www.nobuyuki-umetani.com/pba2021s/collision_detection_broad.pdf) |
| (5)<br> May. 17 | **Numerical Optimization**<br/>Hessian & Jacobian,<br>Newton-Raphson method | [task2](task2)<br>deadline: May 20th | | [[19]](http://www.nobuyuki-umetani.com/pba2021s/optimization.pdf) |
| (6)<br> May. 24 | **Simple Deformation Energy**<br/>mass-spring system | [task3](task3)<br>deadline: May 27th | [[1]](http://www.nobuyuki-umetani.com/pba2021s/linsol_cg.pdf), [[2]](http://www.nobuyuki-umetani.com/pba2021s/linsol_cgprecond.pdf), [[3]](http://www.nobuyuki-umetani.com/pba2021s/linsol_ludecomp.pdf) | [[6]](http://www.nobuyuki-umetani.com/pba2021s/mass_spring_system.pdf) |
| (7)<br> May. 31 | **Solving Large Linear System**<br/>Sparse matrix data structure<br/>Conjugate gradient method | [task5](task5)<br>deadline: June 3rd | | [[8]](http://www.nobuyuki-umetani.com/pba2021s/linear_system_solver.pdf),[[20]](http://www.nobuyuki-umetani.com/pba2021s/matrix_data_structure.pdf) |
| (8)<br> Jun. 7  | **Optimization with Constraint**<br/>Lagrange multiplier method<br>**Rigid Body Dynamics**<br>Rotation representation | [task6](task6)<br>deadline: June 10th | [[4]](http://www.nobuyuki-umetani.com/pba2021s/mech_rotation.pdf), [[5]](http://www.nobuyuki-umetani.com/pba2021s/mech_rigidbody.pdf) | [[9]](http://www.nobuyuki-umetani.com/pba2021s/optimization_with_constraints.pdf),[[21]](http://www.nobuyuki-umetani.com/pba2021s/rotation.pdf) |
| (9)<br> Jun. 14 | **Rigid Body Dynamics2**<br/>inertia tensor, <br/>angular velocity<br>impulse based method | [task7](task7)<br>deadline: June 17th | | [[10]](http://www.nobuyuki-umetani.com/pba2021s/rigid_body_dynamics.pdf) |
| (10)<br> Jun. 21 | Lagrangian mechanics<br />Variational time integration<br />**Continuum Mechanics**<br> tensor | [task8](task8)<br>deadline: June 24th | [[6]](http://www.nobuyuki-umetani.com/pba2021s/mech_fluidcontinuum.pdf), [[7]](http://www.nobuyuki-umetani.com/pba2021s/mech_fluidgoverning.pdf) | [[17]](http://www.nobuyuki-umetani.com/pba2021s/lagrangian_mechanics.pdf), [[16] ](http://www.nobuyuki-umetani.com/pba2021s/variational_integration.pdf) |
| (11)<br> Jun. 28 | **Continuum Mechanics2**<br>Mesh interpolation<br />Tensor | [task11](task11)<br>deadline: July 1st | [[8]](http://www.nobuyuki-umetani.com/pba2021s/fem_outline.pdf), [[9]](http://www.nobuyuki-umetani.com/pba2021s/fem_linearsolid.pdf), [[10]](http://www.nobuyuki-umetani.com/pba2021s/fem_mitc3.pdf) | [[4]](http://www.nobuyuki-umetani.com/pba2021s/grid_mesh_interpolation.pdf), [[12]](http://www.nobuyuki-umetani.com/pba2021s/tensor.pdf) |
| (12)<br> Jul. 5  | **Geometric Deformation**<br> singular value decomposition,<br> shape matching method,<br> linear blend skinning,<br> as-rigid-as possible deformation | [task9](task9)<br>deadline: July 8th | | [[22]](http://www.nobuyuki-umetani.com/pba2021s/geometric_deformation.pdf) |
| (13)<br> Jul. 12 | **Advanced Interpolation**<br> mean value coordinate,<br> radial based function |  | [[11]](http://www.nobuyuki-umetani.com/pba2021s/bem_laplace.pdf), [[12]](http://www.nobuyuki-umetani.com/pba2021s/bem_helmholtz.pdf) | [[23]](http://www.nobuyuki-umetani.com/pba2021s/advanced_interpolation.pdf) |


## Grading

- 20% lecture attendance
  - Counted by attending the lecture, asking question, and making comments ...etc
  - Number of question counts: maximum 1 count for 1 lecture, ~~5~~  **2** counts for entire course
  - Attendance is counted based on writing a secret keyword on LMS. The keyword is announced for each lecture.  
- 80% small assignemnts
  - see below

## Assignemnts

There are many small programming assignments. To do the assignments, you need to create your own copy of this repository through **GitHub Classroom**.  These assignements needs to be submitted using **pull request** functionality of the GitHub. Look at the following document. 

[How to Submit the Assignments](doc/submit.md)

### Policy

- Do the assignment by yourself. Don't share the assignments with others.
- Don't post the answers of the assignment on Slack 
- Late submission of an assignment is subject to grade deduction
- Score each assignemnt will not be open soon (instructer needs to adjust weight of the score later)

### Tasks

- [task0](task0): Make C++ Program with CMake
- [task1](task1): Particle System
- [task2](task2): Optimization
- [task3](task3): Mass-spring system
- [task4](task4): Sort & Sweep Method
- [task5](task5): Solving Large Linear System
- [task6](task6): Optimization with Constraints
- [task7](task7): Optimization of Rotation
- [task8](task8): Variational Implicit Euler
- [task9](task9): Shape Matching Method
- [task11](task11): Inertia Tensor



## Slides

- [[1] introduction](http://www.nobuyuki-umetani.com/pba2021s/introduction.pdf)
- [[2] data_structure](http://www.nobuyuki-umetani.com/pba2021s/data_structure.pdf)
- [[3] time_integration](http://www.nobuyuki-umetani.com/pba2021s/time_integration.pdf)
- [[4] grid_mesh_interpolation](http://www.nobuyuki-umetani.com/pba2021s/grid_mesh_interpolation.pdf)
- [[5] collision_detection_broad](http://www.nobuyuki-umetani.com/pba2021s/collision_detection_broad.pdf)
- [[6] mass_spring_system](http://www.nobuyuki-umetani.com/pba2021s/mass_spring_system.pdf)
- [[8] linear_system_solver](http://www.nobuyuki-umetani.com/pba2021s/linear_system_solver.pdf)
- [[9] optimization with constraints](http://www.nobuyuki-umetani.com/pba2021s/optimization_with_constraints.pdf)
- [[10] rigid_body_dynamics](http://www.nobuyuki-umetani.com/pba2021s/rigid_body_dynamics.pdf)
- [[12] tensor](http://www.nobuyuki-umetani.com/pba2021s/tensor.pdf)
- [[13] cpp language](http://www.nobuyuki-umetani.com/pba2021s/cpp.pdf)
- [[14] newtonian mechanics](http://www.nobuyuki-umetani.com/pba2021s/newtonian_mechanics.pdf)
- [[15] git+github](http://www.nobuyuki-umetani.com/pba2021s/git.pdf)
- [[16] variational_integration](http://www.nobuyuki-umetani.com/pba2021s/variational_integration.pdf)
- [[17] lagrangian_mechanics](http://www.nobuyuki-umetani.com/pba2021s/lagrangian_mechanics.pdf)
- [[18] pca](http://www.nobuyuki-umetani.com/pba2021s/pca.pdf)
- [[19] optimization](http://www.nobuyuki-umetani.com/pba2021s/optimization.pdf)
- [[20] matrix_data_structure](http://www.nobuyuki-umetani.com/pba2021s/matrix_data_structure.pdf)
- [[21] rotation representation](http://www.nobuyuki-umetani.com/pba2021s/rotation.pdf)
- [[22]geometric_defmormation](http://www.nobuyuki-umetani.com/pba2021s/geometric_deformation.pdf)
- [[23]advanced_interpolation](http://www.nobuyuki-umetani.com/pba2021s/advanced_interpolation.pdf)




## Reading Material

- [Physically Based Modeling: Principles and Practice, Siggraph '97 Course notes by Dr. Baraff](http://www.cs.cmu.edu/~baraff/sigcourse/index.html)
- [Physics-Based Animation  by Kenny Erleben et al. (free textobook about rigid body dynamics)](https://iphys.wordpress.com/2020/01/12/free-textbook-physics-based-animation/)
- [Dynamic Deformables: Implementation and Production Practicalities, SIGGRAPH 2020 Courses](http://www.tkim.graphics/DYNAMIC_DEFORMABLES/)
- [Awesome Computer Graphics (GitHub)](https://github.com/luisnts/awesome-computer-graphics)
- [Skinning: Real-time Shape Deformation SIGGRAPH 2014 Course](https://skinning.org/)

