#ifndef QUAD_HPP
#define QUAD_HPP

#include <vector>
#include <string>
#include <casadi/casadi.hpp>
#include <fstream>
#include <yaml-cpp/yaml.h>

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

    double v_max;
    double cd;
    double g;

public:
    void fillMatrix(DM &i);
    void readfile(std::string file);
    quad(std::string path_file);
};

#endif