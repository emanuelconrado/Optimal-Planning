#ifndef TRACK_HPP
#define TRACK_HPP
#include <yaml-cpp/yaml.h>
#include <vector>
#include <optional>
#include <fstream>
#include <string>
#include <iostream>

class Track
{
private:
public:
    std::vector<double> init_pos = {};
    std::vector<double> init_att = {};
    std::vector<double> init_vel = {};
    std::vector<double> init_omega = {};
    std::vector<double> end_pos = {};
    std::vector<double> end_att = {};
    std::vector<double> end_vel = {};
    std::vector<double> end_omega = {};
    std::vector<std::vector<double>> gates;
    bool ring;
    Track(std::string path_file);
    ~Track();
    void readfile(std::string file);
};



#endif