//
// Created by kanhua on 2/23/20.
//
#include <iostream>
#include "gtest/gtest.h"
#include "DataPlot.h"
#include "yaml-cpp/yaml.h"
#include "AsphericSurface.h"
#include "OpticalSystem.h"

TEST(yaml,helloworld){
  YAML::Emitter out;
  out << "Hello, World!";

  std::cout << "Here's the output YAML:\n" << out.c_str(); // prints "Hello, World!"
}

TEST(yaml,readconfig){

    YAML::Node config = YAML::LoadFile("../tests/lens_config.yaml");
    std::cout << config["output_fig_file"] << std::endl;
    std::cout << config["surfaces"];
    AsphericSurface s1= parse_surface_from_yaml_node(config["surfaces"][0]);
    AsphericSurface s2= parse_surface_from_yaml_node(config["surfaces"][1]);

  auto r=s1.render_plot_points();
  auto r2=s2.render_plot_points();

  PLStreamWrapper pls("two_surfaces.svg");

  pls._plstream->env(-5,5,-5,5,0,0);
  pls.plot(r.first,r.second);
  pls.plot(r2.first,r2.second);


}

TEST(yaml, load_optical_system){

  YAML::Node config = YAML::LoadFile("../tests/lens_config.yaml");
  std::cout << config["rays"];

  OpticalSystem optsys=
      load_optical_system_from_yaml_node(config["surfaces"],config["rays"]);

  optsys.solve();

  optsys.render_plot();

}
