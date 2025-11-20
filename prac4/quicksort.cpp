/*
 * QUICKSORT - Divide y Conquistar
 * Ordena dividiendo el arreglo en particiones alrededor de un pivote.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(n log n)?
 *   - En cada nivel hacemos O(n) comparaciones (partition)
 *   - Con buen pivote, dividimos el problema en 2 mitades: log(n) niveles
 *   - Total: n comparaciones × log(n) niveles = O(n log n)
 *   - Peor caso O(n²): pivote malo crea árbol degenerado de n niveles
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Divide y conquista usando un pivote. En cada nivel del árbol de recursión
 *   procesas todos los n elementos (particionándolos). Con un buen pivote
 *   (mediana), divides el problema a la mitad cada vez, creando log(n) niveles.
 *   Total: n trabajo × log(n) niveles = n log n.
 *   PEOR CASO O(n²): Si siempre eliges el peor pivote (mínimo o máximo),
 *   creas un árbol degenerado con n niveles en lugar de log(n).
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(log n)?
 *   - Cada llamada recursiva usa espacio en el stack
 *   - Con buen pivote: profundidad log(n)
 *   - No crea copias del arreglo (ordena in-place)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Cada llamada recursiva usa espacio en el stack. Con pivotes balanceados,
 *   la profundidad es log(n). No crea copias del arreglo (ordena in-place),
 *   solo guarda índices y posiciones del pivote en cada nivel.
 */
#include <bits/stdc++.h>
using namespace std;

// Función de partición - Lomuto partition scheme
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// QuickSort recursivo
void quicksort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Hoare partition scheme (alternativa más eficiente)
int partitionHoare(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low - 1;
    int j = high + 1;
    
    while (true) {
        do { i++; } while (arr[i] < pivot);
        do { j--; } while (arr[j] > pivot);
        
        if (i >= j) return j;
        
        swap(arr[i], arr[j]);
    }
}

void quicksortHoare(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionHoare(arr, low, high);
        quicksortHoare(arr, low, pi);
        quicksortHoare(arr, pi + 1, high);
    }
}

// QuickSort con pivote aleatorio (evita peor caso)
int partitionRandom(vector<int>& arr, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    return partition(arr, low, high);
}

void quicksortRandom(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionRandom(arr, low, high);
        quicksortRandom(arr, low, pi - 1);
        quicksortRandom(arr, pi + 1, high);
    }
}

// Función auxiliar para imprimir arrays
void printArray(const vector<int>& arr, const string& label) {
    cout << label << ": ";
    for (int x : arr) cout << x << " ";
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    srand(time(0));
    
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    quicksort(arr, 0, arr.size() - 1);
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    return 0;
}

/*
COMPLEJIDAD:
- Temporal Promedio: O(n log n)
- Temporal Peor Caso: O(n²) cuando el array está ordenado y pivote es primer/último elemento
- Espacial: O(log n) por la pila de recursión

VENTAJAS:
- In-place (no requiere espacio adicional significativo)
- Rápido en la práctica
- Cache-friendly

VARIANTES:
- Lomuto: Más simple, pivote al final
- Hoare: Más eficiente, menos swaps
- Random: Evita peor caso
*/
