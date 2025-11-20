/*
 * DYNAMIC PROGRAMMING - Ejemplo bottom-up
 * Calcula función usando tabla DP.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(a·b)?
 *   - Llena matriz de a filas × b columnas
 *   - Cada celda dp[i][j] se calcula en O(1)
 *   - Total: a × b celdas × O(1) = O(a·b)
 *   - No hay recalculación gracias a memoización
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Ejemplo genérico de DP bottom-up. Llena matriz de a filas × b columnas,
 *   cada celda en O(1). Total: a × b.
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(a·b)?
 *   - Matriz dp[][] de tamaño (a+1) × (b+1)
 *   - Optimización posible: usar solo 2 filas → O(min(a,b))
 *   - Depende si necesitas reconstruir solución o solo valor
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Matriz dp[][] de (a+1)×(b+1). Optimización posible a O(min(a,b)) usando
 *   solo 2 filas si no reconstruyes solución.
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
int memo[MAXN][MAXN];
bool visitado[MAXN][MAXN];

int dp_bottomup(int n, int m) {
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++) dp[i][0] = 0;
    for (int j = 0; j <= m; j++) dp[0][j] = 0;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = max({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    }
    return dp[n][m];
}

int main() {
    int a, b;
    cin >> a >> b;
    int resultado = dp_bottomup(a, b);
    cout << resultado << endl;
    return 0;
}
