cmake_minimum_required(VERSION 3.9)
project(OneMax)

set(CMAKE_CXX_STANDARD 14)

add_executable(OneMax main.cpp one_plus_lambda.cpp one_plus_lambda.h one_plus_lambda_tuning.cpp one_plus_lambda_tuning.h one_plus_lambda_fast.cpp one_plus_lambda_fast.h one_plus_lambda_tuning_fast.cpp one_plus_lambda_tuning_fast.h)