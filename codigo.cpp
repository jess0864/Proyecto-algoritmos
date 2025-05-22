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
    cout << "6. Imprimir empresas por sector\n";
    cout << "7. Promedio del precio de acciones por sector\n";
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
            // Mostrar empresas disponibles y su ticker antes de pedir el ticker
            vector<Empresa*> lista = arbol.obtenerEmpresasOrdenadas();
            cout << "Empresas disponibles:\n";
            for (auto e : lista) {
                cout << "  " << e->ticker << " - " << e->nombre << endl;
            }
            string ticker;
            cout << "Ticker: "; getline(cin, ticker);
            Empresa* emp = arbol.buscarEmpresa(ticker);
            if (emp) {
                cout << "---------------------------------------------------------------\n";
                cout << " Ticker   | Empresa                  | Sector         | Precio actual\n";
                cout << "---------------------------------------------------------------\n";
                // Ticker (máx 8)
                cout << " ";
                int t = 0;
                for (; t < 8 && emp->ticker[t] != '\0'; ++t) cout << emp->ticker[t];
                for (; t < 8; ++t) cout << " ";
                cout << " | ";
                // Nombre (máx 24)
                int n = 0;
                for (; n < 24 && emp->nombre[n] != '\0'; ++n) cout << emp->nombre[n];
                for (; n < 24; ++n) cout << " ";
                cout << " | ";
                // Sector (máx 14)
                int s = 0;
                for (; s < 14 && emp->sector[s] != '\0'; ++s) cout << emp->sector[s];
                for (; s < 14; ++s) cout << " ";
                cout << " | " << emp->precioActual << endl;
                cout << "---------------------------------------------------------------\n";
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
        } else if (opcion == 6) { // Imprimir empresas por sector
            // Mostrar sectores disponibles antes de pedir el sector
            vector<Empresa*> lista = arbol.obtenerEmpresasOrdenadas();
            vector<string> sectores;
            for (auto e : lista) {
                bool existe = false;
                for (size_t i = 0; i < sectores.size(); ++i) {
                    if (sectores[i] == e->sector) {
                        existe = true;
                        break;
                    }
                }
                if (!existe) sectores.push_back(e->sector);
            }
            cout << "Sectores disponibles:\n";
            for (size_t i = 0; i < sectores.size(); ++i) {
                cout << "  - " << sectores[i] << endl;
            }
            string sector;
            cout << "Sector: "; getline(cin, sector);
            arbol.imprimirEmpresasPorSector(sector);
        } else if (opcion == 7) { // Promedio del precio de acciones por sector
            // Mostrar todos los promedios de todos los sectores
            vector<Empresa*> lista = arbol.obtenerEmpresasOrdenadas();
            vector<string> sectores;
            for (auto e : lista) {
                bool existe = false;
                for (size_t i = 0; i < sectores.size(); ++i) {
                    if (sectores[i] == e->sector) {
                        existe = true;
                        break;
                    }
                }
                if (!existe) sectores.push_back(e->sector);
            }
            cout << "-----------------------------------------------\n";
            cout << " Promedio del precio de acciones por sector\n";
            cout << "-----------------------------------------------\n";
            for (size_t i = 0; i < sectores.size(); ++i) {
                float promedio = arbol.promedioPrecioPorSector(sectores[i]);
                cout << " " << sectores[i] << ": " << promedio << endl;
            }
            cout << "-----------------------------------------------\n";
        }
    } while (opcion != 0);
    cout << "Saliendo...\n";
    return 0;
}
