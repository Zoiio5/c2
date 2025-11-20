#include <bits/stdc++.h>
using namespace std;

/*
 * DFS - Depth First Search (Búsqueda en Profundidad)
 * Explora profundo antes de retroceder.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(V + E)?
 *   - Visita cada vértice exactamente una vez: O(V)
 *   - Por cada vértice, revisa sus aristas salientes: O(E) en total
 *   - No repite porque marca 'visited'
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Visita cada vértice exactamente una vez (gracias al array 'visited'),
 *   y por cada vértice explora todas sus aristas salientes. Como cada arista
 *   se revisa una sola vez desde su vértice origen: V visitas + E exploraciones = O(V+E).
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(V)?
 *   - Array 'visited' de tamaño V
 *   - Stack de recursión en peor caso (cadena): profundidad V
 *   - Vector 'order' guarda V nodos
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Array 'visited': V booleanos. Stack de recursión: en el peor caso
 *   (grafo en cadena) profundidad V. Vector 'order': guarda los V nodos
 *   visitados. Total: O(V) elementos.
 */

// DFS - Depth First Search
vector<int> adj[100005];
bool visited[100005];
vector<int> order;

void dfs(int u) {
    visited[u] = true;
    order.push_back(u);
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    int n, m, inicio;
    cin >> n >> m >> inicio;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);  // Para grafo no dirigido
    }
    
    dfs(inicio);
    
    cout << "Orden DFS desde " << inicio << ": ";
    for (int x : order) cout << x << " ";
    cout << endl;
    
    return 0;
}
