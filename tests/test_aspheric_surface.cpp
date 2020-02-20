#include <iostream>
#include "gtest/gtest.h"
#include "AsphericSurface.h"



TEST(surface, initialize){

  EXPECT_EQ(1.0, 1.0);
  AsphericSurface surface1(1.0/19.0,3,0,10,0,0,false,"PMMA",false);
  auto r=surface1.render_plot_points();
  std::cout << r.first;
  std::cout << r.second;

}