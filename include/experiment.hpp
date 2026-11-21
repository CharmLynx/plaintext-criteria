#pragma once

#include <vector>
#include <string>
#include <random>
#include <functional>

struct Distortion {
    std::string name;
    std::function<std::vector<int>(const std::vector<int>&, std::mt19937&)> make;
};

std::vector<Distortion> all_distortions();

std::vector<std::vector<int>> make_distorted(const Distortion& d,
                                             const std::vector<std::vector<int>>& X,
                                             std::mt19937& rng);