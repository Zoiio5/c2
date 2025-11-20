#include <bits/stdc++.h>
using namespace std;

/*
 * TSP - Travelling Salesman Problem (Backtracking con poda)
 * Encuentra el ciclo más corto visitando todas las ciudades.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(n!) peor caso?
 *   - Sin poda: prueba todas las permutaciones de n ciudades = n!
 *   - Con poda: descarta ramas cuando costo parcial ≥ mejor solución
 *   - En práctica: mucho mejor que n! pero sigue exponencial
 *   - Para n>15, usar DP bitmask O(n²·2ⁿ) o heurísticas
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Sin poda, prueba todas las permutaciones de n ciudades: n!. Con poda
 *   (descartando rutas cuando costo parcial ≥ mejor solución), mejora
 *   considerablemente pero sigue siendo exponencial. Para n>15 es inviable;
 *   mejor usar DP con bitmask O(n²·2ⁿ) o heurísticas.
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(n)?
 *   - Vector path: guarda n ciudades
 *   - Vector visited: n booleanos
 *   - Stack de recursión: profundidad n
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Vector path: n ciudades. Vector visited: n booleanos. Stack de recursión:
 *   profundidad n. Total: O(n).
 */

// TSP usando Backtracking
int n;
int dist[20][20];
int minCost = INT_MAX;
vector<int> bestPath;

void tspBacktrack(vector<int>& path, vector<bool>& visited, int currCost, int count) {
    if (count == n) {
        // Regresar al inicio
        int totalCost = currCost + dist[path.back()][path[0]];
        if (totalCost < minCost) {
            minCost = totalCost;
            bestPath = path;
        }
        return;
    }
    
    int curr = path.back();
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            // Poda: si ya superamos el mínimo, no continuar
            if (currCost + dist[curr][i] >= minCost) continue;
            
            visited[i] = true;
            path.push_back(i);
            tspBacktrack(path, visited, currCost + dist[curr][i], count + 1);
            path.pop_back();
            visited[i] = false;
        }
    }
}

int main() {
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
        }
    }
    
    vector<bool> visited(n, false);
    vector<int> path;
    
    visited[0] = true;
    path.push_back(0);
    
    tspBacktrack(path, visited, 0, 1);
    
    cout << "Costo mínimo: " << minCost << endl;
    cout << "Camino: ";
    for (int x : bestPath) cout << x << " ";
    cout << bestPath[0] << endl;
    
    return 0;
}
