#include "../include/planner.hpp"

Planner::Planner(Quad &quad, Track &track, Function (*func)(Function), YAML::Node &options){
    this->wp = DM(track.gates).T();

    if(!track.end_pos.empty()){
        if(track.gates.size() > 0){
            DM end_pos = DM(track.end_pos);
            this->wp = horzcat(this->wp, DM(track.end_pos));
        }else this->wp = DM(track.end_pos);
    }

    if(!track.init_pos.empty()){
        this->p_init = DM(track.init_pos);
    }else this->p_init = this->wp(Slice(), wp.size2() - 1);

    if(!track.init_att.empty()){
        this->q_init = DM(track.init_att);
    }else this->q_init = DM({1,0,0,0}).T();

    this->dynamics = quad.dynamics();
    this->fdyn = func(dynamics);

    this->NX = dynamics.size1_in(0);
    this->NU = dynamics.size1_in(1);
    this->NW = this->wp.size2();

    this->dist.push_back(norm_2(this->wp(Slice(), 0) - this->p_init));

    for(int i = 0; i < this->NW - 1; i++){
        dist.push_back(dist[i] + norm_2(this->wp(Slice(), i+1) - this->wp(Slice(), i)));
    }

    if(options["nodes_per_gate"]){
        this->NPW = options["nodes_per_gate"].as<int>();
    }else this->NPW = 30;

    if(options["tolerance"]){
        this->tol = options["tolerance"].as<double>();
    }else this->tol = 0.3;

    this-> N = NPW * NW;
    dpn = dist.back()(0).scalar() / N;

    if(this->dpn < this->tol){
        this->suff_str = "sufficient";
    }else suff_str = "insufficient";

    std::cout << "Discretization over " << this->N << " nodes and " << dist.back()(0).scalar() << "m" << std::endl;
    std::cout << "results in " << this->dpn << " per nodes, " << suff_str << " for tolerance of " << this->tol << std::endl;

    // (N * dist(1,2,3,4)) / dist.back()(0).scalar()
    i_switch = mult_scalar(this->N, this->dist);
    div_scalar(dist.back()(0).scalar(), i_switch);
    to_int(i_switch);

    std::cout << i_switch << std::endl;
    std::cout << dist << std::endl;
}

Planner::~Planner(){

}

std::vector<DM> Planner::mult_scalar(const int &N, std::vector<DM> dist){
    for(auto i = 0; i < dist.size(); i++){
        dist[i] = dist[i] * N;
    }

    return dist;
}

void Planner::div_scalar(const double &N, std::vector<DM> &dist){
    for(auto i = 0; i < dist.size(); i++){
        dist[i] = dist[i] / N;
    }
}

void Planner::to_int(std::vector<DM> &dist){
    for(auto i = 0; i < dist.size(); i++){
        dist[i] = static_cast<int>(dist[i].scalar());
    }
}