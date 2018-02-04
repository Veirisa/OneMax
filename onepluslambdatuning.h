#ifndef ONEPLUSLAMBDATUNING_H
#define ONEPLUSLAMBDATUNING_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

struct onepluslambdatuning {

    explicit onepluslambdatuning(size_t new_lambda, size_t n);
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

    bool choice(double prob);
    size_t func(const string& s);
    void change_p(operation op);
    string change_s(const string& s, double prob);
};


#endif //ONEPLUSLAMBDATUNING_H
