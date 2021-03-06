//
// Created by Kan-Hua Lee on 2020/02/16.
//

#include "OpticalRay.h"
#include <cmath>

OpticalRay::OpticalRay(double z_0, double y_0, double theta, double wavelength)
    : z_0(z_0), y_0(y_0), theta(theta), wavelength(wavelength) {
  this->k << std::cos(theta), std::sin(theta);
  this->intensity = 1.0;
  this->v_0 << z_0, y_0;
  this->attenu_coef_list.push_back(1.0);
  this->end_ts.push_back(std::numeric_limits<double>::infinity());
  this->dt = 0;
  this->paths.push_back(
      std::make_pair(v_0, theta)); // TODO: check if this is pass by reference
}

void OpticalRay::update_after_intersect(double t_end, double new_theta,
                                        double attenu_coef, bool end_beam) {

  Eigen::Vector2d prev_v0 = v_0; // copy previous starting point of ray

  v_0 = v_0 + k * t_end;

  z_0 = v_0(0);
  y_0 = v_0(1);

  update_theta(new_theta);

  double next_t = t_end + dt;

  dt = next_t;

  end_ts[end_ts.size() - 1] = next_t;

  // calculate attenuation
  Eigen::Vector2d dv = v_0 - prev_v0;
  double r = dv.norm();

  // TODO: deal with attenuation coefficient

  paths.push_back(std::make_pair(v_0, theta));

  if (!end_beam) {
    end_ts.push_back(std::numeric_limits<double>::infinity());
  }
}

void OpticalRay::update_theta(double new_theta) {
  theta = new_theta;

  k << std::cos(theta), std::sin(theta);
}

double OpticalRay::estimate_t(double target_z) {

  double t = (target_z - v_0(0)) / k(0);

  return t;
}

std::pair<Eigen::ArrayXd, Eigen::ArrayXd>
OpticalRay::render_plot_points(double end_time) {

  Eigen::ArrayXd x_arr(paths.size() + 1);
  Eigen::ArrayXd y_arr(paths.size() + 1);
  for (int idx = 0; idx < paths.size(); idx++) {
    std::pair<Eigen::Vector2d, double> v_0_theta = paths[idx];
    auto v_0 = v_0_theta.first;
    auto theta = v_0_theta.second;
    x_arr[idx] = v_0[0];
    y_arr[idx] = v_0[1];
  }

  // plot the section after the intersetion
  double delta_t = end_time - end_ts[end_ts.size() - 2];
  // get last elements
  auto last_v_0_theta = paths[paths.size() - 1];
  auto v_0 = last_v_0_theta.first;
  auto theta = last_v_0_theta.second;
  x_arr[paths.size()] = v_0[0] + delta_t * cos(theta);
  y_arr[paths.size()] = v_0[1] + delta_t * sin(theta);

  return std::make_pair(x_arr, y_arr);
}

OpticalRay parse_ray_from_yaml_node(YAML::Node ray_node) {
  return OpticalRay(ray_node["z_0"].as<double>(), ray_node["y_0"].as<double>(),
                    ray_node["theta"].as<double>(),
                    ray_node["wavelength"].as<double>());
}