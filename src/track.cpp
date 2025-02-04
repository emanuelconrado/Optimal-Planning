#include "../include/track.hpp"

Track::Track(std::string path_file){
    this->gates = {};
    this->ring = false;

    std::ifstream file(path_file);

    if(file.is_open()){
        readfile(path_file);
    }else std::cout << "Não abriu" << std::endl;
}

void Track::readfile(std::string file){
    YAML::Node dado = YAML::LoadFile(file);
    YAML::Node initial;

    if(dado["gates"]){
        auto gate = dado["gates"];
        this->gates.reserve(gate.size());

        for(std::size_t i = 0; i < gate.size(); i++){
            std::vector<double> row;
            row.reserve(gate[0].size());

            for(std::size_t j = 0; j < gate[0].size(); j++){
                 row.push_back(gate[i][j].as<double>());
            }

            this->gates.push_back(row);
        }
    }else std::cout << "No gates specified in file" << std::endl;

    if(dado["initial"]){
        initial = dado["initial"];
    }else{
        initial = dado;
    }

    if(initial["position"]){
        auto position = initial["position"];
        this->init_pos.reserve(position.size());

        for(std::size_t i = 0; i < position.size(); i++){
            this->init_pos.push_back(position[i].as<double>());
        }
    }

    if(initial["attitude"]){
        auto attitude = initial["attitude"];
        this->init_att.reserve(attitude.size());

        for(std::size_t i = 0; i < attitude.size(); i++){
            this->init_att.push_back(attitude[i].as<double>());
        }
    }

    if(initial["velocity"]){
        auto velocity = initial["velocity"];
        this->init_vel.reserve(velocity.size());

        for(std::size_t i = 0; i < velocity.size(); i++){
            this->init_vel.push_back(velocity[i].as<double>());
        }
    }

    if(initial["omega"]){
        auto omega = initial["omega"];
        this->init_omega.reserve(omega.size());

        for(std::size_t i = 0; i < omega.size(); i++){
            this->init_omega.push_back(omega[i].as<double>());
        }
    }

    if(dado["end"]){
        auto end = dado["end"];

        if(end["position"]){
            auto position = end["position"];
            this->end_pos.reserve(position.size());

            for(std::size_t i = 0; i < position.size(); i++){
                this->end_pos.push_back(position[i].as<double>());
            }
        }

        if(end["attitude"]){
            auto attitude = end["attitude"];
            this->end_att.reserve(attitude.size());

            for(std::size_t i = 0; i < attitude.size(); i++){
                this->end_att.push_back(attitude[i].as<double>());
            }
        }

        if(end["velocity"]){
            auto velocity = end["velocity"];
            this->end_vel.reserve(velocity.size());

            for(std::size_t i = 0; i < velocity.size(); i++){
                this->end_vel.push_back(velocity[i].as<double>());
            }
        }

        if(end["omega"]){
            auto omega = end["omega"];
            this->end_omega.reserve(omega.size());

            for(std::size_t i = 0; i < omega.size(); i++){
                this->end_omega.push_back(omega[i].as<double>());
            }
        }
    }

    if(dado["ring"]){
        this->ring = dado["ring"].as<bool>();
    }
}

Track::~Track(){}