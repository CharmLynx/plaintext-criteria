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
    uniform_int_distribution<int> dist_a(0, M / 2 - 1);
    uniform_int_distribution<int> dist_b(0, M - 1);

    int a = 1;
    int b = 0;
    while (a == 1 && b == 0) {
        a = 2 * dist_a(rng) + 1;
        b = dist_b(rng);
    }

    vector<int> result(text.size());
    for (size_t i = 0; i < text.size(); i++) {
        result[i] = (a * text[i] + b) % M;
    }
    return result;
}

vector<int> affine_bigram(const vector<int>& text, mt19937& rng) {
    const int M2 = M * M;
    uniform_int_distribution<int> dist_a(0, M2 / 2 - 1);
    uniform_int_distribution<int> dist_b(0, M2 - 1);

    int a = 1;
    int b = 0;
    while (a == 1 && b == 0) {
        a = 2 * dist_a(rng) + 1;
        b = dist_b(rng);
    }

    vector<int> result(text.size());
    for (size_t i = 0; i + 1 < text.size(); i += 2) {
        int x = text[i] * M + text[i + 1];
        int y = (a * x + b) % M2;
        result[i] = y / M;
        result[i + 1] = y % M;
    }
    return result;
}