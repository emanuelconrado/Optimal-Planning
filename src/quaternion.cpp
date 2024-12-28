#include "../include/quaternion.hpp"

MX quat_mult(const MX &q1, const MX &q2){

    MX ans = vertcat(q2(0) * q1(0) - q2(1) * q1(1) - q2(2) * q1(2) - q2(3) * q1(3),
                    q2(0) * q1(1) + q2(1) * q1(0) - q2(2) * q1(3) + q2(3) * q1(2),
                    q2(0) * q1(2) + q2(2) * q1(0) + q2(1) * q1(3) - q2(3) * q1(1),
                    q2(0) * q1(3) - q2(1) * q1(2) + q2(2) * q1(1) + q2(3) * q1(0));
    
    // MX w = q1(0) * q2(0) - q1(1) * q2(1) - q1(2) * q2(2) - q1(3) * q2(3);
    // MX x = q1(0) * q2(1) + q1(1) * q2(0) + q1(2) * q2(3) - q1(3) * q2(2);
    // MX y = q1(0) * q2(2) - q1(1) * q2(3) + q1(2) * q2(0) + q1(3) * q2(1);
    // MX z = q1(0) * q2(3) + q1(1) * q2(2) - q1(2) * q2(1) + q1(3) * q2(0);

    return ans;
}

MX rotate_quat(const MX &q1, const MX &v1){
    MX ans = quat_mult(quat_mult(q1, vertcat(0, v1)), vertcat(q1(0),-q1(1), -q1(2), -q1(3)));
    return vertcat(ans(1), ans(2), ans(3));
}