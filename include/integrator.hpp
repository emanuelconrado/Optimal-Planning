#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP
#include <casadi/casadi.hpp>
#include <iostream>

using namespace casadi;

Function euler(Function dinamics);
Function RungeKutte(Function dinamics);

#endif