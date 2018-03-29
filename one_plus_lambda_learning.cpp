#include "one_plus_lambda_learning.h"

one_plus_lambda_learning::one_plus_lambda_learning(size_t new_lambda, size_t new_n) :
        lambda(new_lambda), n(new_n),
        p(NUMERATOR_P / n),
        min_p((double)1 / new_n),
        max_p(0.5),
        generator(unsigned(time(0))),
        alpha(DEFAULT_ALPHA),
        gamma(DEFAULT_GAMMA) {
    init_q();
};

void one_plus_lambda_learning::set_constants(double new_alpha, double new_gamma) {
    alpha = new_alpha;
    gamma = new_gamma;
}

void one_plus_lambda_learning::init_q() {
    Q.resize(lambda + 1);
    for (size_t i = 0; i <= lambda; ++i) {
        Q[i][0] = Q[i][1] = 0;
    }
}

size_t one_plus_lambda_learning::init_func(const string& s) {
    size_t result = 0;
    for (size_t i = 0; i < n; ++i) {
        if (s[i] == '1') {
            ++result;
        }
    }
    return result;
}

size_t one_plus_lambda_learning::func(const representative& parent, const vector<size_t>& dif) {
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

vector<size_t> one_plus_lambda_learning::generate_dif(const string& s) {
    vector<size_t> dif;
    size_t ind = next_inv_ind(0);
    while (ind < n) {
        dif.push_back(ind);
        ind = next_inv_ind(ind + 1);
    }
    return dif;
}

one_plus_lambda_learning::operation one_plus_lambda_learning::change_p(size_t suc, operation op, double r, size_t new_suc) {
    if (op != UNDEF) {
        Q[suc][op] = Q[suc][op] + alpha * (r + gamma * max(Q[new_suc][DIV], Q[new_suc][MUL]) - Q[suc][op]);
    }
    if (Q[new_suc][MUL] > Q[new_suc][DIV] || (Q[new_suc][MUL] == Q[new_suc][DIV] && choice(0.5))) {
        p = min(p * 2, max_p);
        return MUL;
    } else {
        p = max(p / 2, min_p);
        return DIV;
    }
}

size_t one_plus_lambda_learning::generate_solution(const string& init_s) {
    assert(init_s.size() == n);
    representative cur(init_s, init_func(init_s));
    size_t calculatings = 1;
    size_t suc = 0;
    operation op = UNDEF;
    while (cur.f < n) {
        vector<size_t> best_dif;
        size_t best_f = 0;
        size_t new_suc = 0;
        for (size_t i = 0; i < lambda; ++i) {
            vector<size_t> dif = move(generate_dif(cur.s));
            size_t f = func(cur, dif);
            if (f >= best_f) {
                best_f = f;
                best_dif = move(dif);
            }
            if (f > cur.f) {
                ++new_suc;
            }
        }
        operation new_op = change_p(suc, op, (double)best_f - (double)cur.f, new_suc);
        if (best_f >= cur.f) {
            cur.change(best_dif, best_f);
        }
        calculatings += lambda;
        suc = new_suc;
        op = new_op;
    }
    return calculatings;
}