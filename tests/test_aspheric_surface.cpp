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
  OpticalRay ray(-1,2,0,500);
  //OpticalRay ray2(-1,0,0,500);
  const_refractive_index_functor nr(1.0);

  surface1.intersect(ray,nr);

  auto xy=ray.render_plot_points();

  auto r=surface1.render_plot_points();

  PLStreamWrapper pls("test1.svg");

  pls._plstream->env(-5,5,-5,5,0,0);
  pls.plot(xy.first,xy.second);
  pls.plot(r.first,r.second);
}


TEST(ray, intersect2){

  AsphericSurface surface1(1.0/19.0,3,0,3,0,0,false,"pmma",false);
  AsphericSurface surface2(-1.0/19.0,5,0,3,0,0,false,"air",false);
  OpticalRay ray(-1,2,0,500);
  //OpticalRay ray2(-1,0,0,500);
  const_refractive_index_functor nr(1.0);

  surface1.intersect(ray,nr);

  surface2.intersect(ray,surface1._nr_functor);

  auto xy=ray.render_plot_points();

  auto r=surface1.render_plot_points();
  auto r2=surface2.render_plot_points();

  PLStreamWrapper pls("two_surface_intersection.svg");

  pls._plstream->env(-3,15,-5,5,0,0);
  pls.plot(xy.first,xy.second);
  pls.plot(r.first,r.second);
  pls.plot(r2.first,r2.second);
}