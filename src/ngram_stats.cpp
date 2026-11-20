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
    vector<double> freq(counts.size());
    long long total = 0;
    for (size_t i = 0; i < counts.size(); i++) {
        total += counts[i];
    }
    for (size_t i = 0; i < counts.size(); i++) {
        freq[i] = (double)counts[i] / total;
    }
    return freq;
}

double entropy(const vector<double>& freq, int l) {
    double h = 0;
    for (size_t i = 0; i < freq.size(); i++) {
        if (freq[i] > 0) {
            h -= freq[i] * log2(freq[i]);
        }
    }
    h /= l;
    return h;
}

double coincidence_index(const vector<long long>& counts) {
    long long L = 0;
    double I = 0;
    for (size_t i = 0; i < counts.size(); i++) {
        if (counts[i] > 0) {
            I += counts[i] * (counts[i] - 1);
        }
    }
    for (size_t i = 0; i < counts.size(); i++) {
        L += counts[i];
    }
    I /= L;
    I /= L - 1;
    return I;
}