//
// Algoritmos e Estruturas de Dados --- 2025/2026
//
// Joaquim Madeira - Nov 2025
//
// GraphDominatingSets - Computing Vertex Dominating Sets for UNDIRECTED graphs
//

// Student Name : Henrique Tardelli
// Student Number : 125087
// Student Name : Gabriel Gúzman
// Student Number : 126180

/*** COMPLETE THE GraphIsDominatingSet FUNCTION ***/
/*** COMPLETE THE GraphMinDominatingSet FUNCTION ***/
/*** COMPLETE THE GraphMinWeightDominatingSet FUNCTION ***/

#include "GraphDominatingSets.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IndicesSet.h"
#include "instrumentation.h"

long long unsigned int iterations_counter = 0;				//Varíavel para testar a complexidade de GraphComputeMinDominatingSet()

//
// TO BE COMPLETED
//
// Check if the given set is a dominating set for the graph
// Return 1 if true, or 0 otherwise
//
// A dominating set is a set of graph vertices such that every other
// graph vertex not in the set is adjacent to a graph vertex in the set
//
int GraphIsDominatingSet(const Graph* g, IndicesSet* vertSet) {
	assert(g != NULL);
	assert(GraphIsDigraph(g) == 0);
	assert(IndicesSetIsEmpty(vertSet) == 0);
	
	IndicesSet* allVertices = GraphGetSetVertices(g);		//Conjunto de todos os vértices do grafo g
  
	int result = 1;							//result = 1, Dominante
									//result != 1, Não dominante
								
	int v = IndicesSetGetFirstElem(allVertices);			//Iterador para percorrermos os vértices do grafo
									//
	while(v != -1){
		if(IndicesSetContains(vertSet, v)){
			v = IndicesSetGetNextElem(allVertices);		//Verifica se v está no conjunto
			continue;
		}

		int HasNeighbor = 0;					//Varíavel que indica se é vizinho no conjunto
		IndicesSet* neighbors = GraphGetSetAdjacentsTo(g, v);	//Obtemos os vértices adjacentes a v

		int neighbor = IndicesSetGetFirstElem(neighbors);
		while(neighbor != -1){					//Iterar pelos vizinhos para ver se algum pertence ao vertSet
			if(IndicesSetContains(vertSet, neighbor)){
				HasNeighbor = 1;
				break;					//Encontramos um vizinho que domina v
			}
			neighbor = IndicesSetGetNextElem(neighbors);
		}

		IndicesSetDestroy(&neighbors);				//Libertar memória do conjunto dos vértices adjacentes
		
		if(!HasNeighbor){					//Se v não está no conjunto E nenhum vizinho está
			result = 0;
			break;
		}

		v = IndicesSetGetNextElem(allVertices);			//Passa para o próximo vértice do grafo

	}

	IndicesSetDestroy(&allVertices);				//Libertar memória do conjunto de todosos vértices
  

	return result;
}

//
// TO BE COMPLETED
//
// Compute a MIN VERTEX DOMINATING SET of the graph
// using an EXHAUSTIVE SEARCH approach
// Return the/a dominating set
//
//
// Compute a MIN VERTEX DOMINATING SET of the graph
// using an EXHAUSTIVE SEARCH approach
// Return the/a dominating set
//
IndicesSet* GraphComputeMinDominatingSet(const Graph* g) {
    assert(g != NULL);
    assert(GraphIsDigraph(g) == 0);
    
    unsigned int range = GraphGetVertexRange(g);             				
    IndicesSet* candidate = IndicesSetCreateEmpty(range);    				//Cria conjunto candidato vazio                 
    IndicesSet* bestSet = NULL;                              				//Guarda a melhor solução (menor)
    unsigned int minSize = range + 1;                        				//Tamanho mínimo encontrado (inic. alto)

    do {
	iterations_counter++;								//Incrementa varíavel de teste computacional
        if(bestSet != NULL && IndicesSetGetNumElems(candidate) >= minSize) continue;	//Se candidato atual >= melhor tamanho pula

        
        if(IndicesSetIsEmpty(candidate) && GraphGetNumVertices(g) > 0) continue;

        if(GraphIsDominatingSet(g, candidate)) {             				//Verifica se é dominante
            unsigned int currentSize = IndicesSetGetNumElems(candidate);
            
            if (bestSet == NULL || currentSize < minSize) {  				//Se for a primeira ou menor solução atualiza tamanho mínimo
                minSize = currentSize;                       				
                if (bestSet != NULL) IndicesSetDestroy(&bestSet); 			//Limpa solução anterior
                bestSet = IndicesSetCreateCopy(candidate);   				//Guarda cópia do candidato
            }
        }
    } while(IndicesSetNextSubset(candidate));                				//Gera próximo subconjunto (contador binário)

    IndicesSetDestroy(&candidate);                           				//Limpa candidato auxiliar
    
    if(bestSet == NULL) return IndicesSetCreateEmpty(range); 				//Retorna vazio se falhar
    
    return bestSet;
}

//
// TO BE COMPLETED
//
// Compute a MIN WEIGHT VERTEX DOMINATING SET of the graph
// using an EXHAUSTIVE SEARCH approach
// Return the dominating set
//
IndicesSet* GraphComputeMinWeightDominatingSet(const Graph* g) {
	assert(g != NULL);
	assert(GraphIsDigraph(g) == 0);

	unsigned int range = GraphGetVertexRange(g);

	double* weights = GraphComputeVertexWeights(g);							//Cálculo antecipado do peso dos vértice grafo e serve como verificação pra ver
													//Se o grafo têm pesos ou não.
	if(weights == NULL) { return IndicesSetCreateEmpty(range); }					//Se houver erro na alocação de pesos retornamos o vazio
	
	IndicesSet* candidate = IndicesSetCreateEmpty(range);
	IndicesSet* bestSet = NULL;

	double minTotalWeight = 0.0;									//Garantir que o primeiro conjunto válido encontrado seja aceite
	

	do{
		double currentTotalWeight = 0.0;							//Calcular o peso deste candidato

		if(!IndicesSetIsEmpty(candidate)){
			int v = IndicesSetGetFirstElem(candidate);
			while (v != -1) {
				currentTotalWeight += weights[v];
				v = IndicesSetGetNextElem(candidate);
			}
		}

		if (bestSet != NULL && currentTotalWeight >= minTotalWeight){ continue; }		//Se o peso atual já é maior ou igual ao melhor encontrado, ignoramos

		if (IndicesSetIsEmpty(candidate) && GraphGetNumVertices(g) > 0){ continue; }		//Conjunto vazio num grafo com vértices nunca dominantes
		
		if (GraphIsDominatingSet(g, candidate)){						//Verificar se é dominante
			minTotalWeight = currentTotalWeight;						//Caso o peso do conjunto atual for menor ele atualiza
			
			if(bestSet != NULL){ IndicesSetDestroy(&bestSet); }
			bestSet = IndicesSetCreateCopy(candidate);
		}
	}while(IndicesSetNextSubset(candidate));

	IndicesSetDestroy(&candidate);									//Libertação de memória
	free(weights);

	if(bestSet == NULL){
		return IndicesSetCreateEmpty(range);
	}

	return bestSet;
}
