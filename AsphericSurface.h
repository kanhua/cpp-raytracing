//
// Created by Kan-Hua Lee on 2020/02/16.
//

#ifndef CPP_RAYTRACING__ASPHERICSURFACE_H_
#define CPP_RAYTRACING__ASPHERICSURFACE_H_

#include <string>
#include <vector>
#include <map>
#include "yaml-cpp/yaml.h"
#include "OpticalRay.h"

double c_ray_param_eq(const double &t, double c, double k, double z0, double y0,
                      double theta, double A, double B, double z_l);


double c_ray_param_eq_prime(const double &t, double c, double k, double z0,
                            double y0, double theta, double A, double B,
                            double z_l);

struct aspheric_surface_functor {

  aspheric_surface_functor(double c=0, double k=0, double A=0, double B=0, double z_l=0)
      : c(c), k(k), A(A), B(B), z_l(z_l) {
    ray_z0=0;
    ray_y0=0;
    theta=0;
  }

  std::pair<double, double> operator()(double const &t) {
    // f(x)
    double fx = c_ray_param_eq(t, c, k, ray_z0, ray_y0, theta,
                               A, B, z_l);

    // first derivative f'(x)
    double fpx=c_ray_param_eq_prime(t, c, k, ray_z0, ray_y0, theta,
                                    A, B, z_l);

    return std::make_pair(fx,fpx);

  }
  void set_ray_param(double in_ray_z0, double in_ray_y0, double in_ray_theta)
  {
    ray_z0 = in_ray_z0;
    ray_y0 = in_ray_y0;
    theta= in_ray_theta;
  }

private:
  double c, k, ray_z0, ray_y0, theta, A, B, z_l;
};

struct const_refractive_index_functor{
  const_refractive_index_functor(double const nr): nr(nr){};

  double operator()(double wavelength){
    return nr;
  }

 private:
  double nr;

};


std::map<std::string, double> init_material_map();



class AsphericSurface {
public:
  AsphericSurface(double curvature, double z_0, double konic,
                  double aperture_radius, double A, double B, bool record_rays,
                  std::string material, bool end_beam);

  Eigen::Vector2d get_tangent_vec(double yp, double epsilon = 0.01,
                         bool normalize = true);

  Eigen::Vector2d get_normal_vec(double yp, double epsilon = 0.01);

  void intersect(OpticalRay &ray,const_refractive_index_functor prev_n);

  double get_surface_zr(double r);

  Eigen::Vector2d get_refraction(double yp,OpticalRay ray,double prev_n);

  std::pair<Eigen::VectorXd ,Eigen::VectorXd > render_plot_points();
    const_refractive_index_functor _nr_functor;
private:
  double c, k, z_0, A, B, aperture_radius;
  double y_min,y_max; //Future: future version may have shifts in y
  bool record_rays;
  bool end_beam;
  std::vector<OpticalRay> ray_bins;
  aspheric_surface_functor _as_surface_func;

};

AsphericSurface parse_from_yaml_node(YAML::Node surface_node);


#endif //CPP_RAYTRACING__ASPHERICSURFACE_H_
