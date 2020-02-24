//
// Created by kanhua on 2/24/20.
//

#include "OpticalSystem.h"

void OpticalSystem::add_surface(AsphericSurface sf) {
  _surfaces.emplace_back(sf);
}

void OpticalSystem::add_ray(OpticalRay ray) { _rays.emplace_back(ray); }

OpticalRay OpticalSystem::solve_single_ray(OpticalRay &current_ray) {

  for (auto iter = _surfaces.begin(); iter != _surfaces.end(); iter++) {
    if (iter == _surfaces.begin()) {
      iter->intersect(current_ray, const_refractive_index_functor(1.0));
    }
    iter->intersect(current_ray, (iter - 1)->_nr_functor);
  }

  return current_ray;
}

void OpticalSystem::solve() {

  for (int index=0;index<_rays.size();index++) {
    auto temp_ray=solve_single_ray(_rays[index]);
    _rays[index]=temp_ray;
  }

}

void OpticalSystem::render_plot() {

  PLStreamWrapper pls("quick_optical_system_plot.svg");

  pls._plstream->env(-3, 15, -5, 5, 0, 0);

  // plot surfaces
  for (auto iter = _surfaces.begin(); iter != _surfaces.end(); iter++) {
    auto surface_xy = iter->render_plot_points();
    pls.plot(surface_xy.first, surface_xy.second);
  }

  for (auto iter = _rays.begin(); iter != _rays.end(); iter++) {
    auto ray_xy = iter->render_plot_points();
    pls.plot(ray_xy.first, ray_xy.second);
  }
}

OpticalSystem load_optical_system_from_yaml_node(YAML::Node surface_node,
                                                 YAML::Node ray_node) {

  OpticalSystem optsys;

  // add surfaces
  for (YAML::const_iterator it= surface_node.begin(); it!= surface_node.end();it++)
  {
    auto sf=parse_surface_from_yaml_node(*it);
    optsys.add_surface(sf);
  }

  for (YAML::const_iterator it= ray_node.begin();it!= ray_node.end();it++)
  {
    auto ray=parse_ray_from_yaml_node(*it);
    optsys.add_ray(ray);
  }

  return optsys;

}
