#include "../include/quad.hpp"

quad::quad(std::string path_file)
{
    this->m = 1;
    this->l = 1;

    this->t_max = 5;
    this->t_min = 0;
    this->omega_max = 3;
    this->ctau = 0.5;
    this->rampup_dist = 0;
    this->t_ramp_start = 5;
    this->omega_ramp_start = 3;

    this->v_max = 0.0;
    this->cd = 0.0;
    this->g = 9.801;

    std::ifstream file(path_file);

    if(file.is_open()){
        readfile(path_file);
    }
    
}

void quad::readfile(std::string file){
    YAML::Node dado = YAML::LoadFile(file);

    if (dado["mass"]){
        this->m = dado["mass"].as<double>();
    }else std::cout << "No mass specified in file" << std::endl;

    if(dado["arm_length"]){
        this->l = dado["arm_length"].as<double>();
    }else std::cout << "No arm_lenth specified in file" << std::endl;

    if(dado["inertia"]){
        auto inertia = dado["inertia"];
        for(std::size_t i = 0; i < inertia.size(); i++){
            for(std::size_t j = 0; j < inertia[i].size(); j++){
                this->i(i,j) = inertia[i][j].as<double>();
            }
        }

        this->i_inv = inv(this->i);
    }else std::cout << "No inertia specified in file" << std::endl;

    if(dado["TWR_max"]){
        this->t_max = dado["TWR_max"].as<double>() * 9.81 * (this->m/4);
    }else if(dado["thrust_max"]){
        this->t_max = dado["thrust_max"].as<double>();
    }else std::cout << "No max thrust specified in file" << std::endl;

    if(dado["TWR_min"]){
        this->t_max = dado["TWR_min"].as<double>() * 9.81 * (this->m/4);
    }else if(dado["thrust_min"]){
        this->t_max = dado["thrust_min"].as<double>();
    }else std::cout << "No min thrust specified in file" << std::endl;


    if(dado["omega_max_xy"]){
        this->omega_max_xy = dado["omega_max_xy"].as<double>();
    }else std::cout << "No max omega_xy specified in file" << std::endl;

    if(dado["omega_max_z"]){
        this->omega_max_z = dado["omega_max_z"].as<double>();
    }else std::cout << "No max omega_z specified in file" << std::endl;

    if(dado["torque_coeff"]){
        this->ctau = dado["torque_coeff"].as<double>();
    }else std::cout << "No thrust to drag coefficient specified in file" << std::endl;

    if(dado["v_max"]){
        this->v_max = dado["v_max"].as<double>();
        double a_max = 4 * (this->t_max / this->m);
        double a_hmax = sqrt(a_max*a_max - this->g*this->g);
        this->cd = a_hmax/this->v_max;
    }

    if(dado["drag_coeff"]){
        this->cd = dado["drag_coeff"].as<double>();
    }

    if(dado["rampup_dist"]){
        this->rampup_dist = dado["rampup_dist"].as<double>();
    }

    if(dado["TWR_ramp_start"] && dado["omega_ramp_start"]){
        this->t_ramp_start = std::min(dado["TWR_ramp_start"].as<double>() * 9.81 * (this->m/4), this->t_max);
        this->omega_ramp_start = std::min((dado["omega_ramp_start"].as<double>()), this->omega_max_xy);
    }else{
        std::cout << "No TWR_ramp_start or omega_ramp_start specified. Disabling rampup" << std::endl;
        this->rampup_dist = 0;
    }
}

Function quad::dynamics(){
    MX p = MX::sym("p", 3);
    MX v = MX::sym("v", 3);
    MX q = MX::sym("q", 4);
    MX w = MX::sym("w", 3);
    MX T = MX::sym("thrust", 4);

    MX x = vertcat(p, v, q, w);
    MX u = T;

    DM g = DM({0, 0, -this->g});

    MX x_dot = vertcat(v, 
    rotate_quat(q, vertcat(0, 0, (T(0) + T(1) + T(2) + T(3))/this->m)) + g - v * this->cd,
    0.5*quat_mult(q, vertcat(0,w)),
    mtimes(this->i_inv, vertcat(
        this->l*(T(0) - T(1) - T(2) + T(3)),
        this->l*(-T(0) - T(1) + T(2) + T(3)),
        this->ctau*(T(0) - T(1) + T(2) - T(3))
    ) - cross(w, mtimes(this->i,w)))
    );

    std::vector<MX> inputs = {x, u};
    std::vector<MX> outputs = {x_dot};

    Function fx = Function("f",  inputs, outputs);

    return fx;
}

