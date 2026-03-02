#include <iostream>

int main() {
    int limpieza[20]; // Vector de tamaño 20
    
    // Semilla para el generador aleatorio (usamos la dirección de memoria para variar)
    unsigned long long datoLimpieza = (unsigned long long)&limpieza;

    std::cout << "Generando entorno de limpieza aleatorio (0=Limpio, 1=Sucio):" << std::endl;
    std::cout << "{";

    for (int i = 0; i < 20; i++) {
        // Algoritmo LCG (Generador Congruencial Lineal) para aleatoriedad sin librerías
        datoLimpieza = datoLimpieza * 1664525 + 1013904223;
        
        // Generamos 0 o 1
        limpieza[i] = (datoLimpieza >> 16) % 2; 

        // Imprimimos el valor
        std::cout << limpieza[i];
        if (i < 19) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    
    return 0;
}
