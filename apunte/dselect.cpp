#include <bits/stdc++.h>
using namespace std;

/*
 * DSELECT - Deterministic Selection (Mediana de Medianas)
 * Garantiza O(n) en peor caso usando pivote inteligente.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(n) garantizado?
 *   - Divide en grupos de 5: O(n/5) medianas
 *   - Encuentra mediana de medianas recursivamente: T(n/5)
 *   - Particiona con ese pivote: O(n)
 *   - Garantiza descartar 30% mínimo: T(0.7n) en peor caso
 *   - Recurrencia: T(n) = T(n/5) + T(0.7n) + O(n) → O(n)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Median-of-medians garantiza pivote decente. Divide en grupos de 5,
 *   encuentra medianas recursivamente, usa esa mediana como pivote.
 *   Recurrencia: T(n) = T(n/5) + T(7n/10) + O(n) = O(n) garantizado
 *   (Teorema Maestro).
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(n)?
 *   - Stack de recursión: en peor caso O(n) de profundidad
 *   - T(n) = T(n/5) + T(0.7n) puede llevar a profundidad lineal
 *   - Grupos de 5 se procesan in-place
 *   - No crea copias grandes del arreglo
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Stack de recursión: T(n) = T(n/5) + T(0.7n) tiene profundidad O(n) en
 *   el peor caso (no es log n porque suma de fracciones 1/5 + 0.7 = 0.9 < 1
 *   pero acumula). O(n) espacial.
 */

// DSelect - Selección determinista (Mediana de Medianas)
int partition(vector<int>& arr, int l, int r, int pivotIdx) {
    int pivot = arr[pivotIdx];
    swap(arr[pivotIdx], arr[r]);
    int storeIdx = l;
    
    for (int i = l; i < r; i++) {
        if (arr[i] < pivot) {
            swap(arr[i], arr[storeIdx]);
            storeIdx++;
        }
    }
    swap(arr[storeIdx], arr[r]);
    return storeIdx;
}

int findMedian(vector<int>& arr, int l, int r) {
    sort(arr.begin() + l, arr.begin() + r + 1);
    return l + (r - l) / 2;
}

int medianOfMedians(vector<int>& arr, int l, int r) {
    if (r - l < 5) return findMedian(arr, l, r);
    
    for (int i = l; i <= r; i += 5) {
        int subRight = min(i + 4, r);
        int medianIdx = findMedian(arr, i, subRight);
        swap(arr[medianIdx], arr[l + (i - l) / 5]);
    }
    
    int mid = l + (r - l) / 10;
    return medianOfMedians(arr, l, l + (r - l) / 5);
}

int dselect(vector<int>& arr, int l, int r, int k) {
    if (l == r) return arr[l];
    
    int pivotIdx = medianOfMedians(arr, l, r);
    pivotIdx = partition(arr, l, r, pivotIdx);
    
    int rank = pivotIdx - l + 1;
    
    if (rank == k) return arr[pivotIdx];
    else if (k < rank) return dselect(arr, l, pivotIdx - 1, k);
    else return dselect(arr, pivotIdx + 1, r, k - rank);
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    int result = dselect(arr, 0, n - 1, k);
    
    cout << "El " << k << "-ésimo elemento más pequeño es: " << result << endl;
    
    return 0;
}
