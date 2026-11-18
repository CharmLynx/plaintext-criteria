#include "alphabet.hpp"

using namespace std;

const vector<string> LETTERS = {
    "а", "б", "в", "г", "д", "е", "є", "ж",
    "з", "и", "і", "ї", "й", "к", "л", "м", 
    "н", "о", "п", "р", "с", "т", "у", "ф", 
    "х", "ц", "ч", "ш", "щ", "ь", "ю", "я"
};


int letter_to_index(const string& letter) {
    for (int i = 0; i < M; i++) {
        if (LETTERS[i] == letter) {
            return i;
        }
    }
    return -1;
}

string index_to_letter(int index) {
    return LETTERS[index];
}