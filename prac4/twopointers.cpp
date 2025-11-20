/*
 * TWO POINTERS - Técnica de dos punteros
 * 
 * ¿Por qué O(n) temporal?
 *   Cada puntero (l, r) recorre el array a lo sumo una vez.
 *   l avanza: O(n), r avanza: O(n) → total O(2n) = O(n)
 *   Nunca retrocedemos ambos punteros, solo avanzamos.
 * 
 * ¿Por qué O(1) espacial (típico)?
 *   Solo usamos variables l, r, sum/count (constante).
 *   Si necesitamos set/map para ventana: O(k) donde k es tamaño ventana.
 * 
 * EXPLICACIÓN INTUITIVA:
 *   Dos punteros (izquierdo l, derecho r) que avanzan inteligentemente.
 *   Ejemplo: encontrar subarray con suma = target.
 *   - Si suma < target → avanzar r (agregar más elementos)
 *   - Si suma > target → avanzar l (quitar elementos)
 *   - Si suma == target → ¡encontrado!
 *   Evita probar todas las combinaciones O(n²), solo O(n) movimientos.
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 1. Subarray con suma exacta = target
pair<int,int> subarray_sum(vector<int>& arr, int target) {
    int n = arr.size();
    int l = 0, r = 0, sum = 0;
    
    while (r < n) {
        sum += arr[r];
        
        // Contraer ventana si suma > target
        while (sum > target && l <= r) {
            sum -= arr[l++];
        }
        
        if (sum == target) {
            return {l, r};  // encontrado [l, r]
        }
        
        r++;
    }
    
    return {-1, -1};  // no encontrado
}

// 2. Subarray con suma >= target (mínima longitud)
int min_subarray_sum(vector<int>& arr, int target) {
    int n = arr.size();
    int l = 0, r = 0, sum = 0;
    int min_len = INT_MAX;
    
    while (r < n) {
        sum += arr[r];
        
        // Contraer al máximo mientras suma >= target
        while (sum >= target && l <= r) {
            min_len = min(min_len, r - l + 1);
            sum -= arr[l++];
        }
        
        r++;
    }
    
    return min_len == INT_MAX ? -1 : min_len;
}

// 3. Sliding window: máximo subarray con k elementos únicos
int max_k_distinct(vector<int>& arr, int k) {
    int n = arr.size();
    int l = 0, r = 0;
    int max_len = 0;
    map<int, int> freq;  // frecuencia en ventana
    
    while (r < n) {
        freq[arr[r]]++;
        
        // Contraer si > k distintos
        while ((int)freq.size() > k) {
            freq[arr[l]]--;
            if (freq[arr[l]] == 0) {
                freq.erase(arr[l]);
            }
            l++;
        }
        
        max_len = max(max_len, r - l + 1);
        r++;
    }
    
    return max_len;
}

// 4. Two Sum en array ordenado (retorna valores)
pair<int,int> two_sum_sorted(vector<int>& arr, int target) {
    int l = 0, r = arr.size() - 1;
    
    while (l < r) {
        int sum = arr[l] + arr[r];
        
        if (sum == target) {
            return {arr[l], arr[r]};
        } else if (sum < target) {
            l++;  // necesitamos suma mayor
        } else {
            r--;  // necesitamos suma menor
        }
    }
    
    return {-1, -1};
}

// 5. Container with most water (Leetcode 11)
int max_area(vector<int>& height) {
    int l = 0, r = height.size() - 1;
    int max_water = 0;
    
    while (l < r) {
        int h = min(height[l], height[r]);
        int width = r - l;
        max_water = max(max_water, h * width);
        
        // Mover puntero del lado más bajo (greedy)
        if (height[l] < height[r]) {
            l++;
        } else {
            r--;
        }
    }
    
    return max_water;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Test 1: Subarray con suma exacta
    cout << "=== SUBARRAY SUM ===\n";
    vector<int> arr1 = {1, 4, 2, 5, 3, 7};
    int target = 10;
    auto [l1, r1] = subarray_sum(arr1, target);
    cout << "Array: [1, 4, 2, 5, 3, 7], target=" << target << "\n";
    cout << "Subarray [" << l1 << ", " << r1 << "]: ";
    for (int i = l1; i <= r1; i++) cout << arr1[i] << " ";
    cout << "\n\n";
    
    // Test 2: Mínima longitud con suma >= target
    cout << "=== MIN SUBARRAY LENGTH (suma >= target) ===\n";
    vector<int> arr2 = {2, 3, 1, 2, 4, 3};
    target = 7;
    int min_len = min_subarray_sum(arr2, target);
    cout << "Array: [2, 3, 1, 2, 4, 3], target=" << target << "\n";
    cout << "Mínima longitud: " << min_len << "\n\n";
    
    // Test 3: Sliding window k distintos
    cout << "=== MAX SUBARRAY con K DISTINTOS ===\n";
    vector<int> arr3 = {1, 2, 1, 2, 3, 1, 1, 3};
    int k = 2;
    int max_len = max_k_distinct(arr3, k);
    cout << "Array: [1, 2, 1, 2, 3, 1, 1, 3], k=" << k << "\n";
    cout << "Máxima longitud: " << max_len << "\n\n";
    
    // Test 4: Two sum en array ordenado
    cout << "=== TWO SUM (sorted) ===\n";
    vector<int> arr4 = {1, 3, 5, 7, 9, 11};
    target = 12;
    auto [a, b] = two_sum_sorted(arr4, target);
    cout << "Array: [1, 3, 5, 7, 9, 11], target=" << target << "\n";
    cout << "Par encontrado: " << a << " + " << b << " = " << target << "\n\n";
    
    // Test 5: Container with most water
    cout << "=== CONTAINER WITH MOST WATER ===\n";
    vector<int> heights = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    int water = max_area(heights);
    cout << "Heights: [1, 8, 6, 2, 5, 4, 8, 3, 7]\n";
    cout << "Máxima agua: " << water << "\n";
    
    return 0;
}
