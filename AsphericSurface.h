//
// Created by Kan-Hua Lee on 2020/02/16.
//

#ifndef CPP_RAYTRACING__ASPHERICSURFACE_H_
#define CPP_RAYTRACING__ASPHERICSURFACE_H_

#include <string>
#include <vector>
#include "OpticalRay.h"

double c_ray_param_eq(const double &t, double c, double k, double z0, double y0,
                      double theta, double A, double B, double z_l);


double c_ray_param_eq_prime(const double &t, double c, double k, double z0,
                            double y0, double theta, double A, double B,
                            double z_l);

struct aspheric_surface_functor {
  aspheric_surface_functor(){};

  aspheric_surface_functor(double c, double k, double A, double B, double z_l)
      : c(c), k(k), A(A), B(B), z_l(z_l) {}

  std::pair<double, double> operator()(double const &t) {
    // f(x)
    double fx = c_ray_param_eq(t, c = c, k = k, z0 = z0, y0 = y0, theta = theta,
                               A = A, B = B, z_l = z_l);

    // first derivative f'(x)
    double fpx=c_ray_param_eq_prime(t, c = c, k = k, z0 = z0, y0 = y0, theta = theta,
                                    A = A, B = B, z_l = z_l);

    return std::make_pair(fx,fpx);

  }
  void set_ray_param(double z0, double y0, double theta)
  {
    z0=z0;
    y0=y0;
    theta=theta;
  }

private:
  double c, k, z0, y0, theta, A, B, z_l;
};


class AsphericSurface {
public:
  AsphericSurface(double curvature, double z_0, double konic,
                  double aperture_radius, double A, double B, bool record_rays,
                  std::string material, bool end_beam);

  double get_tangent_vec(double yp, double epsilon = 0.01,
                         double normalize = true);

  double get_normal_vec(double yp, double epsilon = 0.01);


private:
  double c, k, z_0, A, B, aperture_radius;
  double y_min,y_max; //Future: future version may have shifts in y
  bool record_rays;
  std::vector<OpticalRay> ray_bins;
  aspheric_surface_functor _as_surface_func;

};

#endif //CPP_RAYTRACING__ASPHERICSURFACE_H_
