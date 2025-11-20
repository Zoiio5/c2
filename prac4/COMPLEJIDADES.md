# Complejidades de Algoritmos - Referencia Rápida

## Ordenamiento

| Algoritmo | Temporal | Espacial | Notas |
|-----------|----------|----------|-------|
| **SelectionSort** | O(n²) | O(1) | Siempre O(n²), in-place |
| **InsertionSort** | O(n) ~ O(n²) | O(1) | O(n) mejor caso, bueno para datos casi ordenados |
| **BubbleSort** | O(n) ~ O(n²) | O(1) | O(n) con optimización si ya ordenado |
| **MergeSort** | O(n log n) | O(n) | Estable, predecible |
| **QuickSort** | O(n log n) promedio | O(log n) | O(n²) peor caso, in-place |
| **Counting Inversions** | O(n log n) | O(n) | Basado en MergeSort |

## Selección

| Algoritmo | Temporal | Espacial | Notas |
|-----------|----------|----------|-------|
| **Binary Search** | O(log n) | O(1) | Requiere arreglo ordenado |
| **RSelect** | O(n) promedio | O(log n) | Aleatorio, O(n²) peor caso |
| **DSelect** | O(n) garantizado | O(log n) | Mediana de medianas |

## Grafos - Recorridos

| Algoritmo | Temporal | Espacial | Notas |
|-----------|----------|----------|-------|
| **BFS** | O(V + E) | O(V) | Cola, camino más corto en grafos no pesados |
| **DFS** | O(V + E) | O(V) | Stack/recursión, detecta ciclos |
| **Topological Sort** | O(V + E) | O(V) | DFS en DAG |
| **SCC (Kosaraju)** | O(V + E) | O(V + E) | Dos pasadas de DFS |

## Grafos - Caminos Mínimos

| Algoritmo | Temporal | Espacial | Notas |
|-----------|----------|----------|-------|
| **Dijkstra** | O((V+E) log V) | O(V) | Pesos no negativos, heap |
| **Bellman-Ford** | O(V·E) | O(V) | Permite pesos negativos |
| **Floyd-Warshall** | O(V³) | O(V²) | Todos los pares |
| **A*** | O(E) ~ O(b^d) | O(V) | Heurística, mejor que Dijkstra |

## Grafos - MST

| Algoritmo | Temporal | Espacial | Notas |
|-----------|----------|----------|-------|
| **Prim** | O(E log V) | O(V) | Mejor para grafos densos |
| **Kruskal** | O(E log E) | O(V) | Union-Find, mejor para dispersos |

## Programación Dinámica

| Algoritmo | Temporal | Espacial | Notas |
|-----------|----------|----------|-------|
| **Knapsack 0/1** | O(n·W) | O(n·W) → O(W) | W = capacidad |
| **Unbounded Knapsack** | O(n·W) | O(W) | Permite repetición |
| **MWIS** | O(V) | O(V) | En árboles |
| **Sequence Alignment** | O(n·m) | O(n·m) | Needleman-Wunsch |
| **Fibonacci DP** | O(n) | O(n) → O(1) | Vs O(2ⁿ) recursivo |

## Algoritmos Greedy

| Algoritmo | Temporal | Espacial | Notas |
|-----------|----------|----------|-------|
| **Fractional Knapsack** | O(n log n) | O(n) | Ordenar por ratio |
| **Huffman Coding** | O(n + k log k) | O(k) | k = caracteres únicos |
| **Scheduling FCFS** | O(n log n) | O(n) | Ordenar por llegada |

## Backtracking

| Algoritmo | Temporal | Espacial | Notas |
|-----------|----------|----------|-------|
| **TSP** | O(n!) | O(n) | Con poda, factible para n≤15 |
| **N-Queens** | O(n!) | O(n) | Con poda |
| **Subsets (Bitmask)** | O(n·2ⁿ) | O(n·2ⁿ) | 2ⁿ subconjuntos |
| **Permutations** | O(n·n!) | O(n·n!) | n! permutaciones |
| **Combinations C(n,k)** | O(C(n,k)·k) | O(C(n,k)·k) | C(n,k) = n!/(k!(n-k)!) |

## Leyenda

- **V** = Vértices
- **E** = Aristas  
- **n** = Tamaño del input
- **W** = Capacidad (knapsack)
- **k** = Número de elementos únicos
- **~** = Aproximadamente/Depende del caso
- **→** = Puede optimizarse a

## Notas Importantes

1. **Temporal vs Espacial**: A veces se puede reducir espacio a costa de tiempo
2. **In-place**: Algoritmos O(1) espacio modifican el input original
3. **Estabilidad**: Merge/Insertion son estables, Quick/Selection no lo garantizan
4. **Mejor caso**: Útil cuando datos tienen patrones conocidos
5. **Promedio vs Peor**: RSelect tiene O(n) promedio pero O(n²) peor caso
