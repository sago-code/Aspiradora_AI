#include <iostream>
#include <string>

static void esperarEnter(const char* prompt) {
    std::cout << prompt;
    std::string linea;
    std::getline(std::cin, linea);
}

//Imprime verticalmente el estado del entorno de limpieza
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

    // Semilla (se utiliza la dirección del arreglo como punto de partida para variar el resultado)
    unsigned long long datoLimpieza = (unsigned long long)&limpieza;

    // Generamos el arreglo aleatorio de 20 (0 = limpio, 1 = sucio) limitando a máximo 13 celdas sucias.
    // Si aparecen más de 13 "1", mantenemos una selección aleatoria uniforme de 13 posiciones sucias.
    int indicesSucios[13];
    int suciedad = 0;

    // Generamos el arreglo aleatorio de 20 (0 = limpio, 1 = sucio) limitando a máximo 13 celdas sucias.
    for (int i = 0; i < 20; i++) {

        // Generamos un número aleatorio para la celda actual
        datoLimpieza = datoLimpieza * 1664525 + 1013904223;
        int b = (datoLimpieza >> 16) % 2;

        // Si el número es 0, la celda es limpia
        if (b == 0) {
            limpieza[i] = 0;
            continue;
        }

        // Si el número es 1, la celda es sucia
        limpieza[i] = 1;

        // Si hay menos de 13 celdas sucias, la celda actual se convierte en sucia
        if (suciedad < 13) {
            limpieza[i] = 1;
            indicesSucios[suciedad] = i;
            suciedad++;
            continue;
        }

        // Si hay más de 13 celdas sucias, la celda actual se convierte en limpia
        limpieza[i] = 0;
        // Elige aleatoriamente una celda sucia para limpiar
        datoLimpieza = datoLimpieza * 1664525 + 1013904223;
        int r = (datoLimpieza >> 16) % (suciedad + 1);

        // Si la celda elegida es una celda sucia, la convierte en limpia
        if (r < 13) {
            limpieza[indicesSucios[r]] = 0;
            limpieza[i] = 1;
            indicesSucios[r] = i;
        } else {
            limpieza[i] = 0;
        }
    }

    std::cout << "Generando entorno de limpieza aleatorio (0=Limpio, 1=Sucio)." << std::endl;
    imprimirVertical(limpieza, -1, "Estado inicial del entorno:");

    esperarEnter("\nPresiona Enter para iniciar la aspiradora...");

    // Simulamos la aspiradora en el entorno
    for (int i = 0; i < 20; i++) {

        // Mostrar el estado actual del entorno
        std::cout << "\n";
        imprimirVertical(limpieza, i, "Aspiradora en la celda actual:");
        std::cout << "Celda [" << i << "]: " << (limpieza[i] == 1 ? "Sucio" : "Limpio") << std::endl;

        // Esperar a que el usuario presione Enter para actuar
        esperarEnter("Presiona Enter para actuar...");

        // Si la celda actual es sucia, la recoge
        // Si la celda actual es limpia, no hace nada
        if (limpieza[i] == 1) {

            // Recogemos la celda actual en la aspiradora y la convierte en limpia
            int* nuevo = new int[tamañoAspiradora + 1];

            // Copiamos los elementos actuales de la aspiradora al arreglo arreglo nuevo
            for (int j = 0; j < tamañoAspiradora; j++) {
                nuevo[j] = aspiradora[j];
            }

            // Agregamos la celda actual al arreglo arreglo nuevo
            nuevo[tamañoAspiradora] = i;

            // Liberamos la memoria del arreglo anterior
            delete[] aspiradora;
            
            // Asignamos el arreglo arreglo nuevo a la aspiradora
            aspiradora = nuevo;

            // Incrementamos el tamaño del arreglo arreglo nuevo
            tamañoAspiradora++;

            // Convertimos la celda actual en limpia
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

    // Mostramos los índices de las celdas recogidas
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