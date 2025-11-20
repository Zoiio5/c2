#include <bits/stdc++.h>
using namespace std;

/*
 * TOPOLOGICAL SORT (Ordenamiento Topológico)
 * Ordena DAG respetando dependencias.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(V + E)?
 *   - Es un DFS completo que visita todos los vértices: O(V)
 *   - Y todas las aristas exactamente una vez: O(E)
 *   - Push al stack es O(1) por nodo
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Es esencialmente un DFS completo que además guarda el orden en un stack.
 *   Misma complejidad que DFS: visita V vértices y E aristas exactamente
 *   una vez. Push al stack es O(1) por nodo.
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(V)?
 *   - Array 'visited': V elementos
 *   - Stack de recursión (DFS): hasta V de profundidad
 *   - topoStack guarda los V nodos
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Array 'visited': V elementos. Stack de recursión DFS: hasta V de
 *   profundidad. topoStack: almacena los V nodos. Todo proporcional a V: O(V).
 */

// Topological Sort usando DFS
vector<int> adj[100005];
bool visited[100005];
stack<int> topoStack;

void dfs(int u) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
    
    topoStack.push(u);
}

vector<int> topologicalSort(int n) {
    memset(visited, false, sizeof(visited));
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    
    vector<int> result;
    while (!topoStack.empty()) {
        result.push_back(topoStack.top());
        topoStack.pop();
    }
    
    return result;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);  // Grafo dirigido
    }
    
    vector<int> topo = topologicalSort(n);
    
    cout << "Ordenamiento topológico: ";
    for (int x : topo) cout << x << " ";
    cout << endl;
    
    return 0;
}
