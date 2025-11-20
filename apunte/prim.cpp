#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

/*
 * ALGORITMO DE PRIM - MST con Priority Queue
 * Construye árbol de expansión mínima creciendo desde un nodo inicial.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O((V + E) log V)?
 *   - Cada vértice se extrae del heap una vez: V × log(V)
 *   - Por cada vértice, revisa sus vecinos: E aristas totales
 *   - Cada inserción/actualización en heap: log(V)
 *   - Total: V·log(V) + E·log(V) = O((V + E) log V)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Similar a Dijkstra: cada vértice entra/sale del min-heap una vez: V × log(V).
 *   Relaja todas las aristas: E × log(V). Total: (V+E) log V.
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(V + E)?
 *   - Grafo de adyacencia: O(V + E)
 *   - Priority queue: hasta O(E) entradas (versión lazy)
 *   - Arrays enMST, padre: O(V)
 *   - Vector aristasMST: O(V-1) = O(V)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Grafo de adyacencia: O(V+E). Min-heap: hasta V elementos. Arrays enMST,
 *   padre: O(V). Dominante: O(V+E).
 */

struct Arista {
    int destino;
    ll peso;
};

// Par: {peso, vertice}
struct Nodo {
    ll peso;
    int vertice;
    bool operator>(const Nodo& otro) const {
        return peso > otro.peso; // Min-heap
    }
};

// Función mejorada de Prim con inicio aleatorio
pair<ll, vector<pair<int, int>>> prim(int n, vector<vector<Arista>>& grafo, int inicio = -1) {
    // Si no se especifica inicio, elegir uno aleatorio
    if (inicio == -1) {
        srand(time(nullptr));
        inicio = rand() % n;
    }
    
    vector<bool> enMST(n, false);
    priority_queue<Nodo, vector<Nodo>, greater<Nodo>> pq;
    
    vector<pair<int, int>> aristasMST;
    vector<int> padre(n, -1);
    ll pesoTotal = 0;
    
    // Iniciar desde el vértice elegido
    pq.push({0, inicio});
    padre[inicio] = inicio;
    
    int aristas_procesadas = 0;
    
    while (!pq.empty() && aristas_procesadas < n - 1) {
        Nodo actual = pq.top();
        pq.pop();
        
        int v = actual.vertice;
        ll peso = actual.peso;
        
        if (enMST[v]) continue;
        
        // Agregar vértice al MST
        enMST[v] = true;
        pesoTotal += peso;
        
        // Guardar la arista (excepto el nodo inicial)
        if (v != inicio) {
            aristasMST.push_back({padre[v], v});
            aristas_procesadas++;
        }
        
        // Buscar vecino de menor costo no visitado
        for (const Arista& e : grafo[v]) {
            if (!enMST[e.destino]) {
                pq.push({e.peso, e.destino});
                padre[e.destino] = v;
            }
        }
    }
    
    return {pesoTotal, aristasMST};
}

// ============================================
// EJEMPLO DE USO
// ============================================

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<Arista>> grafo(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        grafo[u].push_back({v, w});
        grafo[v].push_back({u, w});
    }
    
    auto [peso, aristas] = prim(n, grafo);
    cout << "Peso MST: " << peso << endl;
    cout << "Aristas:" << endl;
    for (auto [u, v] : aristas) {
        cout << u << " - " << v << endl;
    }
    
    return 0;
}
