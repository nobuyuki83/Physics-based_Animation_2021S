# Task0

Follow the instruction below to build the attached C++ code. This code will display an OpenGL window showing a triangle.  Take a screenshot of the window and paste the image below.  

$$$$$$

(paste the screen shot image here)

$$$$$$



## Instruction 

First of all, make sure your are in the branch `task0`.  You can check your the current branch by

```bash
git branch -a   # list all branches, showing the current branch 
```

If there is no branch with name `task0`, make it by

```bash
git branch task0   # make branch `task0`
```

After creating the branch `task0`, set it as the current branch by

```bash
git checkout task0  # switch into the `task0` branch
```


Set up C++ programming environment. You need git, C++ compiler and cmake installed in your computer. Read the following document 


`GLFW` library is necessary to compile the code. Read the following document


After the environment is ready, let's build and compile the code. We do **out-of-source** build by making a new directory for build `task0/build` and compile inside that directory
```bash
cd task0
mkdir build
cd build
cmake .. 
cmake --build .
```

Update the markdown document by editing `pba-<username>/task0/README.md` (Please learn the syntax of the markdown document by yourself).  

Finally, you submit the document by pushing to the repository. 

```bash
git status
git add .
git commit -m "task0 finished"
git push
```


## Trouble Shooting

- I mistakenly submit the assignement in the `master` branch
  - Make a branch `task0` and submit again








