#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

//el problma es como el ejercicio anterior pero por tiempo no lo podre hacer resmido



// parámetros del algoritmo genético
int tam_genes = 100; // número de genes
int tam_pop = 20; // número de individuos en la población
int tam_torneio = 20; // tamaño del torneo
int geracoes = 3252; // numero de generaciones
double prob_mut = 0.2; // probabilidad de mutación
double prob_cruz = 0.7; // probabilidad de cruce

// población
vector<vector<int> > populacao;

void inicializaPopulacao()
{
	for(int i = 0; i < tam_pop; i++)
	{
		vector<int> individuo;

		for(int j = 0; j < tam_genes; j++)
		{
			int num = rand() % 2; // elige un número en el rango [0,1]
			individuo.push_back(num);// insertar en el vector del individuo
		}

		populacao.push_back(individuo); // insertar en el vector de población
	}
}

void mostrarPopulacao()
{
	for(int i = 0; i < tam_pop; i++)
	{
		for(int j = 0; j < tam_genes; j++)
			cout << populacao[i][j] << " ";
		cout << endl;
	}
}

// devuelve la puntuación del individuo
int obterPontuacao(vector<int> individuo)
{
	// la puntuación es la suma de los valores de los genes
	int soma = 0;

	for(int i = 0; i < tam_genes; i++)
		soma += individuo[i];
	return soma;
}

// realizar la mutación
void mutacao(vector<int>& individuo)
{
// elige un gen al azar en el rango [0, tam_genes - 1]
	int gene = rand() % tam_genes;

// modificar el valor del gen elegido
	if(individuo[gene] == 0)
		individuo[gene] = 1;
	else
		individuo[gene] = 0;
}
// realizar el cruce
void cruzamento(int indice_pai1, int indice_pai2, vector<int>& filho)
{
// elige un punto al azar en el rango [0, tam_genes - 1]
	int ponto = rand() % tam_genes;

	for(int i = 0; i <= ponto; i++)
		filho.push_back(populacao[indice_pai1][i]);
	for(int i = ponto + 1; i < tam_genes; i++)
		filho.push_back(populacao[indice_pai2][i]);
}

// devuelve el índice del mejor individuo de la población
int obterMelhor()
{
	int indice_melhor = 0;
	int score_melhor = obterPontuacao(populacao[0]);

	for(int i = 1; i < tam_pop; i++)
	{
		int score = obterPontuacao(populacao[i]);
		if(score > score_melhor)
		{
			indice_melhor = i;
			score_melhor = score;
		}
	}

	return indice_melhor;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	inicializaPopulacao();
//mostrarPoblación();

	for(int i = 0; i < geracoes; i++)
	{
		for(int j = 0; j < tam_torneio; j++)
		{

	// calcular la probabilidad de cruce
			double prob = ((double) rand() / ((double)RAND_MAX + 1));

			if(prob < prob_cruz)
			{
	// elige dos padres
				int indice_pai1 = rand() % tam_pop;
				int indice_pai2;

			// asegurar que los índices principales no sean iguales
				do
				{
					indice_pai2 = rand() % tam_pop;
				}
				while(indice_pai1 == indice_pai2);

				vector<int> filho;

			// aplicar cruce de 1 punto
				cruzamento(indice_pai1, indice_pai2, filho);

		// calcular la probabilidad de mutación
				prob = ((double) rand() / ((double)RAND_MAX + 1));

				if(prob < prob_mut)
					mutacao(filho);

				int score_pai = obterPontuacao(populacao[indice_pai1]);
				int score_filho = obterPontuacao(filho);

			/*
si el puntaje del niño es mejor que el
que el padre 1, luego reemplace el padre 1 con el hijo
*/
				if(score_filho > score_pai)
				{
			// copia los genes del hijo al padre
					for(int k = 0; k < tam_genes; k++)
						populacao[indice_pai1][k] = filho[k];
				}
			}
		}

		cout << "Generación " << i + 1 << endl;
		cout << "Mejor: ";

		int indice_melhor = obterMelhor();
		int score_melhor = obterPontuacao(populacao[indice_melhor]);

		for(int j = 0; j < tam_genes; j++)
			cout << populacao[indice_melhor][j] << " ";

		cout << "\nPuntuación: " << score_melhor << "\n\n";

	// comprobar si se ha encontrado la solución óptima global
		if(score_melhor == tam_genes)
			break;
	}

	return 0;
}
