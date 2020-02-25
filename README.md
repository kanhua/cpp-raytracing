# Ray Tracing


## Installation and build

The following install procedures only tested on Ubuntu Linux

- Clone this repo with ```--recurse-submodules```
- Download BOOST library
- Add cmake parameter ```-DBOOST_ROOT=/your/boost/library```
- Download and add Eigen library
- Install plplot: ```sudo apt-get install libplplot-dev``` ```pkg-config --cflags --libs plplot-c++```
- Install yaml-cpp:
  - Downlaod [yaml-cpp](https://github.com/jbeder/yaml-cpp)
  - Make a ```./build``` directory
  - Run ```cmake ..```
  - Run ```make``` and then ```sudo make install```.
 or ```sudo apt-get install libyaml-cpp-dev```
 
## Execution of the program
