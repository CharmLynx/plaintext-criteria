#include "criteria/forbidden.hpp"
#include "ngram_stats.hpp"

using namespace std;

bool criterion_1_0(const vector<int>& text, int l,
                   const vector<int>& forbidden) {
    vector<long long> counts = count_ngrams(text, l);
    for (int x : forbidden) {
        if (counts[x] > 0) {
            return true;
        }
    }
    return false;
}

bool criterion_1_1(const vector<int>& text, int l,
                   const vector<int>& forbidden, int k_p) {
    vector<long long> counts = count_ngrams(text, l);
    int found = 0;
    for (int x : forbidden) {
        if (counts[x] > 0) {
            found++;
        }
    }
    return found >= k_p;
}

bool criterion_1_2(const vector<int>& text, int l,
                   const vector<int>& forbidden,
                   const vector<double>& lang_freq) {
    vector<double> freq = to_frequencies(count_ngrams(text, l));
    for (int x : forbidden) {
        if (freq[x] > lang_freq[x]) {
            return true;
        }
    }
    return false;
}

bool criterion_1_3(const vector<int>& text, int l,
                   const vector<int>& forbidden,
                   const vector<double>& lang_freq) {
    vector<double> freq = to_frequencies(count_ngrams(text, l));
    double F_p = 0;
    double K_p = 0;
    for (int x : forbidden) {
        F_p += freq[x];
        K_p += lang_freq[x];
    }
    return F_p > K_p;
}