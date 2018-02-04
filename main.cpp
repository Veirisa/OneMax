#include <fstream>
#include "onepluslambda.h"
#include "onepluslambdatuning.h"

string random_string(mt19937 generator, size_t n) {
    char a[n];
    for (size_t i = 0; i < n; ++i) {
        if (generator() < (generator.max() >> 1)) {
            a[i] = '0';
        } else {
            a[i] = '0';
        }
    }
    return string(a, n);
}

int main() {
    mt19937 generator(time(0));
    size_t calc[100];

    /*ofstream f_opl("one_plus_lambda.out");
    f_opl << "testing one_plus_lambda:\n\n";

    for (size_t lambda = 1; lambda <= 10; ++lambda) {
        for (size_t n = 100; n <= 1000; n += 100) {
            onepluslambda gen(lambda, n);
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
            f_opl << "lambda: " << lambda << "  n: " << n << "  calculatings: " << calculatings << "  deviation: " << deviation << "\n";
        }
        f_opl << "\n";
    }*/

    ofstream f_oplt("one_plus_lambda_tuning.out");
    f_oplt << "testing one_plus_lambda_tuning:\n\n";

    for (size_t lambda = 1; lambda <= 10; ++lambda) {
        for (size_t n = 100; n <= 1000; n += 100) {
            onepluslambdatuning gen_tun(lambda, n);
            size_t calculatings = 0, deviation = 0;
            for (size_t test = 0; test < 100; ++test) {
                calc[test] = gen_tun.generate_solution(random_string(generator, n));
                calculatings += calc[test];
            }
            calculatings /= 100;
            for (size_t i = 0; i < 100; ++i) {
                deviation += (calc[i] - calculatings) * (calc[i] - calculatings);
            }
            deviation = (size_t)sqrt(deviation / n);
            cout << "lambda: " << lambda << "  n: " << n << "\n";
            f_oplt << "lambda: " << lambda << "  n: " << n << "  calculatings: " << calculatings << "  deviation: " << deviation << "\n";
        }
        f_oplt << "\n";
    }


    return 0;
}