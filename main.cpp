#include <iostream>
#include "yaml-cpp/yaml.h"
#include "OpticalSystem.h"

void load_and_plot(std::string config_file)
{
  YAML::Node config = YAML::LoadFile(config_file);

  OpticalSystem optsys=
      load_optical_system_from_yaml_node(config["surfaces"],config["rays"]);

  optsys.solve();

  optsys.render_plot(config["output_fig_file"].as<std::string>());
}




int main(int argc, char *argv[]) {
  std::cout << "Processing...." <<  argv[1] <<std::endl;
  load_and_plot(std::string(argv[1]));
  return 0;
}