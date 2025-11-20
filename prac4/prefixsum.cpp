/*
 * PREFIX SUM - Sumas acumuladas
 * 
 * ¿Por qué O(n) temporal (precálculo)?
 *   Recorremos el array una vez para calcular prefix[i] = prefix[i-1] + arr[i-1].
 *   n iteraciones × O(1) cada una = O(n)
 * 
 * ¿Por qué O(1) temporal (query)?
 *   La suma de rango [l, r] es: prefix[r+1] - prefix[l]
 *   Solo 1 resta y 2 accesos a array → O(1) constante
 * 
 * ¿Por qué O(n) espacial?
 *   Array 'prefix' de tamaño n+1 para almacenar sumas acumuladas.
 *   prefix[i] = suma de arr[0..i-1]
 * 
 * EXPLICACIÓN INTUITIVA:
 *   Imagina que tienes las distancias parciales de un viaje: [3km, 5km, 2km, 7km].
 *   Las distancias acumuladas son: [0, 3, 8, 10, 17].
 *   Para saber la distancia del tramo 1→3: 10km - 3km = 7km (¡sin sumar de nuevo!).
 *   Prefix sum te da "distancia total hasta i" en O(1).
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Prefix Sum 1D
class PrefixSum1D {
private:
    vector<ll> prefix;
    int n;
    
public:
    PrefixSum1D(vector<ll>& arr) {
        n = arr.size();
        prefix.assign(n + 1, 0);
        
        // Precálculo O(n)
        for (int i = 1; i <= n; i++) {
            prefix[i] = prefix[i-1] + arr[i-1];
        }
    }
    
    // Query O(1): suma [l, r] (0-indexed)
    ll query(int l, int r) {
        return prefix[r+1] - prefix[l];
    }
    
    // Suma total
    ll total() {
        return prefix[n];
    }
};

// Prefix Sum 2D (matriz)
class PrefixSum2D {
private:
    vector<vector<ll>> prefix;
    int n, m;
    
public:
    PrefixSum2D(vector<vector<ll>>& mat) {
        n = mat.size();
        m = mat[0].size();
        prefix.assign(n+1, vector<ll>(m+1, 0));
        
        // Precálculo O(n*m)
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                prefix[i][j] = mat[i-1][j-1]
                             + prefix[i-1][j]
                             + prefix[i][j-1]
                             - prefix[i-1][j-1];
            }
        }
    }
    
    // Query O(1): suma rectángulo [r1,c1] a [r2,c2] (0-indexed)
    ll query(int r1, int c1, int r2, int c2) {
        r1++; c1++; r2++; c2++;  // convertir a 1-indexed
        
        return prefix[r2][c2]
             - prefix[r1-1][c2]
             - prefix[r2][c1-1]
             + prefix[r1-1][c1-1];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Test 1: Prefix Sum 1D
    cout << "=== PREFIX SUM 1D ===\n";
    vector<ll> arr = {3, 5, 2, 7, 1, 4};
    PrefixSum1D ps1d(arr);
    
    cout << "Array: [3, 5, 2, 7, 1, 4]\n";
    cout << "Suma [0, 3]: " << ps1d.query(0, 3) << " (esperado: 3+5+2+7=17)\n";
    cout << "Suma [2, 4]: " << ps1d.query(2, 4) << " (esperado: 2+7+1=10)\n";
    cout << "Suma [1, 5]: " << ps1d.query(1, 5) << " (esperado: 5+2+7+1+4=19)\n";
    cout << "Suma total: " << ps1d.total() << "\n\n";
    
    // Test 2: Prefix Sum 2D
    cout << "=== PREFIX SUM 2D ===\n";
    vector<vector<ll>> mat = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    PrefixSum2D ps2d(mat);
    
    cout << "Matriz 3x4:\n";
    for (auto& row : mat) {
        for (ll x : row) cout << setw(3) << x;
        cout << "\n";
    }
    
    cout << "\nSuma rectángulo [0,0] a [1,1]: " << ps2d.query(0, 0, 1, 1) 
         << " (esperado: 1+2+5+6=14)\n";
    cout << "Suma rectángulo [1,1] a [2,3]: " << ps2d.query(1, 1, 2, 3) 
         << " (esperado: 6+7+8+10+11+12=54)\n";
    cout << "Suma completa [0,0] a [2,3]: " << ps2d.query(0, 0, 2, 3) 
         << " (esperado: 78)\n";
    
    return 0;
}
