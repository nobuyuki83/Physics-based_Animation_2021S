# Task3: Mass-spring System

**Deadline: May 27th (Thursday) at 15:00pm**

![preview](preview.png)

## Setting Up

Please take a look at the following document for environment setup, creating branch, and making pull request.

[How to Submit the Assignment](../doc/submit.md)

In this assignment, it is necessary to install [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page) library. 
Please follow the following document for setting up.    

[How to set up the Eigen Library](../doc/setup_eigen.md)  


Additionally, you need the library [DelFEM2](https://github.com/nobuyuki83/delfem2) in `pba-<username>/3rd_party` 

```bash
$ cd pba-<username> # go to the top of local repository
$ git submodule update --init 3rd_party/delfem2
```

(DelFEM2 is a collection of useful C++ codes written by the instructer.)



## Problem1

Run the program and take a screen shot.

=== paset screenshot here ===



## Problem 2

The current program to comute hessian of the enegy is not complete. 
Fill the code around line #56 to optimize the deformation energy by solving the minimization of the deformation energy. 










