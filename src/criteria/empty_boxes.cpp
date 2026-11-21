#include "criteria/empty_boxes.hpp"
#include "ngram_stats.hpp"

using namespace std;

bool criterion_5_1(const vector<int>& text, int l,
                   const vector<int>& frequent, int k_empt) {
    vector<long long> counts = count_ngrams(text, l);
    int empty = 0;
    for (int x : frequent) {
        if (counts[x] == 0) {
            empty++;
        }
    }
    return empty >= k_empt;
}