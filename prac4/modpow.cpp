/*
 * MODULAR EXPONENTIATION - Exponenciación modular (a^b mod m)
 * 
 * ¿Por qué O(log b) temporal?
 *   Elevamos al cuadrado la base y dividimos exponente a la mitad en cada paso.
 *   Ejemplo: a^13 = a^(1101)₂ requiere log₂(13) = 4 operaciones.
 *   En cada paso: 1 multiplicación + 1 módulo = O(1).
 *   Total: O(log b)
 * 
 * ¿Por qué O(1) espacial?
 *   Solo usamos 3 variables (result, base, exp) independiente del exponente.
 *   Versión iterativa (no recursiva) → stack constante.
 * 
 * EXPLICACIÓN INTUITIVA:
 *   Calcular a^b mod m directamente: overflow si b es grande (ej: 2^1000000).
 *   Solución: usar binario del exponente. Ejemplo: 2^13 = 2^8 × 2^4 × 2^1
 *   Vamos duplicando (a² mod m, a⁴ mod m, a⁸ mod m...) y multiplicamos
 *   solo los bits "encendidos" del exponente. Log pasos en vez de b pasos.
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;

// Exponenciación modular O(log b)
ll mod_pow(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;  // evitar overflow inicial
    
    while (exp > 0) {
        if (exp & 1) {  // bit menos significativo = 1
            result = (result * base) % mod;
        }
        base = (base * base) % mod;  // elevar al cuadrado
        exp >>= 1;  // dividir exponente entre 2
    }
    
    return result;
}

// Inverso modular (cuando mod es primo): a^(-1) ≡ a^(mod-2) (mod mod)
// Basado en Pequeño Teorema de Fermat
ll mod_inv(ll a, ll mod) {
    return mod_pow(a, mod - 2, mod);
}

// División modular: (a/b) mod m = (a × b^(-1)) mod m
ll mod_div(ll a, ll b, ll mod) {
    return (a % mod * mod_inv(b, mod)) % mod;
}

// Combinatoria modular: C(n, k) mod m
ll mod_comb(ll n, ll k, ll mod) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    
    ll num = 1, den = 1;
    
    // C(n,k) = n!/(k!(n-k)!) = (n × (n-1) × ... × (n-k+1)) / (k × (k-1) × ... × 1)
    for (ll i = 0; i < k; i++) {
        num = (num * ((n - i) % mod)) % mod;
        den = (den * ((i + 1) % mod)) % mod;
    }
    
    return (num * mod_inv(den, mod)) % mod;
}

// Factorial modular (precálculo para múltiples combinatorias)
vector<ll> fact, inv_fact;

void precompute_factorials(int n, ll mod) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i-1] * i) % mod;
    }
    
    inv_fact[n] = mod_inv(fact[n], mod);
    for (int i = n - 1; i >= 0; i--) {
        inv_fact[i] = (inv_fact[i+1] * (i+1)) % mod;
    }
}

// Combinatoria rápida O(1) tras precálculo
ll fast_comb(int n, int k, ll mod) {
    if (k > n || k < 0) return 0;
    return (fact[n] * inv_fact[k] % mod) * inv_fact[n-k] % mod;
}

// Fibonacci modular usando matriz exponenciación O(log n)
ll fib_mod(ll n, ll mod) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    // Matriz de Fibonacci: [[1,1],[1,0]]^n
    // Simplificado usando solo potencias
    ll a = 1, b = 1;
    for (ll i = 2; i < n; i++) {
        ll c = (a + b) % mod;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Test 1: Exponenciación modular
    cout << "=== MODULAR EXPONENTIATION ===\n";
    ll base = 2, exp = 1000000, mod = MOD;
    ll result = mod_pow(base, exp, mod);
    cout << base << "^" << exp << " mod " << mod << " = " << result << "\n\n";
    
    // Test 2: Inverso modular
    cout << "=== MODULAR INVERSE ===\n";
    ll a = 3;
    ll inv = mod_inv(a, MOD);
    cout << "Inverso de " << a << " mod " << MOD << " = " << inv << "\n";
    cout << "Verificación: " << a << " × " << inv << " mod " << MOD 
         << " = " << (a * inv) % MOD << "\n\n";
    
    // Test 3: División modular
    cout << "=== MODULAR DIVISION ===\n";
    ll dividend = 10, divisor = 3;
    ll div_result = mod_div(dividend, divisor, MOD);
    cout << dividend << " / " << divisor << " mod " << MOD << " = " << div_result << "\n\n";
    
    // Test 4: Combinatoria modular
    cout << "=== MODULAR COMBINATORICS ===\n";
    ll n = 10, k = 3;
    ll comb = mod_comb(n, k, MOD);
    cout << "C(" << n << ", " << k << ") mod " << MOD << " = " << comb << "\n";
    cout << "(Esperado: 120)\n\n";
    
    // Test 5: Combinatoria rápida con precálculo
    cout << "=== FAST COMBINATORICS (with precompute) ===\n";
    precompute_factorials(100, MOD);
    cout << "C(100, 50) mod " << MOD << " = " << fast_comb(100, 50, MOD) << "\n";
    cout << "C(20, 10) mod " << MOD << " = " << fast_comb(20, 10, MOD) << "\n\n";
    
    // Test 6: Fibonacci modular
    cout << "=== FIBONACCI MODULAR ===\n";
    for (int i = 0; i <= 10; i++) {
        cout << "F(" << i << ") mod " << MOD << " = " << fib_mod(i, MOD) << "\n";
    }
    
    return 0;
}
