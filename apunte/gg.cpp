/*
 * GREEDY - Knapsack fraccionario
 * Selecciona items por mejor ratio valor/peso.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(n log n)?
 *   - Calcular ratios valor/peso: recorre n items = O(n)
 *   - Ordenar n items por ratio descendente: O(n log n)
 *   - Selección voraz: recorre items ordenados = O(n)
 *   - Dominante: O(n log n) del sort
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Calcular ratios: O(n). Ordenar por ratio: O(n log n). Selección voraz: O(n).
 *   Dominante: O(n log n) del ordenamiento.
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(n)?
 *   - Vector de elementos: almacena n items = O(n)
 *   - Sort in-place usa stack de recursión: O(log n)
 *   - Dominante: O(n) del vector de items
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Vector de n items. Sort usa stack O(log n). Dominante: O(n).
 */
#include <bits/stdc++.h>
using namespace std;

struct Elemento {
    int valor, peso;
    double ratio;
};

bool comparar(const Elemento& a, const Elemento& b) {
    return a.ratio > b.ratio;
}

int main() {
    int n, capacidad;
    cin >> n >> capacidad;
    
    vector<Elemento> elementos(n);
    for (int i = 0; i < n; i++) {
        cin >> elementos[i].valor >> elementos[i].peso;
        elementos[i].ratio = (double)elementos[i].valor / elementos[i].peso;
    }
    
    sort(elementos.begin(), elementos.end(), comparar);
    int valor_total = 0, usado = 0;
    
    for (const auto& e : elementos) {
        if (usado + e.peso <= capacidad) {
            usado += e.peso;
            valor_total += e.valor;
        }
    }
    cout << valor_total << endl;
    return 0;
}
