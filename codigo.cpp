// Código base para un sistema de gestión de acciones y noticias financieras

#include "empresa.h"

/**
 * @brief Muestra el menú principal para elegir entre opciones por empresa o por sector.
 */
void mostrarMenuPrincipal() {
    cout << "\n--- Sistema de Gestión de Acciones ---\n";
    cout << "1. Opciones por empresa\n";
    cout << "2. Opciones por sector\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opción: ";
}

/**
 * @brief Muestra el submenú de opciones relacionadas con empresas.
 * 
 * Permite al usuario buscar empresas, imprimir listados, ver historial, calcular promedios y buscar por rango de precio.
 */
void mostrarMenuEmpresa() {
    cout << "\n--- Opciones por empresa ---\n";
    cout << " 1. Buscar empresa por ticker\n";
    cout << " 2. Imprimir empresas (orden alfabético)\n";
    cout << " 3. Imprimir empresas (por precio actual descendente)\n";
    cout << " 4. Mostrar historial de precios de una empresa\n";
    cout << " 5. Calcular promedio móvil de una empresa\n";
    cout << " 6. Buscar empresas por rango de precio actual\n";
    cout << " 7. Empresa con acción más barata\n";
    cout << " 8. Empresa con acción más cara\n";
    cout << " 0. Volver al menú principal\n";
    cout << "Seleccione una opción: ";
}

/**
 * @brief Muestra el submenú de opciones relacionadas con sectores.
 * 
 * Permite al usuario imprimir empresas por sector y ver promedios de precios por sector.
 */
void mostrarMenuSector() {
    cout << "\n--- Opciones por sector ---\n";
    cout << " 1. Imprimir empresas por sector\n";
    cout << " 2. Promedio del precio de acciones por sector\n";
    cout << " 0. Volver al menú principal\n";
    cout << "Seleccione una opción: ";
}

/**
 * @brief Función principal del programa.
 * 
 * Controla el flujo del sistema de gestión de acciones, mostrando menús y ejecutando las opciones seleccionadas por el usuario.
 * 
 * @return 0 al finalizar correctamente.
 */
int main() {
    ABBEmpresas arbol; ///< Árbol binario de búsqueda que almacena todas las empresas.
    int opcionPrincipal;
    do {
        mostrarMenuPrincipal();
        cin >> opcionPrincipal;
        cin.ignore();
        if (opcionPrincipal == 1) { 
            /// Opciones relacionadas con empresas
            int opcionEmpresa;
            do {
                mostrarMenuEmpresa();
                cin >> opcionEmpresa;
                cin.ignore();
                if (opcionEmpresa == 1) { 
                    /// Buscar empresa por ticker y mostrar su información
                    vector<Empresa*> lista = arbol.obtenerEmpresasOrdenadas();
                    cout << "Empresas disponibles:\n";
                    for (auto e : lista) {
                        cout << "  " << e->ticker << " - " << e->nombre << endl;
                    }
                    string ticker;
                    cout << "Ticker: "; getline(cin, ticker);
                    Empresa* emp = arbol.buscarEmpresa(ticker);
                    arbol.imprimirEmpresa(emp);
                } else if (opcionEmpresa == 2) { 
                    /// Imprimir todas las empresas en orden alfabético
                    arbol.imprimirEmpresas();
                } else if (opcionEmpresa == 3) { 
                    /// Imprimir empresas ordenadas por precio actual descendente
                    arbol.imprimirPorPrecio();
                } else if (opcionEmpresa == 4) { 
                    /// Mostrar historial de precios de una empresa específica
                    string ticker;
                    cout << "Ticker: "; getline(cin, ticker);
                    Empresa* emp = arbol.buscarEmpresa(ticker);
                    if (emp) {
                        cout << "Historial de precios de " << emp->nombre << " (" << emp->ticker << "):\n";
                        cout << "------------------------------------------\n";
                        cout << "   Fecha       | Precio de cierre\n";
                        cout << "------------------------------------------\n";
                        NodoPrecio* actual = emp->historialPrecios.cabeza;
                        vector<NodoPrecio*> historial;
                        while (actual) {
                            historial.push_back(actual);
                            actual = actual->siguiente;
                        }
                        for (int i = historial.size() - 1; i >= 0; --i) {
                            for (int f = 0; f < 10 && historial[i]->fecha[f] != '\0'; ++f)
                                cout << historial[i]->fecha[f];
                            for (int f = historial[i]->fecha.size(); f < 12; ++f) cout << " ";
                            cout << "| " << historial[i]->precioCierre << endl;
                        }
                        cout << "------------------------------------------\n";
                    } else {
                        cout << "Empresa no encontrada.\n";
                    }
                } else if (opcionEmpresa == 5) { 
                    /// Calcular el promedio móvil de una empresa
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
                } else if (opcionEmpresa == 6) { 
                    /// Buscar empresas cuyo precio actual está en un rango dado
                    float minPrecio, maxPrecio;
                    cout << "Ingrese el precio mínimo: "; cin >> minPrecio;
                    cout << "Ingrese el precio máximo: "; cin >> maxPrecio;
                    cin.ignore();
                    vector<Empresa*> resultado = arbol.buscarEmpresasPorRangoPrecio(minPrecio, maxPrecio);
                    arbol.imprimirEmpresas(resultado);
                } else if (opcionEmpresa == 7) { 
                    /// Mostrar la empresa con la acción más barata
                    Empresa* minEmp = arbol.obtenerEmpresaMasBarata();
                    arbol.imprimirEmpresa(minEmp);
                } else if (opcionEmpresa == 8) { 
                    /// Mostrar la empresa con la acción más cara
                    Empresa* maxEmp = arbol.obtenerEmpresaMasCara();
                    arbol.imprimirEmpresa(maxEmp);
                }
            } while (opcionEmpresa != 0);
        } else if (opcionPrincipal == 2) { 
            /// Opciones relacionadas con sectores
            int opcionSector;
            do {
                mostrarMenuSector();
                cin >> opcionSector;
                cin.ignore();
                if (opcionSector == 1) { 
                    /// Imprimir todas las empresas de un sector específico
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
                } else if (opcionSector == 2) { 
                    /// Mostrar el promedio del precio actual de las acciones por sector
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
            } while (opcionSector != 0);
        }
    } while (opcionPrincipal != 0);
    cout << "Saliendo...\n";
    return 0;
}
