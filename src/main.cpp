#include <iostream>
#include "casadi/casadi.hpp"
#include "../include/quad.hpp"
#include "../include/track.hpp"
using namespace casadi;

int main(int argc, char** argv){
    quad q(argv[1]);
    q.dynamics();
    track t(argv[2]);
    return 0;
}