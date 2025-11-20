/*
 * N-QUEENS - Backtracking
 * Coloca N reinas en tablero N×N sin que se ataquen.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(N!) con poda?
 *   - Sin poda: colocar N reinas en N² casillas = combinatoria masiva
 *   - Con poda: descarta inmediatamente posiciones inválidas (diagonal, fila, columna)
 *   - Primer nivel: N opciones, segundo: ~(N-2), tercero: ~(N-4)...
 *   - Peor caso: O(N!) pero poda lo reduce drásticamente a ~O(N^N) práctico
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Sin poda serían N² casillas combinadas de forma masiva. Con poda
 *   (descartando diagonales, filas, columnas atacadas): Fila 1: N opciones,
 *   Fila 2: ~N-2 opciones válidas, Fila 3: ~N-4... Aproximadamente O(N!),
 *   pero la poda reduce a algo entre N! y N^N en la práctica.
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(N)?
 *   - Vector tablero: almacena columna de cada reina (N enteros)
 *   - Stack de recursión: profundidad N (una llamada por fila)
 *   - Contador de soluciones: O(1)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Vector tablero: N enteros (columna de cada reina). Stack de recursión:
 *   profundidad N (una fila por nivel). Total: O(N).
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ========== ESTRUCTURA GENÉRICA DE BACKTRACKING ==========

/*
PLANTILLA GENERAL BACKTRACKING:

1. ESTADO:
   - ¿Qué variables describen la solución parcial?
   - vector<int> solucion_actual

2. CASO BASE:
   - ¿Cuándo tenemos una solución completa?
   - if (nivel == n) → procesar solución

3. GENERAR CANDIDATOS:
   - ¿Qué opciones tenemos en este nivel?
   - for cada candidato posible

4. VERIFICAR FACTIBILIDAD:
   - ¿Es válido agregar este candidato?
   - Verificar restricciones

5. RECURSIÓN:
   - ELEGIR: agregar candidato
   - EXPLORAR: llamada recursiva
   - RETROCEDER: quitar candidato (backtrack)
*/

// ========== PATRÓN 1: ESTRUCTURA BÁSICA ==========

void backtrack_basico(int nivel, int n, vector<int>& solucion, vector<bool>& usado) {
    // 1. CASO BASE: solución completa
    if (nivel == n) {
        cout << "Solución: ";
        for (int x : solucion) cout << x << " ";
        cout << endl;
        return;
    }
    
    // 2. GENERAR candidatos para este nivel
    for (int candidato = 0; candidato < n; candidato++) {
        
        // 3. VERIFICAR factibilidad
        if (!usado[candidato]) {
            
            // 4. ELEGIR: hacer el movimiento
            solucion.push_back(candidato);
            usado[candidato] = true;
            
            // 5. EXPLORAR: recursión al siguiente nivel
            backtrack_basico(nivel + 1, n, solucion, usado);
            
            // 6. RETROCEDER: deshacer el movimiento
            solucion.pop_back();
            usado[candidato] = false;
        }
    }
}

// ========== PATRÓN 2: CON PODA (OPTIMIZACIÓN) ==========

int mejor_valor = -1;
vector<int> mejor_solucion;

bool puede_mejorar(int nivel, int valor_actual, int valor_restante) {
    // Poda por optimalidad: ¿es posible mejorar la mejor solución?
    return (valor_actual + valor_restante) > mejor_valor;
}

void backtrack_con_poda(int nivel, int n, vector<int>& solucion, 
                         int valor_actual, const vector<int>& valores) {
    // Calcular valor restante (cota superior)
    int valor_restante = 0;
    for (int i = nivel; i < n; i++) {
        valor_restante += valores[i];
    }
    
    // PODA: si no podemos mejorar, retornar
    if (!puede_mejorar(nivel, valor_actual, valor_restante)) {
        return;
    }
    
    // Caso base: solución completa
    if (nivel == n) {
        if (valor_actual > mejor_valor) {
            mejor_valor = valor_actual;
            mejor_solucion = solucion;
        }
        return;
    }
    
    // Probar cada opción
    for (int decision = 0; decision <= 1; decision++) {
        int nuevo_valor = valor_actual;
        
        if (decision == 1) {
            solucion.push_back(nivel);
            nuevo_valor += valores[nivel];
        }
        
        backtrack_con_poda(nivel + 1, n, solucion, nuevo_valor, valores);
        
        if (decision == 1) {
            solucion.pop_back();
        }
    }
}

// ========== PATRÓN 3: PERMUTACIONES ==========
// Generar todas las permutaciones de n elementos

void generar_permutaciones(int nivel, int n, vector<int>& perm, vector<bool>& usado) {
    // Caso base
    if (nivel == n) {
        for (int x : perm) cout << x << " ";
        cout << endl;
        return;
    }
    
    // Probar cada elemento no usado
    for (int i = 0; i < n; i++) {
        if (!usado[i]) {
            perm.push_back(i);
            usado[i] = true;
            
            generar_permutaciones(nivel + 1, n, perm, usado);
            
            perm.pop_back();
            usado[i] = false;
        }
    }
}

// ========== PATRÓN 4: SUBCONJUNTOS (SUBSET SUM) ==========
// Generar subconjuntos que cumplan una condición

void generar_subconjuntos(int pos, int n, vector<int>& subset, 
                          int suma_actual, int suma_objetivo) {
    // Caso base: solución encontrada
    if (suma_actual == suma_objetivo) {
        cout << "Subconjunto: ";
        for (int x : subset) cout << x << " ";
        cout << endl;
        return;
    }
    
    // Poda: si nos pasamos, retornar
    if (pos >= n || suma_actual > suma_objetivo) {
        return;
    }
    
    // OPCIÓN 1: INCLUIR elemento actual
    subset.push_back(pos);
    generar_subconjuntos(pos + 1, n, subset, suma_actual + pos, suma_objetivo);
    subset.pop_back();
    
    // OPCIÓN 2: NO INCLUIR elemento actual
    generar_subconjuntos(pos + 1, n, subset, suma_actual, suma_objetivo);
}

// ========== PATRÓN 5: COMBINACIONES ==========
// Generar combinaciones de k elementos de n

void generar_combinaciones(int inicio, int k, int n, vector<int>& combinacion) {
    // Caso base: tenemos k elementos
    if (combinacion.size() == k) {
        for (int x : combinacion) cout << x << " ";
        cout << endl;
        return;
    }
    
    // Probar elementos desde 'inicio' hasta n
    for (int i = inicio; i < n; i++) {
        combinacion.push_back(i);
        generar_combinaciones(i + 1, k, n, combinacion);
        combinacion.pop_back();
    }
}

// ========== PATRÓN 6: N-REINAS (CON VERIFICACIÓN AVANZADA) ==========

bool es_seguro(const vector<int>& tablero, int fila, int col) {
    for (int i = 0; i < fila; i++) {
        int col_reina = tablero[i];
        
        // Misma columna
        if (col_reina == col) return false;
        
        // Diagonal
        if (abs(col_reina - col) == abs(i - fila)) return false;
    }
    return true;
}

void nreinas(int fila, int n, vector<int>& tablero, int& soluciones) {
    if (fila == n) {
        soluciones++;
        return;
    }
    
    for (int col = 0; col < n; col++) {
        if (es_seguro(tablero, fila, col)) {
            tablero.push_back(col);
            nreinas(fila + 1, n, tablero, soluciones);
            tablero.pop_back();
        }
    }
}

// ========== PATRÓN 7: COLOREO DE GRAFOS ==========

bool es_color_valido(const vector<vector<int>>& grafo, const vector<int>& colores,
                     int nodo, int color) {
    // Verificar que ningún vecino tenga este color
    for (int vecino : grafo[nodo]) {
        if (vecino < nodo && colores[vecino] == color) {
            return false;
        }
    }
    return true;
}

void colorear_grafo(int nodo, int n, const vector<vector<int>>& grafo,
                    vector<int>& colores, int num_colores) {
    if (nodo == n) {
        cout << "Coloreo: ";
        for (int c : colores) cout << c << " ";
        cout << endl;
        return;
    }
    
    for (int color = 0; color < num_colores; color++) {
        if (es_color_valido(grafo, colores, nodo, color)) {
            colores[nodo] = color;
            colorear_grafo(nodo + 1, n, grafo, colores, num_colores);
            colores[nodo] = -1;
        }
    }
}

// ========== PATRÓN 8: SUDOKU ==========

bool es_valido_sudoku(vector<vector<int>>& tablero, int fila, int col, int num) {
    // Verificar fila
    for (int j = 0; j < 9; j++) {
        if (tablero[fila][j] == num) return false;
    }
    
    // Verificar columna
    for (int i = 0; i < 9; i++) {
        if (tablero[i][col] == num) return false;
    }
    
    // Verificar subcuadro 3x3
    int inicio_fila = (fila / 3) * 3;
    int inicio_col = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[inicio_fila + i][inicio_col + j] == num) {
                return false;
            }
        }
    }
    
    return true;
}

bool resolver_sudoku(vector<vector<int>>& tablero) {
    // Buscar celda vacía
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (tablero[i][j] == 0) {
                // Probar números del 1 al 9
                for (int num = 1; num <= 9; num++) {
                    if (es_valido_sudoku(tablero, i, j, num)) {
                        tablero[i][j] = num;
                        
                        if (resolver_sudoku(tablero)) {
                            return true;
                        }
                        
                        tablero[i][j] = 0;  // Backtrack
                    }
                }
                return false;  // No hay solución
            }
        }
    }
    return true;  // Tablero completo
}

// ========== TÉCNICAS DE OPTIMIZACIÓN ==========

/*
TÉCNICAS DE PODA:

1. PODA POR FACTIBILIDAD:
   - Eliminar ramas que violan restricciones

2. PODA POR OPTIMALIDAD:
   - Eliminar ramas que no pueden mejorar la mejor solución
   - Usar cotas superiores/inferiores

3. PODA POR SIMETRÍA:
   - Evitar explorar soluciones simétricas/equivalentes

4. ORDENAR CANDIDATOS:
   - Probar primero los más prometedores
   - Encontrar soluciones buenas rápido

5. VERIFICACIÓN TEMPRANA:
   - Detectar inconsistencias lo antes posible
*/

// ========== TEMPLATE GENÉRICO UNIVERSAL ==========

template<typename Estado>
void backtrack_generico(
    Estado& estado_actual,
    bool (*es_solucion)(const Estado&),
    void (*procesar_solucion)(const Estado&),
    vector<int> (*generar_candidatos)(const Estado&),
    bool (*es_factible)(const Estado&, int),
    void (*hacer_movimiento)(Estado&, int),
    void (*deshacer_movimiento)(Estado&, int)
) {
    // Caso base
    if (es_solucion(estado_actual)) {
        procesar_solucion(estado_actual);
        return;
    }
    
    // Generar candidatos
    vector<int> candidatos = generar_candidatos(estado_actual);
    
    for (int candidato : candidatos) {
        if (es_factible(estado_actual, candidato)) {
            // Elegir
            hacer_movimiento(estado_actual, candidato);
            
            // Explorar
            backtrack_generico(estado_actual, es_solucion, procesar_solucion,
                             generar_candidatos, es_factible,
                             hacer_movimiento, deshacer_movimiento);
            
            // Retroceder
            deshacer_movimiento(estado_actual, candidato);
        }
    }
}

int main() {
    int n;
    cin >> n;
    
    vector<int> tablero;
    int sol_count = 0;
    nreinas(0, n, tablero, sol_count);
    cout << sol_count << endl;
    
    return 0;
}