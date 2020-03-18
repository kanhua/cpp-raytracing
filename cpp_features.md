# C++ features used

### Loops, Functions, I/O
- **The project demonstrates an understanding of C++ functions and control structures**:
this program uses many for-loop and If-clauses.
- **The project reads data from a file and process the data, or the program writes data to a file**: 
this program reads process the input data of a YAML file, and then output the result figure to a SVG file.


### Object-Oriented Programming
- **The project uses Object Oriented Programming techniques**: this program encapsulates the ray-tracing algorithms
in ```OpticalRays``` and ```AsphericSurfaces``` classes. 
- **Classes use appropriate access specifiers for class members**: ```public``` and ```private``` specifiers were used in all of the classes.
- **Templates generalize functions in the project**: ```template<class T> void PLStreamWrapper::plot (T &x, T &y)``` 
can accepts input of any container types that implements ```[]``` operators.

### Memory management
- **The project makes use of references in function declarations**:
Functions such as ```AsphericSurface::intersect(OpticalRay &ray, const_refractive_index_functor prev_n)``` and  
```AsphericSurface::intersect(OpticalRay &ray, const_refractive_index_functor prev_n)``` uses references as function arguments.
- **The project uses smart pointers instead of raw pointers**:
 ```template<class T> void PLStreamWrapper::plot (T &x, T &y)``` 
 converts the contents in the container ```x``` and ```y```  into C-style dynamic array, 
 pointed by unique_ptr, and then use ```.get()``` function to pass them into ```plstrem->line()``` function.