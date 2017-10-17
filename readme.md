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

Obstacles are defined by a location on the map and their radius. 

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

## Import

Open Eclipse, go to File -> Import -> General -> Existing Projects into Workspace -> 
Select "boilerplate-eclipse" directory created previously as root directory -> Finish

# Edit

Source files may be edited under the "[Source Directory]" label in the Project Explorer.


## Build

To build the project, in Eclipse, unfold RRTPath project in Project Explorer,
unfold Build Targets, double click on "all" to build all projects.

## Running the demo
The demo can be found in main.cpp within the app source directory. To customize it you may set any of the variables in the customizable variables section at the top.
  map_height: The height of your rectangular map
  map_width: The width of your rectangular map
  start_x: the x coordinate of where you want your path to begin
  start_y: the y coordinate of where you want your path to begin
  goal_x: the x coordinate of your goal location
  goal_y: the y coordinate of your goal location
  step: how far you travel at each algorithm iteration. Smaller steps
       have more detail and may create a more efficient path, but take longer
       to run.
  radius: how near you need to be to the goal to "reach" it
  
Obstacles may be added to the map in the create obstacles here section. Simply create your obstacle(s) and then add them to the map as shown.
  
Your path is printed to the console at the conclusion of the demo.

In Eclipse, right click on the shell-app in Project Explorer in the app folder and select Run As -> Local C/C++ Application

## Running the tests

In Eclipse, right click on cpp-test in Project Explorer in the test folder and select Run As -> Local C/C++ Application

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

