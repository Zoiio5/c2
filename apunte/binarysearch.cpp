/*
 * BINARY SEARCH - Búsqueda binaria
 * 
 * ¿Por qué O(log n) temporal?
 *   En cada iteración dividimos el espacio de búsqueda a la mitad.
 *   T(n) = T(n/2) + O(1) → Por teorema maestro: O(log n)
 *   Ejemplo: n=1024 → log₂(1024) = 10 comparaciones máximo
 * 
 * ¿Por qué O(1) espacial?
 *   Solo usamos 3 variables (l, r, mid) independiente del tamaño del array.
 *   No hay recursión (versión iterativa), no hay arrays auxiliares.
 * 
 * EXPLICACIÓN INTUITIVA:
 *   Imagina buscar una palabra en el diccionario. En vez de leer página
 *   por página (O(n)), abres el libro por la mitad y decides si buscar
 *   en la mitad izquierda o derecha. Repites hasta encontrar la palabra.
 *   Cada decisión elimina la mitad de las opciones → log₂(n) pasos.
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Búsqueda binaria estándar - retorna índice o -1
int binary_search(vector<int>& arr, int target) {
    int l = 0, r = arr.size() - 1;
    
    while (l <= r) {
        int mid = l + (r - l) / 2;  // evita overflow
        
        if (arr[mid] == target) 
            return mid;
        
        if (arr[mid] < target) 
            l = mid + 1;  // buscar en mitad derecha
        else 
            r = mid - 1;  // buscar en mitad izquierda
    }
    
    return -1;  // no encontrado
}

// Lower bound: primer elemento >= target
int lower_bound_custom(vector<int>& arr, int target) {
    int l = 0, r = arr.size();
    
    while (l < r) {
        int mid = l + (r - l) / 2;
        
        if (arr[mid] < target) 
            l = mid + 1;
        else 
            r = mid;
    }
    
    return l;  // índice del primer >= target
}

// Upper bound: primer elemento > target
int upper_bound_custom(vector<int>& arr, int target) {
    int l = 0, r = arr.size();
    
    while (l < r) {
        int mid = l + (r - l) / 2;
        
        if (arr[mid] <= target) 
            l = mid + 1;
        else 
            r = mid;
    }
    
    return l;  // índice del primer > target
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Test 1: Binary Search estándar
    vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15};
    int target = 7;
    
    int idx = binary_search(arr, target);
    cout << "Binary Search: " << target << " encontrado en índice " << idx << "\n";
    
    // Test 2: Lower/Upper bound
    target = 7;
    int lb = lower_bound_custom(arr, target);
    int ub = upper_bound_custom(arr, target);
    
    cout << "Lower bound de " << target << ": índice " << lb << " (valor " << arr[lb] << ")\n";
    cout << "Upper bound de " << target << ": índice " << ub << " (valor " << arr[ub] << ")\n";
    
    // Test 3: Contar elementos en rango [5, 11]
    int range_l = 5, range_r = 11;
    int count = upper_bound_custom(arr, range_r) - lower_bound_custom(arr, range_l);
    cout << "Elementos en rango [" << range_l << ", " << range_r << "]: " << count << "\n";
    
    // Test 4: STL equivalente
    auto it_lb = lower_bound(arr.begin(), arr.end(), 7);
    auto it_ub = upper_bound(arr.begin(), arr.end(), 7);
    cout << "\nSTL lower_bound: " << (it_lb - arr.begin()) << "\n";
    cout << "STL upper_bound: " << (it_ub - arr.begin()) << "\n";
    
    return 0;
}
