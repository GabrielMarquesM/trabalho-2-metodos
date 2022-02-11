#include "func-auxiliares.hpp"

std::vector<double> Gauss_Seidel(std::vector<std::vector<double>> A,std::vector<double> id, int n, double epsilon, std::vector<double> &erro, int & iteracoes);

bool sassenfeld(std::vector<std::vector<double>> A, int n);