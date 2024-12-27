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

    // if(dado["inertia"]){
    //     i = DM(dado["inertia"].as<double>());
    // }

    std::cout << this->i(1,1) << std::endl;

    std::cout << "Massa: " << this->m << std::endl;

    // if 'inertia' in quad:
    //   self.I = DM(quad['inertia'])
    //   self.I_inv = inv(self.I)
    // else:
    //   print("No inertia specified in " + filename)


    // if 'TWR_max' in quad:
    //   self.T_max = quad['TWR_max'] * 9.81 * self.m / 4
    // elif 'thrust_max' in quad:
    //   self.T_max = quad['thrust_max']
    // else:
    //   print("No max thrust specified in " + filename)

    // if 'TWR_min' in quad:
    //   self.T_min = quad['TWR_min'] * 9.81 * self.m / 4
    // elif 'thrust_min' in quad:
    //   self.T_min = quad['thrust_min']
    // else:
    //   print("No min thrust specified in " + filename)

    // if 'omega_max_xy' in quad:
    //   self.omega_max_xy = quad['omega_max_xy']
    // else:
    //   print("No max omega_xy specified in " + filename)

    // if 'omega_max_z' in quad:
    //   self.omega_max_z = quad['omega_max_z']
    // else:
    //   print("No max omega_z specified in " + filename)

    // if 'torque_coeff' in quad:
    //   self.ctau = quad['torque_coeff']
    // else:
    //   print("No thrust to drag coefficient specified in " + filename)

    // if 'v_max' in quad:
    //   self.v_max = quad['v_max']
    //   a_max = 4 * self.T_max / self.m
    //   a_hmax = sqrt(a_max**2 - self.g**2)
    //   self.cd = a_hmax / self.v_max
    // if 'drag_coeff' in quad:
    //   self.cd = quad['drag_coeff']

    // if 'rampup_dist' in quad:
    //   self.rampup_dist = quad['rampup_dist']
    //   if 'TWR_ramp_start' in quad and 'omega_ramp_start' in quad:
    //     self.T_ramp_start = min(quad['TWR_ramp_start'] * 9.81 * self.m / 4, self.T_max)
    //     self.omega_ramp_start = min(quad['omega_ramp_start'], self.omega_max_xy)
    //   else:
    //     print("No TWR_ramp_start or omega_ramp_start specified. Disabling rampup")
    //     rampup_dist = 0

    // if (config["massa"]) {
    //     massa = config["massa"].as<double>();
    // }
}

void quad::fillMatrix(DM &i){

}

