#ifndef PLANNER_HPP
#define PLANNER_HPP
#include "quad.hpp"
#include "integrator.hpp"
#include "track.hpp"
#include <unordered_map>
#include <variant>

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

    std::vector<int> x;
    std::vector<int> xg;
    std::vector<int> g;
    std::vector<int> lb;
    std::vector<int> ub;
    std::vector<int> J;


    double vel_guess;
    double dpn;
    double tol;

    std::vector<int> iteration_plot;

    YAML::Node solver_options;
    YAML::Node t_guess;
    YAML::Node solver_type;

    std::string suff_str;
    std::vector<DM> dist;
    std::vector<DM> i_switch;
public:
    Planner(Quad &quad, Track &track, Function (*func)(Function), YAML::Node &options);
    std::vector<DM> mult_scalar(const int &N, std::vector<DM> dis);
    void div_scalar(const double &N, std::vector<DM> &dist);
    void to_int(std::vector<DM> &dist);
    std::vector<DM> generate_range(int start, int end, int step);
    ~Planner();
};



#endif