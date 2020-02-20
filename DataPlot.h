//
// Created by E284652 on 2/20/2020.
//

#ifndef CPP_RAYTRACING_DATAPLOT_H
#define CPP_RAYTRACING_DATAPLOT_H

#include<memory>
#include"plstream.h"

void test_func(int a,int b);

typedef std::unique_ptr<PLFLT[]> PlfltPtr;

template<class T>
class DataPlot{

public:
  DataPlot(const T &x, const T &y);

  void render_plot();

private:

  void convert_vector_to_plflt_array(T x, T y);
  PlfltPtr _x_data_ptr;
  PlfltPtr _y_data_ptr;
  double _xmin, _ymin, _xmax, _ymax;
  int _len;

};

#include "DataPlot.cpp"
#endif // CPP_RAYTRACING_DATAPLOT_H
