#pragma once

#include <string>
#include <vector>

#include "experiment.hpp"

void write_letter_table(const std::string& path,
                        const std::vector<double>& freq);

void write_bigram_table(const std::string& path,
                        const std::vector<double>& freq);

void write_error_tables(const std::string& dir,
                        const std::vector<ResultRow>& rows,
                        const std::vector<Distortion>& distortions);