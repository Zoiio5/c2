/*
 * DFS + BFS - Recorrido de grafos
 * 
 * ¿Por qué O(V+E) temporal (ambos)?
 *   DFS/BFS visitan cada vértice V exactamente una vez: O(V).
 *   Para cada vértice, recorren sus aristas adyacentes: O(E) en total.
 *   Total: O(V + E)
 * 
 * ¿Por qué O(V) espacial?
 *   - Array 'visited': V booleanos
 *   - DFS recursivo: stack de recursión hasta V de profundidad
 *   - BFS: cola puede tener hasta V elementos simultáneos
 *   - Lista de adyacencia: O(V + E) pero se cuenta aparte
 * 
 * EXPLICACIÓN INTUITIVA:
 *   DFS (Depth-First Search): Explorar "en profundidad". Como un laberinto,
 *   sigues un camino hasta el fondo antes de retroceder. Usa stack/recursión.
 * 
 *   BFS (Breadth-First Search): Explorar "en amplitud". Como ondas en agua,
 *   visitas todos los vecinos inmediatos antes de alejarte. Usa cola (queue).
 */

#include <bits/stdc++.h>
using namespace std;

int n;  // número de vértices
vector<vector<int>> adj;  // lista de adyacencia
vector<bool> visited;

// DFS recursivo
void dfs(int u) {
    visited[u] = true;
    cout << u << " ";
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

// BFS iterativo
void bfs(int start) {
    queue<int> q;
    vector<bool> vis(n, false);
    vector<int> dist(n, -1);
    
    q.push(start);
    vis[start] = true;
    dist[start] = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        cout << u << " ";
        
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    
    cout << "\nDistancias desde " << start << ": ";
    for (int i = 0; i < n; i++) {
        cout << dist[i] << " ";
    }
    cout << "\n";
}

// Contar componentes conexas
int count_components() {
    visited.assign(n, false);
    int components = 0;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
            components++;
            cout << "\n";
        }
    }
    
    return components;
}

// Detectar ciclos usando DFS
bool has_cycle_dfs(int u, int parent) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            if (has_cycle_dfs(v, u)) return true;
        } else if (v != parent) {
            return true;  // arista de retorno = ciclo
        }
    }
    
    return false;
}

bool has_cycle() {
    visited.assign(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (has_cycle_dfs(i, -1)) return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Crear grafo de ejemplo
    n = 7;
    adj.assign(n, vector<int>());
    
    // Grafo: 0-1-2-3
    //        |   |
    //        4   5-6
    adj[0] = {1, 4};
    adj[1] = {0, 2};
    adj[2] = {1, 3, 5};
    adj[3] = {2};
    adj[4] = {0};
    adj[5] = {2, 6};
    adj[6] = {5};
    
    cout << "=== DFS desde 0 ===\n";
    visited.assign(n, false);
    dfs(0);
    cout << "\n\n";
    
    cout << "=== BFS desde 0 ===\n";
    bfs(0);
    cout << "\n";
    
    cout << "=== COMPONENTES CONEXAS ===\n";
    int comp = count_components();
    cout << "Total componentes: " << comp << "\n\n";
    
    cout << "=== DETECCIÓN DE CICLOS ===\n";
    cout << (has_cycle() ? "Tiene ciclos" : "No tiene ciclos") << "\n";
    
    return 0;
}
