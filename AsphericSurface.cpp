//
// Created by Kan-Hua Lee on 2020/02/16.
//

#include "AsphericSurface.h"


double c_ray_param_eq(double t, double c, double k, double z0, double y0,
                      double theta, double A, double B, double z_l) {

  return A * pow(t * sin(theta) + y0, 4) + B * pow(t * sin(theta) + y0, 6) +
         c * pow(t * sin(theta) + y0, 2) /
             (sqrt(-pow(c, 2) * (k + 1) * pow(t * sin(theta) + y0, 2) + 1) +
              1) -
         t * cos(theta) - z0 + z_l;
}

double c_ray_param_eq_prime(double t, double c, double k, double z0, double y0,
                            double theta, double A, double B, double z_l) {
  return 4 * A *pow(t * sin(theta) + y0, 3) * sin(theta) +
      6 * B *pow(t * sin(theta) + y0, 5) * sin(theta) +
      pow(c, 3) * (k + 1) * pow(t * sin(theta) + y0, 3) * sin(theta) /
          (sqrt(-pow(c, 2) * (k + 1) * pow(t * sin(theta) + y0, 2) + 1) *
           pow(sqrt(-pow(c, 2) * (k + 1) * pow(t * sin(theta) + y0, 2) + 1) + 1,
               2)) +
      2 * c *(t * sin(theta) + y0) * sin(theta) /
          (sqrt(-pow(c, 2) * (k + 1) * pow(t * sin(theta) + y0, 2) + 1) + 1) -
      cos(theta);
}