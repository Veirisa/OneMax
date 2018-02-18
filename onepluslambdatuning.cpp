#include "onepluslambdatuning.h"

onepluslambdatuning::onepluslambdatuning(size_t new_lambda, size_t new_n) : lambda(new_lambda), n(new_n), p(NUMERATOR_P / n),
                                                                            min_p((double)2 / new_n), max_p(0.25),
                                                                            generator(unsigned(time(0))) {};

bool onepluslambdatuning::choice(double prob) {
    return (double)generator() / generator.max() < prob;
}

void onepluslambdatuning::change_p(operation op) {
    if (choice(0.5)) {
        if (op == MUL) {
            p = min(p * 2, max_p);
        } else {
            p = max(p / 2, min_p);
        }
    } else {
        if (choice(0.5)) {
            p = min(p * 2, max_p);
        } else {
            p = max(p / 2, min_p);
        }
    }
}

string onepluslambdatuning::change_s(const string& s, double prob) {
    string child(s);
    for (size_t i = 0; i < n; ++i) {
        bool c = choice(prob);
        if ((s[i] == '0' && !c) || (s[i] == '1' && c)) {
            child[i] = '0';
        } else {
            child[i] = '1';
        }
    }
    return child;
}

size_t onepluslambdatuning::func(const string& s) {
    size_t result = 0;
    for (size_t i = 0; i < n; ++i) {
        if (s[i] == '1') {
            ++result;
        }
    }
    return result;
}

size_t onepluslambdatuning::generate_solution(const string& init_s) {
    representative cur(init_s, func(init_s));
    size_t calculatings = 1;
    while (cur.f < n) {
        representative best("", 0);
        operation best_op = UNDEF;
        for (size_t i = 0; i < lambda; ++i) {
            string s = change_s(cur.s, i < (lambda >> 1) ? p * 2 : p / 2);
            size_t f  = func(s);
            if (f >= best.f) {
                best = representative(s, f);
                best_op = i < (lambda >> 1) ? MUL : DIV;
            }
        }
        if (best.f >= cur.f) {
            cur = best;
        }
        change_p(best_op);
        calculatings += lambda;
    }
    return calculatings;
}