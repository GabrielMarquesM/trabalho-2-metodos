#include "func-auxiliares.hpp"
#include "gauss-jacobi.hpp"
#include "gauss-seidel.hpp"

int main(){
  std::cout << std::fixed << std::setprecision(5);

  std::vector<std::vector<double>> A;
  std::tuple<std::vector<std::vector<double>>,std::vector<double>> tupla_A_jacobi, tupla_A_seidel; 
	std::vector<std::vector<double>> inversa_A_jacobi, inversa_A_seidel;
	std::vector<double> b;
	std::vector<double> d_jacobi, d_seidel;
  std::vector<double> erro_jacobi;
  std::vector<double> erro_seidel;
  int iter_jacobi=0;
  int iter_seidel=0;
	int n=0;
	double epsilon;
  bool dd;
  bool sf;

	std::cout<<"Insira a quantidade de deslocamentos: ";
	std::cin>> n;
 
	std::cout<<"Insira os valores de A"<<std::endl;
	for(int i=0;i<n;i++){
		std::vector<double> aux;
		double valor;
		for(int j=0;j<n;j++){
			valor = 0;
			std::cout<<"Valor de "<<"A["<<i<<"]"<<"["<<j<<"]: ";
			std::cin>> valor;
			aux.push_back(valor);
		}
		A.push_back(aux);
	}

	std::cout<<"Insira os valores para b"<<std::endl;
	double valor;
	for(int i =0;i<n;i++){
		std::cout<<"Valor de "<<"b["<<i<<"]:";
		std::cin>>valor;
		b.push_back(valor);
	}

	std::cout<<"Insira uma precisao"<<std::endl;
	std::cin>>epsilon;

	std::cout<<std::endl;

  dd = diagonal_Dominante(A,n);
  sf = sassenfeld(A,n);
  std::string avisoDiagonal = !(dd)? "Falha no criterio diagonal dominante": "Converge para ambos os métodos";
  std::string avisoSassenfeld = !(sf)? "Falha no criterio Sassenfeld": "Converge para Gauss Seidel";
  std::cout << avisoDiagonal << std::endl <<avisoSassenfeld<< std::endl; 
  
  tupla_A_jacobi = calcula_inversa(A, n, epsilon, &Gauss_Jacobi,iter_jacobi);
  
  std::cout<<std::endl;
  
  inversa_A_jacobi = std::get<0>(tupla_A_jacobi);
  erro_jacobi = std::get<1>(tupla_A_jacobi);
  
  d_jacobi = calcula_deslocamento(inversa_A_jacobi,b);
  std::cout<<"Metodo: Gauss-Jacobi"<< std::endl;
  quadro_comparativo(A,inversa_A_jacobi, d_jacobi, erro_jacobi,iter_jacobi);

  tupla_A_seidel = calcula_inversa(A, n, epsilon, &Gauss_Seidel,iter_seidel);

  inversa_A_seidel = std::get<0>(tupla_A_seidel);
  erro_seidel = std::get<1>(tupla_A_seidel);

  std::cout<<std::endl;
  d_seidel = calcula_deslocamento(inversa_A_seidel,b);
  std::cout<<"Metodo: Gauss-Seidel"<< std::endl;
  quadro_comparativo(A,inversa_A_seidel, d_seidel, erro_seidel,iter_seidel);
}