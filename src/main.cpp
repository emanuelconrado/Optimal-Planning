#include <iostream>
#include "casadi/casadi.hpp"
#include "../include/quad.hpp"
using namespace casadi;

int main(int argc, char** argv){
    quad q(argv[1]);
    q.dynamics();
    return 0;
}