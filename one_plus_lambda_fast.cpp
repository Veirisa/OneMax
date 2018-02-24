#include "one_plus_lambda_fast.h"

one_plus_lambda_fast::one_plus_lambda_fast(size_t new_lambda, size_t new_n) : lambda(new_lambda), n(new_n), p((double)1 / new_n),
                                                                    generator(unsigned(time(0))) {};

size_t one_plus_lambda_fast::init_func(const string& s) {
    size_t result = 0;
    for (size_t i = 0; i < n; ++i) {
        if (s[i] == '1') {
            ++result;
        }
    }
    return result;
}

size_t one_plus_lambda_fast::func(const representative& parent, const vector<size_t>& dif) {
    size_t result = parent.f;
    for (size_t i = 0; i < dif.size(); ++i) {
        if (parent.s[dif[i]] == '1') {
            --result;
        } else {
            ++result;
        }
    }
    return result;
}

vector<size_t> one_plus_lambda_fast::generate_dif(const string& s) {
    vector<size_t> dif;
    size_t ind = next_inv_ind(0);
    while (ind < n) {
        dif.push_back(ind);
        ind = next_inv_ind(ind + 1);
    }
    return dif;
}

size_t one_plus_lambda_fast::generate_solution(const string& init_s) {
    assert(init_s.size() == n);
    representative cur(init_s, init_func(init_s));
    size_t calculatings = 1;
    while (cur.f < n) {
        vector<size_t> best_dif;
        size_t best_f = 0;
        for (size_t i = 0; i < lambda; ++i) {
            vector<size_t> dif = move(generate_dif(cur.s));
            size_t f = func(cur, dif);
            if (f >= best_f) {
                best_f = f;
                best_dif = move(dif);
            }
        }
        if (best_f >= cur.f) {
            cur.change(best_dif, best_f);
        }
        calculatings += lambda;
    }
    return calculatings;
}