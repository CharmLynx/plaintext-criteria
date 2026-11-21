#include "distortions.hpp"
#include "alphabet.hpp"

using namespace std;

vector<int> vigenere(const vector<int>& text, int r, mt19937& rng) {
    uniform_int_distribution<int> dist(0, M - 1);

    vector<int> key(r, 0);
    bool all_zero = true;
    while (all_zero) {
        for (int i = 0; i < r; i++) {
            key[i] = dist(rng);
            if (key[i] != 0) {
                all_zero = false;
            }
        }
    }

    vector<int> result(text.size());
    for (size_t i = 0; i < text.size(); i++) {
        result[i] = (text[i] + key[i % r]) % M;
    }
    return result;
}

vector<int> affine(const vector<int>& text, mt19937& rng) {
    return {};
}

vector<int> affine_bigram(const vector<int>& text, mt19937& rng) {
    return {};
}