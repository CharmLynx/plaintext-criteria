#include "generators.hpp"
#include "alphabet.hpp"

using namespace std;

vector<int> uniform_sequence(int L, int l, mt19937& rng) {
    vector<int> result(L);
    if (l == 1) {
        uniform_int_distribution<int> dist(0, M - 1);
        for (int i = 0; i < L; i++) {
            result[i] = dist(rng);
        }
    } else {
        uniform_int_distribution<int> dist(0, M * M - 1);
        for (int i = 0; i + 1 < L; i += 2) {
            int y = dist(rng);
            result[i] = y / M;
            result[i + 1] = y % M;
        }
    }
    return result;
}

vector<int> recurrent_sequence(int L, int l, mt19937& rng) {
    return {};
}