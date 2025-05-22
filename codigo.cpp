// Código base para un sistema de gestión de acciones y noticias financieras

#include "empresa.h"

/**
 * @brief Muestra el menú principal de opciones por consola.
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
 * Permite gestionar empresas, consultar precios y calcular promedios móviles.
 * @return 0 al finalizar correctamente.
 */
int main() {
    ABBEmpresas arbol;
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();
        if (opcion == 1) { // Buscar empresa por ticker
            string ticker;
            cout << "Ticker: "; getline(cin, ticker);
            Empresa* emp = arbol.buscarEmpresa(ticker);
            if (emp) {
                cout << emp->ticker << " | " << emp->nombre << " | " << emp->sector
                     << " | Precio actual: " << emp->precioActual << endl;
            } else {
                cout << "Empresa no encontrada.\n";
            }
        } else if (opcion == 2) { // Imprimir empresas (orden alfabético)
            arbol.imprimirEmpresas();
        } else if (opcion == 3) { // Imprimir empresas (por precio actual descendente)
            arbol.imprimirPorPrecio();
        } else if (opcion == 4) { // Mostrar historial de precios de una empresa
            string ticker;
            cout << "Ticker: "; getline(cin, ticker);
            Empresa* emp = arbol.buscarEmpresa(ticker);
            if (emp) {
                cout << "Historial de precios de " << emp->ticker << ": ";
                emp->historialPrecios.imprimir();
            } else {
                cout << "Empresa no encontrada.\n";
            }
        } else if (opcion == 5) { // Calcular promedio móvil de una empresa
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
