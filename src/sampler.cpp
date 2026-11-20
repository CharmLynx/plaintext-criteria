#include "sampler.hpp"

using namespace std;

vector<vector<int>> sample_texts(const vector<int>& corpus, int L, int N, mt19937& rng) {
    vector<vector<int>> texts;
    uniform_int_distribution<size_t> dist(0, corpus.size() - L);

    for (int i = 0; i < N; i++) {
        size_t start = dist(rng);
        vector<int> text;
        for (size_t j = start; j < start + L; j++) {
            text.push_back(corpus[j]);
        }
        texts.push_back(text);
    }

    return texts;
}