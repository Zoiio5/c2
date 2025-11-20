#include <bits/stdc++.h>
using namespace std;

/*
 * INSERTION SORT
 * Construye el arreglo ordenado insertando elementos uno a uno.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(n²) promedio?
 *   - Para cada elemento (n iteraciones)
 *   - Lo compara con los anteriores hasta encontrar su lugar (promedio n/2)
 *   - Total: n × n/2 = n²/2 = O(n²)
 *   - Mejor caso O(n): si ya está ordenado, solo hace n comparaciones
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Como ordenar cartas en tu mano: tomas una carta nueva y la insertas en
 *   su posición correcta entre las ya ordenadas. En promedio, cada carta se
 *   compara con la mitad de las anteriores (n/2). Para n cartas: n × n/2 = n²/2.
 *   MEJOR CASO O(n): Si ya está ordenado, solo verificas una vez cada elemento.
 *   PEOR CASO O(n²): Si está al revés, cada elemento debe retroceder hasta el inicio.
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(1)?
 *   - Inserta elementos moviéndolos en el mismo arreglo
 *   - Solo usa variable 'key' para guardar elemento temporal
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Solo necesitas una variable 'key' para guardar el elemento que estás
 *   insertando. Todo ocurre en el arreglo original.
 */

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    insertionSort(arr);
    
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    return 0;
}
