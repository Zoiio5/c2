#include <bits/stdc++.h>
using namespace std;

/*
 * BUBBLE SORT
 * Intercambia repetidamente elementos adyacentes fuera de orden.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(n²)?
 *   - Primera pasada: compara n-1 pares
 *   - Segunda pasada: compara n-2 pares
 *   - Total: (n-1) + (n-2) + ... + 1 = O(n²)
 *   - Mejor caso O(n): con flag 'swapped', si ya ordenado termina en una pasada
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Imagina ordenar cartas comparando pares adyacentes. En la primera pasada
 *   comparas n-1 pares, en la segunda n-2, y así: (n-1) + (n-2) + ... + 1 =
 *   n(n-1)/2 ≈ n²/2 comparaciones. Es como hacer una burbuja que sube n veces,
 *   cada vez más corta.
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(1)?
 *   - Solo usa flag 'swapped' y contadores i, j
 *   - Intercambia elementos en el mismo arreglo
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Solo necesitas una variable temporal para intercambiar dos elementos y un
 *   flag para saber si hubo cambios. Todo el ordenamiento ocurre en el mismo
 *   arreglo, sin copias.
 */

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    bubbleSort(arr);
    
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    return 0;
}
