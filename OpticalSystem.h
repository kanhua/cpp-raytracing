//
// Created by kanhua on 2/24/20.
//

#ifndef CPP_RAYTRACING_OPTICALSYSTEM_H
#define CPP_RAYTRACING_OPTICALSYSTEM_H

#include "AsphericSurface.h"
#include "DataPlot.h"
#include "OpticalRay.h"
#include <vector>
#include "yaml-cpp/yaml.h"

class OpticalSystem {
public:
  OpticalSystem(){};

  void add_surface(AsphericSurface sf);
  void add_ray(OpticalRay ray);
  void solve();
  OpticalRay solve_single_ray(OpticalRay &current_ray);
  void render_plot();

private:
  std::vector<AsphericSurface> _surfaces;
  std::vector<OpticalRay> _rays;
};

OpticalSystem load_optical_system_from_yaml_node(YAML::Node surface_node,
                                                 YAML::Node ray_node);

#endif // CPP_RAYTRACING_OPTICALSYSTEM_H
