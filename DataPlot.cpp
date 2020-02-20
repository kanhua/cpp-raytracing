//
// Created by E284652 on 2/20/2020.
//

#include "DataPlot.h"
#include <algorithm>

template<class T>
DataPlot<T>::DataPlot(const T &x, const T &y){
  convert_vector_to_plflt_array(x,y);

  _xmin =x.minCoeff();
  _xmax =x.maxCoeff();
  _ymin =y.minCoeff();
  _ymax =y.maxCoeff();

}


template<class T>
void DataPlot<T>::convert_vector_to_plflt_array(T x, T y) {

  std::unique_ptr<PLFLT[]> x_ptr = std::make_unique<PLFLT[]>(x.size());
  std::unique_ptr<PLFLT[]> y_ptr = std::make_unique<PLFLT[]>(y.size());

  for (int i = 0; i < x.size(); i++) {
    x_ptr[i] = (PLFLT)x(i);
    y_ptr[i] = (PLFLT)y(i);
  }

  _x_data_ptr=std::move(x_ptr);
  _y_data_ptr=std::move(y_ptr);
}

template<class T>
void DataPlot<T>::render_plot() {


  plstream *pls = new plstream();

  pls->sfnam("test.svg");
  pls->sdev("svg");
  // Parse and process command line arguments

  // Initialize plplot
  pls->init();

  // Create a labelled box to hold the plot.

  pls->env(_xmin, _xmax, _ymin, _ymax, 0, 0 );
  pls->lab( "x", "y=100 x#u2#d", "Simple PLplot demo of a 2D line plot" );

  // Plot the data that was prepared above.
  pls->line( 3, _x_data_ptr.get(), _y_data_ptr.get() );

  // In C++ we don't call plend() to close PLplot library
  // this is handled by the destructor
  delete pls;

}

void test_func(int a, int b){
  a+b;
}