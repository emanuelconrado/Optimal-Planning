#include <iostream>
#include "casadi/casadi.hpp"
#include "../include/quad.hpp"
#include "../include/track.hpp"
#include "../include/integrator.hpp"

using namespace casadi;

int main(int argc, char** argv){

    if(argc > 1){
        quad q(argv[1]);
        Function dynamics = q.dynamics();
        track t(argv[2]);

        Function integrator = euler(dynamics);
        Function integrator2 = RungeKutte(dynamics);
    }else std::cout << "No path file specified" << std::endl;

    return 0;
}