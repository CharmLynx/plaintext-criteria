#pragma once

#include <vector>
#include <random>

std::vector<int> vigenere(const std::vector<int>& text, int r, std::mt19937& rng);

std::vector<int> affine(const std::vector<int>& text, std::mt19937& rng);

std::vector<int> affine_bigram(const std::vector<int>& text, std::mt19937& rng);