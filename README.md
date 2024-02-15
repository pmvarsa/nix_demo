Demonstration Code
==================

This project contains some example code that I wrote as part of my Ph.D. thesis
work. The main focus of this project was to implement a light transport model
for snow, knows as [SPLITSnow](https://doi.org/10.1109/mcg.2023.3307517). The
core functionality of the light interactions was implemented in C++, whereas the
snow sample specification code was implemented using [Lua](https://www.lua.org/).
To this end, a Lua interpreter was embedded into the C++ simulation code.

The model code for this project is *not* open source. However, for the purpose
of providing a sample of my work, the Lua bindings have been made available in
this project repository. The code compiles and executes, but none of the core
functionality has been included. A Lua script that contains a few lines of
code exemplifying the C++ binding is provided in the `scripts` folder. However
execution is akin to a "Hello, World!" program. The name of the executable is
`nix_demo`, where "nix" was the code name of the project. ("Nix" being Latin for
snow.) The Lua script is named `run.lua`.

Getting Started With SPLITSnow
==============================

This document gives a brief overview of how to get started with the
demonstration code. Instructions are provided for how to build the code, execute
the binary locally, and build the documentation.

SPLITSnow is an acronym which stands for SPectral LIght Transport for Snow.

This document and the project was prepared using Ubuntu 20.04 LTS, which is the
Long Term Support version of Ubuntu. For some additional instructions for
building and executing on newer versions of Ubuntu, please see the additional
documentation at the end of this `README`.

For the Impatient
-----------------

Execute this command that uses `apt` to get the required software packages for
building and executing the model.
```sh
  sudo apt install build-essential cmake libreadline-dev
```

Execute this command which uses `apt` to get the packages required for
documentation generation.
```sh
  sudo apt install doxygen graphviz
```

Now execute these commands to build the application and the supporting
documentation:
```sh
  cd nix_demo  # If not already in this folder
  ./bootstrap
  cd Release
  make -j
  make docs
```

Execute these commands to execute the application, which is functionally
equivalent to a "Hello, World!" program:
```sh
  cd ../scripts
  ./nix_demo ./run.lua
```

View the source code documentation:
```sh
  cd ..
  xdg-open docs/html/index.html
```

Folder Structure
----------------

There are three folders with source code included in this demonstration. These
are:

1. `3rdparty`, which contains the Lua distribution used by the project.
2. `src`, which contains the bulk of the demonstration code.
3. `scripts`, which contains the `run.lua` sample script.

Building the Demonstration
--------------------------

SPLITSnow was designed to work on a Debian-based Linux distribution. In
particular, Ubuntu 18.04 and 20.04 were used for development.

A number of software development packages need to be installed in order to build
the project. The `build-essential` package provides the C++ compiler, the
`cmake` package is used for the build system, and Lua depends upon the
`libreadline-dev` package. Another package, called `xclip` is nice-to-have, but
not essential. The `bootstrap` script uses it to place the next command to run
into the X selection buffer, that is, if you are working on an interactive
display.

Execute these commands to get the software packages:
```sh
  sudo apt install build-essential cmake libreadline-dev
  sudo apt install xclip
```

[CMake](https://cmake.org/) is used as the build system for the SPLITSnow
project. CMake generates a lot of output files and is typically executed in a
build folder, rather than in the project folder. Often separate folders are
created for debug and release builds to save compilation time when working on a
project. A script called `bootstrap` has been provided to create these build
folders and execute the `cmake` command for you. The `bootstrap` script will
also update a symbolic links for you, that point to either the `Release` or
`Debug` folders, as appropriate. For example to configure SPLITSnow for a
release build, execute the following command:
```sh
  ./bootstrap -r
```

Notice that `bootstrap` will output the command to execute next in order to
actually compile SPLITSnow. The suggested command is formatted to execute in a
sub-shell, so that when it is complete, you will end up in the same folder. If
you are working on an interactive desktop environment, then the command should
have been placed in the X selection buffer for you to paste into the terminal
with the middle mouse button. For a debug build execute this command:
```sh
  ./bootstrap -d
```

The default execution of `bootstrap`, without an argument, builds in release
mode. If you do not wish to use the `bootstrap` script, the following commands
can be executed instead.
```sh
  mkdir build
  cd build
  cmake ..
```

Now to actually build the software, simply execute `make` in the `build` folder.
If you have multiple cores, you can save time with the `-j` command line
argument to make. For example, when developing on a machine with eight cores:
```sh
  make -j8
```

The executable will be output into the `build/src/` folder and will be named
`nix_demo`, as expected. You do not need to move or copy this executable,
especially if you used `bootstrap`, since a symbolic link to it will already be
present in the scripts folder.

Executing the SPLITSnow Model
-----------------------------

All scripts and utilities for execution are located in the `nix/scripts` folder.
**NB**: The bulk of these scripts have been removed from the demo, and only an
extremely short "Hello, World!" program has been included.

The simplest way to execute the demo is to use the provided Lua script.
```sh
  ./nix_demo run.lua
```

This command should be executed in the `scripts` folder.

Examining the Code
------------------

Some inline source code documentation exists. It has been formatted to work with
the [Doxygen](http://www.doxygen.nl/) document generation software package.  The
following packages are required to generate HTML documentation for the source
code:
```sh
  sudo apt install doxygen graphviz
```

To generate source code documentation, execute the following command in the
`build` folder:
```sh
  make docs
```

To view the documentation in your default web browser, execute the following
command in the `nix_demo` folder:
```sh
  xdg-open docs/html/index.html
```

Your web browser should open a new tab to the source code documentation. A short
introduction to the code is provided on the main page of the source code
documentation.

