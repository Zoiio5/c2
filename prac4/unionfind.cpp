/*
 * UNION-FIND (DSU - Disjoint Set Union)
 * 
 * ¿Por qué O(α(n)) ≈ O(1) temporal por operación?
 *   Con Path Compression + Union by Rank:
 *   - α(n) = función inversa de Ackermann (crece extremadamente lento)
 *   - Para n ≤ 10^80: α(n) ≤ 4 → prácticamente constante
 *   - Amortizado: secuencia de m operaciones toma O(m × α(n))
 * 
 * ¿Por qué O(n) espacial?
 *   - Array parent[n]: almacena padre de cada nodo
 *   - Array rank[n]: altura aproximada de cada árbol
 *   Total: 2n = O(n)
 * 
 * EXPLICACIÓN INTUITIVA:
 *   Estructura para manejar conjuntos disjuntos dinámicamente.
 *   Operaciones: find(x) = ¿a qué conjunto pertenece x?
 *                unite(x, y) = unir conjuntos de x e y
 *   
 *   Optimizaciones:
 *   - Path Compression: al buscar raíz, aplana el árbol (todos apuntan a raíz)
 *   - Union by Rank: unir árbol pequeño bajo el grande (evita árboles altos)
 *   
 *   Aplicaciones: Kruskal MST, componentes dinámicas, detección de ciclos.
 */

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
    int components;
    
public:
    UnionFind(int n) : parent(n), rank(n, 0), components(n) {
        // Inicialmente cada nodo es su propio padre
        iota(parent.begin(), parent.end(), 0);
    }
    
    // Find con Path Compression O(α(n))
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // path compression
        }
        return parent[x];
    }
    
    // Union by Rank O(α(n))
    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        
        if (px == py) return false;  // ya están en el mismo conjunto
        
        // Unir árbol de menor rank bajo el de mayor rank
        if (rank[px] < rank[py]) {
            swap(px, py);
        }
        
        parent[py] = px;
        
        // Si ranks iguales, aumentar rank del nuevo root
        if (rank[px] == rank[py]) {
            rank[px]++;
        }
        
        components--;
        return true;
    }
    
    // Verificar si x e y están conectados
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
    
    // Número de componentes conexas
    int count_components() {
        return components;
    }
    
    // Tamaño del conjunto que contiene x
    int component_size(int x) {
        int root = find(x);
        int size = 0;
        for (int i = 0; i < (int)parent.size(); i++) {
            if (find(i) == root) size++;
        }
        return size;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Test 1: Operaciones básicas
    cout << "=== UNION-FIND BÁSICO ===\n";
    int n = 10;
    UnionFind uf(n);
    
    cout << "Componentes iniciales: " << uf.count_components() << "\n";
    
    // Unir algunos nodos
    uf.unite(0, 1);
    uf.unite(2, 3);
    uf.unite(0, 2);  // ahora {0,1,2,3} están conectados
    uf.unite(5, 6);
    
    cout << "Después de 4 uniones: " << uf.count_components() << " componentes\n\n";
    
    // Test 2: Conectividad
    cout << "=== QUERIES DE CONECTIVIDAD ===\n";
    cout << "¿0 y 3 conectados? " << (uf.connected(0, 3) ? "SÍ" : "NO") << "\n";
    cout << "¿0 y 5 conectados? " << (uf.connected(0, 5) ? "SÍ" : "NO") << "\n";
    cout << "¿5 y 6 conectados? " << (uf.connected(5, 6) ? "SÍ" : "NO") << "\n\n";
    
    // Test 3: Componentes conexas
    cout << "=== COMPONENTES CONEXAS ===\n";
    map<int, vector<int>> components;
    for (int i = 0; i < n; i++) {
        components[uf.find(i)].push_back(i);
    }
    
    int comp_num = 1;
    for (auto& [root, nodes] : components) {
        cout << "Componente " << comp_num++ << ": {";
        for (int i = 0; i < (int)nodes.size(); i++) {
            cout << nodes[i];
            if (i < (int)nodes.size() - 1) cout << ", ";
        }
        cout << "}\n";
    }
    cout << "\n";
    
    // Test 4: Kruskal MST (aplicación típica)
    cout << "=== APLICACIÓN: KRUSKAL MST ===\n";
    
    struct Edge {
        int u, v, w;
        bool operator<(const Edge& e) const { return w < e.w; }
    };
    
    n = 6;
    vector<Edge> edges = {
        {0, 1, 4}, {0, 2, 3}, {1, 2, 1},
        {1, 3, 2}, {2, 3, 4}, {3, 4, 2},
        {4, 5, 6}
    };
    
    sort(edges.begin(), edges.end());
    
    UnionFind mst_uf(n);
    vector<Edge> mst;
    int total_weight = 0;
    
    for (auto& e : edges) {
        if (mst_uf.unite(e.u, e.v)) {
            mst.push_back(e);
            total_weight += e.w;
        }
    }
    
    cout << "Grafo con " << n << " nodos, " << edges.size() << " aristas\n";
    cout << "MST aristas:\n";
    for (auto& e : mst) {
        cout << "  " << e.u << " - " << e.v << " (peso " << e.w << ")\n";
    }
    cout << "Peso total MST: " << total_weight << "\n\n";
    
    // Test 5: Detección de ciclos
    cout << "=== DETECCIÓN DE CICLOS ===\n";
    UnionFind cycle_uf(4);
    vector<pair<int,int>> graph_edges = {{0,1}, {1,2}, {2,0}, {2,3}};
    
    for (auto [u, v] : graph_edges) {
        if (cycle_uf.connected(u, v)) {
            cout << "CICLO detectado al agregar arista " << u << "-" << v << "\n";
        } else {
            cycle_uf.unite(u, v);
            cout << "Arista " << u << "-" << v << " agregada (sin ciclo)\n";
        }
    }
    
    return 0;
}
