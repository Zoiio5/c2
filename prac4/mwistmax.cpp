/*
 * MWIS - Maximum Weighted Independent Set (en árboles)
 * Encuentra el conjunto independiente de peso máximo.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(V)?
 *   - DFS visita cada nodo exactamente una vez: O(V)
 *   - Por cada nodo, calcula dp[u][0] y dp[u][1]: O(1)
 *   - Suma pesos de hijos: O(grado) pero total = O(E) = O(V) en árbol
 *   - Reconstrucción: O(V)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   DFS visita cada nodo exactamente una vez. Por cada nodo calcula dp[u][0]
 *   (no incluirlo) y dp[u][1] (incluirlo) sumando valores de hijos. Aunque
 *   suma sobre hijos, el total de operaciones sobre todas las aristas es
 *   O(E) = O(V) en un árbol (E = V-1).
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(V)?
 *   - Lista de adyacencia: O(V-1) aristas en árbol = O(V)
 *   - Arrays w, dp: O(V) cada uno
 *   - Stack de recursión: profundidad del árbol ≤ V
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Lista de adyacencia: V-1 aristas = O(V). Arrays w, dp: 2V elementos.
 *   Stack de recursión: profundidad del árbol ≤ V. Total: O(V).
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

vector<int> adj[100005];
int w[100005];
int dp[100005][2];

void dfs(int u, int p) {
    dp[u][0] = 0;
    dp[u][1] = w[u];
    
    for (int v : adj[u]) {
        if (v == p) continue;
        
        dfs(v, u);
        
        dp[u][1] += dp[v][0];
        dp[u][0] += max(dp[v][0], dp[v][1]);
    }
}

int main() {
    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++) cin >> w[i];
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    dfs(0, -1);
    int maxPeso = max(dp[0][0], dp[0][1]);
    cout << "Peso máximo: " << maxPeso << endl;
    
    vector<int> seleccionados;
    function<void(int, int, bool)> reconstruir = [&](int u, int p, bool tomado) {
        if (tomado) seleccionados.push_back(u);
        for (int v : adj[u]) {
            if (v == p) continue;
            if (tomado) {
                reconstruir(v, u, false);
            } else {
                reconstruir(v, u, dp[v][1] > dp[v][0]);
            }
        }
    };
    
    reconstruir(0, -1, dp[0][1] > dp[0][0]);
    cout << "Nodos seleccionados: ";
    for (int x : seleccionados) cout << x << " ";
    cout << endl;
    
    return 0;
}