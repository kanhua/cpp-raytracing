//
// Created by kanhua on 2/24/20.
//

#include "OpticalSystem.h"

void OpticalSystem::add_surface(AsphericSurface sf) {
  _surfaces.emplace_back(sf);
}

void OpticalSystem::add_ray(OpticalRay ray) { _rays.emplace_back(ray); }

void OpticalSystem::solve_single_ray(OpticalRay &current_ray) {

  for (auto iter = _surfaces.begin(); iter != _surfaces.end(); iter++) {
    if (iter == _surfaces.begin()) {
      iter->intersect(current_ray, const_refractive_index_functor(1.0));
    }
    iter->intersect(current_ray, (iter - 1)->_nr_functor);
  }
}

void OpticalSystem::solve() {

  for (auto iter = _rays.begin(); iter != _rays.end(); iter++) {
    solve_single_ray(*iter);
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