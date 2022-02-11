#include "gauss-jacobi.hpp"


std::vector<double> Gauss_Jacobi(std::vector<std::vector<double>> A,std::vector<double> id, int n, double epsilon, std::vector<double> &erro, int & iteracoes){

	std::vector<double> x0_aux;
	std::vector<double> x0;
	std::vector<double> x1;
	double valor=0;
  
	std::vector<double> x0_helper;
	for(int i =0;i<n;i++){
		x0_helper = A.at(i);
		x0.push_back(id.at(i)/x0_helper.at(i));
		x1.push_back(0);
		x0_aux.push_back(id.at(i)/x0_helper.at(i));
	}

	while(diff(x0_aux,x1)>=epsilon){
		for (int i = 0; i<n; i++){
			std::vector<double> aux = A.at(i);	
			valor = 0;
			for (int j=0; j<n; j++){
				if(i!=j){
					valor = valor + (aux.at(j)*x0.at(j));
				}
			}
			x1.at(i) = (id.at(i) - valor)/aux.at(i);
		}
		
		for(int k = 0;k<n;k++){
			x0_aux.at(k) = x0.at(k);
			x0.at(k) = x1.at(k);
		}

    iteracoes++;
	}
	
  erro.push_back(diff(x0_aux,x1));

	return x1;
}