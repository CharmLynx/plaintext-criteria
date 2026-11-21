#include "criteria/entropy_test.hpp"
#include "ngram_stats.hpp"

#include <cmath>

using namespace std;

bool criterion_3_0(const vector<int>& text, int l,
                   double lang_entropy, double k_H) {
    double text_entropy = entropy(to_frequencies(count_ngrams(text, l)), l);
    return fabs(lang_entropy - text_entropy) > k_H;
}