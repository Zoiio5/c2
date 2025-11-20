#include <bits/stdc++.h>
using namespace std;

/*
 * FRACTIONAL KNAPSACK (Greedy)
 * Maximiza valor permitiendo fracciones de items.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(n log n)?
 *   - Calcular ratios valor/peso: O(n)
 *   - Ordenar n items por ratio: O(n log n)
 *   - Recorrer items tomando lo que cabe: O(n)
 *   - Dominante: O(n log n) del sort
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   1. Calcular ratios valor/peso: recorre n items = O(n)
 *   2. Ordenar n items por ratio descendente: O(n log n)
 *   3. Selección voraz (llenando capacidad): O(n)
 *   Dominante: ordenamiento O(n log n).
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(n)?
 *   - Vector de items: O(n)
 *   - Sort in-place usa stack O(log n) en promedio
 *   - Variables capacityLeft, totalValue: O(1)
 *   - Total: O(n)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Vector de items: n elementos. Sort usa stack de recursión: O(log n).
 *   Dominante: O(n) del vector.
 */

// Fractional Knapsack - Greedy
struct Item {
    int value, weight;
    double ratio;
};

bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

double fractionalKnapsack(vector<Item>& items, int W) {
    sort(items.begin(), items.end(), compare);
    
    double totalValue = 0.0;
    int currWeight = 0;
    
    for (auto& item : items) {
        if (currWeight + item.weight <= W) {
            currWeight += item.weight;
            totalValue += item.value;
        } else {
            int remaining = W - currWeight;
            totalValue += item.value * ((double)remaining / item.weight);
            break;
        }
    }
    
    return totalValue;
}

int main() {
    int n, W;
    cin >> n >> W;
    
    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        cin >> items[i].value >> items[i].weight;
        items[i].ratio = (double)items[i].value / items[i].weight;
    }
    
    double maxValue = fractionalKnapsack(items, W);
    
    cout << fixed << setprecision(2);
    cout << "Valor máximo: " << maxValue << endl;
    
    return 0;
}
