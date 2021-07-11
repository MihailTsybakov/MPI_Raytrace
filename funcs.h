#ifndef FUNCS
#define FUNCS

#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>

#include "mpi.h"

float scalar_prod(std::vector<float> v1, std::vector<float> v2);

std::vector<float> normalize(std::vector<float> v);

std::vector<float> new_len(std::vector<float> v, float L);

std::vector<float> vector_prod(std::vector<float> v1, std::vector<float> v2);

void check_mpi_errors(int error_code);

std::vector<float> operator-(std::vector<float> v1, std::vector<float> v2);
std::vector<float> operator+(std::vector<float> v1, std::vector<float> v2);
std::vector<float> operator*(std::vector<float> v, float M);

#endif//FUNCS
