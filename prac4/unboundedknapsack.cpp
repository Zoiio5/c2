#include <bits/stdc++.h>
using namespace std;

/*
 * UNBOUNDED KNAPSACK (Mochila con Repetición - DP)
 * Puedes usar cada item múltiples veces.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(n·W)?
 *   - Para cada capacidad w de 1 a W: W iteraciones
 *   - Por cada w, prueba n items: n iteraciones internas
 *   - Total: W × n = O(n·W)
 *   - Cada celda: max de (estado anterior, agregar item i)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Para cada capacidad w (de 1 a W), prueba los n items. Como puedes
 *   reutilizar items, cada celda dp[w] depende de dp[w - peso[i]].
 *   Total: W × n.
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(W)?
 *   - Solo necesita array dp[] de tamaño W+1
 *   - No necesita matriz 2D como 0/1 Knapsack
 *   - Sobreescribe valores porque puede reutilizar items
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Solo un array 1D dp[] de tamaño W+1. No necesitas matriz 2D porque
 *   puedes sobreescribir (reutilizar items está permitido): O(W).
 */

// Unbounded Knapsack (Mochila con Repetición)
int unboundedKnapsack(vector<int>& values, vector<int>& weights, int W) {
    vector<int> dp(W + 1, 0);
    
    for (int w = 1; w <= W; w++) {
        for (int i = 0; i < values.size(); i++) {
            if (weights[i] <= w) {
                dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
            }
        }
    }
    
    return dp[W];
}

int main() {
    int n, W;
    cin >> n >> W;
    
    vector<int> values(n), weights(n);
    for (int i = 0; i < n; i++) cin >> values[i];
    for (int i = 0; i < n; i++) cin >> weights[i];
    
    int maxValue = unboundedKnapsack(values, weights, W);
    
    cout << "Valor máximo: " << maxValue << endl;
    
    return 0;
}
