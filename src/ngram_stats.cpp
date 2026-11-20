#include "ngram_stats.hpp"
#include "alphabet.hpp"

#include <vector>
#include <cmath>

using namespace std;

vector<long long> count_ngrams(const vector<int>& text, int l) {
    switch (l) {
        case 1: {
            vector<long long> counts(M, 0);
            for (size_t i = 0; i < text.size(); i++) {
                counts[text[i]]++;
            }
            return counts;
        }
        case 2: {
            vector<long long> counts(M * M, 0);
            for (size_t i = 0; i + 1 < text.size(); i++) {
                counts[text[i] * M + text[i + 1]]++;
            }
            return counts;
        }
        default:
            return {};
    }
}

vector<double> to_frequencies(const vector<long long>& counts) {

    return {};
}

double entropy(const vector<double>& freq, int l) {

    return {};
}

double coincidence_index(const vector<long long>& counts) {

    return {};
}