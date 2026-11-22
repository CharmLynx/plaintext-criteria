#include "experiment.hpp"
#include "distortions.hpp"
#include "generators.hpp"
#include "evaluator.hpp"
#include "criteria/forbidden.hpp"
#include "criteria/entropy_test.hpp"
#include "criteria/empty_boxes.hpp"
#include "criteria/structural.hpp"
#include "compression.hpp"
#include "sampler.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

vector<Distortion> all_distortions() {
    return {
        {"vigenere_r1", [](const vector<int>& x, mt19937& rng) { return vigenere(x, 1, rng); }},
        {"vigenere_r5", [](const vector<int>& x, mt19937& rng) { return vigenere(x, 5, rng); }},
        {"vigenere_r10", [](const vector<int>& x, mt19937& rng) { return vigenere(x, 10, rng); }},
        {"affine", [](const vector<int>& x, mt19937& rng) { return affine(x, rng); }},
        {"affine_bigram", [](const vector<int>& x, mt19937& rng) { return affine_bigram(x, rng); }},
        {"uniform_l1", [](const vector<int>& x, mt19937& rng) { return uniform_sequence(x.size(), 1, rng); }},
        {"uniform_l2", [](const vector<int>& x, mt19937& rng) { return uniform_sequence(x.size(), 2, rng); }},
        {"recurrent_l1", [](const vector<int>& x, mt19937& rng) { return recurrent_sequence(x.size(), 1, rng); }},
        {"recurrent_l2", [](const vector<int>& x, mt19937& rng) { return recurrent_sequence(x.size(), 2, rng); }},
    };
}

vector<vector<int>> make_distorted(const Distortion& d,
                                   const vector<vector<int>>& X, mt19937& rng) {
    vector<vector<int>> Y;
    for (const vector<int>& x : X) {
        Y.push_back(d.make(x, rng));
    }
    return Y;
}

double error_sum(const Candidate& c,
                 const vector<vector<int>>& X,
                 const vector<vector<vector<int>>>& Ys) {
    double alpha = h1_rate(X, c.criterion);
    double beta_sum = 0;
    for (const vector<vector<int>>& Y : Ys) {
        beta_sum += 1 - h1_rate(Y, c.criterion);
    }
    return alpha + beta_sum / Ys.size();
}

Candidate tune(const vector<Candidate>& candidates,
               const vector<vector<int>>& X,
               const vector<vector<vector<int>>>& Ys) {
    size_t best = 0;
    double best_error = error_sum(candidates[0], X, Ys);
    for (size_t i = 1; i < candidates.size(); i++) {
        double e = error_sum(candidates[i], X, Ys);
        if (e < best_error) {
            best = i;
            best_error = e;
        }
    }
    return candidates[best];
}

string num(double x) {
    ostringstream out;
    out << x;
    return out.str();
}

vector<int> forbidden_sizes(int l) {
    if (l == 1) {
        return {1, 2, 3, 4, 5};
    }
    return {1, 2, 3, 5, 10, 20, 50, 100, 150, 200, 300, 400, 500};
}

vector<CriterionSpec> all_criteria(const LanguageModel& model, mt19937& rng) {
    vector<CriterionSpec> specs;

    specs.push_back({"1.0", [&model](int l, int L) {
        vector<Candidate> result;
        for (int h_p : forbidden_sizes(l)) {
            vector<int> forbidden = rarest_ngrams(model_freq(model, l), h_p);
            result.push_back({"h_p=" + to_string(h_p),
                [forbidden, l](const vector<int>& t) {
                    return criterion_1_0(t, l, forbidden);
                }});
        }
        return result;
    }});

    specs.push_back({"1.1", [&model](int l, int L) {
        vector<Candidate> result;
        for (int h_p : forbidden_sizes(l)) {
            vector<int> forbidden = rarest_ngrams(model_freq(model, l), h_p);
            for (int k_p : {1, 2, 3, 5, 10, 20}) {
                if (k_p > h_p) {
                    continue;
                }
                result.push_back({"h_p=" + to_string(h_p) + ", k_p=" + to_string(k_p),
                    [forbidden, l, k_p](const vector<int>& t) {
                        return criterion_1_1(t, l, forbidden, k_p);
                    }});
            }
        }
        return result;
    }});

    specs.push_back({"1.2", [&model](int l, int L) {
        vector<Candidate> result;
        for (int h_p : forbidden_sizes(l)) {
            vector<int> forbidden = rarest_ngrams(model_freq(model, l), h_p);
            result.push_back({"h_p=" + to_string(h_p),
                [forbidden, l, &model](const vector<int>& t) {
                    return criterion_1_2(t, l, forbidden, model_freq(model, l));
                }});
        }
        return result;
    }});

    specs.push_back({"1.3", [&model](int l, int L) {
        vector<Candidate> result;
        for (int h_p : forbidden_sizes(l)) {
            vector<int> forbidden = rarest_ngrams(model_freq(model, l), h_p);
            result.push_back({"h_p=" + to_string(h_p),
                [forbidden, l, &model](const vector<int>& t) {
                    return criterion_1_3(t, l, forbidden, model_freq(model, l));
                }});
        }
        return result;
    }});

    specs.push_back({"3.0", [&model](int l, int L) {
        vector<Candidate> result;
        double H = model_entropy(model, l);
        for (double k_H : {0.02, 0.05, 0.1, 0.2, 0.3, 0.5, 0.75, 1.0, 1.5, 2.0, 2.5, 3.0, 4.0}) {
            result.push_back({"k_H=" + num(k_H),
                [l, H, k_H](const vector<int>& t) {
                    return criterion_3_0(t, l, H, k_H);
                }});
        }
        return result;
    }});

    specs.push_back({"5.1", [&model](int l, int L) {
        vector<Candidate> result;
        vector<int> js = (l == 1) ? vector<int>{3, 5, 10} : vector<int>{50, 100, 200};
        for (int j : js) {
            vector<int> frequent = most_frequent_ngrams(model_freq(model, l), j);
            int step = max(1, j / 20);
            for (int k_empt = 1; k_empt <= j; k_empt += step) {
                result.push_back({"j=" + to_string(j) + ", k_empt=" + to_string(k_empt),
                    [frequent, l, k_empt](const vector<int>& t) {
                        return criterion_5_1(t, l, frequent, k_empt);
                    }});
            }
        }
        return result;
    }});

    specs.push_back({"structural", [&rng](int l, int L) {
        vector<Candidate> result;
        int random_size = compressed_size(uniform_sequence(L, 1, rng));
        for (double k_low : {0.0, 0.3, 0.5, 0.6, 0.7, 0.8}) {
            for (double k_high : {0.8, 0.85, 0.9, 0.95, 1.0, 1.05, 1.1, 1.2}) {
                if (k_low >= k_high) {
                    continue;
                }
                result.push_back({"k_low=" + num(k_low) + ", k_high=" + num(k_high),
                    [random_size, k_low, k_high](const vector<int>& t) {
                        return criterion_structural(t, random_size, k_low, k_high);
                    }});
            }
        }
        return result;
    }});

    return specs;
}

vector<ResultRow> run_experiment(const vector<int>& test,
                                 const LanguageModel& model,
                                 const vector<int>& lengths,
                                 const vector<int>& counts,
                                 const vector<int>& tune_counts) {
    mt19937 tune_rng(1);
    mt19937 eval_rng(2);
    mt19937 criteria_rng(3);

    vector<Distortion> distortions = all_distortions();
    vector<CriterionSpec> specs = all_criteria(model, criteria_rng);
    vector<ResultRow> rows;

    for (size_t i = 0; i < lengths.size(); i++) {
        int L = lengths[i];
        cout << "L = " << L << endl;

        vector<vector<int>> X_tune = sample_texts(test, L, tune_counts[i], tune_rng);
        vector<vector<vector<int>>> Ys_tune;
        for (const Distortion& d : distortions) {
            Ys_tune.push_back(make_distorted(d, X_tune, tune_rng));
        }

        vector<ResultRow> rows_L;
        vector<Candidate> best[2];
        for (const CriterionSpec& spec : specs) {
            ResultRow row;
            row.L = L;
            row.criterion = spec.name;
            for (int l = 1; l <= 2; l++) {
                Candidate c = tune(spec.candidates(l, L), X_tune, Ys_tune);
                row.thresholds[l - 1] = c.label;
                best[l - 1].push_back(c);
            }
            rows_L.push_back(row);
            cout << "  tuned " << spec.name << endl;
        }
        Ys_tune.clear();

        vector<vector<int>> X_eval = sample_texts(test, L, counts[i], eval_rng);
        for (size_t k = 0; k < specs.size(); k++) {
            for (int l = 0; l < 2; l++) {
                rows_L[k].fp[l] = h1_rate(X_eval, best[l][k].criterion);
            }
        }

        for (const Distortion& d : distortions) {
            vector<vector<int>> Y_eval = make_distorted(d, X_eval, eval_rng);
            for (size_t k = 0; k < specs.size(); k++) {
                for (int l = 0; l < 2; l++) {
                    rows_L[k].fn[l].push_back(1 - h1_rate(Y_eval, best[l][k].criterion));
                }
            }
        }

        rows.insert(rows.end(), rows_L.begin(), rows_L.end());
    }

    return rows;
}