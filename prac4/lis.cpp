/*
 * LIS - Longest Increasing Subsequence (Subsecuencia creciente más larga)
 * 
 * ¿Por qué O(n log n) temporal?
 *   - Iteramos n elementos: O(n)
 *   - Para cada elemento hacemos binary search en dp (tamaño ≤ n): O(log n)
 *   - Total: n × log(n) = O(n log n)
 * 
 * ¿Por qué O(n) espacial?
 *   - Array dp guarda la mejor subsecuencia de cada longitud: tamaño ≤ n
 *   - Arrays auxiliares (parent, pos) para reconstrucción: O(n)
 * 
 * EXPLICACIÓN INTUITIVA:
 *   Queremos la subsecuencia creciente más larga (no consecutiva).
 *   Ejemplo: [3,1,5,2,4] → LIS = [1,2,4] longitud 3
 *   
 *   Array dp[i] = el menor elemento que termina una subsecuencia de longitud i+1.
 *   Si llega un elemento x: buscamos dónde insertarlo (binary search).
 *   Si x es mayor que todos → extendemos LIS. Si no → reemplazamos un elemento
 *   para mantener dp[] lo más pequeño posible (greedy).
 */

#include <bits/stdc++.h>
using namespace std;

// LIS O(n log n) - solo longitud
int lis_length(vector<int>& arr) {
    vector<int> dp;
    
    for (int x : arr) {
        auto it = lower_bound(dp.begin(), dp.end(), x);
        
        if (it == dp.end()) {
            dp.push_back(x);  // x es mayor que todos → extender
        } else {
            *it = x;  // reemplazar para mantener dp[] pequeño
        }
    }
    
    return dp.size();
}

// LIS O(n log n) - con reconstrucción de subsecuencia
pair<int, vector<int>> lis_reconstruct(vector<int>& arr) {
    int n = arr.size();
    vector<int> dp, parent(n, -1), pos(n);
    
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(dp.begin(), dp.end(), arr[i]);
        int idx = it - dp.begin();
        
        if (it == dp.end()) {
            dp.push_back(arr[i]);
        } else {
            *it = arr[i];
        }
        
        pos[i] = idx;  // posición en dp
        
        // Buscar padre (elemento anterior en LIS)
        if (idx > 0) {
            for (int j = i - 1; j >= 0; j--) {
                if (pos[j] == idx - 1 && arr[j] < arr[i]) {
                    parent[i] = j;
                    break;
                }
            }
        }
    }
    
    // Reconstruir subsecuencia
    vector<int> result;
    int curr = -1;
    
    // Encontrar último elemento del LIS
    for (int i = n - 1; i >= 0; i--) {
        if (pos[i] == (int)dp.size() - 1) {
            curr = i;
            break;
        }
    }
    
    // Backtrack usando parent[]
    while (curr != -1) {
        result.push_back(arr[curr]);
        curr = parent[curr];
    }
    
    reverse(result.begin(), result.end());
    return {dp.size(), result};
}

// LIS variante: subsecuencia decreciente más larga (LDS)
int lds_length(vector<int>& arr) {
    vector<int> dp;
    
    for (int x : arr) {
        // Usamos upper_bound (en vez de lower_bound) y buscamos >= x
        auto it = lower_bound(dp.begin(), dp.end(), x, greater<int>());
        
        if (it == dp.end()) {
            dp.push_back(x);
        } else {
            *it = x;
        }
    }
    
    return dp.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Test 1: LIS longitud
    vector<int> arr = {3, 1, 5, 2, 4, 6, 3, 7};
    cout << "=== LIS LENGTH ===\n";
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";
    
    int len = lis_length(arr);
    cout << "Longitud LIS: " << len << "\n\n";
    
    // Test 2: LIS con reconstrucción
    cout << "=== LIS RECONSTRUCT ===\n";
    auto [length, lis_seq] = lis_reconstruct(arr);
    cout << "Longitud: " << length << "\n";
    cout << "Subsecuencia: ";
    for (int x : lis_seq) cout << x << " ";
    cout << "\n\n";
    
    // Test 3: LDS (decreciente)
    cout << "=== LDS (Longest Decreasing Subsequence) ===\n";
    int lds_len = lds_length(arr);
    cout << "Longitud LDS: " << lds_len << "\n\n";
    
    // Test 4: Caso especial - array ordenado
    vector<int> sorted = {1, 2, 3, 4, 5, 6, 7, 8};
    cout << "=== ARRAY ORDENADO ===\n";
    cout << "Array: ";
    for (int x : sorted) cout << x << " ";
    cout << "\n";
    cout << "LIS: " << lis_length(sorted) << " (debe ser n=" << sorted.size() << ")\n";
    
    return 0;
}
