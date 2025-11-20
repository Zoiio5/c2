

/*
 * KNAPSACK 0/1 - Dynamic Programming
 * Maximiza valor seleccionando items sin repetición.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(n·W)?
 *   - n items × W capacidades = n·W celdas en la tabla DP
 *   - Cada celda calcula max de 2 opciones: O(1)
 *   - Reconstrucción de solución: O(n) backtracking
 *   - NOTA: Es pseudo-polinómico (depende del valor W, no su tamaño en bits)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Construye una tabla DP de n items × W capacidades. Cada celda calcula el
 *   máximo entre "tomar el item" o "no tomarlo" en O(1). Total: n × W celdas.
 *   PSEUDO-POLINÓMICO: W es un valor numérico, no el tamaño de su representación.
 *   Si W=1000000, no es polinómico en la entrada (que sería log₂(W) bits).
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(n·W) o O(W) optimizado?
 *   - Tabla DP 2D: matriz de n × W
 *   - Optimización: solo necesita fila anterior → O(W)
 *   - Arrays de items y selected: O(n)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Tabla 2D de n×W. OPTIMIZACIÓN: Solo necesitas la fila anterior, reducible
 *   a O(W) si no reconstruyes la solución.
 */
#include <bits/stdc++.h>
using namespace std;

// Devuelve: {valor_maximo, vector con índices de ítems usados}
pair<long long, vector<int>> knapsack(
    const vector<long long>& val,
    const vector<long long>& wt,
    long long W
) {
    int n = val.size();

    // DP 1D
    vector<long long> dp(W + 1, 0);

    // Para reconstrucción: items_en[w] guardará los ítems usados para alcanzar dp[w]
    vector<vector<int>> items_en(W + 1);

    for (int i = 0; i < n; i++) {
        for (long long w = W; w >= wt[i]; w--) {
            long long tomar = dp[w - wt[i]] + val[i];
            if (tomar > dp[w]) {
                dp[w] = tomar;
                items_en[w] = items_en[w - wt[i]];
                items_en[w].push_back(i);
            }
        }
    }

    // Buscar la mejor capacidad posible (0..W)
    long long bestValue = 0;
    long long bestW = 0;

    for (long long w = 0; w <= W; w++) {
        if (dp[w] > bestValue) {
            bestValue = dp[w];
            bestW = w;
        }
    }

    // Reconstrucción final
    return {bestValue, items_en[bestW]};
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long W;
    cin >> n >> W;
    
    vector<long long> value(n), weight(n);
    for (int i = 0; i < n; i++) cin >> value[i];
    for (int i = 0; i < n; i++) cin >> weight[i];
    
    auto res = knapsack(value, weight, W);
    cout << "Valor máximo: " << res.first << endl;
    cout << "Items seleccionados: ";
    for (int i : res.second) cout << i << " ";
    cout << endl;

    return 0;
}
