#include <iostream>
#include <string>

static void esperarEnter(const char* prompt) {
    std::cout << prompt;
    std::string linea;
    std::getline(std::cin, linea);
}

static void imprimirVertical(const int limpieza[20], int posicion, const char* titulo) {
    std::cout << titulo << std::endl;
    for (int i = 0; i < 20; i++) {
        if (i == posicion) {
            std::cout << "[A] ";
        } else {
            std::cout << "    ";
        }

        std::cout << "[" << i << "] " << limpieza[i] << " (" << (limpieza[i] == 1 ? "Sucio" : "Limpio") << ")" << std::endl;
    }
}

int main() {
    int limpieza[20]; // Vector de tamaño 20

    // "Vector" dinámico para aspiradora
    int* aspiradora = nullptr;
    int tamañoAspiradora = 0;

    // Semilla (usamos la dirección del arreglo como punto de partida para variar el resultado)
    unsigned long long datoLimpieza = (unsigned long long)&limpieza;

    // Generamos el arreglo aleatorio de 20 (0 = limpio, 1 = sucio) limitando a máximo 13 celdas sucias.
    // Si aparecen más de 13 "1", mantenemos una selección aleatoria uniforme de 13 posiciones sucias.
    int indicesSucios[13];
    int suciedad = 0;
    for (int i = 0; i < 20; i++) {
        datoLimpieza = datoLimpieza * 1664525 + 1013904223;
        int b = (datoLimpieza >> 16) % 2;

        if (b == 0) {
            limpieza[i] = 0;
            continue;
        }

        if (suciedad < 13) {
            limpieza[i] = 1;
            indicesSucios[suciedad] = i;
            suciedad++;
            continue;
        }

        datoLimpieza = datoLimpieza * 1664525 + 1013904223;
        int r = (datoLimpieza >> 16) % (suciedad + 1);
        if (r < 13) {
            limpieza[indicesSucios[r]] = 0;
            limpieza[i] = 1;
            indicesSucios[r] = i;
        } else {
            limpieza[i] = 0;
        }
    }

    std::cout << "Generando entorno de limpieza aleatorio (0=Limpio, 1=Sucio)." << std::endl;
    imprimirVertical(limpieza, -1, "Estado inicial (vertical):");

    esperarEnter("\nPresiona Enter para iniciar la aspiradora...");

    for (int i = 0; i < 20; i++) {
        std::cout << "\n";
        imprimirVertical(limpieza, i, "Aspiradora en la celda actual:");
        std::cout << "Celda [" << i << "]: " << (limpieza[i] == 1 ? "Sucio" : "Limpio") << std::endl;

        esperarEnter("Presiona Enter para actuar...");

        if (limpieza[i] == 1) {
            int* nuevo = new int[tamañoAspiradora + 1];
            for (int j = 0; j < tamañoAspiradora; j++) {
                nuevo[j] = aspiradora[j];
            }
            nuevo[tamañoAspiradora] = i;
            delete[] aspiradora;
            aspiradora = nuevo;
            tamañoAspiradora++;

            limpieza[i] = 0;
            std::cout << "Accion: Limpio la celda." << std::endl;
        } else {
            std::cout << "Accion: Nada (ya estaba limpia)." << std::endl;
        }

        imprimirVertical(limpieza, i, "Estado despues de la accion:");
        esperarEnter("Presiona Enter para continuar...");
    }

    // Mostrar lo que recogió la aspiradora
    std::cout << "Celdas sucias recogidas (indices): {";
    for (int i = 0; i < tamañoAspiradora; i++) {
        std::cout << aspiradora[i];
        if (i < tamañoAspiradora - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    std::cout << "Total recogidas: " << tamañoAspiradora << std::endl;

    delete[] aspiradora;

    return 0;
}