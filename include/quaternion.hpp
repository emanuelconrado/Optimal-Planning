#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include <casadi/casadi.hpp>

using namespace casadi;

MX quat_mult(const MX &q1, const MX &q2);
MX rotate_quat(const MX &v1, const MX &q1);


#endif