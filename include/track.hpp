#ifndef TRACK_HPP
#define TRACK_HPP
#include <yaml-cpp/yaml.h>
#include <vector>
#include <optional>
#include <fstream>
#include <string>
#include <iostream>

class track
{
private:
    std::optional <std::vector<double>> init_pos = std::nullopt;
    std::optional <std::vector<double>> init_att = std::nullopt;
    std::optional <std::vector<double>> init_vel = std::nullopt;
    std::optional <std::vector<double>> init_omega = std::nullopt;
    std::optional <std::vector<double>> end_pos = std::nullopt;
    std::optional <std::vector<double>> end_att = std::nullopt;
    std::optional <std::vector<double>> end_vel = std::nullopt;
    std::optional <std::vector<double>> end_omega = std::nullopt;
    std::vector<std::vector<double>> gates;
    bool ring;
public:
    track(std::string path_file);
    ~track();
    void readfile(std::string file);
};



#endif