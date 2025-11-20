# 🏆 TOP 10 ALGORITMOS CRÍTICOS - PROGRAMACIÓN COMPETITIVA

## 📁 Archivos en `prac4/`

| # | Algoritmo | Archivo | Complejidad | Uso Principal |
|---|-----------|---------|-------------|---------------|
| 1 | **Binary Search** | `binarysearch.cpp` | O(log n) | Búsqueda en ordenados, bounds |
| 2 | **Prefix Sum** | `prefixsum.cpp` | O(1) query | Suma de rangos 1D/2D |
| 3 | **Knapsack 0/1** | `knapsack01.cpp` | O(n·W) | DP con restricciones |
| 4 | **DFS + BFS** | `dfsbfs.cpp` | O(V+E) | Recorrido grafos, componentes |
| 5 | **Dijkstra** | `djtra.cpp` | O((V+E)log V) | Caminos mínimos (sin pesos negativos) |
| 6 | **Union-Find** | `unionfind.cpp` | O(α(n)) ≈ O(1) | MST, componentes dinámicas |
| 7 | **LIS** | `lis.cpp` | O(n log n) | Subsecuencia creciente máxima |
| 8 | **Two Pointers** | `twopointers.cpp` | O(n) | Subarrays, sliding window |
| 9 | **Sieve** | `sieve.cpp` | O(n log log n) | Números primos, factorización |
| 10 | **Mod Pow** | `modpow.cpp` | O(log b) | Exponenciación modular, combinatoria |

---

## 🎯 CUÁNDO USAR CADA UNO

### 1️⃣ **Binary Search** (`binarysearch.cpp`)
**Casos de uso:**
- Buscar elemento en array ordenado: O(log n) vs O(n) lineal
- `lower_bound`: primer elemento ≥ x
- `upper_bound`: primer elemento > x
- Contar elementos en rango [l, r]
- Binary search en respuesta (buscar el máximo/mínimo que cumple condición)

**Señales:**
- "Array ordenado"
- "Buscar en log n"
- "Primer/último elemento que cumple..."

---

### 2️⃣ **Prefix Sum** (`prefixsum.cpp`)
**Casos de uso:**
- Suma de subarray [l, r] en O(1) después de O(n) precálculo
- Suma de rectángulo en matriz 2D
- Rango de queries (múltiples consultas de suma)

**Señales:**
- "Q queries de suma en rango"
- "Suma de submatriz"
- "Muchas consultas" (Q >> 1)

**Fórmula clave:**
```cpp
sum[l, r] = prefix[r+1] - prefix[l]
```

---

### 3️⃣ **Knapsack 0/1** (`knapsack01.cpp`)
**Casos de uso:**
- Optimización con capacidad limitada
- Subset sum (subconjunto con suma exacta)
- Asignación de recursos con restricciones

**Señales:**
- "Capacidad W"
- "Maximizar valor"
- "Cada item se usa 0 o 1 vez"

**Variantes:**
- Unbounded knapsack: items ilimitados
- Fractional knapsack: se pueden partir (usar greedy)

---

### 4️⃣ **DFS + BFS** (`dfsbfs.cpp`)
**Casos de uso DFS:**
- Detectar ciclos
- Topological sort
- Componentes fuertemente conexas
- Backtracking (paths, permutaciones)

**Casos de uso BFS:**
- Distancia mínima (grafos no ponderados)
- Shortest path en grid
- Level-order traversal

**Señales:**
- "Grafo"
- "Conectividad"
- "Distancia mínima (unweighted)"
- "Explorar todos los caminos"

---

### 5️⃣ **Dijkstra** (`djtra.cpp`)
**Casos de uso:**
- Camino más corto desde origen a todos los nodos
- Pesos **NO negativos**
- Grafos ponderados

**Señales:**
- "Shortest path"
- "Pesos positivos"
- "Desde un nodo a todos"

**⚠️ NO usar si:**
- Pesos negativos → usar Bellman-Ford
- Grafo denso → considerar Floyd-Warshall

---

### 6️⃣ **Union-Find (DSU)** (`unionfind.cpp`)
**Casos de uso:**
- Kruskal MST (Minimum Spanning Tree)
- Componentes conexas dinámicas (agregar aristas online)
- Detectar ciclos en grafo no dirigido
- Problemas de "friends of friends"

**Señales:**
- "Agregar aristas y verificar conectividad"
- "Minimum Spanning Tree"
- "Disjoint sets"
- "¿X e Y están en el mismo componente?"

**Complejidad:** O(α(n)) ≈ O(1) amortizado

---

### 7️⃣ **LIS (Longest Increasing Subsequence)** (`lis.cpp`)
**Casos de uso:**
- Subsecuencia creciente más larga
- Patience sorting
- Box stacking problems

**Señales:**
- "Subsecuencia (no consecutiva)"
- "Creciente/decreciente"
- "Máxima longitud"

**Variantes:**
- LDS: longest decreasing subsequence
- LIS con reconstrucción de la secuencia

**Clave:** O(n log n) usando binary search + DP

---

### 8️⃣ **Two Pointers** (`twopointers.cpp`)
**Casos de uso:**
- Subarray con suma = target
- Sliding window (ventana deslizante)
- Two sum en array ordenado
- Container with most water
- Subarray con k elementos distintos

**Señales:**
- "Subarray"
- "Ventana de tamaño k"
- "Suma en rango"
- "Dos elementos que suman X"

**Patrón:**
- Expandir ventana (r++)
- Contraer ventana (l++)
- Nunca retroceder ambos punteros

---

### 9️⃣ **Sieve of Eratosthenes** (`sieve.cpp`)
**Casos de uso:**
- Todos los primos hasta n
- Factorización prima
- Contar divisores
- GCD, LCM
- Verificar primalidad

**Señales:**
- "Números primos"
- "Factorizar"
- "Divisores"
- "Múltiples queries de primalidad"

**Complejidad:** O(n log log n) precálculo, O(1) query

---

### 🔟 **Modular Exponentiation** (`modpow.cpp`)
**Casos de uso:**
- a^b mod m eficientemente (evitar overflow)
- Inverso modular (Fermat: a^(-1) ≡ a^(m-2) mod m)
- Combinatoria modular: C(n,k) mod m
- División modular
- Fibonacci modular

**Señales:**
- "mod 10^9+7"
- "mod 998244353"
- "Exponente grande" (b > 10^6)
- "Combinatoria con módulo"

**Complejidad:** O(log b) usando exponenciación binaria

---

## 📊 FRECUENCIA DE USO (competitivas típicas)

```
🔥🔥🔥🔥🔥  Binary Search, Two Pointers, Prefix Sum
🔥🔥🔥🔥    DFS/BFS, Mod Pow
🔥🔥🔥      Dijkstra, Union-Find, Knapsack
🔥��        LIS, Sieve
```

---

## 💡 DECISIÓN RÁPIDA POR LÍMITES

| Límite n | Complejidad aceptable | Algoritmos |
|----------|----------------------|------------|
| n ≤ 10 | O(n!) | Backtracking |
| n ≤ 20 | O(2^n) | Bitmask DP |
| n ≤ 500 | O(n³) | Floyd-Warshall |
| n ≤ 5000 | O(n²) | DP cuadrático |
| n ≤ 10⁵ | O(n log n) | **Sort, Dijkstra, Binary Search, LIS** |
| n ≤ 10⁶ | O(n) | **Two Pointers, Prefix Sum, DFS/BFS** |
| n ≤ 10⁹ | O(log n) | **Binary Search, Mod Pow, GCD** |

---

## ✅ CHECKLIST ANTES DE COMPETIR

### Código Base (copiar estos archivos)
- [ ] `binarysearch.cpp` - búsqueda + bounds
- [ ] `prefixsum.cpp` - sumas de rango
- [ ] `twopointers.cpp` - subarrays eficientes
- [ ] `modpow.cpp` - exponenciación modular
- [ ] `unionfind.cpp` - DSU para grafos

### Durante el problema
1. **Leer límites:** ¿n ≤ 10⁵? → O(n log n) máximo
2. **Identificar patrón:**
   - ¿Ordenado? → Binary Search
   - ¿Grafos? → DFS/BFS/Dijkstra/Union-Find
   - ¿Subarrays? → Two Pointers / Prefix Sum
   - ¿DP con capacidad? → Knapsack
   - ¿Módulo? → Mod Pow
3. **Casos borde:** n=0, n=1, negativos, overflow

---

## 🚀 COMPILACIÓN Y PRUEBA

```bash
# Compilar cualquier archivo
g++ -std=c++17 -O2 -Wall binarysearch.cpp -o binarysearch
./binarysearch

# Compilar todos los TOP 10
for f in binarysearch prefixsum knapsack01 dfsbfs lis twopointers sieve modpow unionfind djtra; do
    g++ -std=c++17 -O2 -Wall ${f}.cpp -o ${f} && echo "✓ ${f}.cpp compilado"
done
```

---

**Repositorio:** `/home/digitalsandman/projects/algoco/prac4/`  
**Referencia completa:** `CODIGOS_ESENCIALES_COMPETITIVA.md`
