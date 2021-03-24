# How to Set Up C++ Programming Environment



To do the assignment, it is necessary to set up the C++ programming environment. Namely, you need **Git** , **C++ Compiler** (of course!) and **cmake**  installed in your computer. This document targets **MacOS**, **Ubuntu** and **Windows**. Depending on the versions of the OS, you may encounter some problems, but I encourage you to sove it by yourself first. These toos are very poupular and there are tons of information on the internet. If you solve the problem, let the instructer know on the slack the problem and solution together with the version of your OS.



## Git 

Git is ncessary to download and upload the assignments. Let's see if the `git` is already installed in your computer. Type the following command and see if the version of the `git` is shown.

```bash
$ git --version
```

If `git` is not installed on your computer, read the following document to install 

https://git-scm.com/book/en/v2/Getting-Started-Installing-Git





## C++ Compilar

For linux, type 

```bash
$ sudo apt-get install build-essential
```



For mac, install `Xcode` first. The Xcode is currently available at

https://developer.apple.com/xcode/

Then, install command line tool with the following command:

```bash
$ xcode-select --install
```

If the install is successful, following command backs the version of the C++ compilar

```bash
$ clang --version
```



For windows, downlod Visual Studio from there (it's free for students)

https://visualstudio.microsoft.com/vs/features/cplusplus/







## CMake

CMake is used to *configure* the project i.e., making a project file to build the code based on the setting written in `CMakeLists.txt`. 

Type following commands to check if you have `cmake` or not in your compuer.

```bash
$ cmake --version
```

If not, download the `cmake` from the link below and instal in your computer.

https://cmake.org/download/

Alternatively, you can install `cmake` using a package manager such as `apt-get` for Ubuntu and `brew` for MacOS. 



