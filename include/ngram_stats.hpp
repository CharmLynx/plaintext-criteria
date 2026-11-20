#pragma once

#include <vector>

std::vector<long long> count_ngrams(const std::vector<int>& text, int l);

std::vector<double> to_frequencies(const std::vector<long long>& counts);

double entropy(const std::vector<double>& freq, int l);

double coincidence_index(const std::vector<long long>& counts);