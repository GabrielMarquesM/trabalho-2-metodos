#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

double diff(std::vector<double> x0, std::vector<double> x1);

std::vector<double> constroi_identidade(int i,int n);

std::vector<std::vector<double>> inicia_inv(int n);

void mostrar_Matriz(std::vector<std::vector<double>> m);

bool linha_Dominante(std::vector<double> A, int n,int i);

bool coluna_Dominante(std::vector<double> A, int n, int i);

bool diagonal_Dominante(std::vector<std::vector<double>> A, int n);

std::tuple<std::vector<std::vector<double>>,std::vector<double>> calcula_inversa(std::vector<std::vector<double>> m,int n, double epsilon, std::vector<double> (*metodo)(std::vector<std::vector<double>>, std::vector<double>,int, double, std::vector<double>&, int &), int & iteracoes);

std::vector<double> calcula_deslocamento(std::vector<std::vector<double>> A_inv, std::vector<double> B);

void quadro_comparativo(std::vector<std::vector<double>> A,std::vector<std::vector<double>> inversa_A, std::vector<double> d, std::vector<double> erro, int iter);