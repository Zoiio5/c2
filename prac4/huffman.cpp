#include <bits/stdc++.h>
using namespace std;

/*
 * HUFFMAN CODING (Compresión - Greedy)
 * Genera códigos de longitud variable óptimos.
 * 
 * COMPLEJIDAD TEMPORAL:
 *   ¿Por qué O(n log n)?
 *   - Insertar n caracteres en min-heap: n × log(n)
 *   - Extraer 2 mínimos y crear nodo interno: se repite n-1 veces
 *   - Cada extracción/inserción: O(log n)
 *   - Total: (n-1) × 2 × log(n) = O(n log n)
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   1. Insertar n caracteres en min-heap: n × log(n)
 *   2. Extraer 2 mínimos y crear nodo interno se repite n-1 veces
 *   3. Cada extracción/inserción: O(log n)
 *   Total: n·log(n) + (n-1)×2×log(n) = O(n log n).
 * 
 * COMPLEJIDAD ESPACIAL:
 *   ¿Por qué O(n)?
 *   - Árbol de Huffman: 2n-1 nodos (n hojas + n-1 internos) = O(n)
 *   - Priority queue: a lo más n nodos simultáneos
 *   - Map de códigos: n entradas
 * 
 *   EXPLICACIÓN INTUITIVA:
 *   Árbol de Huffman: 2n-1 nodos (n hojas + n-1 internos). Priority queue:
 *   máximo n nodos. Map de códigos: n entradas. Total: O(n).
 */

// Huffman Coding
struct Node {
    char ch;
    int freq;
    Node *left, *right;
    
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void printCodes(Node* root, string code, map<char, string>& codes) {
    if (!root) return;
    
    if (!root->left && !root->right) {
        codes[root->ch] = code;
        return;
    }
    
    printCodes(root->left, code + "0", codes);
    printCodes(root->right, code + "1", codes);
}

map<char, string> huffmanCoding(string text) {
    map<char, int> freq;
    for (char ch : text) freq[ch]++;
    
    priority_queue<Node*, vector<Node*>, Compare> pq;
    
    for (auto p : freq) {
        pq.push(new Node(p.first, p.second));
    }
    
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        
        Node* parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        
        pq.push(parent);
    }
    
    map<char, string> codes;
    printCodes(pq.top(), "", codes);
    
    return codes;
}

int main() {
    string text;
    getline(cin, text);
    
    map<char, string> codes = huffmanCoding(text);
    
    cout << "Códigos Huffman:" << endl;
    for (auto p : codes) {
        cout << p.first << ": " << p.second << endl;
    }
    
    // Calcular longitud de codificación
    int totalBits = 0;
    for (char ch : text) {
        totalBits += codes[ch].length();
    }
    
    cout << "\nLongitud original: " << text.length() * 8 << " bits" << endl;
    cout << "Longitud codificada: " << totalBits << " bits" << endl;
    cout << "Compresión: " << fixed << setprecision(2) 
         << (1.0 - (double)totalBits / (text.length() * 8)) * 100 << "%" << endl;
    
    return 0;
}
