#pragma once

#include <vector>
#include <random>

std::vector<int> uniform_sequence(int L, int l, std::mt19937& rng);

std::vector<int> recurrent_sequence(int L, int l, std::mt19937& rng);

std::vector<int> periodic_text(const std::vector<int>& pattern, int L);