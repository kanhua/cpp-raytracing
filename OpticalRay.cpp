//
// Created by Kan-Hua Lee on 2020/02/16.
//

#include "OpticalRay.h"
#include <cmath>

OpticalRay::OpticalRay(double z_0, double y_0, double theta, double wavelength)
    : z_0(z_0), y_0(y_0), theta(theta), wavelength(wavelength) {
  this->k(std::cos(theta), std::sin(theta));
  this->intensity = 1.0;
  this->v_0(z_0, y_0);
  this->attenu_coef_list.push_back(1.0);
  this->end_ts.push_back(std::numeric_limits<double>::infinity());
  this->dt=0;
  this->paths.push_back(std::make_pair(v_0,theta));  //TODO: check if this is pass by reference

}

void OpticalRay::update_after_intersect(double t_end, double new_theta, double attenu_coef, bool end_beam) {

  Eigen::Vector2d prev_v0=v_0; // copy previous starting point of ray

  v_0 = v_0 + k * t_end;

  z_0 = v_0(0);
  y_0=v_0(1);

  update_theta(new_theta);

  double next_t=t_end+dt;

  dt=next_t;

  end_ts[end_ts.size()-1]=next_t;

  //calculate attenuation
  Eigen::Vector2d dv=v_0-prev_v0;
  double r=dv.norm();

  //TODO: deal with attenuation coefficient

  paths.push_back(std::make_pair(v_0,theta));


  if (!end_beam)
  {
    end_ts.push_back(std::numeric_limits<double>::infinity());
  }

}

void OpticalRay::update_theta(double new_theta) {
  theta=new_theta;

  k=Eigen::Vector2d(std::cos(theta),std::sin(theta));

}