#include <bits/stdc++.h>
using namespace std;

/*
 * PERMUTATIONS - Generación de Permutaciones (Backtracking)
 * Genera todas las n! permutaciones.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(n·n!)?
 *   - Hay exactamente n! permutaciones de n elementos
 *   - Por cada permutación, copiar el vector: O(n)
 *   - Total: n! × n = O(n·n!)
 *   - Árbol de decisión: nivel i tiene (n-i+1) opciones → n! hojas
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Hay n! permutaciones de n elementos. Por cada permutación, copiarla al
 *   resultado cuesta O(n). Total: n! × n = n·n!.
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(n)?
 *   - Stack de recursión: profundidad n
 *   - Vector arr modificado in-place: O(n)
 *   - No cuenta almacenar resultado (eso es output)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Vector arr: n elementos. Stack de recursión: profundidad n (un nivel
 *   por posición). Total: O(n) (no contamos el output que almacena las n!
 *   permutaciones).
 */

// Generación de Permutaciones
void generatePermutations(vector<int>& arr, int l, int r, vector<vector<int>>& result) {
    if (l == r) {
        result.push_back(arr);
        return;
    }
    
    for (int i = l; i <= r; i++) {
        swap(arr[l], arr[i]);
        generatePermutations(arr, l + 1, r, result);
        swap(arr[l], arr[i]);  // backtrack
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    vector<vector<int>> permutations;
    generatePermutations(arr, 0, n - 1, permutations);
    
    cout << "Total de permutaciones: " << permutations.size() << endl;
    cout << "Permutaciones:" << endl;
    
    for (auto& perm : permutations) {
        for (int x : perm) cout << x << " ";
        cout << endl;
    }
    
    return 0;
}
