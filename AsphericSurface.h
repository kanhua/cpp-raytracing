//
// Created by Kan-Hua Lee on 2020/02/16.
//

#ifndef CPP_RAYTRACING__ASPHERICSURFACE_H_
#define CPP_RAYTRACING__ASPHERICSURFACE_H_

#include <string>

class AsphericSurface {
public:
  AsphericSurface(double curvature, double z_0,
      double konic, double aperture_radius,
      double A, double B, bool record_rays,
      std::string material,bool end_beam);
};

#endif //CPP_RAYTRACING__ASPHERICSURFACE_H_
