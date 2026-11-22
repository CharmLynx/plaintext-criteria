#pragma once

#include <vector>
#include <functional>

double h1_rate(const std::vector<std::vector<int>>& texts,
               const std::function<bool(const std::vector<int>&)>& criterion);