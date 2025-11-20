# Algoritmos - PRAC4

Colección completa de algoritmos optimizados con ejemplos de ejecución.

## 📋 Índice de Algoritmos

### 🌲 Árboles de Expansión Mínima (MST)
1. **Kruskal.cpp** - MST con Union-Find
   - Complejidad: O(E log V)
   - Mejor para grafos dispersos
   ```bash
   g++ -std=c++17 Kruskal.cpp -o kruskal && ./kruskal
   ```

2. **prim.cpp** - MST con Priority Queue
   - Complejidad: O(E log V)
   - Mejor para grafos densos
   - Soporta inicio aleatorio
   ```bash
   g++ -std=c++17 prim.cpp -o prim && ./prim
   ```

### 🛣️ Caminos Mínimos
3. **djtra.cpp** - Dijkstra
   - Complejidad: O(E log V)
   - Solo pesos positivos
   - Reconstrucción de caminos
   ```bash
   g++ -std=c++17 djtra.cpp -o dijkstra && ./dijkstra
   ```

4. **bellmanford.cpp** - Bellman-Ford
   - Complejidad: O(V·E)
   - Soporta pesos negativos
   - Detecta ciclos negativos
   ```bash
   g++ -std=c++17 bellmanford.cpp -o bellman && ./bellman
   ```

5. **aestrella.cpp** - A* (A-Star)
   - Complejidad: O(E log V) con heurística admisible
   - Búsqueda heurística
   - Requiere función heurística
   ```bash
   g++ -std=c++17 aestrella.cpp -o astar && ./astar
   ```

### 💎 Programación Dinámica
6. **kanpsack.cpp** - Problema de la Mochila (0/1 Knapsack)
   - Complejidad: O(n·W)
   - DP 1D optimizado
   - Reconstrucción de solución
   ```bash
   g++ -std=c++17 kanpsack.cpp -o knapsack && ./knapsack
   ```

7. **mwistmax.cpp** - Maximum Weighted Independent Set en Árbol
   - Complejidad: O(n)
   - DP sobre árboles
   ```bash
   g++ -std=c++17 mwistmax.cpp -o mwis && ./mwis
   ```

8. **alisecu.cpp** - Alineamiento de Secuencias (Needleman-Wunsch)
   - Complejidad: O(n·m)
   - Alineamiento global
   - Reconstrucción de alineamiento
   ```bash
   g++ -std=c++17 alisecu.cpp -o align && ./align
   ```

### 📊 Ordenamiento y Scheduling
9. **quicksort.cpp** - QuickSort (3 variantes)
   - Lomuto partition
   - Hoare partition
   - Random pivot
   - Complejidad: O(n log n) promedio
   ```bash
   g++ -std=c++17 quicksort.cpp -o qsort && ./qsort
   ```

10. **scheduling.cpp** - Algoritmos de Scheduling de CPU
    - FCFS (First Come First Serve)
    - SJF (Shortest Job First)
    - SRTF (Shortest Remaining Time First)
    - Round Robin
    - Priority Scheduling
    ```bash
    g++ -std=c++17 scheduling.cpp -o sched && ./sched
    ```

### 📚 Patrones de Diseño de Algoritmos
11. **gb.cpp** - Patrones de Backtracking
    - Permutaciones
    - Combinaciones
    - Subconjuntos
    - N-Reinas
    - Coloreo de grafos
    - Sudoku
    ```bash
    g++ -std=c++17 gb.cpp -o backtrack && ./backtrack
    ```

12. **gdp.cpp** - Patrones de Programación Dinámica
    - Top-Down (Memoización)
    - Bottom-Up (Tabulación)
    - DP 1D optimizado
    - Reconstrucción de soluciones
    ```bash
    g++ -std=c++17 gdp.cpp -o dp && ./dp
    ```

13. **gg.cpp** - Patrones de Algoritmos Greedy
    - Ordenar y seleccionar
    - Selección iterativa
    - Priority queue
    - Scheduling de actividades
    ```bash
    g++ -std=c++17 gg.cpp -o greedy && ./greedy
    ```

## 🚀 Compilación y Ejecución

### Compilar todos
```bash
for file in *.cpp; do
    g++ -std=c++17 -O2 "$file" -o "${file%.cpp}"
done
```

### Probar todos
```bash
bash test_all.sh
```

## 📊 Tabla Comparativa

| Algoritmo | Tipo | Complejidad Tiempo | Complejidad Espacio | Mejor Caso |
|-----------|------|-------------------|---------------------|------------|
| Kruskal | MST | O(E log V) | O(V) | Grafos dispersos |
| Prim | MST | O(E log V) | O(V + E) | Grafos densos |
| Dijkstra | Caminos | O(E log V) | O(V + E) | Pesos positivos |
| Bellman-Ford | Caminos | O(V·E) | O(V) | Pesos negativos |
| A* | Búsqueda | O(E log V) | O(V) | Con heurística |
| Knapsack | DP | O(n·W) | O(W) | Optimización |
| QuickSort | Ordenamiento | O(n log n) | O(log n) | General |

## 🎯 Características de Cada Implementación

### ✅ Optimizaciones Implementadas
- **Union-Find**: Compresión de caminos + union by rank
- **Priority Queue**: Min-heap optimizado
- **DP**: Espacio optimizado (1D cuando es posible)
- **Memoización**: Cache de resultados
- **Poda**: En backtracking y búsqueda

### 📝 Características Comunes
- Entrada hardcoded (sin necesidad de archivos)
- Múltiples ejemplos por archivo
- Comentarios explicativos
- Análisis de complejidad
- Estilo consistente

## 🔧 Requisitos
- g++ con soporte C++17 o superior
- Sistema operativo: Linux/Mac/Windows con WSL

## 📖 Uso Académico
Estos algoritmos están optimizados para:
- Estudio y comprensión de algoritmos
- Preparación para pruebas/exámenes
- Referencia rápida de implementaciones
- Comparación de estrategias algorítmicas

## 🏆 Algoritmos por Estrategia

### Divide y Conquista
- QuickSort

### Greedy
- Kruskal
- Prim
- Dijkstra
- Scheduling

### Programación Dinámica
- Knapsack
- Bellman-Ford
- Maximum Weighted Independent Set
- Alineamiento de Secuencias

### Backtracking
- N-Reinas
- Coloreo de grafos
- Sudoku
- Permutaciones/Combinaciones

### Búsqueda Heurística
- A* (A-Star)

---

**Autor**: Adaptados y optimizados para uso académico  
**Fecha**: Noviembre 2025  
**Versión**: 1.0
