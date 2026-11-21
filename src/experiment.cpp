#include "experiment.hpp"
#include "distortions.hpp"
#include "generators.hpp"

using namespace std;

vector<Distortion> all_distortions() {
    return {
        {"vigenere_r1", [](const vector<int>& x, mt19937& rng) { return vigenere(x, 1, rng); }},
        {"vigenere_r5", [](const vector<int>& x, mt19937& rng) { return vigenere(x, 5, rng); }},
        {"vigenere_r10", [](const vector<int>& x, mt19937& rng) { return vigenere(x, 10, rng); }},
        {"affine", [](const vector<int>& x, mt19937& rng) { return affine(x, rng); }},
        {"affine_bigram", [](const vector<int>& x, mt19937& rng) { return affine_bigram(x, rng); }},
        {"uniform_l1", [](const vector<int>& x, mt19937& rng) { return uniform_sequence(x.size(), 1, rng); }},
        {"uniform_l2", [](const vector<int>& x, mt19937& rng) { return uniform_sequence(x.size(), 2, rng); }},
        {"recurrent_l1", [](const vector<int>& x, mt19937& rng) { return recurrent_sequence(x.size(), 1, rng); }},
        {"recurrent_l2", [](const vector<int>& x, mt19937& rng) { return recurrent_sequence(x.size(), 2, rng); }},
    };
}

vector<vector<int>> make_distorted(const Distortion& d,
                                   const vector<vector<int>>& X, mt19937& rng) {
    vector<vector<int>> Y;
    for (const vector<int>& x : X) {
        Y.push_back(d.make(x, rng));
    }
    return Y;
}