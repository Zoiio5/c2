#include <bits/stdc++.h>
using namespace std;

/*
 * POWER SET - Generación de Subconjuntos (Máscara Binaria)
 * Genera todos los 2ⁿ subconjuntos.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(n·2ⁿ)?
 *   - Hay exactamente 2ⁿ subconjuntos (cada elemento in/out)
 *   - Por cada máscara (2ⁿ iteraciones), revisa n bits
 *   - Total: 2ⁿ × n = O(n·2ⁿ)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Hay exactamente 2ⁿ subconjuntos (cada elemento puede estar o no estar).
 *   Por cada máscara de bits, revisas n bits para construir el subset.
 *   Total: 2ⁿ × n.
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(n·2ⁿ)?
 *   - Almacena 2ⁿ subconjuntos
 *   - Tamaño promedio de cada subset: n/2
 *   - Total: 2ⁿ × n/2 = O(n·2ⁿ)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Almacenas 2ⁿ subconjuntos, cada uno con tamaño promedio n/2.
 *   Total: 2ⁿ × n/2 ≈ n·2ⁿ.
 */

// Generación de Subconjuntos usando Máscara Binaria
vector<vector<int>> generateSubsets(vector<int>& arr) {
    int n = arr.size();
    vector<vector<int>> subsets;
    
    // 2^n subconjuntos posibles
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> subset;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                subset.push_back(arr[i]);
            }
        }
        subsets.push_back(subset);
    }
    
    return subsets;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    vector<vector<int>> subsets = generateSubsets(arr);
    
    cout << "Total de subconjuntos: " << subsets.size() << endl;
    cout << "Subconjuntos:" << endl;
    
    for (auto& subset : subsets) {
        cout << "{ ";
        for (int x : subset) cout << x << " ";
        cout << "}" << endl;
    }
    
    return 0;
}
