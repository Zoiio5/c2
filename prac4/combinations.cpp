#include <bits/stdc++.h>
using namespace std;

/*
 * COMBINATIONS - Combinaciones de tamaño K (Backtracking)
 * Genera C(n,k) combinaciones.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(C(n,k)·k)?
 *   - Número de combinaciones: C(n,k) = n!/(k!(n-k)!)
 *   - Por cada combinación, copiar k elementos: O(k)
 *   - Total: C(n,k) × k
 *   - Peor caso cuando k=n/2: C(n,n/2) ≈ 2ⁿ/√n
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Genera todas las C(n,k) = n!/(k!(n-k)!) combinaciones. Copiar cada
 *   combinación cuesta O(k). Total: C(n,k) × k.
 *   Peor caso: k = n/2, donde C(n,n/2) es máximo.
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(k)?
 *   - Stack de recursión: profundidad k
 *   - Vector curr: guarda k elementos en construcción
 *   - No cuenta almacenar resultado (output)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Vector curr: k elementos. Stack de recursión: profundidad k.
 *   Total: O(k).
 */

// Combinaciones de tamaño K
void generateCombinations(vector<int>& arr, int k, int start, vector<int>& curr, vector<vector<int>>& result) {
    if (curr.size() == k) {
        result.push_back(curr);
        return;
    }
    
    for (int i = start; i < arr.size(); i++) {
        curr.push_back(arr[i]);
        generateCombinations(arr, k, i + 1, curr, result);
        curr.pop_back();
    }
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    vector<vector<int>> combinations;
    vector<int> curr;
    generateCombinations(arr, k, 0, curr, combinations);
    
    cout << "Total de combinaciones C(" << n << "," << k << "): " << combinations.size() << endl;
    cout << "Combinaciones:" << endl;
    
    for (auto& comb : combinations) {
        cout << "{ ";
        for (int x : comb) cout << x << " ";
        cout << "}" << endl;
    }
    
    return 0;
}
