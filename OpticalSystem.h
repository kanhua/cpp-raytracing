//
// Created by kanhua on 2/24/20.
//

#ifndef CPP_RAYTRACING_OPTICALSYSTEM_H
#define CPP_RAYTRACING_OPTICALSYSTEM_H

#include <vector>
#include "AsphericSurface.h"
#include "OpticalRay.h"
#include "DataPlot.h"

class OpticalSystem {
public:
  OpticalSystem();

  void add_surface(AsphericSurface sf);
  void add_ray(OpticalRay ray);
  void solve();
  void solve_single_ray(OpticalRay& current_ray);
  void render_plot();

private:
  std::vector<AsphericSurface> _surfaces;
  std::vector<OpticalRay> _rays;


};

#endif // CPP_RAYTRACING_OPTICALSYSTEM_H
