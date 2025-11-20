/*solo funciona con valores*/
/*
 * A* SEARCH - Búsqueda informada con heurística
 * Encuentra el camino más corto usando f(n) = g(n) + h(n).
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(b^d) peor caso?
 *   - b = branching factor (vecinos promedio)
 *   - d = profundidad de la solución
 *   - Con mala heurística, explora exponencialmente: b^d nodos
 *   - Con heurística admisible buena: cercano a O((V + E) log V) como Dijkstra
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Con mala heurística (h=0), degrada a Dijkstra: O((V+E) log V). Con
 *   heurística admisible pero poco informativa, explora muchas ramas. En el
 *   peor caso (árbol de branching factor b, profundidad d): O(b^d) nodos explorados.
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(V)?
 *   - Arrays g_score, f_score, parent: 3×V
 *   - Priority queue: hasta V nodos en memoria
 *   - Path reconstruido: a lo más V nodos
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Priority queue: a lo más V nodos abiertos. Arrays g_score, f_score,
 *   parent: 3V elementos. Total: O(V).
 */
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int id;
    int f;
    bool operator>(const Node &other) const {
        return f > other.f;
    }
};

vector<int> a_star(int start, int goal,
                   const vector<vector<pair<int,int>>> &adj,
                   const vector<int>& h) {

    int n = adj.size();
    const int INF = 1e9;

    vector<int> g(n, INF);     // costo real acumulado
    vector<int> parent(n, -1);
    vector<bool> closed(n, false);

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    g[start] = 0;
    pq.push({start, h[start]});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        
        int u = current.id;

        if (closed[u]) continue;
        closed[u] = true;

        if (u == goal) break;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            // NO SE PERMITEN PESOS NEGATIVOS:
            if (w < 0) {
                throw runtime_error("A* received a negative edge weight");
            }

            int tentative = g[u] + w;
            if (tentative < g[v]) {
                g[v] = tentative;
                parent[v] = u;
                int f = tentative + h[v];
                pq.push({v, f});
            }
        }
    }

    if (g[goal] == INF) return {}; // No reachable

    // reconstruct path
    vector<int> path;
    for (int v = goal; v != -1; v = parent[v])
        path.push_back(v);
    reverse(path.begin(), path.end());

    return path;
}

int main() {
    int n, m, inicio, objetivo;
    cin >> n >> m >> inicio >> objetivo;
    
    vector<vector<pair<int,int>>> adj(n);
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    // Leer heurística (valores h para cada nodo)
    vector<int> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    
    auto path = a_star(inicio, objetivo, adj, h);
    
    if (path.empty()) {
        cout << "No path found" << endl;
    } else {
        cout << "Path: ";
        for (int x : path) cout << x << " ";
        cout << endl;
    }
}
