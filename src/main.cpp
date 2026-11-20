#include <fstream>
#include <filesystem>
#include "preprocess.hpp"
#include "ngram_stats.hpp"
#include "report_writer.hpp"

using namespace std;
namespace fs = std::filesystem;

int main() {
    fs::create_directories("output");

    vector<int> corpus = load_corpus("data/raw");

    vector<long long> letter_counts = count_ngrams(corpus, 1);
    vector<double> letter_freq = to_frequencies(letter_counts);
    double letter_entropy = entropy(letter_freq, 1);
    double letter_index = coincidence_index(letter_counts);

    vector<long long> bigram_counts = count_ngrams(corpus, 2);
    vector<double> bigram_freq = to_frequencies(bigram_counts);
    double bigram_entropy = entropy(bigram_freq, 2);
    double bigram_index = coincidence_index(bigram_counts);

    write_letter_table("output/letters.csv", letter_freq);
    write_bigram_table("output/bigrams.csv", bigram_freq);

    ofstream stats("output/stats.txt");
    stats << "corpus = " << corpus.size() << endl;
    stats << "H1 = " << letter_entropy << endl;
    stats << "H2 = " << bigram_entropy << endl;
    stats << "I1 = " << letter_index << endl;
    stats << "I2 = " << bigram_index << endl;
}