# C++ Boilerplate
[![Build Status](https://travis-ci.org/jeshoward/RRTPath.svg?branch=master)](https://travis-ci.org/jeshoward/RRTPath)
[![Coverage Status](https://coveralls.io/repos/github/jeshoward/RRTPath/badge.svg?branch=master)](https://coveralls.io/github/jeshoward/RRTPath?branch=master)
---
## Rapidly Exploring Random Tree Pathing Algorithm ##

A simple rapidly exploring random tree path algorithm implementation. Includes four classes:
-RRTPath
-Vertex
-Map
-Obstacle

The RRTPath class relies upon the map, vertex, and obstacle classes to function. It accepts a map, with or without obstacles, a starting location on the map, a goal location on the map, a distance that the RRT expands at each step, a distance that the RRT uses to check for collisions, and a radius for the goal. It returns the first path it finds (not always the most efficient) between the starting location and the goal as a list of x,y coordinate pairs.

Vertices are simple structures used by RRTPath to keep track of the RRT expansions and to rebuild the path from the start to the goal. They consist of an x,y coordinate location and a link to the vertex that preceded it.

The map class is a simple grid. The default size of the map is 10x10, but can be customized to any rectangular height and width. Maps can have obstacles or not. 

Obstacles are simple squares defined by a location on the map and their size. 

Vertices are simple structs used by RRTPath to keep track of the RRT expansions and to rebuild the path from the start to the goal. They consist of an x,y coordinate location and a link to the vertex that preceded it.

## Standard install via command-line
```
git clone --recursive https://github.com/jeshoward/RRTPath
cd <path to repository>
mkdir build
cd build
cmake ..
make
```

## Building for code coverage
```
sudo apt-get install lcov
cmake -D COVERAGE=ON -D CMAKE_BUILD_TYPE=Debug ../
make
make code_coverage
```
This generates a index.html page in the build/coverage sub-directory that can be viewed locally in a web browser.

## Working with Eclipse IDE ##

## Installation

In your Eclipse workspace directory (or create a new one), checkout the repo (and submodules)
```
mkdir -p ~/workspace
cd ~/workspace
git clone --recursive https://github.com/jeshoward/RRTPath
```

In your work directory, use cmake to create an Eclipse project for an [out-of-source build] of cpp-boilerplate

```
cd ~/workspace
mkdir -p boilerplate-eclipse
cd boilerplate-eclipse
cmake -G "Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D CMAKE_ECLIPSE_VERSION=4.7.0 -D CMAKE_CXX_COMPILER_ARG1=-std=c++14 ../cpp-boilerplate/
```

## Dependencies
RRTPath includes the ability to generate a 2D visualization of the RRT and the final path taken by use of the matplotlib-cpp library, which can be found at:

https://github.com/lava/matplotlib-cpp

Installation terminal command is:

sudo apt-get install python-matplotlib python-numpy python2.7-dev

Matplotlib is a C++ wrapper for the python library matplotlib. In order to use the library you will need to have a working python installation. The matplotlib library is available under the MIT license.

The matplotlib.h file can be placed anywhere to be included in your project.

To add Python.h to your Eclipse environment go to Project -> Properties -> C/C++ Include Paths and Symbols and add an external include path to your python directory (/usr/include/python2.7 if you followed the instructions from the matplotlibcpp's readme). 

## Import

Open Eclipse, go to File -> Import -> General -> Existing Projects into Workspace -> 
Select "boilerplate-eclipse" directory created previously as root directory -> Finish

# Edit

Source files may be edited under the "[Source Directory]" label in the Project Explorer.


## Build

To build the project, in Eclipse, unfold RRTPath project in Project Explorer,
unfold Build Targets, double click on "all" to build all projects.

## Run

1. In Eclipse, right click on the boilerplate-eclipse in Project Explorer,
select Run As -> Local C/C++ Application

2. Choose the binaries to run (e.g. shell-app, cpp-test for unit testing)


## Contributing
This implementation was an exercise in software engineering practices for the University of Maryland course ENPM808X - Software Development for Robotics. No contributions are particularly desired, though feel free to spiffy up the code for your own use.

- Google C++ Sytle

    To include and use Google C++ Style formatter in Eclipse

    1. In Eclipse, go to Window -> Preferences -> C/C++ -> Code Style -> Formatter. 
    Import [eclipse-cpp-google-style][reference-id-for-eclipse-cpp-google-style] and apply.

    2. To use Google C++ style formatter, right click on the source code or folder in 
    Project Explorer and choose Source -> Format

[reference-id-for-eclipse-cpp-google-style]: https://raw.githubusercontent.com/google/styleguide/gh-pages/eclipse-cpp-google-style.xml

## Licensing
The code in this project is licensed under GNU public license

