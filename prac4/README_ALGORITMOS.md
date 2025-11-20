# Algoritmos Implementados - Programación Competitiva

## I. Ordenamiento (Sorting)
- [x] **MergeSort** - O(n log n)
- [x] **QuickSort** - O(n log n) promedio
- [x] **SelectionSort** - O(n²)
- [x] **InsertionSort** - O(n²)
- [x] **BubbleSort** - O(n²)
- [x] **Counting Inversions** - O(n log n) usando MergeSort

## II. Selección (Selection)
- [x] **Binary Search** - O(log n)
- [x] **RSelect** - Selección aleatoria O(n) promedio
- [x] **DSelect** - Mediana de medianas O(n) determinista

## III. Grafos (Graphs)
### Recorridos
- [x] **BFS** - Breadth-First Search
- [x] **DFS** - Depth-First Search

### Caminos Mínimos
- [x] **Dijkstra** - Caminos mínimos con pesos positivos
- [x] **Bellman-Ford** - Caminos mínimos con pesos negativos
- [x] **Floyd-Warshall** - Todos los pares
- [x] **A*** - Búsqueda informada

### Árboles de Expansión Mínima (MST)
- [x] **Prim** - MST para grafos densos
- [x] **Kruskal** - MST para grafos dispersos

### Otros
- [x] **Topological Sort** - Ordenamiento topológico
- [x] **SCC** - Componentes fuertemente conectadas (Kosaraju)

## IV. Programación Dinámica (DP)
- [x] **Knapsack 0/1** - Mochila clásica con reconstrucción
- [x] **Unbounded Knapsack** - Mochila con repetición
- [x] **Fractional Knapsack** - Mochila fraccionaria (Greedy)
- [x] **MWIS** - Maximum Weighted Independent Set
- [x] **Sequence Alignment** - Needleman-Wunsch
- [x] **Fibonacci** - Ejemplo básico de DP

## V. Backtracking
- [x] **N-Queens** - Problema de las N reinas
- [x] **TSP** - Travelling Salesman con poda
- [x] **Permutations** - Generación de permutaciones
- [x] **Subsets** - Generación de subconjuntos (máscara binaria)
- [x] **Combinations** - Combinaciones de tamaño k

## VI. Algoritmos Greedy
- [x] **Fractional Knapsack** - Mochila fraccionaria
- [x] **Huffman Coding** - Códigos de Huffman
- [x] **Scheduling (FCFS)** - Planificación de procesos
- [x] **Greedy Pattern** - Patrón general

## VII. Divide y Conquistar
- [x] **MergeSort** - Ordenamiento
- [x] **QuickSort** - Ordenamiento
- [x] **Closest Pair** - Par más cercano
- [x] **Strassen** - Multiplicación de matrices O(n^2.81)
- [x] **Counting Inversions** - Conteo de inversiones

## VIII. Otros
- [x] **Scheduling Algorithms** - FCFS, SJF, SRTF, RR, Priority

## Formato de Entrada
Todos los algoritmos aceptan entrada desde `stdin` y muestran:
- **Resultado principal** (valor óptimo, distancia, etc.)
- **Reconstrucción de solución** (camino, items seleccionados, etc.)

## Compilación
```bash
g++ -std=c++17 <archivo>.cpp -o <ejecutable>
```

## Testing
```bash
bash run_tests.sh       # Algoritmos principales
bash test_nuevos.sh     # Algoritmos nuevos
```
