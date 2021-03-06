# Ray Tracing

This program implements the core algorithm of sequential ray-tracing. 
Instead of using ray transfer matrix (a.k.a. ABCD matrix), this program uses differential geometry, 
which can cope with any parameterizable surfaces.

![alt text](examples/convex_lens_1.svg)


## Installation and build

The following install procedures only tested on Ubuntu Linux

- Clone this repo with ```--recurse-submodules```
- Download BOOST library
- Add cmake parameter ```-DBOOST_ROOT=/your/boost/library```
- Download and add Eigen library
- Install plplot: ```sudo apt-get install libplplot-dev``` ```pkg-config --cflags --libs plplot-c++```
- Install yaml-cpp:
  - Download [yaml-cpp](https://github.com/jbeder/yaml-cpp)
  - Make a ```./build``` directory
  - Run ```cmake ..```
  - Run ```make``` and then ```sudo make install```.
 or ```sudo apt-get install libyaml-cpp-dev```
 
## Dependencies

This software builds with googletest and eigen, please make sure you add ```--recurse-submodules``` 
when cloning the repo, i.e.,
```bash
git clone https://github.com/kanhua/cpp-raytracing.git --recurse-submodules
```
 
This software requires the following external libraries

#### Boost
 Download Boost and set ```-DBOOST_ROOT=/your/boost/library``` when running cmake.
 
#### plplot

Use apt-get: 
```sudo apt-get install libplplot-dev``` 
then check if the package exists by:
```pkg-config --cflags --libs plplot-c++``` or
```pkg-config --cflags --libs plplotd-c++```

#### yaml-cpp

Use ```sudo apt-get install libyaml-cpp-dev```

Alternatively:
  - Downlaod [yaml-cpp](https://github.com/jbeder/yaml-cpp)
  - Make a ```./build``` directory
  - Run ```cmake ..```
  - Run ```make``` and then ```sudo make install```.
  
## Build

In the root folder of this repo:

```bash
mkdir build
cd build
cmake ..
make
```

## Run the program

In ```build``` directory, run the command ```cpp-raytracing``` using the following usage
```
./cpp_raytracing [config_filename]
```

```config_filename``` is a yaml file that sets the lenses and the rays parameters for the program to run.


For example, if the executable sits in ```build/``` directory in project root folder, you can type:

```$xslt
./cpp_raytracing ../examples/single_biconvex_lens.yaml
```
Upon successful run, this program should generate a SVG file that plots the ray tracing results.
You can try other example yaml files in ```examples/``` folder.

### Project structure

The entry class of the simulation is ```OpticalSystem```, which consists of vectors of ```OpticalRays``` and ```AsphericSurfaces```.
```AsphericSurfaces``` class manages the shape of the lens surfaces; ```OpticalRays``` records the paths of each light rays.
The key algorithm of this program occurs 
in ```AsphericSurface::intersect(OpticalRay &ray, const_refractive_index_functor prev_n)```, 
which calculates the intersection between a ray and a lens surface, and then calculates the refracted path after that.

Then, the simulated data is plotted by PlPlot library via the wrapper ```PLStreamWrapper```.



