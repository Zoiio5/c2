/*
 * KRUSKAL - MST con Union-Find optimizado
 * Construye árbol de expansión mínima ordenando aristas.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(E log E)?
 *   - Ordenar E aristas: O(E log E)
 *   - Por cada arista, hacer find() y union(): O(α(V)) ≈ O(1) con path compression
 *   - Procesar E aristas: E × α(V) ≈ O(E)
 *   - Dominante: O(E log E) del sort
 *   - Como V ≤ E en grafos conexos: O(E log E) = O(E log V)
 *   - α(V) = inversa de Ackermann (prácticamente constante, ≤ 4)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Ordenar E aristas por peso: E log E. Procesar cada arista con Union-Find:
 *   E × α(V). Como α(V) ≤ 4 en la práctica (función Ackermann inversa),
 *   se considera casi constante. Dominante: O(E log E) del ordenamiento.
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(V + E)?
 *   - Union-Find: arrays parent y rank de tamaño V
 *   - Vector de aristas (entrada): O(E)
 *   - Vector MST result: O(V-1) = O(V)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Vector de aristas: E elementos. Union-Find (parent, rank): 2V elementos.
 *   Total: O(V+E).
 */
#include <bits/stdc++.h>
using namespace std;

struct Arista {
    int u, v;
    long long peso;
    
    // Constructor para facilitar inicialización
    Arista(int _u, int _v, long long _peso) : u(_u), v(_v), peso(_peso) {}
};

// Estructura Union-Find optimizada
struct UnionFind {
    vector<int> padre;
    vector<int> rango;
    int componentes; // Número de componentes conexas
    
    // Inicializar estructura
    UnionFind(int n) {
        padre.resize(n);
        rango.resize(n, 0);
        componentes = n;
        for (int i = 0; i < n; i++) {
            padre[i] = i;
        }
    }
    
    // FIND con compresión de caminos
    // Complejidad: O(α(n)) amortizado
    int find(int x) {
        if (padre[x] != x) {
            padre[x] = find(padre[x]); // Compresión: conecta directamente a la raíz
        }
        return padre[x];
    }
    
    // UNION by rank (unión por rango)
    // Complejidad: O(α(n)) amortizado
    bool unir(int x, int y) {
        int px = find(x);
        int py = find(y);
        
        if (px == py) return false; // Ya están en el mismo conjunto
        
        // Une el árbol más pequeño al más grande
        if (rango[px] < rango[py]) {
            padre[px] = py;
        } else if (rango[px] > rango[py]) {
            padre[py] = px;
        } else {
            padre[py] = px;
            rango[px]++; // Incrementa rango solo si son iguales
        }
        
        componentes--;
        return true;
    }
    
    // Verifica si dos nodos están conectados
    bool conectados(int x, int y) {
        return find(x) == find(y);
    }
    
    // Retorna el número de componentes conexas
    int numComponentes() {
        return componentes;
    }
};

// Comparador para ordenar aristas por peso
bool compararArista(const Arista& a, const Arista& b) {
    return a.peso < b.peso;
}

// ALGORITMO DE KRUSKAL
// Retorna el MST y el peso total
pair<vector<Arista>, long long> kruskal(int n, vector<Arista>& aristas) {
    // Inicializar Union-Find
    UnionFind uf(n);
    
    // Ordenar aristas por peso (menor a mayor)
    sort(aristas.begin(), aristas.end(), compararArista);
    
    vector<Arista> mst;
    long long pesoTotal = 0;
    
    // Iterar sobre las aristas ordenadas
    for (const auto& arista : aristas) {
        // Si los vértices no están conectados, añadir arista al MST
        if (uf.find(arista.u) != uf.find(arista.v)) {
            mst.push_back(arista);
            pesoTotal += arista.peso;
            uf.unir(arista.u, arista.v);
            
            // Optimización: terminar cuando tenemos V-1 aristas
            if ((int)mst.size() == n - 1) break;
        }
    }
    
    return {mst, pesoTotal};
}

// Versión alternativa que retorna si el grafo es conexo
pair<vector<Arista>, long long> kruskalConValidacion(int n, vector<Arista>& aristas, bool& esConexo) {
    UnionFind uf(n);
    sort(aristas.begin(), aristas.end(), compararArista);
    
    vector<Arista> mst;
    long long pesoTotal = 0;
    
    for (const auto& arista : aristas) {
        if (uf.find(arista.u) != uf.find(arista.v)) {
            mst.push_back(arista);
            pesoTotal += arista.peso;
            uf.unir(arista.u, arista.v);
            
            if ((int)mst.size() == n - 1) break;
        }
    }
    
    // Verificar si el grafo es conexo (todas las componentes unidas)
    esConexo = (uf.numComponentes() == 1);
    
    return {mst, pesoTotal};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<Arista> aristas;
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        aristas.push_back(Arista(u, v, w));
    }
    
    auto [mst, peso] = kruskal(n, aristas);
    cout << "Peso MST: " << peso << endl;
    cout << "Aristas:" << endl;
    for (auto& e : mst) {
        cout << e.u << " - " << e.v << " (" << e.peso << ")" << endl;
    }
    return 0;
}
