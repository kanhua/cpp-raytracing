//
// Created by E284652 on 2/20/2020.
//


#ifndef CPP_RAYTRACING_PLOT_HELPER_H
#define CPP_RAYTRACING_PLOT_HELPER_H

#include <memory>
#include "plstream.h"
#include "Eigen/Dense"

typedef std::unique_ptr<PLFLT[]> PlfltPtr;


template<typename T>void ordin_func(T &a, T &b){};

template<class T>
class DataPlot{

public:
  DataPlot(const T &x, const T &y);

  void render_plot();


private:

  void convert_vector_to_plflt_array(T x, T y);
  PlfltPtr _x_data_ptr;
  PlfltPtr _y_data_ptr;


};





#endif // CPP_RAYTRACING_PLOT_HELPER_H
