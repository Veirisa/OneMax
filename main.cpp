#include <fstream>
#include <iomanip>
#include "one_plus_lambda.h"
#include "one_plus_lambda_fast.h"
#include "one_plus_lambda_tuning.h"
#include "one_plus_lambda_tuning_fast.h"
#include "one_plus_lambda_learning.h"


const size_t TEST_SIZE = 100;
mt19937 generator(time(0));

string random_string(mt19937 generator, size_t n) {
    char a[n];
    for (size_t i = 0; i < n; ++i) {
        if (generator() < (generator.max() >> 1)) {
            a[i] = '0';
        } else {
            a[i] = '1';
        }
    }
    return string(a, n);
}


size_t calc[TEST_SIZE];

template <typename OPL>
void testing(ofstream& fout, size_t lambda, size_t n) {
    cout << "lambda: " << lambda << "  n: " << n << "\n";
    OPL gen(lambda, n);
    size_t calculatings = 0, deviation = 0;
    for (size_t test = 0; test < TEST_SIZE; ++test) {
        calc[test] = gen.generate_solution(random_string(generator, n));
        calculatings += calc[test];
    }
    calculatings /= TEST_SIZE;
    for (size_t i = 0; i < TEST_SIZE; ++i) {
        deviation += (calc[i] - calculatings) * (calc[i] - calculatings);
    }
    deviation = (size_t)sqrt(deviation / TEST_SIZE);
    fout << "lambda: " << lambda << "  n: " << n << "  calculatings: " << calculatings << "  deviation: " << deviation << "\n";
}

template <typename OPL>
void full_testing(const string& algorithm_name, bool withHard) {
    cout <<  "\n" << algorithm_name << "\n\n";
    ofstream fout(algorithm_name + ".txt");
    fout << "testing " << algorithm_name << ":\n\n";
    for (size_t lambda = 1; lambda <= 10; ++lambda) {
        for (size_t n = 100; n <= 1000; n += 100) {
            testing<OPL>(fout, lambda, n);
        }
        fout << "\n";
    }
    if (withHard) {
        for (size_t lambda = 50; lambda <= 3200; lambda *= 2) {
            for (size_t n = 10000; n <= 100000; n += 10000) {
                testing<OPL>(fout, lambda, n);
            }
            fout << "\n";
        }
    }
}


void testing_detail_Q_learning_states() {
    cout <<  "\n" << "detail Q-learning states" << "\n\n";
    vector<size_t> visits, buf_visits;
    for (size_t lambda = 100; lambda <= 1600; lambda *= 4) {
        for (size_t n = 10000; n <= 100000; n += 10000) {
            cout << "lambda: " << lambda << "  n: " << n << "\n";
            ofstream fout("Q_learning_states/lambda_is_" + to_string(lambda) + "/n_is_" + to_string(n) + ".txt");
            fout << "Q-learning (lambda = " << to_string(lambda) << ", n = " << to_string(n) << ")\n\n";
            fout << "state - visits:"<< "\n";
            one_plus_lambda_learning gen(lambda, n);
            visits.resize(lambda + 1, 0);
            for (size_t test = 0; test < TEST_SIZE; ++test) {
                buf_visits = gen.generate_visits(random_string(generator, n));
                for (size_t st = 0; st <= lambda; ++st) {
                    visits[st] += buf_visits[st];
                }
            }
            for (size_t st = 0; st <= lambda; ++st) {
                visits[st] = (visits[st] + TEST_SIZE / 2) / TEST_SIZE;
                fout << st << "\t" << visits[st] << "\n";
            }
            visits.clear();
        }
        cout << "\n";
    }
}

void testing_Q_learning_states() {
    cout <<  "\n" << "Q-learning states" << "\n\n";
    ofstream fout("Q_learning_states/3200.txt");
    fout <<  "\n" << "testing Q-learning states" << "\n\n";
    fout << "lambda - n - one_visited - one_of_all - one_of_visited - many_visited - many_of_all - many_of_visited\n";
    vector<size_t> buf_visits;
    for (size_t lambda = 50; lambda <= 3200; lambda *= 2) {
        for (size_t n = 10000; n <= 100000; n += 10000) {
            cout << lambda << "\t" << n << "\t";
            one_plus_lambda_learning gen(lambda, n);
            size_t state_with_one_visit = 0;
            size_t state_with_many_visits = 0;
            double one_of_all = 0, one_of_visited = 0;
            double many_of_all = 0, many_of_visited = 0;
            for (size_t test = 0; test < TEST_SIZE; ++test) {
                buf_visits = gen.generate_visits(random_string(generator, n));
                size_t cur_state_with_one_visit = 0, cur_state_with_many_visits = 0;
                size_t cur_visited = 0;
                for (size_t st = 0; st <= lambda; ++st) {
                    if (buf_visits[st] > 0) {
                        if (buf_visits[st] == 1) {
                            ++cur_state_with_one_visit;
                        } else {
                            ++cur_state_with_many_visits;
                        }
                        ++cur_visited;
                    }
                }
                state_with_one_visit += cur_state_with_one_visit;
                one_of_all += (double)cur_state_with_one_visit / lambda;
                one_of_visited += (double)cur_state_with_one_visit / cur_visited;
                state_with_many_visits += cur_state_with_many_visits;
                many_of_all += (double)cur_state_with_many_visits / lambda;
                many_of_visited += (double)cur_state_with_many_visits / cur_visited;
            }
            state_with_one_visit = (state_with_one_visit + TEST_SIZE / 2) / TEST_SIZE;
            one_of_all /= TEST_SIZE;
            one_of_visited /= TEST_SIZE;
            state_with_many_visits = (state_with_many_visits + TEST_SIZE / 2) / TEST_SIZE;
            many_of_all /= TEST_SIZE;
            many_of_visited /= TEST_SIZE;
            cout << state_with_one_visit << "\t"
                 << fixed << setprecision(3) << one_of_all << "\t"
                 << fixed << setprecision(3) << one_of_visited << "\t"
                 << state_with_many_visits << "\t"
                 << fixed << setprecision(3) << many_of_all << "\t"
                 << fixed << setprecision(3) << many_of_visited << "\n";
            fout << lambda << "\t" << n << "\t"
                 << state_with_one_visit << "\t"
                 << fixed << setprecision(3) << one_of_all << "\t"
                 << fixed << setprecision(3) << one_of_visited << "\t"
                 << state_with_many_visits << "\t"
                 << fixed << setprecision(3) << many_of_all << "\t"
                 << fixed << setprecision(3) << many_of_visited << "\n";
        }
        cout << "\n";
        fout << "\n";
    }
}


int main() {
    /*full_testing<one_plus_lambda>("one_plus_lambda", false);
    full_testing<one_plus_lambda_fast>("one_plus_lambda_fast", true);
    full_testing<one_plus_lambda_tuning>("one_plus_lambda_tuning", false);
    full_testing<one_plus_lambda_tuning_fast>("one_plus_lambda_tuning_fast", true);
    full_testing<one_plus_lambda_learning>("one_plus_lambda_learning", true);*/
    //testing_detail_Q_learning_states();
    //testing_Q_learning_states();
    return 0;
}