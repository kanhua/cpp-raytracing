#include <iostream>
#include "gtest/gtest.h"
#include "AsphericSurface.h"
#include "DataPlot.h"
#include "OpticalRay.h"


TEST(surface, initialize){

  AsphericSurface surface1(1.0/19.0,3,0,10,0,0,false,"PMMA",false);
  auto r=surface1.render_plot_points();
  std::cout << r.first;
  std::cout << r.second;
  DataPlot dp(r.first,r.second);
  dp.render_plot();

}

TEST(ray, initialize){
  OpticalRay ray(-10,0,0,500);

  ray.update_after_intersect(30,-0.1,1, false);

  auto xy=ray.render_plot_points();

  DataPlot dpt(xy.first, xy.second);
  dpt.render_plot();

}

TEST(ray, intersect){

  AsphericSurface surface1(1.0/19.0,3,0,10,0,0,false,"PMMA",false);
  OpticalRay ray(-1,0,0,500);
  const_refractive_index_functor nr(1.0);

  surface1.intersect(ray,nr);

  auto xy=ray.render_plot_points();

  DataPlot dpt(xy.first, xy.second);
  dpt.render_plot();

}