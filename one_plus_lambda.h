#ifndef ONE_PLUS_LAMBDA_H
#define ONE_PLUS_LAMBDA_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <random>
#include <cassert>
using namespace std;

struct one_plus_lambda {

    explicit one_plus_lambda(size_t new_lambda, size_t new_n);
    size_t generate_solution(const string& init_s);

private:

    struct representative {
        string s;
        size_t f;

        representative(const string& new_s, size_t new_f) : s(new_s), f(new_f) {};
        representative& operator=(const representative& other) = default;
    };

    size_t lambda, n;
    double p;
    mt19937 generator;

    inline bool choice() {
        return (double)generator() / generator.max() < p;
    }

    size_t func(const string& s);
    string generate_child(const string& s);
};

#endif //ONE_PLUS_LAMBDA_H
