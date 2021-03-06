//
// Created by Kan-Hua Lee on 2020/02/16.
//

#include <vector>
#include "Eigen/Dense"
#include "yaml-cpp/yaml.h"

#ifndef CPP_RAYTRACING__OPTICAL_RAY_H_
#define CPP_RAYTRACING__OPTICAL_RAY_H_


class OpticalRay {

 public:
  double z_0;
  double y_0;
  double theta;
  Eigen::Vector2d v_0;
  Eigen::Vector2d k;
  double wavelength;
  double intensity;
  double dt;
  std::vector<double> end_ts;
  std::vector<double> attenu_coef_list;
  std::vector<std::pair<Eigen::Vector2d,double>> paths;

  //constructor
  OpticalRay(double z_0,double y_0,double theta, double wavelength);

  void update_after_intersect(double t_end,double new_theta,double attenu_coef,bool end_beam);

  void update_theta(double new_theta);

  double estimate_t(double target_z);

  Eigen::Vector2d get_next_v0(double delta_t){return v_0+k*delta_t;};

  std::pair<Eigen::ArrayXd, Eigen::ArrayXd> render_plot_points(double end_time=20);


};

OpticalRay parse_ray_from_yaml_node(YAML::Node ray_node);
#endif //CPP_RAYTRACING__OPTICAL_RAY_H_
