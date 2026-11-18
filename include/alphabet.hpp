#pragma once

#include <string>
#include <vector>

const int M = 32;

extern const std::vector<std::string> LETTERS;

int letter_to_index(const std::string& letter);

std::string index_to_letter(int index);