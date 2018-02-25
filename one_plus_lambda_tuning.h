#ifndef ONE_PLUS_LAMBDA_TUNING_H
#define ONE_PLUS_LAMBDA_TUNING_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <random>
#include <algorithm>
#include <cassert>
using namespace std;

struct one_plus_lambda_tuning {

    explicit one_plus_lambda_tuning(size_t new_lambda, size_t n);
    size_t generate_solution(const string& init_s);

private:

    enum operation {
        UNDEF, MUL, DIV
    };

    struct representative {
        string s;
        size_t f;

        representative(const string& new_s, size_t new_f) : s(new_s), f(new_f) {};
        representative& operator=(const representative& other) = default;
    };

    const double NUMERATOR_P = 2;
    size_t lambda, n;
    double p, min_p, max_p;
    mt19937 generator;

    inline bool choice(double prob) {
        return (double)generator() / generator.max() < prob;
    }

    size_t func(const string& s);
    string generate_child(const string& s, double prob);
    void change_p(operation op);
};

#endif //ONE_PLUS_LAMBDA_TUNING_H
