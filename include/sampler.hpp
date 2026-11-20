#pragma once

#include <vector>
#include <random>

std::vector<std::vector<int>> sample_texts(const std::vector<int>& corpus, int L, int N, std::mt19937& rng);