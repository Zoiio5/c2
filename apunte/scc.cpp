#include <bits/stdc++.h>
using namespace std;

/*
 * SCC - Strongly Connected Components (Algoritmo de Kosaraju)
 * Encuentra componentes fuertemente conexas.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(V + E)?
 *   - Primera DFS en grafo original: O(V + E)
 *   - Crear grafo transpuesto: O(E) invirtiendo aristas
 *   - Segunda DFS en grafo transpuesto: O(V + E)
 *   - Total: 2(V + E) + E = O(V + E)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   1. Primera DFS en grafo original: O(V+E)
 *   2. Invertir todas las aristas: O(E)
 *   3. Segunda DFS en grafo transpuesto: O(V+E)
 *   Total: 2(V+E) + E = O(V+E) (las constantes se ignoran en Big-O).
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(V + E)?
 *   - Grafo original adj: O(E) aristas
 *   - Grafo transpuesto adjT: O(E) aristas
 *   - Arrays visited, component, stack: O(V)
 *   - Dominante: O(V + E)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Grafo original 'adj': E aristas. Grafo transpuesto 'adjT': E aristas.
 *   Arrays visited, component, stack: O(V). Dominante: O(V+E) por almacenar
 *   ambos grafos.
 */

// Componentes Fuertemente Conectadas (Kosaraju's Algorithm)
vector<int> adj[100005];
vector<int> adjT[100005];
bool visited[100005];
stack<int> finishStack;
int component[100005];

void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) dfs1(v);
    }
    finishStack.push(u);
}

void dfs2(int u, int comp) {
    component[u] = comp;
    for (int v : adjT[u]) {
        if (component[v] == -1) dfs2(v, comp);
    }
}

int kosaraju(int n) {
    memset(visited, false, sizeof(visited));
    memset(component, -1, sizeof(component));
    
    // Primera pasada: llenar stack por orden de finalización
    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfs1(i);
    }
    
    // Segunda pasada: encontrar componentes
    int numComponents = 0;
    while (!finishStack.empty()) {
        int u = finishStack.top();
        finishStack.pop();
        if (component[u] == -1) {
            dfs2(u, numComponents);
            numComponents++;
        }
    }
    
    return numComponents;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adjT[v].push_back(u);  // Grafo transpuesto
    }
    
    int numSCC = kosaraju(n);
    
    cout << "Número de SCCs: " << numSCC << endl;
    cout << "Componentes:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Nodo " << i << " -> Componente " << component[i] << endl;
    }
    
    return 0;
}
