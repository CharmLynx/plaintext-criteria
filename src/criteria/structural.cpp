#include "criteria/structural.hpp"
#include "compression.hpp"

using namespace std;

bool criterion_structural(const vector<int>& text, int random_size,
                          double k_low, double k_high) {
    double ratio = (double)compressed_size(text) / random_size;
    return ratio < k_low || ratio > k_high;
}