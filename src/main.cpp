#include <iostream>
#include <fstream>
#include <filesystem>
#include "preprocess.hpp"
#include "ngram_stats.hpp"
#include "language_model.hpp"
#include "experiment.hpp"
#include "report_writer.hpp"

using namespace std;
namespace fs = std::filesystem;

int main() {
    fs::create_directories("output");

    vector<int> train;
    vector<int> test;
    load_split_corpus("data/raw", 0.75, train, test);

    LanguageModel model = build_language_model(train);

    write_letter_table("output/letters.csv", model.letter_freq);
    write_bigram_table("output/bigrams.csv", model.bigram_freq);

    ofstream stats("output/stats.txt");
    stats << "train = " << train.size() << endl;
    stats << "test = " << test.size() << endl;
    stats << "H1 = " << model.letter_entropy << endl;
    stats << "H2 = " << model.bigram_entropy << endl;
    stats << "I1 = " << coincidence_index(count_ngrams(train, 1)) << endl;
    stats << "I2 = " << coincidence_index(count_ngrams(train, 2)) << endl;

    vector<ResultRow> rows = run_experiment(test, model,
                                            {10, 100, 1000, 10000},
                                            {10000, 10000, 10000, 1000},
                                            {1000, 1000, 1000, 200});
    write_error_tables("output", rows, all_distortions());
}