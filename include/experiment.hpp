#pragma once

#include <vector>
#include <string>
#include <random>
#include <functional>

#include "language_model.hpp" 

struct Distortion {
    std::string name;
    std::function<std::vector<int>(const std::vector<int>&, std::mt19937&)> make;
};

std::vector<Distortion> all_distortions();

std::vector<std::vector<int>> make_distorted(const Distortion& d,
                                             const std::vector<std::vector<int>>& X,
                                             std::mt19937& rng);

struct Candidate {
    std::string label;
    std::function<bool(const std::vector<int>&)> criterion;
};

double error_sum(const Candidate& c,
                 const std::vector<std::vector<int>>& X,
                 const std::vector<std::vector<std::vector<int>>>& Ys);

Candidate tune(const std::vector<Candidate>& candidates,
               const std::vector<std::vector<int>>& X,
               const std::vector<std::vector<std::vector<int>>>& Ys);

struct CriterionSpec {
    std::string name;
    std::function<std::vector<Candidate>(int l, int L)> candidates;
};

std::vector<CriterionSpec> all_criteria(const LanguageModel& model, std::mt19937& rng);

struct ResultRow {
    int L;
    std::string criterion;
    std::string thresholds[2];            
    double fp[2];                         
    std::vector<double> fn[2];            
};

std::vector<ResultRow> run_experiment(const std::vector<int>& test,
                                      const LanguageModel& model,
                                      const std::vector<int>& lengths,
                                      const std::vector<int>& counts,
                                      const std::vector<int>& tune_counts);