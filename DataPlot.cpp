//
// Created by E284652 on 2/20/2020.
//

#include <algorithm>

template<class T>
DataPlot<T>::DataPlot(const T &x, const T &y){
  convert_vector_to_plflt_array(x,y);

  _xmin =x.minCoeff();
  _xmax =x.maxCoeff();
  _ymin =y.minCoeff();
  _ymax =y.maxCoeff();
  _len=x.size();

}


template<class T>
void DataPlot<T>::convert_vector_to_plflt_array(T x, T y) {

  std::unique_ptr<PLFLT[]> x_ptr = std::make_unique<PLFLT[]>(x.size());
  std::unique_ptr<PLFLT[]> y_ptr = std::make_unique<PLFLT[]>(y.size());

  for (int i = 0; i < x.size(); i++) {
    x_ptr[i] = (PLFLT)x(i);
    y_ptr[i] = (PLFLT)y(i);
  }

  _x_data_ptr=to_plflt_array(x);
  _y_data_ptr=std::move(y_ptr);
}

template<class T>
std::unique_ptr<PLFLT[]> to_plflt_array(T x)
{
  std::unique_ptr<PLFLT[]> x_ptr = std::make_unique<PLFLT[]>(x.size());
  for (int i=0;i<x.size();i++)
  {
    x_ptr[i] = (PLFLT)x(i);
  }

  return std::move(x_ptr);

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
  pls->line( _len, _x_data_ptr.get(), _y_data_ptr.get() );

  // In C++ we don't call plend() to close PLplot library
  // this is handled by the destructor
  delete pls;

}


template<class T> void PLStreamWrapper::adjust_layout(T &x, T &y) {
  double _temp_xmin =x.minCoeff();
  double _temp_xmax =x.maxCoeff();
  double _temp_ymin =y.minCoeff();
  double _temp_ymax =y.maxCoeff();

  if (_temp_xmax>_xmax) _xmax=_temp_xmax;
  if (_temp_ymax>_ymax) _ymax=_temp_ymax;
  if (_temp_xmin<_xmin) _xmin=_temp_xmin;
  if (_temp_ymin<_ymin) _ymin=_temp_ymin;

  _plstream->env(_xmin,_xmax,_ymin,_ymax,0,0);


}

template<class T> void PLStreamWrapper::plot (T &x, T &y)
{
  std::unique_ptr<PLFLT[]> x_ptr = to_plflt_array(x);
  std::unique_ptr<PLFLT[]> y_ptr = to_plflt_array(y);

  //adjust_layout(x,y);

  _plstream->lab( "z", "y", "2D ray-tracing plot" );

  _plstream->line(x.size(),x_ptr.get(),y_ptr.get());

}