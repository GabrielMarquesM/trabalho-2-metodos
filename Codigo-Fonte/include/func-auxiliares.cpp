#include "func-auxiliares.hpp"

double diff(std::vector<double> x0, std::vector<double> x1){
	double aux1=0;
	double aux2=0;

	for(int i=0;i<x0.size();i++){
		if(fabs(x1.at(i))>aux2){
			aux2 = fabs(x1.at(i));
		}
		
		if(aux1<fabs(fabs(x1.at(i)) - fabs(x0.at(i)))){
			aux1 = fabs(x1.at(i) - x0.at(i));
		}
	}
	return aux1/aux2;
}


std::vector<double> constroi_identidade(int i,int n){
	std::vector<double> id;
	for(int j =0;j<n;j++){
		if(j == i){
			id.push_back(1);
		}
		else{
			id.push_back(0);
		}
	}
	return id;
}



std::vector<std::vector<double>> inicia_inv(int n){
	std::vector<std::vector<double>> inv;
	for(int i=0;i<n;i++){
		std::vector<double> aux;
		for(int j=0;j<n;j++){
			aux.push_back(0);
		}
		inv.push_back(aux);
	}
	return inv;
}


void mostrar_Matriz(std::vector<std::vector<double>> m){
	for(std::vector<double> v : m){
		for(double i:v){
			std::cout<< i <<" ";
		}
		std::cout<<std::endl;
	}
}


bool linha_Dominante(std::vector<double> A, int n,int i){
	double sum = 0;
	double diagonal = 0;
	for(int k=0;k<n;k++){
		if(i==k){
			diagonal = fabs(A.at(k));
		}
		else{
			sum = sum + fabs(A.at(k));
		}
	}
	if(sum>=diagonal){
		return false;
	}
	return true;
}



bool coluna_Dominante(std::vector<double> A, int n, int i){
	double sum = 0;
	double diagonal = 0;
	for(int k=0;k<n;k++){
		if(i==k){
			diagonal = fabs(A.at(k));
		}
		else{
			sum = sum + fabs(A.at(k));
		}
	}
	if(sum>=diagonal){
		return false;
	}
	return true;
}


bool diagonal_Dominante(std::vector<std::vector<double>> A, int n){
	for(int i=0;i<n; i++){
		std::vector<double> aux = A.at(i);
		std::vector<double> aux2;
		
		for(int j=0;j<n; j++){
			std::vector<double> helper = A.at(j);
			aux2.push_back(helper.at(i));
		}
		bool ld = linha_Dominante(aux,n,i);
		bool cd = coluna_Dominante(aux2,n,i);
		if((ld == false) && (cd == false)){
		 	return false;
		}
	}
	return true;
}


std::tuple<std::vector<std::vector<double>>,std::vector<double>> calcula_inversa(std::vector<std::vector<double>> m,int n, double epsilon, std::vector<double> (*metodo)(std::vector<std::vector<double>>, std::vector<double>,int, double, std::vector<double>&,int &), int & iteracoes){

	std::vector<std::vector<double>> inv;
  std::vector<std::vector<double>> inv_matrix;
	std::vector<double> aux;

  std::vector<double> erro;


	for(int i=0;i<n;i++){
		aux = metodo(m,constroi_identidade(i,n),n,epsilon, erro, iteracoes);
		inv.push_back(aux);
	}

	inv_matrix.resize(n, std::vector<double>(n));

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			inv_matrix.at(j).at(i) = inv.at(i).at(j);
		}
	}

	return std::make_tuple(inv_matrix, erro);
}


std::vector<double> calcula_deslocamento(std::vector<std::vector<double>> A_inv, std::vector<double> B){

  
	std::vector<double> d;
	double valor = 0;
	
	for(int i=0;i<B.size();i++){
		std::vector<double> linha = A_inv.at(i);
		valor = 0;
		for(int j = 0; j < B.size();j++){
			valor = valor + ((linha.at(j))*(B.at(j)));
		}
		d.push_back(valor);
	}
	return d;
}



void quadro_comparativo(std::vector<std::vector<double>> A,std::vector<std::vector<double>> inversa_A, std::vector<double> d, std::vector<double> erro, int iter){

  std::cout<< "Matriz A (" << A.size() << "x" << A.size() << ")" << std::endl;

  mostrar_Matriz(A);
  
  std::cout<< std::endl << "Inversa de A (" << A.size() << "x" << A.size() << ")" << std::endl;

  mostrar_Matriz(inversa_A);

  std::cout << "Numero de iteracoes: " << iter << std::endl;

  std::cout<< std::endl << "Vetor de deslocamentos (d)" << std::endl;

  std::cout<< "[";
  for_each(d.begin(),d.end(),[](double e){std::cout<<e<<" ";});
  std::cout<<'\b';
  std::cout<< "]"<<std::endl;

  std::cout << std::endl;
  int cont = 0;
  for(double e : erro){
    std::cout << "Erro da coluna " << cont << " = " << e << std::endl;
    cont++;
  }

      
  for(int i = 0; i < d.size(); i++){

    if(fabs(d.at(i)) > 0.4){
      std::cout<<"Existe um deslocamento =" << d.at(i) <<  "> 0.4, existindo riscos de serios danos e um problema gigantesco"<<std::endl;
      break;
    }
  }
}
