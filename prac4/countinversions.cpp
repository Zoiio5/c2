#include <bits/stdc++.h>
using namespace std;

/*
 * COUNTING INVERSIONS (Sort-and-CountInv)
 * Cuenta pares (i,j) donde i < j pero arr[i] > arr[j] usando MergeSort.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(n log n)?
 *   - Divide el arreglo recursivamente: log(n) niveles (como árbol binario)
 *   - En cada nivel, procesa todos los n elementos al hacer merge
 *   - Total: n trabajo × log(n) niveles = O(n log n)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Divide el arreglo recursivamente hasta tener elementos individuales
 *   (log n niveles de división). Luego hace merge de las mitades ordenadas,
 *   comparando y contando inversiones. En cada nivel procesa todos los n
 *   elementos. Total: n × log n.
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(n)?
 *   - En merge, crea arrays left y right que suman O(n) elementos
 *   - Stack de recursión: log(n) llamadas, pero memoria se reutiliza
 *   - Dominante: arrays temporales O(n)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Durante el merge, crea arrays temporales 'left' y 'right' que juntos
 *   suman n elementos. Aunque el stack de recursión tiene profundidad log(n),
 *   la memoria dominante son estos arrays temporales: O(n).
 */

// Conteo de inversiones usando MergeSort
long long mergeAndCount(vector<int>& arr, int l, int m, int r) {
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);
    
    int i = 0, j = 0, k = l;
    long long inv_count = 0;
    
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
            inv_count += (left.size() - i);
        }
    }
    
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
    
    return inv_count;
}

long long mergeSortAndCount(vector<int>& arr, int l, int r) {
    long long inv_count = 0;
    if (l < r) {
        int m = l + (r - l) / 2;
        inv_count += mergeSortAndCount(arr, l, m);
        inv_count += mergeSortAndCount(arr, m + 1, r);
        inv_count += mergeAndCount(arr, l, m, r);
    }
    return inv_count;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    long long inversions = mergeSortAndCount(arr, 0, n - 1);
    
    cout << "Inversiones: " << inversions << endl;
    cout << "Arreglo ordenado: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    return 0;
}
