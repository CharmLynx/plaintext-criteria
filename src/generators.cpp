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
    int mod = (l == 1) ? M : M * M;
    int count = (l == 1) ? L : L / 2;
    uniform_int_distribution<int> dist(0, mod - 1);

    vector<int> s(count);
    s[0] = 0;
    s[1] = 0;
    while (s[0] == 0 && s[1] == 0) {
        s[0] = dist(rng);
        s[1] = dist(rng);
    }
    for (int i = 2; i < count; i++) {
        s[i] = (s[i - 1] + s[i - 2]) % mod;
    }

    if (l == 1) {
        return s;
    }

    vector<int> result(L);
    for (int i = 0; i < count; i++) {
        result[2 * i] = s[i] / M;
        result[2 * i + 1] = s[i] % M;
    }
    return result;
}

vector<int> periodic_text(const vector<int>& pattern, int L) {
    vector<int> result(L);
    for (int i = 0; i < L; i++) {
        result[i] = pattern[i % pattern.size()];
    }
    return result;
}