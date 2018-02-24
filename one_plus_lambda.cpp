#include "one_plus_lambda.h"

one_plus_lambda::one_plus_lambda(size_t new_lambda, size_t new_n) : lambda(new_lambda), n(new_n), p((double)1 / new_n),
                                                                generator(unsigned(time(0))) {};

size_t one_plus_lambda::func(const string& s) {
    size_t result = 0;
    for (size_t i = 0; i < n; ++i) {
        if (s[i] == '1') {
            ++result;
        }
    }
    return result;
}

string one_plus_lambda::generate_child(const string& s) {
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

size_t one_plus_lambda::generate_solution(const string& init_s) {
    assert(init_s.size() == n);
    representative cur(init_s, func(init_s));
    size_t calculatings = 1;
    while (cur.f < n) {
        representative best("" , 0);
        for (size_t i = 0; i < lambda; ++i) {
            string s = generate_child(cur.s);
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