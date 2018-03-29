#ifndef ONE_PLUS_LAMBDA_TUNING_FAST_H
#define ONE_PLUS_LAMBDA_TUNING_FAST_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <random>
#include <algorithm>
#include <cassert>
using namespace std;

struct one_plus_lambda_tuning_fast {

    explicit one_plus_lambda_tuning_fast(size_t new_lambda, size_t new_n);
    size_t generate_solution(const string& init_s);

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

    const double NUMERATOR_P = 2;
    size_t lambda, n;
    double p, min_p, max_p;
    mt19937 generator;

    inline bool choice(double prob) {
        return (double)generator() / generator.max() < prob;
    }

    inline size_t next_inv_ind(size_t start_ind, double prob) {
        return start_ind + size_t(log((double)generator() / generator.max()) / log(1 - prob));
    }

    size_t init_func(const string& s);
    size_t func(const representative& parent, const vector<size_t>& dif);
    vector<size_t> generate_dif(const string& s, double prob);
    void change_p(operation op);
};

#endif //ONE_PLUS_LAMBDA_TUNING_FAST_H
