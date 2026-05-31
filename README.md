# Graph Theory & Dominating Sets - TAD (AED)

##  Overview
This repository features a structural implementation of a **Graph Abstract Data Type (TAD GRAPH)** developed for the **Algoritmos e Estruturas de Dados** course at the **Universidade de Aveiro**. 

The main objective of this project is to model undirected complex graphs using an adjacency list model and implement specialized optimization algorithms to compute structural properties, specifically focusing on **Dominating Sets** using exhaustive search strategies.

##  Project Architecture
The codebase is modularly engineered, isolating individual structural concerns:
* **`Graph.c` / `Graph.h`**: Manages vertex array mapping, adjacency pointers via customized `SortedList` structures, and subgraph generation.
* **`GraphDominatingSets.c` / `GraphDominatingSets.h`**: Dedicated module housing the combinatorial evaluation constraints and optimization algorithms.
* **`IndicesSet.c` / `IndicesSet.h`**: Auxiliary data type used to perform high-performance integer set operations over vertex identifiers.
* **`IntegersStack.c` / `IntegersStack.h`**: Low-level stack structures leveraged internally by the search operations.
* **`relatorio_aed2.pdf`**: Theoretical documentation containing the algorithmic complexity analysis for the optimization routines.

##  Implemented Algorithms & Functions

### 1. Advanced Graph Mechanics
* **`GraphGetSetAdjacen  tsTo`**: Computes and retrieves a dedicated dynamic set containing all adjacent vertices linked to a target node.
* **`GraphComputeVertexWeights`**: Evaluates topological importance by mapping structural node-weight distributions based on adjacent edge configurations.
* **`GraphGetSubGraph`**: Generates a completely new valid subgraph instance derived from a filtered set of source vertices.

### 2. Optimization & Combinatorial Search (Dominating Sets)
A vertex set is a **Dominating Set** if every vertex not in $D$ is adjacent to at least one vertex in $D$. This repository implements:
* **`GraphIsDominatingSet`**: A validation routine checking if a specific subset of nodes successfully dominates the target graph.
* **`GraphComputeMinDominatingSet`**: An optimization algorithm that uses **exhaustive search** (combinatorial backtracking) to extract the absolute minimum cardinality dominating set.
* **`GraphComputeMinWeightDominatingSet`**: A cost-minimization algorithm that computes the optimal dominating set yielding the minimum total weight accumulation across its vertex distribution.

## Performance & Complexity
The implementation prioritizes strict memory bounds to prevent leaks when processing recursive permutations. The accompanying report (`relatorio_aed2.pdf`) provides a detailed **Big-O** characterization mapping the computational cost behavior of the exhaustive backtracking trees against scaling topological ranges.
