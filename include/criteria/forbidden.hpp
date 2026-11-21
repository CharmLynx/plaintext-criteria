#pragma once

#include <vector>

bool criterion_1_0(const std::vector<int>& text, int l,
                   const std::vector<int>& forbidden);

bool criterion_1_1(const std::vector<int>& text, int l,
                   const std::vector<int>& forbidden, int k_p);

bool criterion_1_2(const std::vector<int>& text, int l,
                   const std::vector<int>& forbidden,
                   const std::vector<double>& lang_freq);

bool criterion_1_3(const std::vector<int>& text, int l,
                   const std::vector<int>& forbidden,
                   const std::vector<double>& lang_freq);