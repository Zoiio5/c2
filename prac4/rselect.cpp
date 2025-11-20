#include <bits/stdc++.h>
using namespace std;

/*
 * RSELECT - Randomized Selection
 * Encuentra el k-ésimo elemento más pequeño usando pivotes aleatorios.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(n) promedio?
 *   - Con pivote aleatorio, esperamos dividir en mitades aproximadas
 *   - Trabajo: n + n/2 + n/4 + ... = n(1 + 1/2 + 1/4 + ...) = 2n = O(n)
 *   - Serie geométrica converge a constante
 *   - Peor caso O(n²): si siempre elige peor pivote (muy raro con aleatorio)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Con pivote aleatorio, en promedio particiona el arreglo de forma balanceada.
 *   Recurrencia: T(n) = T(n/2) + O(n) = O(n) promedio. Peor caso O(n²) si
 *   siempre eliges mal pivote.
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(log n) promedio?
 *   - Cada recursión usa espacio en el stack
 *   - Con buen pivote: profundidad esperada log(n)
 *   - Peor caso O(n): si pivote siempre es malo (árbol degenerado)
 *   - No crea copias, modifica arreglo in-place
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Stack de recursión con pivotes balanceados: profundidad log(n) promedio.
 *   Peor caso: O(n) si degenerado.
 */

// RSelect - Selección aleatoria del k-ésimo elemento
int partition(vector<int>& arr, int l, int r) {
    int pivotIdx = l + rand() % (r - l + 1);
    swap(arr[pivotIdx], arr[r]);
    int pivot = arr[r];
    int i = l - 1;
    
    for (int j = l; j < r; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[r]);
    return i + 1;
}

int rselect(vector<int>& arr, int l, int r, int k) {
    if (l == r) return arr[l];
    
    int pivotIdx = partition(arr, l, r);
    int rank = pivotIdx - l + 1;
    
    if (rank == k) return arr[pivotIdx];
    else if (k < rank) return rselect(arr, l, pivotIdx - 1, k);
    else return rselect(arr, pivotIdx + 1, r, k - rank);
}

int main() {
    srand(time(0));
    
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    int result = rselect(arr, 0, n - 1, k);
    
    cout << "El " << k << "-ésimo elemento más pequeño es: " << result << endl;
    
    return 0;
}
