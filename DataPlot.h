//
// Created by E284652 on 2/20/2020.
//

#ifndef CPP_RAYTRACING_DATAPLOT_H
#define CPP_RAYTRACING_DATAPLOT_H

#include "plstream.h"
#include <memory>
#include <string>

typedef std::unique_ptr<PLFLT[]> PlfltPtr;

template <class T> class DataPlot {

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

template <class T> std::unique_ptr<PLFLT[]> to_plflt_array(T x);

class PLStreamWrapper {
public:
  std::unique_ptr<plstream> _plstream;
  PLStreamWrapper(std::string filename) {
    _plstream = std::make_unique<plstream>();
    _plstream->sfnam(filename.c_str());
    _plstream->sdev("svg");

    _plstream->init();
  }

  template <class T>
  void plot(T &x,
            T &y); // TODO: add additional parameter for line color and labels

private:
  double _xmin = std::numeric_limits<double>::max(),
         _xmax = std::numeric_limits<double>::min(),
         _ymin = std::numeric_limits<double>::max(),
         _ymax = std::numeric_limits<double>::min();
  unsigned int _len=0;
  void _initialize_plot(); // init filename, device, other initialization

  template<class T>
  void adjust_layout(T &x, T &y); // adjust xmin, xmax

};

#include "DataPlot.cpp"
#endif // CPP_RAYTRACING_DATAPLOT_H
