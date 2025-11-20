#include <bits/stdc++.h>
using namespace std;

/*
 * SELECTION SORT
 * Encuentra iterativamente el mínimo y lo coloca en su posición.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(n²)?
 *   - Primer elemento: compara con n-1 elementos
 *   - Segundo elemento: compara con n-2 elementos
 *   - Total: (n-1) + (n-2) + ... + 1 = n(n-1)/2 ≈ n²/2 = O(n²)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   En cada iteración buscas el mínimo entre los elementos restantes.
 *   Primera búsqueda: n-1 comparaciones, segunda: n-2, tercera: n-3...
 *   Total: (n-1) + (n-2) + ... + 1 = n²/2 comparaciones. Aunque siempre
 *   hace el mismo trabajo (no mejora con datos ordenados), es más eficiente
 *   en escrituras que Bubble Sort.
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(1)?
 *   - Solo usa variables auxiliares (minIdx, i, j)
 *   - Intercambia elementos directamente en el arreglo original
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Solo guardas el índice del mínimo actual. El intercambio usa una variable
 *   temporal. Ordena in-place sin memoria extra.
 */

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    selectionSort(arr);
    
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    return 0;
}
