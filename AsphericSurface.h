//
// Created by Kan-Hua Lee on 2020/02/16.
//

#ifndef CPP_RAYTRACING__ASPHERICSURFACE_H_
#define CPP_RAYTRACING__ASPHERICSURFACE_H_

#include <string>
#include <vector>
#include "OpticalRay.h"

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
  bool record_rays;
  std::vector<OpticalRay> ray_bins;

};

#endif //CPP_RAYTRACING__ASPHERICSURFACE_H_
