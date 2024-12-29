#include "../include/integrator.hpp"

Function euler(Function dynamics){
    MX dt = MX::sym("dt", 1);
    MX x = MX::sym("x", dynamics.size1_in(0));
    MX u = MX::sym("u", dynamics.size1_in(1));

    // std::map<std::string, MX> args;
    // args["x"] = x;
    // args["u"] = u;

    auto result = dynamics({{"x", x}, {"u", u}});
    //auto result = dynamics(args);
    MX dynamics_eval = result.at("x_dot");

    MX xn = x + dt * dynamics_eval;

    Function integrator = Function("integrator", {x, u, dt}, {xn}, {"x", "u", "dt"}, {"xn"});

    return integrator;
}

Function RungeKutte(Function dynamics){
    MX dt = MX::sym("dt", 1);
    MX x = MX::sym("x", dynamics.size1_in(0));
    MX u = MX::sym("u", dynamics.size1_in(1));

    std::map<std::string, MX> args;
    args["x"] = x;
    args["u"] = u;
    args["dt"] = dt;

    auto result = dynamics({{"x", x}, {"u", u}});
    MX k1 = result.at("x_dot");

    MX x_adjusted = x + (dt / 2) * k1;
    result = dynamics({{"x", x_adjusted}, {"u", u}});
    MX k2 = result.at("x_dot");

    x_adjusted = x + (dt / 2 )* k2;
    result = dynamics({{"x", x_adjusted}, {"u", u}});
    MX k3 = result.at("x_dot");

    x_adjusted = x + dt * k3;
    result = dynamics({{"x", x_adjusted}, {"u", u}});
    MX k4 = result.at("x_dot");

    MX xn = x + dt/6 * (k1 + 2*k2 + 2*k3 + k4);

    Function integrator = Function("integrator", {x, u, dt}, {xn}, {"x", "u", "dt"}, {"xn"});

    return integrator;
}




// from casadi import MX, Function


// def Euler(dynamics):
//   dt = MX.sym('dt', 1)
//   x = MX.sym('x', dynamics.size1_in(0))
//   u = MX.sym('u', dynamics.size1_in(1))
//   integrator = Function('integrator',
//     [x, u, dt],
//     [x + dt * dynamics(x, u)],
//     ['x', 'u', 'dt'], ['xn'])
//   return integrator

// def RungeKutta4(dynamics):
//   dt = MX.sym('dt', 1)
//   x = MX.sym('x', dynamics.size1_in(0))
//   u = MX.sym('u', dynamics.size1_in(1))
//   k1 = dynamics(x, u)
//   k2 = dynamics(x + dt/2 * k1, u)
//   k3 = dynamics(x + dt/2 * k2, u)
//   k4 = dynamics(x + dt * k3, u)
//   integrator = Function('integrator',
//     [x, u, dt],
//     [x + dt/6 * (k1 + 2*k2 + 2*k3 + k4)],
//     ['x', 'u', 'dt'], ['xn'])
//   return integrator