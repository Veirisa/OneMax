#ifndef ONEPLUSLAMBDA_H
#define ONEPLUSLAMBDA_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <random>
using namespace std;

struct onepluslambda {

    explicit onepluslambda(size_t new_lambda, size_t n);
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

    bool choice();
    size_t func(const string& s);
    string change_s(const string& s);

};
#endif //ONEPLUSLAMBDA_H
