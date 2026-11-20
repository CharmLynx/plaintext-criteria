#include "report_writer.hpp"
#include "alphabet.hpp"

#include <fstream>

using namespace std;

void write_letter_table(const string& path,
                        const vector<double>& freq) {
    ofstream f(path);
    f << "letter,freq" << endl;
    for (int i = 0; i < M; i++) {
        f << index_to_letter(i) << "," << freq[i] << endl;
    }
}

void write_bigram_table(const string& path,
                        const vector<double>& freq) {
    ofstream f(path);

    for (int j = 0; j < M; j++) {
        f << "," << index_to_letter(j);
    }
    f << endl;

    for (int i = 0; i < M; i++) {
        f << index_to_letter(i);
        for (int j = 0; j < M; j++) {
            f << "," << freq[i * M + j];
        }
        f << endl;
    }
}