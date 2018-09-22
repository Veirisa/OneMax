#ifndef ONE_PLUS_LAMBDA_LEARNING_H
#define ONE_PLUS_LAMBDA_LEARNING_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <random>
#include <algorithm>
#include <cassert>
#include <array>
using namespace std;

struct one_plus_lambda_learning {

    explicit one_plus_lambda_learning(size_t new_lambda, size_t new_n);
    void set_constants(double new_alpha, double new_gamma);
    size_t generate_solution(const string& init_s);
    vector<size_t> generate_visits(const string& init_s);

private:

    enum operation {
        MUL, DIV, UNDEF
    };

    struct representative {
        string s;
        size_t f;

        representative(const string& new_s, size_t new_f) : s(new_s), f(new_f) {};

        void change(const vector<size_t>& dif, size_t new_f) {
            f = new_f;
            for (size_t i = 0; i < dif.size(); ++i) {
                if (s[dif[i]] == '1') {
                    s[dif[i]] = '0';
                } else {
                    s[dif[i]] = '1';
                }
            }
        }
    };

    const double NUMERATOR_P = 1;
    const double DEFAULT_ALPHA = 0.8;
    const double DEFAULT_GAMMA = 0.2;
    double alpha, gamma;
    size_t lambda, n;
    double p, min_p, max_p;
    mt19937 generator;
    vector<array<double, 2>> Q;
    vector<size_t> visits;

    inline bool choice(double prob) {
        return (double)generator() / generator.max() < prob;
    }

    inline size_t next_inv_ind(size_t start_ind) {
        return start_ind + size_t(log((double)generator() / generator.max()) / log(1 - p));
    }

    void init_q();
    size_t init_func(const string& s);
    size_t func(const representative& parent, const vector<size_t>& dif);
    vector<size_t> generate_dif(const string& s);
    operation change_p(size_t suc, operation op, double r, size_t new_suc);
};


#endif //ONE_PLUS_LAMBDA_LEARNING_H
