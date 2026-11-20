#pragma once

#include <string>
#include <vector>

void write_letter_table(const std::string& path,
                        const std::vector<double>& freq);

void write_bigram_table(const std::string& path,
                        const std::vector<double>& freq);