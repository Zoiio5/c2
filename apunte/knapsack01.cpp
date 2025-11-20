/*
 * KNAPSACK 0/1 - Mochila clásica (DP)
 * 
 * ¿Por qué O(n·W) temporal?
 *   Tabla DP de n items × W capacidades. Llenamos cada celda una vez: O(n·W).
 *   Cada celda toma O(1): max(no_tomar, tomar).
 * 
 * ¿Por qué O(n·W) espacial (versión 2D)?
 *   Matriz dp[n+1][W+1] almacena soluciones de subproblemas.
 *   Se puede optimizar a O(W) usando solo 1 fila (versión 1D).
 * 
 * ¿Por qué O(W) espacial (versión optimizada)?
 *   Solo necesitamos la fila anterior para calcular la actual.
 *   Usando 1 array dp[W+1] y recorriendo de derecha a izquierda.
 * 
 * EXPLICACIÓN INTUITIVA:
 *   Tienes una mochila con capacidad W y n objetos (peso, valor).
 *   Para cada objeto decides: "¿lo llevo o no?". Si lo llevas, sumas su
 *   valor pero gastas su peso. Eliges la combinación que maximiza valor
 *   sin exceder capacidad. DP evita recalcular las mismas decisiones.
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Knapsack 0/1 - Versión optimizada O(W) espacio
ll knapsack_1d(vector<ll>& w, vector<ll>& v, ll W) {
    int n = w.size();
    vector<ll> dp(W + 1, 0);
    
    for (int i = 0; i < n; i++) {
        // Recorrer de derecha a izquierda para no sobreescribir
        for (ll cap = W; cap >= w[i]; cap--) {
            dp[cap] = max(dp[cap], dp[cap - w[i]] + v[i]);
        }
    }
    
    return dp[W];
}

// Knapsack 0/1 - Con reconstrucción de solución O(n·W) espacio
pair<ll, vector<int>> knapsack_2d(vector<ll>& w, vector<ll>& v, ll W) {
    int n = w.size();
    vector<vector<ll>> dp(n+1, vector<ll>(W+1, 0));
    
    // Llenar tabla DP
    for (int i = 1; i <= n; i++) {
        for (ll cap = 0; cap <= W; cap++) {
            // Opción 1: no tomar item i-1
            dp[i][cap] = dp[i-1][cap];
            
            // Opción 2: tomar item i-1 (si cabe)
            if (cap >= w[i-1]) {
                dp[i][cap] = max(dp[i][cap], dp[i-1][cap - w[i-1]] + v[i-1]);
            }
        }
    }
    
    // Reconstruir solución
    vector<int> items;
    ll cap = W;
    for (int i = n; i > 0; i--) {
        if (dp[i][cap] != dp[i-1][cap]) {
            items.push_back(i-1);  // item i-1 fue tomado
            cap -= w[i-1];
        }
    }
    
    reverse(items.begin(), items.end());
    return {dp[n][W], items};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Test: Problema clásico
    vector<ll> w = {2, 3, 4, 5};       // pesos
    vector<ll> v = {3, 4, 5, 6};       // valores
    ll W = 8;                          // capacidad
    
    cout << "=== KNAPSACK 0/1 ===\n";
    cout << "Capacidad: " << W << "\n";
    cout << "Items (peso, valor):\n";
    for (int i = 0; i < w.size(); i++) {
        cout << "  Item " << i << ": (" << w[i] << ", " << v[i] << ")\n";
    }
    
    // Versión 1D (solo valor máximo)
    ll max_val_1d = knapsack_1d(w, v, W);
    cout << "\nValor máximo (1D): " << max_val_1d << "\n";
    
    // Versión 2D (con reconstrucción)
    auto [max_val_2d, items] = knapsack_2d(w, v, W);
    cout << "Valor máximo (2D): " << max_val_2d << "\n";
    
    cout << "\nItems seleccionados: ";
    ll total_weight = 0, total_value = 0;
    for (int idx : items) {
        cout << idx << " ";
        total_weight += w[idx];
        total_value += v[idx];
    }
    cout << "\nPeso total: " << total_weight << "/" << W << "\n";
    cout << "Valor total: " << total_value << "\n";
    
    // Verificación detallada
    cout << "\nDetalle de items seleccionados:\n";
    for (int idx : items) {
        cout << "  Item " << idx << ": peso=" << w[idx] << ", valor=" << v[idx] << "\n";
    }
    
    return 0;
}
