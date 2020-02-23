//
// Created by Kan-Hua Lee on 2020/02/16.
//

#include "AsphericSurface.h"
#include <boost/math/tools/roots.hpp>

double c_ray_param_eq(const double &t, double c, double k, double z0, double y0,
                      double theta, double A, double B, double z_l) {

  return A * pow(t * sin(theta) + y0, 4) + B * pow(t * sin(theta) + y0, 6) +
         c * pow(t * sin(theta) + y0, 2) /
             (sqrt(-pow(c, 2) * (k + 1) * pow(t * sin(theta) + y0, 2) + 1) +
              1) -
         t * cos(theta) - z0 + z_l;
}

double c_ray_param_eq_prime(const double &t, double c, double k, double z0,
                            double y0, double theta, double A, double B,
                            double z_l) {
  return 4 * A * pow(t * sin(theta) + y0, 3) * sin(theta) +
         6 * B * pow(t * sin(theta) + y0, 5) * sin(theta) +
         pow(c, 3) * (k + 1) * pow(t * sin(theta) + y0, 3) * sin(theta) /
             (sqrt(-pow(c, 2) * (k + 1) * pow(t * sin(theta) + y0, 2) + 1) *
              pow(sqrt(-pow(c, 2) * (k + 1) * pow(t * sin(theta) + y0, 2) + 1) +
                      1,
                  2)) +
         2 * c * (t * sin(theta) + y0) * sin(theta) /
             (sqrt(-pow(c, 2) * (k + 1) * pow(t * sin(theta) + y0, 2) + 1) +
              1) -
         cos(theta);
}

double spherical_lens_prime(double r, double c, double k, double A, double B) {
  return 4 * A * pow(r, 3) + 6 * B * pow(r, 5) +
         pow(c, 3) * pow(r, 3) * (k + 1) /
             (sqrt(-pow(c, 2) * pow(r, 2) * (k + 1) + 1) *
              pow(sqrt(-pow(c, 2) * pow(r, 2) * (k + 1) + 1) + 1, 2)) +
         2 * c * r / (sqrt(-pow(c, 2) * pow(r, 2) * (k + 1) + 1) + 1);
}
AsphericSurface::AsphericSurface(double curvature, double z_0, double konic,
                                 double aperture_radius, double A, double B,
                                 bool record_rays, std::string material,
                                 bool end_beam)
    : z_0(z_0), c(curvature), k(konic), aperture_radius(aperture_radius), A(A),
      B(B), record_rays(record_rays), end_beam(end_beam), _nr_functor(1.5) {

  y_min = -aperture_radius;
  y_max = aperture_radius;
  _as_surface_func = aspheric_surface_functor(c, k, A, B, z_0);

  //auto material_map=init_material_map();

  //_nr_functor(material_map[material]);

  // TODO: load attenuation coefficients
}



double AsphericSurface::get_surface_zr(double r) {

  double z = c * pow(r, 2) / (1 + sqrt(1 - (1 + k) * pow(c * r, 2))) + z_0 +
             A * pow(r, 4) + B * pow(r, 6);

  return z;
}

Eigen::Vector2d AsphericSurface::get_refraction(double yp, OpticalRay ray,
                                                double prev_n) {

  double nr = _nr_functor(ray.wavelength);
  Eigen::Vector2d norm_vec=-get_normal_vec(yp,0.01);

  //calculate cosine from Snell's law
  double cos_I=norm_vec.dot(ray.k);
  double sin_I=sqrt(1-pow(cos_I,2));
  double sin_Ip=prev_n*sin_I/nr;
  double cos_Ip=sqrt(1-pow(sin_Ip,2));

  //calculate the refractive vector

  double nprpn = nr * cos_Ip - prev_n * cos_I;

  Eigen::Vector2d next_r = 1 / nr * (prev_n * ray.k + nprpn * norm_vec);

  return next_r;
}

Eigen::Vector2d AsphericSurface::get_tangent_vec(double yp, double epsilon,
                                                 bool normalize) {
  double xp_p=spherical_lens_prime(yp,c,k,A,B);
  Eigen::Vector2d tangent_vec(xp_p,1);

  if (normalize)
  {
    tangent_vec=tangent_vec/tangent_vec.norm();
  }

  return tangent_vec;

}

Eigen::Vector2d AsphericSurface::get_normal_vec(double yp, double epsilon) {
  Eigen::Vector2d tangent_vec=get_tangent_vec(yp,0.01,true);

  Eigen::Vector2d norm_vec(-tangent_vec(1),tangent_vec(0));

  return norm_vec;
}

void AsphericSurface::intersect(OpticalRay &ray,
                                const_refractive_index_functor prev_n) {

  // guess the next intersection point
  double t_min_p_1 = ray.estimate_t(get_surface_zr(aperture_radius));
  double t_min_p_2 = ray.estimate_t(z_0);
  double guess = std::min(t_min_p_1, t_min_p_2);

  // Set ray parameter in surface functor
  _as_surface_func.set_ray_param(ray.z_0,ray.y_0,ray.theta);

  double epsilon = 0.5;

  const int digits =
      std::numeric_limits<double>::digits; // Maximum possible binary digits
                                           // accuracy for type T.
  int get_digits = static_cast<int>(
      digits * 0.6); // Accuracy doubles with each step, so stop when we have
  // just over half the digits correct.
  const boost::uintmax_t maxit = 20;
  boost::uintmax_t it = maxit;
  double intersect_t = boost::math::tools::newton_raphson_iterate(
      _as_surface_func, guess, guess / 2, guess * 2, get_digits, it);


  Eigen::Vector2d next_v = ray.get_next_v0(intersect_t);

  double next_y = next_v(1);

  if (next_y <= y_max && next_y >= y_min) {
    // TODO: record rays

    Eigen::Vector2d next_r =
        get_refraction(next_y, ray, prev_n(ray.wavelength));
    double new_theta =
        atan2(next_r(1), next_r(0)); // TODO: need to check if the input
                                     // paramter is the same as np.arctan2

    ray.update_after_intersect(
        intersect_t, new_theta, 0,
        end_beam); // TODO: change attenuation coefficients here
  }
}

std::pair<Eigen::VectorXd ,Eigen::VectorXd > AsphericSurface::render_plot_points(){
  Eigen::VectorXd rs=Eigen::VectorXd::LinSpaced(300,-aperture_radius,aperture_radius);
  Eigen::VectorXd zs=rs;

  for (int i=0;i<rs.size();i++)
  {
    zs(i)=get_surface_zr(rs(i));
  }

  return std::make_pair(zs,rs);
}

std::map<std::string, double> init_material_map() {

std::map<std::string, double> material_map;
material_map.insert(
    std::make_pair("PMMA",1.5));
material_map.insert(
    std::make_pair("air", 0.0));

return material_map;
}