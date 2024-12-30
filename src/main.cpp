#include "../include/planner.hpp"

using namespace casadi;

int main(int argc, char** argv){
    Quad *q(nullptr);
    Track *t(nullptr);

    if(argc > 1){
        q = new Quad(argv[1]);
    }else std::cout << "No path file specified" << std::endl;

    if(argc > 2){
        t = new Track(argv[2]);
    }

    YAML::Node dado = YAML::LoadFile(argv[3]);


    Planner p(*q, *t, RungeKutte, dado);

    // if(argc > 1){
    //     quad q(argv[1]);
    //     Function dynamics = q.dynamics();
    //     track t(argv[2]);

    //     Function integrator = euler(dynamics);
    //     Function integrator2 = RungeKutte(dynamics);
    // }else std::cout << "No path file specified" << std::endl;

    return 0;
}