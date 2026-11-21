#include "preprocess.hpp"
#include "alphabet.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

string read_file(const string& path) {
    ifstream f(path, ios::binary);
    stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

int utf8_char_length(unsigned char first_byte) {
    if ((first_byte & 0b10000000) == 0b00000000) {
        return 1;
    }
    if ((first_byte & 0b11100000) == 0b11000000) {
        return 2;
    }
    if ((first_byte & 0b11110000) == 0b11100000) {
        return 3;
    }
    if ((first_byte & 0b11111000) == 0b11110000) {
        return 4;
    }
    return 1;
}

const vector<string> UPPER = {
    "А", "Б", "В", "Г", "Д", "Е", "Є", "Ж",
    "З", "И", "І", "Ї", "Й", "К", "Л", "М",
    "Н", "О", "П", "Р", "С", "Т", "У", "Ф",
    "Х", "Ц", "Ч", "Ш", "Щ", "Ь", "Ю", "Я"
};

string normalize_char(const string& ch) {
    if (ch == "ґ" || ch == "Ґ") {
        return "г";
    }
    for (int i = 0; i < M; i++) {
        if (UPPER[i] == ch) {
            return LETTERS[i];
        }
    }
    return ch;
}

vector<int> clean_text(const string& text) {
    vector<int> result;
    size_t pos = 0;

    while (pos < text.size()) {
        int len = utf8_char_length(text[pos]);
        string ch = text.substr(pos, len);
        ch = normalize_char(ch);
        int idx = letter_to_index(ch);
        if (idx != -1) {
            result.push_back(idx);
        }
        pos += len;
    }

    return result;
}


vector<int> load_corpus(const string& dir) {
    vector<string> paths;
    for (const auto& entry : fs::directory_iterator(dir)) {
        paths.push_back(entry.path().string());
    }

    sort(paths.begin(), paths.end());

    vector<int> corpus;
    for (const string& path : paths) {
        vector<int> part = clean_text(read_file(path));
        corpus.insert(corpus.end(), part.begin(), part.end());
        cout << path << ": " << part.size() << endl;
    }

    return corpus;
}

vector<string> sorted_files(const string& dir) {
    vector<string> paths;
    for (const auto& entry : fs::directory_iterator(dir)) {
        paths.push_back(entry.path().string());
    }
    sort(paths.begin(), paths.end());
    return paths;
}

void load_split_corpus(const string& dir, double train_share,
                       vector<int>& train, vector<int>& test) {
    for (const string& path : sorted_files(dir)) {
        vector<int> book = clean_text(read_file(path));
        size_t border = book.size() * train_share;
        train.insert(train.end(), book.begin(), book.begin() + border);
        test.insert(test.end(), book.begin() + border, book.end());
        cout << path << ": " << border << " + " << book.size() - border << endl;
    }
}