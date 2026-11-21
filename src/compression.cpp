#include "compression.hpp"

#include <zlib.h>

using namespace std;

int compressed_size(const vector<int>& text) {
    vector<unsigned char> input(text.size());
    for (size_t i = 0; i < text.size(); i++) {
        input[i] = text[i];
    }

    uLongf output_size = compressBound(input.size());
    vector<unsigned char> output(output_size);

    compress2(output.data(), &output_size, input.data(), input.size(), 9);

    return output_size;
}