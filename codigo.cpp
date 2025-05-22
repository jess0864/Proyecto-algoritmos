/**
 * @file codigo.cpp
 * @brief Sistema de gestión de acciones y noticias financieras.
 * 
 * Este archivo contiene la función principal y el menú de usuario para interactuar
 * con el árbol de empresas y sus precios históricos.
 */

#include "empresa.h"

/**
 * @brief Muestra el menú principal de opciones al usuario.
 */
void mostrarMenu() {
    cout << "\n--- Sistema de Gestión de Acciones ---\n";
    cout << "1. Buscar empresa por ticker\n";
    cout << "2. Imprimir empresas (orden alfabético)\n";
    cout << "3. Imprimir empresas (por precio actual descendente)\n";
    cout << "4. Mostrar historial de precios de una empresa\n";
    cout << "5. Calcular promedio móvil de una empresa\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opción: ";
}

/**
 * @brief Función principal del programa.
 * 
 * Inicializa el árbol de empresas y permite al usuario interactuar con el sistema
 * mediante un menú de opciones.
 * 
 * @return int Código de salida del programa.
 */
int main() {
    ABBEmpresas arbol; ///< Árbol binario de búsqueda de empresas
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();
        if (opcion == 1) { 
            /// Buscar empresa por ticker
            string ticker;
            cout << "Ticker: "; getline(cin, ticker);
            Empresa* emp = arbol.buscarEmpresa(ticker);
            if (emp) {
                cout << emp->ticker << " | " << emp->nombre << " | " << emp->sector
                     << " | Precio actual: " << emp->precioActual << endl;
            } else {
                cout << "Empresa no encontrada.\n";
            }
        } else if (opcion == 2) { 
            /// Imprimir empresas (orden alfabético)
            arbol.imprimirEmpresas();
        } else if (opcion == 3) { 
            /// Imprimir empresas (por precio actual descendente)
            arbol.imprimirPorPrecio();
        } else if (opcion == 4) { 
            /// Mostrar historial de precios de una empresa
            string ticker;
            cout << "Ticker: "; getline(cin, ticker);
            Empresa* emp = arbol.buscarEmpresa(ticker);
            if (emp) {
                cout << "Historial de precios de " << emp->ticker << ": ";
                emp->historialPrecios.imprimir();
            } else {
                cout << "Empresa no encontrada.\n";
            }
        } else if (opcion == 5) { 
            /// Calcular promedio móvil de una empresa
            string ticker;
            int dias;
            cout << "Ticker: "; getline(cin, ticker);
            cout << "Número de días para promedio móvil: "; cin >> dias;
            Empresa* emp = arbol.buscarEmpresa(ticker);
            if (emp) {
                float prom = emp->historialPrecios.promedioMovil(dias);
                cout << "Promedio móvil de " << dias << " días: " << prom << endl;
            } else {
                cout << "Empresa no encontrada.\n";
            }
            cin.ignore();
        }
    } while (opcion != 0);
    cout << "Saliendo...\n";
    return 0;
}
