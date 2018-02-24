#include "one_plus_lambda_tuning_fast.h"

one_plus_lambda_tuning_fast::one_plus_lambda_tuning_fast(size_t new_lambda, size_t new_n) : lambda(new_lambda), n(new_n), p(NUMERATOR_P / n),
                                                                                  min_p((double)2 / new_n), max_p(0.25),
                                                                                  generator(unsigned(time(0))) {};

void one_plus_lambda_tuning_fast::change_p(operation op) {
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

vector<size_t> one_plus_lambda_tuning_fast::generate_dif(const string& s, double prob) {
    vector<size_t> dif;
    size_t ind = next_inv_ind(0, prob);
    while (ind < n) {
        dif.push_back(ind);
        ind = next_inv_ind(ind + 1, prob);
    }
    return dif;
}

size_t one_plus_lambda_tuning_fast::init_func(const string& s) {
    size_t result = 0;
    for (size_t i = 0; i < n; ++i) {
        if (s[i] == '1') {
            ++result;
        }
    }
    return result;
}

size_t one_plus_lambda_tuning_fast::func(const representative& parent, const vector<size_t>& dif) {
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

size_t one_plus_lambda_tuning_fast::generate_solution(const string& init_s) {
    assert(init_s.size() == n);
    representative cur(init_s, init_func(init_s));
    size_t calculatings = 1;
    while (cur.f < n) {
        vector<size_t> best_dif;
        size_t best_f = 0;
        operation best_op = UNDEF;
        for (size_t i = 0; i < lambda; ++i) {
            vector<size_t> dif = move(generate_dif(cur.s, i < (lambda >> 1) ? p * 2 : p / 2));
            size_t f = func(cur, dif);
            if (f >= best_f) {
                best_f = f;
                best_dif = move(dif);
                best_op = i < (lambda >> 1) ? MUL : DIV;
            }
        }
        if (best_f >= cur.f) {
            cur.change(best_dif, best_f);
        }
        change_p(best_op);
        calculatings += lambda;
    }
    return calculatings;
}