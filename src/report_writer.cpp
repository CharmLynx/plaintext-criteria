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

void write_error_tables(const string& dir,
                        const vector<ResultRow>& rows,
                        const vector<Distortion>& distortions) {
    for (size_t d = 0; d < distortions.size(); d++) {
        ofstream f(dir + "/errors_" + distortions[d].name + ".csv");
        f << "L,criterion,thresholds_l1,FP_l1,FN_l1,thresholds_l2,FP_l2,FN_l2" << endl;
        for (const ResultRow& row : rows) {
            f << row.L << "," << row.criterion << ","
              << "\"" << row.thresholds[0] << "\"," << row.fp[0] << "," << row.fn[0][d] << ","
              << "\"" << row.thresholds[1] << "\"," << row.fp[1] << "," << row.fn[1][d] << endl;
        }
    }
}