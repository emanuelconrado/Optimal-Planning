#ifndef QUAD_HPP
#define QUAD_HPP

#include <vector>
#include <string>
#include <casadi/casadi.hpp>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <math.h>
#include <algorithm>
#include "quaternion.hpp"
#include <optional>

using namespace casadi;


class quad
{
private:
    double m;
    double l;

    DM i = DM({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
    DM i_inv = inv(i);
    double t_max;
    double t_min;
    double omega_max;
    double ctau;
    double rampup_dist;
    double t_ramp_start;
    double omega_ramp_start;

    double omega_max_xy;
    double omega_max_z;

    std::optional<double> v_max = std::nullopt;
    double cd;
    double g;

public:
    void readfile(std::string file);
    quad(std::string path_file);
    Function dynamics();
};

#endif