#ifndef PLANNER_HPP
#define PLANNER_HPP
#include "quad.hpp"
#include "integrator.hpp"
#include "track.hpp"

class Planner
{
private:
    DM wp;
    DM p_init;
    DM q_init;
    Function dynamics;
    Function fdyn;

    int NX;
    int NU;
    int NW;
    int NPW;

    int N;
    double dpn;

    double tol;

    std::string suff_str;
    std::vector<DM> dist;
    std::vector<DM> i_switch;
public:
    Planner(Quad &quad, Track &track, Function (*func)(Function), YAML::Node &options);
    std::vector<DM> mult_scalar(const int &N, std::vector<DM> dis);
    void div_scalar(const double &N, std::vector<DM> &dist);
    void to_int(std::vector<DM> &dist);
    ~Planner();
};



#endif