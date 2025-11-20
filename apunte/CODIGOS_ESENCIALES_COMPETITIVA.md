# 🏆 CÓDIGOS ESENCIALES PARA COMPETENCIA DE PROGRAMACIÓN

## 📋 TEMPLATE BASE (OBLIGATORIO)

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi = vector<int>;
using vll = vector<ll>;

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define F first
#define S second

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;

void solve() {
    // código aquí
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t = 1;
    // cin >> t;  // descomentar para múltiples casos
    while(t--) solve();
    
    return 0;
}
```

---

## 🔥 TOP 10 ALGORITMOS CRÍTICOS

### 1. 🔍 **BÚSQUEDA BINARIA** (O(log n))
**Uso:** Búsqueda en arreglos ordenados, encontrar límites

```cpp
// Búsqueda binaria estándar
int binary_search(vector<int>& arr, int target) {
    int l = 0, r = arr.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

// Lower/Upper bound
auto it_lower = lower_bound(all(arr), x); // primer ≥ x
auto it_upper = upper_bound(all(arr), x); // primer > x
```

**Casos de uso:**
- ✓ Encontrar elemento en array ordenado
- ✓ Respuesta a búsqueda en rango [l, r]
- ✓ Optimización de tiempo en DP

---

### 2. 📊 **PREFIX SUM** (O(n) precálculo, O(1) query)
**Uso:** Suma de rangos en arrays

```cpp
// Precálculo O(n)
vector<ll> prefix(n + 1, 0);
for (int i = 1; i <= n; i++) {
    prefix[i] = prefix[i-1] + arr[i-1];
}

// Query O(1): suma [l, r]
ll range_sum(int l, int r) {
    return prefix[r+1] - prefix[l];
}

// 2D Prefix Sum
vector<vector<ll>> prefix2d(n+1, vector<ll>(m+1, 0));
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        prefix2d[i][j] = mat[i-1][j-1] 
                       + prefix2d[i-1][j] 
                       + prefix2d[i][j-1] 
                       - prefix2d[i-1][j-1];
    }
}
```

---

### 3. 🎒 **KNAPSACK 0/1** (O(n·W) DP)
**Uso:** Optimización con restricciones de peso/capacidad

```cpp
// Versión optimizada O(W) espacio
ll knapsack(vector<ll>& w, vector<ll>& v, ll W) {
    vector<ll> dp(W + 1, 0);
    for (int i = 0; i < n; i++) {
        for (ll cap = W; cap >= w[i]; cap--) {
            dp[cap] = max(dp[cap], dp[cap - w[i]] + v[i]);
        }
    }
    return dp[W];
}

// Con reconstrucción de solución
pair<ll, vi> knapsack_path(vector<ll>& w, vector<ll>& v, ll W) {
    vector<vector<ll>> dp(n+1, vector<ll>(W+1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (ll cap = 0; cap <= W; cap++) {
            dp[i][cap] = dp[i-1][cap]; // no tomar
            if (cap >= w[i-1]) {
                dp[i][cap] = max(dp[i][cap], 
                                dp[i-1][cap - w[i-1]] + v[i-1]);
            }
        }
    }
    
    // Reconstruir
    vi items;
    ll cap = W;
    for (int i = n; i > 0; i--) {
        if (dp[i][cap] != dp[i-1][cap]) {
            items.pb(i-1);
            cap -= w[i-1];
        }
    }
    return {dp[n][W], items};
}
```

---

### 4. 🌲 **DFS + BFS** (O(V+E) grafos)
**Uso:** Recorrido de grafos, componentes conexas

```cpp
// DFS recursivo
vector<bool> visited;
vector<vi> adj;

void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) dfs(v);
    }
}

// BFS iterativo
void bfs(int start) {
    queue<int> q;
    vector<bool> visited(n, false);
    vector<int> dist(n, INF);
    
    q.push(start);
    visited[start] = true;
    dist[start] = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

// Componentes conexas
int count_components() {
    visited.assign(n, false);
    int components = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
            components++;
        }
    }
    return components;
}
```

---

### 5. 🛣️ **DIJKSTRA** (O((V+E) log V))
**Uso:** Caminos mínimos desde un origen (pesos NO negativos)

```cpp
vector<ll> dijkstra(int start, vector<vector<pll>>& adj) {
    int n = adj.size();
    vector<ll> dist(n, LINF);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
```

---

### 6. 🔗 **UNION-FIND (DSU)** (O(α(n)) ≈ O(1))
**Uso:** Componentes dinámicas, MST (Kruskal)

```cpp
struct UnionFind {
    vi parent, rank;
    int components;
    
    UnionFind(int n) : parent(n), rank(n, 0), components(n) {
        iota(all(parent), 0);
    }
    
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        
        if (rank[px] < rank[py]) swap(px, py);
        parent[py] = px;
        if (rank[px] == rank[py]) rank[px]++;
        
        components--;
        return true;
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};
```

---

### 7. 📏 **LIS (Longest Increasing Subsequence)** (O(n log n))
**Uso:** Subsecuencia creciente más larga

```cpp
// O(n log n) con búsqueda binaria
int lis(vector<int>& arr) {
    vector<int> dp;
    for (int x : arr) {
        auto it = lower_bound(all(dp), x);
        if (it == dp.end()) dp.pb(x);
        else *it = x;
    }
    return sz(dp);
}

// Con reconstrucción O(n log n)
vi lis_path(vector<int>& arr) {
    int n = sz(arr);
    vi dp, parent(n, -1), pos(n);
    
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(all(dp), arr[i]);
        int idx = it - dp.begin();
        
        if (it == dp.end()) dp.pb(arr[i]);
        else *it = arr[i];
        
        pos[i] = idx;
        if (idx > 0) {
            for (int j = i-1; j >= 0; j--) {
                if (pos[j] == idx-1 && arr[j] < arr[i]) {
                    parent[i] = j;
                    break;
                }
            }
        }
    }
    
    // Reconstruir
    vi result;
    int curr = -1;
    for (int i = n-1; i >= 0; i--) {
        if (pos[i] == sz(dp)-1) {
            curr = i;
            break;
        }
    }
    
    while (curr != -1) {
        result.pb(arr[curr]);
        curr = parent[curr];
    }
    
    reverse(all(result));
    return result;
}
```

---

### 8. 🎯 **TWO POINTERS** (O(n))
**Uso:** Subarrays, sumas objetivo, ventanas deslizantes

```cpp
// Subarray con suma exacta = target
pii two_sum(vector<int>& arr, int target) {
    int l = 0, r = 0, sum = 0;
    
    while (r < sz(arr)) {
        sum += arr[r];
        
        while (sum > target && l <= r) {
            sum -= arr[l++];
        }
        
        if (sum == target) return {l, r};
        r++;
    }
    return {-1, -1};
}

// Sliding window máximo tamaño k
int max_window(vector<int>& arr, int k) {
    int l = 0, r = 0, max_len = 0;
    set<int> window;
    
    while (r < sz(arr)) {
        while (window.count(arr[r])) {
            window.erase(arr[l++]);
        }
        window.insert(arr[r]);
        
        if (sz(window) <= k) {
            max_len = max(max_len, r - l + 1);
        }
        r++;
    }
    return max_len;
}
```

---

### 9. 🔢 **SIEVE OF ERATOSTHENES** (O(n log log n))
**Uso:** Todos los primos hasta n

```cpp
vector<bool> sieve(int n) {
    vector<bool> is_prime(n+1, true);
    is_prime[0] = is_prime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i*i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

// Factorización prima O(sqrt(n))
map<ll, int> prime_factors(ll n) {
    map<ll, int> factors;
    for (ll i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            factors[i]++;
            n /= i;
        }
    }
    if (n > 1) factors[n]++;
    return factors;
}
```

---

### 10. 🧮 **EXPONENCIACIÓN MODULAR** (O(log n))
**Uso:** a^b mod m eficientemente

```cpp
ll mod_pow(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Inverso modular (cuando mod es primo)
ll mod_inv(ll a, ll mod) {
    return mod_pow(a, mod - 2, mod);
}

// Combinatoria modular
ll mod_comb(ll n, ll k, ll mod) {
    if (k > n) return 0;
    
    ll num = 1, den = 1;
    for (ll i = 0; i < k; i++) {
        num = (num * ((n - i) % mod)) % mod;
        den = (den * ((i + 1) % mod)) % mod;
    }
    return (num * mod_inv(den, mod)) % mod;
}
```

---

## 🛠️ UTILIDADES ESENCIALES

### Lectura rápida
```cpp
template<typename T>
void read(T& x) { cin >> x; }

template<typename T, typename... Args>
void read(T& x, Args&... args) {
    cin >> x;
    read(args...);
}
```

### Debug
```cpp
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#define dbgarr(arr) cerr << #arr << ": "; for(auto x : arr) cerr << x << ' '; cerr << '\n'
#else
#define dbg(x)
#define dbgarr(arr)
#endif
```

### GCD/LCM
```cpp
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
```

---

## 📚 ESTRUCTURAS ADICIONALES

### Segment Tree (suma de rango)
```cpp
struct SegTree {
    vi tree;
    int n;
    
    SegTree(vector<int>& arr) {
        n = sz(arr);
        tree.assign(4*n, 0);
        build(arr, 1, 0, n-1);
    }
    
    void build(vi& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2*node, l, mid);
        build(arr, 2*node+1, mid+1, r);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
    
    int query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return tree[node];
        
        int mid = (l + r) / 2;
        return query(2*node, l, mid, ql, qr) +
               query(2*node+1, mid+1, r, ql, qr);
    }
    
    int query(int l, int r) {
        return query(1, 0, n-1, l, r);
    }
};
```

---

## 🎯 CHECKLIST ANTES DE COMPETIR

**Configuración:**
- [ ] Template base cargado
- [ ] Macros y typedefs configurados
- [ ] Fast I/O activado

**Durante el problema:**
- [ ] Leer entrada/salida cuidadosamente
- [ ] Identificar límites (n ≤ 10⁵? 10⁶? 10⁹?)
- [ ] Elegir estructura de datos apropiada
- [ ] Verificar casos borde (n=0, n=1, negativos)
- [ ] Probar con ejemplos del problema

**Complejidades según límites:**
- n ≤ 10: O(n!) - Backtracking, permutaciones
- n ≤ 20: O(2ⁿ) - Bitmask DP, subsets
- n ≤ 500: O(n³) - Floyd-Warshall, DP cúbico
- n ≤ 5000: O(n²) - DP cuadrático, loops anidados
- n ≤ 10⁵: O(n log n) - Sort, Dijkstra, Segment Tree
- n ≤ 10⁶: O(n) - Linear scan, prefix sum
- n ≤ 10⁹: O(log n) - Binary search, GCD

---

## 💡 TIPS FINALES

1. **Siempre usa `long long` cuando:**
   - Multiplicaciones pueden dar > 2×10⁹
   - Sumas acumuladas
   - Distancias en grafos

2. **Evita TLE:**
   - `ios::sync_with_stdio(false)`
   - `cin.tie(nullptr)`
   - Usar `'\n'` en lugar de `endl`

3. **Debugging:**
   - Imprimir variables intermedias
   - Verificar índices (0-indexed vs 1-indexed)
   - Revisar overflow

4. **Estructuras por uso:**
   - Conteo/frecuencias → `map<int,int>`
   - Unicidad → `set<int>`
   - Heap/Priority → `priority_queue`
   - Grafos → `vector<vector<int>>`
   - DP → `vector<vector<ll>>`
