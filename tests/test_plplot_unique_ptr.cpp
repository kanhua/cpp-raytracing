// Simple demo of a 2D line plot.
//
// Copyright (C) 2011-2014 Alan W. Irwin
// Copyright (C) 2012  Andrew Ross
//
// This file is part of PLplot.
//
// PLplot is free software; you can redistribute it and/or modify
// it under the terms of the GNU Library General Public License as published
// by the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// PLplot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with PLplot; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
//
//

#include <memory>
#include "plc++demos.h"
#include "plot_helper.h"

#ifdef PL_USE_NAMESPACE
using namespace std;
#endif

class x00 {
public:
  x00( int, char ** );

private:
  // Class data
  plstream         *pls;

  static const int NSIZE;
};

const int x00::NSIZE = 101;

x00::x00( int argc, char **argv )
{
  int dyn_size=101;
  std::unique_ptr<PLFLT[]> x=std::make_unique<PLFLT[]>(dyn_size);
  std::unique_ptr<PLFLT[]> y=std::make_unique<PLFLT[]>(dyn_size);
  PLFLT xmin = 0., xmax = 1., ymin = 0., ymax = 100.;
  int   i;

  // Prepare data to be plotted.
  for ( i = 0; i < dyn_size; i++ )
  {
    x[i] = (PLFLT) ( i ) / (PLFLT) ( dyn_size - 1 );
    y[i] = ymax * x[i] * x[i];
  }

  std::unique_ptr<PLFLT[]> xx=convert_vector_to_plflt_array(Eigen::VectorXd::Ones(5));


  for ( i = 0; i < dyn_size; i++ )
  {
    std::cout << x[i] <<" " << y[i] <<std::endl;
  }


  pls = new plstream();

  // Parse and process command line arguments
  pls->parseopts( &argc, argv, PL_PARSE_FULL );

  // Initialize plplot
  pls->init();

  // Create a labelled box to hold the plot.
  pls->env( xmin, xmax, ymin, ymax, 0, 0 );
  pls->lab( "x", "y=100 x#u2#d", "Simple PLplot demo of a 2D line plot" );

  // Plot the data that was prepared above.
  pls->line( NSIZE, x.get(), y.get() );


  // In C++ we don't call plend() to close PLplot library
  // this is handled by the destructor
  delete pls;
}

int main( int argc, char ** argv )
{
  x00 *x = new x00( argc, argv );
  delete x;
}


//--------------------------------------------------------------------------
//                              End of x00.cc
//--------------------------------------------------------------------------
