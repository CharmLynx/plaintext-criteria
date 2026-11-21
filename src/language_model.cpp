#include "language_model.hpp"
#include "ngram_stats.hpp"

#include <algorithm>

using namespace std;

LanguageModel build_language_model(const vector<int>& corpus) {
    LanguageModel model;
    model.letter_freq = to_frequencies(count_ngrams(corpus, 1));
    model.bigram_freq = to_frequencies(count_ngrams(corpus, 2));
    model.letter_entropy = entropy(model.letter_freq, 1);
    model.bigram_entropy = entropy(model.bigram_freq, 2);
    return model;
}

const vector<double>& model_freq(const LanguageModel& model, int l) {
    if (l == 1) {
        return model.letter_freq;
    }
    return model.bigram_freq;
}

double model_entropy(const LanguageModel& model, int l) {
    if (l == 1) {
        return model.letter_entropy;
    }
    return model.bigram_entropy;
}

vector<int> rarest_ngrams(const vector<double>& freq, int k) {
    vector<int> indices(freq.size());
    for (size_t i = 0; i < freq.size(); i++) {
        indices[i] = i;
    }

    stable_sort(indices.begin(), indices.end(), [&freq](int a, int b) {
        return freq[a] < freq[b];
    });

    indices.resize(k);
    return indices;
}

vector<int> most_frequent_ngrams(const vector<double>& freq, int k) {
    return {};
}