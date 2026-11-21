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
    return false;
}

bool criterion_1_2(const vector<int>& text, int l,
                   const vector<int>& forbidden,
                   const vector<double>& lang_freq) {
    return false;
}

bool criterion_1_3(const vector<int>& text, int l,
                   const vector<int>& forbidden,
                   const vector<double>& lang_freq) {
    return false;
}