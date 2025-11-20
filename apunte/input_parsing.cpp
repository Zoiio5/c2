/*
 * INPUT PARSING - Técnicas de lectura de entrada
 * 
 * COMPLEJIDAD:
 *   - getline + stringstream: O(n) donde n es el largo de la línea
 *   - cin >> : O(1) por token
 * 
 * EXPLICACIÓN:
 *   Diferentes técnicas para leer entrada en competitivas:
 *   1. cin básico (separado por espacios)
 *   2. getline + stringstream (líneas completas)
 *   3. scanf (más rápido para gran volumen)
 *   4. Fast I/O (ios::sync_with_stdio(false))
 */

#include <bits/stdc++.h>
using namespace std;

// ==================== TÉCNICA 1: GETLINE + STRINGSTREAM ====================
// Útil para: líneas con formato variable, parsing complejo
void tecnica_getline_stringstream() {
    cout << "=== GETLINE + STRINGSTREAM ===\n";
    cout << "Ingresa líneas 'articulo palabra num1 num2' (Ctrl+D para terminar):\n";
    
    struct Registro {
        string nombre;
        int a, b;
    };
    
    vector<Registro> registros;
    string linea;
    
    while (getline(cin, linea)) {
        istringstream iss(linea);
        string articulo, palabra;
        Registro r;
        
        if (iss >> articulo >> palabra >> r.a >> r.b) {
            r.nombre = articulo + " " + palabra;
            registros.push_back(r);
        }
    }
    
    cout << "\nLeído " << registros.size() << " registros:\n";
    for (const auto& r : registros) {
        cout << r.nombre << " -> " << r.a << ", " << r.b << "\n";
    }
}

// ==================== TÉCNICA 2: CIN BÁSICO ====================
// Útil para: entrada simple separada por espacios/newlines
void tecnica_cin_basico() {
    cout << "=== CIN BÁSICO ===\n";
    
    int n;
    cout << "Cantidad de elementos: ";
    cin >> n;
    
    vector<int> arr(n);
    cout << "Ingresa " << n << " números: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    cout << "Array leído: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";
}

// ==================== TÉCNICA 3: MÚLTIPLES CASOS DE PRUEBA ====================
// Patrón común: leer T casos
void tecnica_multiples_casos() {
    cout << "=== MÚLTIPLES CASOS ===\n";
    
    int t;
    cout << "Número de casos de prueba: ";
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        
        // Procesar caso
        int suma = 0;
        for (int x : arr) suma += x;
        
        cout << "Suma: " << suma << "\n";
    }
}

// ==================== TÉCNICA 4: LEER HASTA EOF ====================
// Útil cuando no se sabe cuántos datos vienen
void tecnica_eof() {
    cout << "=== LEER HASTA EOF ===\n";
    
    int x;
    vector<int> numeros;
    
    cout << "Ingresa números (Ctrl+D para terminar): ";
    while (cin >> x) {
        numeros.push_back(x);
    }
    
    cout << "Leídos " << numeros.size() << " números\n";
}

// ==================== TÉCNICA 5: LEER MATRIZ ====================
void tecnica_matriz() {
    cout << "=== LEER MATRIZ ===\n";
    
    int n, m;
    cout << "Dimensiones (n m): ";
    cin >> n >> m;
    
    vector<vector<int>> mat(n, vector<int>(m));
    
    cout << "Ingresa matriz " << n << "x" << m << ":\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
        }
    }
    
    cout << "Matriz leída:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }
}

// ==================== TÉCNICA 6: LEER GRAFO ====================
void tecnica_grafo() {
    cout << "=== LEER GRAFO ===\n";
    
    int n, m;  // n = nodos, m = aristas
    cout << "Nodos y aristas (n m): ";
    cin >> n >> m;
    
    vector<vector<int>> adj(n);
    
    cout << "Ingresa " << m << " aristas (u v):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);  // grafo no dirigido
    }
    
    cout << "Lista de adyacencia:\n";
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int v : adj[i]) cout << v << " ";
        cout << "\n";
    }
}

// ==================== TÉCNICA 7: GETLINE PURO (STRINGS COMPLETOS) ====================
void tecnica_getline_puro() {
    cout << "=== GETLINE PURO ===\n";
    
    cin.ignore();  // limpiar buffer después de cin >>
    
    int n;
    cout << "Cantidad de líneas: ";
    cin >> n;
    cin.ignore();  // importante!
    
    vector<string> lineas;
    
    cout << "Ingresa " << n << " líneas:\n";
    for (int i = 0; i < n; i++) {
        string linea;
        getline(cin, linea);
        lineas.push_back(linea);
    }
    
    cout << "Líneas leídas:\n";
    for (int i = 0; i < lineas.size(); i++) {
        cout << i << ": " << lineas[i] << "\n";
    }
}

// ==================== TÉCNICA 8: FAST I/O ====================
void tecnica_fast_io() {
    cout << "=== FAST I/O ===\n";
    
    // Poner al inicio del main():
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
    cout << "Fast I/O configurado (ver código)\n";
    cout << "Usar solo cin/cout, NO mezclar con scanf/printf\n";
}

// ==================== TÉCNICA 9: PARSING CON DELIMITADORES ====================
void tecnica_delimitadores() {
    cout << "=== PARSING CON DELIMITADORES ===\n";
    
    string entrada = "10,20,30,40,50";
    cout << "String: " << entrada << "\n";
    
    vector<int> numeros;
    stringstream ss(entrada);
    string token;
    
    while (getline(ss, token, ',')) {  // delimitador ','
        numeros.push_back(stoi(token));
    }
    
    cout << "Números parseados: ";
    for (int x : numeros) cout << x << " ";
    cout << "\n";
}

// ==================== TÉCNICA 10: LEER PARES ====================
void tecnica_pares() {
    cout << "=== LEER PARES ===\n";
    
    int n;
    cout << "Cantidad de pares: ";
    cin >> n;
    
    vector<pair<int,int>> pares;
    
    cout << "Ingresa " << n << " pares (x y):\n";
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        pares.push_back({x, y});
    }
    
    cout << "Pares leídos:\n";
    for (auto [x, y] : pares) {
        cout << "(" << x << ", " << y << ")\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << "TÉCNICAS DE INPUT PARSING\n";
    cout << "=========================\n\n";
    
    // Descomentar la técnica que quieras probar:
    
    // tecnica_getline_stringstream();
    // tecnica_cin_basico();
    // tecnica_multiples_casos();
    // tecnica_eof();
    // tecnica_matriz();
    // tecnica_grafo();
    // tecnica_getline_puro();
    // tecnica_fast_io();
    // tecnica_delimitadores();
    // tecnica_pares();
    
    // Ejemplo simple del enunciado:
    cout << "Ejemplo: Leer 'articulo palabra num1 num2'\n";
    cout << "Ingresa líneas (Ctrl+D para terminar):\n";
    
    struct Registro {
        string nombre;
        int a, b;
    };
    
    vector<Registro> registros;
    string linea;
    
    while (getline(cin, linea)) {
        istringstream iss(linea);
        string articulo, palabra;
        Registro r;
        
        if (iss >> articulo >> palabra >> r.a >> r.b) {
            r.nombre = articulo + " " + palabra;
            registros.push_back(r);
        }
    }
    
    cout << "\nResultado:\n";
    for (const auto& r : registros) {
        cout << r.nombre << " -> " << r.a << ", " << r.b << "\n";
    }
    
    return 0;
}
