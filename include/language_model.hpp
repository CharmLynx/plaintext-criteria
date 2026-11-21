#pragma once

#include <vector>

struct LanguageModel {
    std::vector<double> letter_freq;   
    std::vector<double> bigram_freq;   
    double letter_entropy;             
    double bigram_entropy;             
};

LanguageModel build_language_model(const std::vector<int>& corpus);

const std::vector<double>& model_freq(const LanguageModel& model, int l);

double model_entropy(const LanguageModel& model, int l);

std::vector<int> rarest_ngrams(const std::vector<double>& freq, int k);

std::vector<int> most_frequent_ngrams(const std::vector<double>& freq, int k);