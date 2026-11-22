#include "evaluator.hpp"

using namespace std;

double h1_rate(const vector<vector<int>>& texts,
               const function<bool(const vector<int>&)>& criterion) {
    int count = 0;
    for (const vector<int>& text : texts) {
        if (criterion(text)) {
            count++;
        }
    }
    return (double)count / texts.size();
}