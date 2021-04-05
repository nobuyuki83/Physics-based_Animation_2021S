# How to Submit the Assignment 

There are many small programming assignments. These assignements needs to be submitted using **pull request** functionality of the GitHub. 



## Making your repository using GitHub Classroom

![](../doc/githubclassroom.png)

The assignment is submitted using "pullrequest" functionality of the GitHub. Using the system called "GitHub Classroom", students makes their own private repository that is a copy of "https://github.com/PBA-2021S/pba". If a student have a GitHub account named "hoge", the name of the repository will be "pba-hoge". The private repository if only visible from the student and the instructor. In the second class, It will be shown how to make your own class repository using GitHub classroom. 



## Overview

![](../doc/branchstructure.png)

Let's assume you are looking at the repository `pba-<username>` (e.g., pba-nobuyuki83) and the  `task<task number>` is the assignment (e.g., task2). The submission is made by

1. create a branch of the name `task<task number>`

2. follow the instruction written in `\pba-<username>/task<task number>/README.md`

3. push the repository with the branch `task<task number>`

4. make a pull request on GitHub page

5. Instructor will close the pull request after grading. 

   

## Setup C++ Programming Environment

First of all, you need to setup C++ Probramming environment (git, cmake, c++ compilar)

- [How to Set Up C++ Programming Environment](../doc/setup_env.md)



## Download the Repository

If you don't have the local repository in your computer, clone it from the remote repository

```bash
$ git clone https://github.com/PBA-2021S/pba-<username>.git
```

**Before doing each assignment**, Sync the local repository to the remote repository.

```bash
$ cd pba-<username>   # go to the local repository
$ git checkout master   # set master branch as the current branch
$ git fetch origin master   # download the master branch from remote repository
$ git reset --hard origin/master   # reset the local master branch same as remote repository
```



## Setup Library

You need to install GLFW Library.

- [How to Set Up GLFW Library](../doc/setup_glfw.md)



## Make Branch for Each Assignment

Create the `task<number>` branch and set it as the current branch. For `task1` the commands look like

```bash
$ git branch task1    # create task1 branch
$ git checkout task1  # switch into the task1 branch
$ git branch -a       # make sure you are in the task1 branch
```

Now, you are ready to edit the code and do the assignment!



## Do the Assignment

 Edit the code and this mark down document.



## Upload the Change

After you finish editing, you submit the updates pushing to the `task<number>` branch of the remote repository. For `task1` the command look like

```bash
cd pba-<username>    # go to the top of the repository
git status  # check the changes
git add .   # stage the changes
git status  # check the staged changes
git commit -m "task1 finished"   # the comment can be anything
git push --set-upstream origin task1  # update the task1 branch of the remote repository
```



## Make a Pull Request

got to the GitHub webpage `https://github.com/PBA-2021S/pba-<username>` . If everything looks good on this page, make a pull request. 

![](../doc/pullrequest.png)



## Trouble Shooting

I mistakenly submit the assignement in the `master` branch

- Make a branch `task<number>` and submit again