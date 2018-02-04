#include "onepluslambda.h"

onepluslambda::onepluslambda(size_t new_lambda, size_t new_n) : lambda(new_lambda), n(new_n), p((double)1 / new_n),
                                                                generator(unsigned(time(0))) {};

bool onepluslambda::choice() {
    return (double)generator() / generator.max() < p;
}

string onepluslambda::change_s(const string& s) {
    string child(s);
    for (size_t i = 0; i < n; ++i) {
        bool c = choice();
        if ((s[i] == '0' && !c) || (s[i] == '1' && c)) {
            child[i] = '0';
        } else {
            child[i] = '1';
        }
    }
    return child;
}

size_t onepluslambda::func(const string& s) {
    size_t result = 0;
    for (size_t i = 0; i < n; ++i) {
        if (s[i] == '1') {
            ++result;
        }
    }
    return result;
}

size_t onepluslambda::generate_solution(const string& init_s) {
    representative cur(init_s, func(init_s));
    size_t calculatings = 1;
    while (cur.f < n) {
        representative best("" , 0);
        for (size_t i = 0; i < lambda; ++i) {
            string s = change_s(cur.s);
            size_t f  = func(s);
            if (f >= best.f) {
                best = representative(s, f);
            }
        }
        if (best.f >= cur.f) {
            cur = best;
        }
        calculatings += lambda;
    }
    return calculatings;
}