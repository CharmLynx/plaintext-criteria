#pragma once

#include <string>
#include <vector>

std::string read_file(const std::string& path);

int utf8_char_length(unsigned char first_byte);

std::string normalize_char(const std::string& ch);

std::vector<int> clean_text(const std::string& text);