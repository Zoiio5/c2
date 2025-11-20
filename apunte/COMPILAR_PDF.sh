#!/bin/bash

# Script para compilar top10_codigos.tex a PDF

echo "🔧 Verificando dependencias LaTeX..."

if ! command -v pdflatex &> /dev/null; then
    echo "❌ pdflatex no encontrado"
    echo ""
    echo "📦 Instalar con:"
    echo "   sudo apt-get update"
    echo "   sudo apt-get install texlive-latex-base texlive-latex-extra"
    exit 1
fi

echo "✅ pdflatex encontrado"
echo ""
echo "📄 Compilando top10_codigos.tex..."

pdflatex -interaction=nonstopmode top10_codigos.tex

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ PDF compilado exitosamente"
    ls -lh top10_codigos.pdf | awk '{print "   Tamaño: " $5}'
    echo ""
    echo "🔍 Ver PDF:"
    echo "   xdg-open top10_codigos.pdf"
else
    echo ""
    echo "❌ Error en compilación"
    echo "   Ver top10_codigos.log para detalles"
fi

# Limpiar archivos temporales
rm -f *.aux *.log *.out
