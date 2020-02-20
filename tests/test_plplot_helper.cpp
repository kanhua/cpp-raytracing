//
// Created by E284652 on 2/20/2020.
//

#include <iostream>
#include "gtest/gtest.h"
#include "Eigen/Dense"
#include "DataPlot.h"
#include "plstream.h"



TEST(test_converter,test1){

  Eigen::VectorXd a(3);
  a<<1,2,3;
  Eigen::VectorXd b(3);
  b<<1,2,3;

  test_func(1,2);

  DataPlot<Eigen::VectorXd> dpt(a,b);
  dpt.render_plot();


 // for ( int i = 0; i < a.size(); i++ )
  //{
    //std::cout << c.first[i] <<" " << c.second[i] <<std::endl;
  //}

}