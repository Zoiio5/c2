/*
 * SIEVE OF ERATOSTHENES - Criba de Eratóstenes (números primos)
 * 
 * ¿Por qué O(n log log n) temporal?
 *   Iteramos desde 2 hasta √n: O(√n).
 *   Para cada primo p, marcamos múltiplos: n/p operaciones.
 *   Suma sobre primos p ≤ √n: n × (1/2 + 1/3 + 1/5 + ...) = O(n log log n)
 * 
 * ¿Por qué O(n) espacial?
 *   Array booleano is_prime[n+1] para marcar primos/compuestos: O(n)
 * 
 * EXPLICACIÓN INTUITIVA:
 *   Imagina una lista de números del 2 al n. Empiezas con 2 (primo),
 *   tachas todos sus múltiplos (4,6,8,...). Sigues con 3 (primo),
 *   tachas 6,9,12,... Continúas hasta √n. Los números no tachados son primos.
 *   
 *   Es como un "filtro": eliminas candidatos múltiplos de primos conocidos.
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Criba básica O(n log log n)
vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            // Marcar múltiplos de i como compuestos
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    return is_prime;
}

// Criba que retorna lista de primos
vector<int> sieve_primes(int n) {
    vector<bool> is_prime = sieve(n);
    vector<int> primes;
    
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    
    return primes;
}

// Factorización prima de n usando O(sqrt(n))
map<ll, int> prime_factors(ll n) {
    map<ll, int> factors;
    
    // Probar divisores hasta √n
    for (ll i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            factors[i]++;
            n /= i;
        }
    }
    
    // Si queda n > 1, es un primo
    if (n > 1) {
        factors[n]++;
    }
    
    return factors;
}

// Contar divisores de n usando factorización
int count_divisors(ll n) {
    auto factors = prime_factors(n);
    int count = 1;
    
    // Si n = p1^a1 × p2^a2 × ... × pk^ak
    // divisores = (a1+1) × (a2+1) × ... × (ak+1)
    for (auto [p, exp] : factors) {
        count *= (exp + 1);
    }
    
    return count;
}

// GCD usando Euclides O(log(min(a,b)))
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

// LCM usando GCD
ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;  // evita overflow
}

// Verificar si n es primo (trial division) O(√n)
bool is_prime_check(ll n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    // Probar divisores de la forma 6k ± 1
    for (ll i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Test 1: Criba hasta 50
    cout << "=== SIEVE (primos hasta 50) ===\n";
    int n = 50;
    auto primes = sieve_primes(n);
    cout << "Primos hasta " << n << ": ";
    for (int p : primes) cout << p << " ";
    cout << "\nTotal: " << primes.size() << " primos\n\n";
    
    // Test 2: Factorización prima
    cout << "=== PRIME FACTORIZATION ===\n";
    ll num = 360;
    auto factors = prime_factors(num);
    cout << num << " = ";
    bool first = true;
    for (auto [p, exp] : factors) {
        if (!first) cout << " × ";
        cout << p;
        if (exp > 1) cout << "^" << exp;
        first = false;
    }
    cout << "\n\n";
    
    // Test 3: Contar divisores
    cout << "=== COUNT DIVISORS ===\n";
    num = 360;
    int div_count = count_divisors(num);
    cout << num << " tiene " << div_count << " divisores\n\n";
    
    // Test 4: GCD y LCM
    cout << "=== GCD & LCM ===\n";
    ll a = 48, b = 18;
    cout << "a=" << a << ", b=" << b << "\n";
    cout << "GCD: " << gcd(a, b) << "\n";
    cout << "LCM: " << lcm(a, b) << "\n\n";
    
    // Test 5: Verificar primalidad
    cout << "=== PRIMALITY TEST ===\n";
    vector<ll> test_nums = {17, 91, 97, 100, 1009};
    for (ll x : test_nums) {
        cout << x << " es " << (is_prime_check(x) ? "PRIMO" : "COMPUESTO") << "\n";
    }
    
    return 0;
}
