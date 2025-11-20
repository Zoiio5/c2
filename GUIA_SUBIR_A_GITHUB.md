# 📤 GUÍA PARA SUBIR A GITHUB

## 🔧 PASO 1: Inicializar Git (solo primera vez)

```bash
cd /home/digitalsandman/projects/algoco

# Inicializar repositorio
git init

# Configurar usuario (si no está configurado)
git config --global user.name "Tu Nombre"
git config --global user.email "tu-email@ejemplo.com"
```

---

## 📝 PASO 2: Crear .gitignore

```bash
cat > .gitignore << 'GITIGNORE'
# Ejecutables
*.out
a.out
*.exe

# Archivos temporales C++
*.o
*.obj

# LaTeX temporales
*.aux
*.log
*.out
*.toc
*.pdf~

# Zone.Identifier (WSL)
*.Zone.Identifier

# Temporales del sistema
.DS_Store
Thumbs.db

# Carpetas de build
build/
bin/
obj/

# Archivos de prueba
test
test.txt
in.text
GITIGNORE
```

---

## 📦 PASO 3: Agregar archivos

```bash
# Ver qué archivos se agregarán
git status

# Agregar todos los archivos
git add .

# O agregar solo prac4/
git add prac4/

# Ver estado
git status
```

---

## 💾 PASO 4: Hacer commit

```bash
# Commit inicial
git commit -m "feat: Agregar 39 algoritmos de programación competitiva

- TOP 10 algoritmos críticos
- Grafos: DFS, BFS, Dijkstra, Bellman-Ford, Kruskal, Prim, SCC, Topo Sort
- DP: Knapsack 0/1, LIS, Count Inversions
- Greedy: Huffman, Scheduling, Fractional Knapsack
- Sorting: QuickSort, MergeSort, Bubble, Insertion, Selection
- Búsqueda: Binary Search, RSelect, DSelect
- Matemática: Sieve, Mod Pow
- Estructuras: Union-Find
- Utilidades: Input Parsing (10 técnicas), Two Pointers, Prefix Sum
- Documentación: LaTeX PDF compacto (29 páginas)
- Guías: TOP10_RESUMEN.md, CODIGOS_ESENCIALES_COMPETITIVA.md"
```

---

## 🌐 PASO 5: Crear repositorio en GitHub

### Opción A: Desde navegador (recomendado si no tienes conexión ahora)

1. Ve a https://github.com/new
2. Nombre: `algoco` o `competitive-programming`
3. Descripción: "39 algoritmos de programación competitiva en C++"
4. Público/Privado: según prefieras
5. **NO** marcar "Initialize with README" (ya tienes archivos)
6. Click "Create repository"

### Opción B: Con GitHub CLI (si tienes `gh` instalado)

```bash
# Login (si no estás conectado)
gh auth login

# Crear repositorio
gh repo create algoco --public --source=. --remote=origin --push
```

---

## 🚀 PASO 6: Conectar con GitHub y subir

```bash
# Agregar remote (usa la URL de TU repositorio)
git remote add origin https://github.com/TU-USUARIO/algoco.git

# O con SSH (recomendado)
git remote add origin git@github.com:TU-USUARIO/algoco.git

# Verificar remote
git remote -v

# Subir al repositorio
git push -u origin main

# Si tu rama se llama "master" en vez de "main":
git branch -M main
git push -u origin main
```

---

## 🔑 PASO 7: Autenticación (si no estás conectado)

### Si usas HTTPS:
GitHub ya no acepta contraseñas. Necesitas un **Personal Access Token**:

1. Ve a https://github.com/settings/tokens
2. Click "Generate new token (classic)"
3. Scopes: marca `repo`
4. Copia el token
5. Al hacer `git push`, usa el token como contraseña

### Si usas SSH (recomendado):
```bash
# Generar clave SSH (si no tienes)
ssh-keygen -t ed25519 -C "tu-email@ejemplo.com"

# Copiar clave pública
cat ~/.ssh/id_ed25519.pub

# Agregar a GitHub: https://github.com/settings/ssh/new
```

---

## �� PASO 8: Crear README.md (opcional pero recomendado)

```bash
cat > README.md << 'README'
# 🏆 Algoritmos de Programación Competitiva

Colección de **39 algoritmos** esenciales para competencias de programación en C++17.

## 📚 Contenido

### 🔥 TOP 10 Críticos
1. **Binary Search** - O(log n)
2. **Prefix Sum** - O(1) query
3. **Knapsack 0/1** - O(n·W)
4. **DFS + BFS** - O(V+E)
5. **Dijkstra** - O((V+E)log V)
6. **Union-Find** - O(α(n))
7. **LIS** - O(n log n)
8. **Two Pointers** - O(n)
9. **Sieve** - O(n log log n)
10. **Mod Pow** - O(log b)

### 📂 Categorías
- **Grafos**: Dijkstra, Bellman-Ford, Kruskal, Prim, DFS, BFS, SCC, Topo Sort, A*
- **DP**: Knapsack 0/1, Unbounded, LIS, Count Inversions
- **Greedy**: Huffman, Scheduling, Fractional Knapsack
- **Sorting**: QuickSort, MergeSort, Bubble, Insertion, Selection
- **Búsqueda**: Binary Search, RSelect, DSelect
- **Matemática**: Sieve, Mod Pow, GCD
- **Estructuras**: Union-Find
- **Utilidades**: Input Parsing, Two Pointers, Prefix Sum

## 🚀 Uso

```bash
# Compilar cualquier algoritmo
g++ -std=c++17 -O2 -Wall prac4/binarysearch.cpp -o binarysearch
./binarysearch

# Compilar todos
cd prac4
for f in *.cpp; do g++ -std=c++17 -O2 "$f" -o "${f%.cpp}"; done
```

## 📄 Documentación

- `TOP10_RESUMEN.md` - Guía rápida de cuándo usar cada algoritmo
- `CODIGOS_ESENCIALES_COMPETITIVA.md` - Template completo + utilidades
- `top10_codigos.pdf` - PDF imprimible (29 páginas, ultra compacto)

## ✅ Características

- ✓ Todos compilan con `-std=c++17 -O2 -Wall -Wextra`
- ✓ Explicaciones de complejidad ("¿Por qué O(...)?")
- ✓ Explicaciones intuitivas
- ✓ Código listo para copiar en competitivas
- ✓ Tests incluidos

## 📊 Estructura

```
algoco/
├── prac4/                          # 39 algoritmos
│   ├── binarysearch.cpp
│   ├── dijkstra.cpp
│   ├── knapsack01.cpp
│   └── ... (36 más)
├── TOP10_RESUMEN.md                # Guía rápida
├── CODIGOS_ESENCIALES_COMPETITIVA.md
└── top10_codigos.pdf               # PDF imprimible
```

## 🎯 Límites y Complejidades

| n ≤ | Complejidad | Algoritmos |
|-----|-------------|------------|
| 10 | O(n!) | Backtracking, Permutations |
| 20 | O(2^n) | Subsets, Bitmask DP |
| 500 | O(n³) | Floyd-Warshall |
| 5000 | O(n²) | DP cuadrático |
| 10⁵ | O(n log n) | Sort, Dijkstra, Binary Search |
| 10⁶ | O(n) | Two Pointers, Prefix Sum |
| 10⁹ | O(log n) | Binary Search, Mod Pow |

## 📖 Licencia

Libre para uso educativo y competitivo.
README

git add README.md
git commit -m "docs: Agregar README completo"
```

---

## 🔄 COMANDOS ÚTILES

```bash
# Ver estado
git status

# Ver historial
git log --oneline

# Ver cambios
git diff

# Agregar más archivos después
git add prac4/nuevo_algoritmo.cpp
git commit -m "feat: Agregar nuevo algoritmo"
git push

# Actualizar desde GitHub (pull)
git pull origin main

# Crear .gitignore si no existe
echo "*.out" >> .gitignore
echo "*.exe" >> .gitignore
git add .gitignore
git commit -m "chore: Agregar .gitignore"
git push
```

---

## 📌 NOTAS IMPORTANTES

1. **Primera vez**: Necesitas hacer `git init` y configurar remote
2. **Autenticación**: Usa SSH (recomendado) o Personal Access Token (no contraseña)
3. **Archivos grandes**: Git no sube bien archivos > 100MB (tus .cpp son pequeños, OK)
4. **PDF**: El `top10_codigos.pdf` (289KB) se subirá sin problemas

---

## 🆘 TROUBLESHOOTING

### "fatal: not a git repository"
```bash
git init
```

### "remote origin already exists"
```bash
git remote remove origin
git remote add origin https://github.com/TU-USUARIO/algoco.git
```

### "failed to push some refs"
```bash
git pull origin main --rebase
git push origin main
```

### "Support for password authentication was removed"
- Usa Personal Access Token o SSH (ver Paso 7)

---

## 📞 PASOS RESUMIDOS (cuando tengas conexión)

```bash
# 1. Inicializar
cd /home/digitalsandman/projects/algoco
git init

# 2. Agregar archivos
git add .
git commit -m "feat: Agregar 39 algoritmos competitivos"

# 3. Crear repo en GitHub (navegador)
# https://github.com/new

# 4. Conectar y subir
git remote add origin https://github.com/TU-USUARIO/algoco.git
git branch -M main
git push -u origin main
```

¡Listo! 🎉
