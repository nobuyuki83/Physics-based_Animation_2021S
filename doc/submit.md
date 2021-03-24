## How to Submit the Assignment 

First of all, you need to setup C++ Probramming environment (git, cmake, c++ compilar)

- [How to Set Up C++ Programming Environment](../doc/setup_env.md)



If you don't have the local repository in your computer, clone it from the remote repository

```bash
$ git clone https://github.com/PBA-2021S/pba-<username>.git
```



Sync the local repository to the remote repository.

```bash
$ cd pba-<username>   # go to the local repository
$ git checkout master   # set master branch as the current branch
$ git fetch origin master   # download the master branch from remote repository
$ git reset --hard origin/master   # reset the local master branch same as remote repository
```



You need to install GLFW Library.

- [How to Set Up GLFW Library](../doc/setup_glfw.md)



Create the `task<number>` branch and set it as the current branch. For `task1` the commands look like

```bash
$ git branch task1    # create task1 branch
$ git checkout task1  # switch into the task1 branch
$ git branch -a       # make sure you are in the task1 branch
```

Now, you are ready to edit the code and do the assignment!



=== Edit the code and this mark down document here ===



After you finish editing, you submit the updates pushing to the `task<number>` branch of the remote repository. For `task1` the command look like

```bash
cd pba-<username>    # go to the top of the repository
git status  # check the changes
git add .   # stage the changes
git status  # check the staged changes
git commit -m "task1 finished"   # the comment can be anything
git push --set-upstream origin task1  # update the task1 branch of the remote repository
```



got to the GitHub webpage `https://github.com/PBA-2021S/pba-<username>` . If everything looks good on this page, make a pull request. 

![](../doc/pullrequest.png)