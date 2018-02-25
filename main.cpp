#include <fstream>
#include "one_plus_lambda.h"
#include "one_plus_lambda_fast.h"
#include "one_plus_lambda_tuning.h"
#include "one_plus_lambda_tuning_fast.h"

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

mt19937 generator(time(0));
size_t calc[100];

template <typename OPL>
void testing(const string& algorithm_name) {
    cout <<  "\n" << algorithm_name << "\n\n";
    ofstream fout(algorithm_name + ".txt");
    fout << "testing " << algorithm_name << ":\n\n";

    for (size_t lambda = 1; lambda <= 10; ++lambda) {
        for (size_t n = 100; n <= 1000; n += 100) {
            OPL gen(lambda, n);
            size_t calculatings = 0, deviation = 0;
            for (size_t test = 0; test < 100; ++test) {
                calc[test] = gen.generate_solution(random_string(generator, n));
                calculatings += calc[test];
            }
            calculatings /= 100;
            for (size_t i = 0; i < 100; ++i) {
                deviation += (calc[i] - calculatings) * (calc[i] - calculatings);
            }
            deviation = (size_t)sqrt(deviation / n);
            cout << "lambda: " << lambda << "  n: " << n << "\n";
            fout << "lambda: " << lambda << "  n: " << n << "  calculatings: " << calculatings << "  deviation: " << deviation << "\n";
        }
        fout << "\n";
    }
}

size_t BIG_LAMBDA = 200;

template <typename OPL>
void hard_testing(const string& algorithm_name) {
    cout <<  "\n" << algorithm_name + " (hard)" << "\n\n";
    ofstream fout(algorithm_name + "_(big).txt");
    fout << "hard testing " << algorithm_name << ":\n\n";
    for (size_t n = 10000; n <= 100000; n += 10000) {
        OPL gen(BIG_LAMBDA, n);
        size_t calculatings = 0, deviation = 0;
        for (size_t test = 0; test < 100; ++test) {
            calc[test] = gen.generate_solution(random_string(generator, n));
            calculatings += calc[test];
        }
        calculatings /= 100;
        for (size_t i = 0; i < 100; ++i) {
            deviation += (calc[i] - calculatings) * (calc[i] - calculatings);
        }
        deviation = (size_t)sqrt(deviation / n);
        cout << "lambda: " << BIG_LAMBDA << "  n: " << n << "\n";
        fout << "lambda: " << BIG_LAMBDA << "  n: " << n << "  calculatings: " << calculatings << "  deviation: " << deviation << "\n";
    }

}

int main() {
    //testing<one_plus_lambda>("one_plus_lambda");
    //testing<one_plus_lambda_fast>("one_plus_lambda_fast");
    hard_testing<one_plus_lambda_fast>("one_plus_lambda_fast");
    //testing<one_plus_lambda_tuning>("one_plus_lambda_tuning");
    //testing<one_plus_lambda_tuning_fast>("one_plus_lambda_tuning_fast");
    hard_testing<one_plus_lambda_tuning_fast>("one_plus_lambda_tuning_fast");
    return 0;
}