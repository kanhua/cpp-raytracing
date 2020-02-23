//
// Created by kanhua on 2/23/20.
//
#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include <iostream>

TEST(yaml,helloworld){
  YAML::Emitter out;
  out << "Hello, World!";

  std::cout << "Here's the output YAML:\n" << out.c_str(); // prints "Hello, World!"
}
