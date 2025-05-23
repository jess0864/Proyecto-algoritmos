// Código base para un sistema de gestión de acciones y noticias financieras

#include "empresa.h"
#include "noticia.h"

// Añade declaración externa para los sectores de empresa.h
extern const vector<string> SECTORES_EMPRESA;

/**
 * @brief Muestra el menú principal para elegir entre opciones por empresa, sector o noticias.
 */
void mostrarMenuPrincipal() {
    cout << "\n================ MENÚ PRINCIPAL ================\n";
    cout << " 1. Consultas de empresas\n";
    cout << " 2. Consultas por sector\n";
    cout << " 3. Simulación y noticias\n";
    cout << " 0. Salir\n";
    cout << "-----------------------------------------------\n";
    cout << "Seleccione una opción: ";
}

/**
 * @brief Muestra el submenú de opciones relacionadas con empresas.
 * 
 * Permite al usuario buscar empresas, imprimir listados, ver historial, calcular promedios y buscar por rango de precio.
 */
void mostrarMenuEmpresa() {
    cout << "\n------ CONSULTAS DE EMPRESAS ------\n";
    cout << " 1. Buscar empresa por ticker\n";
    cout << " 2. Listar empresas (alfabético)\n";
    cout << " 3. Listar empresas (por precio descendente)\n";
    cout << " 4. Historial y promedio móvil de precios\n";
    cout << " 5. Buscar empresas por rango de precio\n";
    cout << " 6. Empresa con acción más barata/cara\n";
    cout << " 0. Volver al menú principal\n";
    cout << "-----------------------------------\n";
    cout << "Seleccione una opción: ";
}

/**
 * @brief Muestra el submenú de opciones relacionadas con sectores.
 * 
 * Permite al usuario imprimir empresas por sector y ver promedios de precios por sector.
 */
void mostrarMenuSector() {
    cout << "\n------ CONSULTAS POR SECTOR ------\n";
    cout << " 1. Listar empresas por sector\n";
    cout << " 2. Promedio de precios por sector\n";
    cout << " 0. Volver al menú principal\n";
    cout << "----------------------------------\n";
    cout << "Seleccione una opción: ";
}

/**
 * @brief Muestra el submenú de opciones relacionadas con simulación y noticias financieras.
 * 
 * Permite al usuario gestionar noticias financieras, incluyendo inserción, búsqueda, ordenamiento y análisis.
 */
void mostrarMenuSimulacion() {
    cout << "\n------ SIMULACIÓN Y NOTICIAS ------\n";
    cout << " 1. Insertar noticia manualmente y ajustar precios\n";
    cout << " 2. Generar noticias aleatorias y simular mercado\n";
    cout << " 3. Mostrar noticias (por prioridad o fecha)\n";
    cout << " 4. Buscar noticias (por sector o palabra clave)\n";
    cout << " 5. Estadísticas y alertas de noticias\n";
    cout << " 6. Ver cambios de todas las empresas dadas las noticias\n";
    cout << " 7. Ver cambios de una empresa en específico dadas las noticias\n";
    cout << " 0. Volver al menú principal\n";
    cout << "-----------------------------------\n";
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
    ColaPrioridadNoticias colaNoticias; ///< Cola de prioridad para noticias financieras.
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
                    /// Mostrar historial de precios de una empresa específica y calcular promedio móvil
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
                        int dias;
                        cout << "¿Calcular promedio móvil? (Ingrese días o 0 para omitir): ";
                        cin >> dias;
                        cin.ignore();
                        if (dias > 0) {
                            float prom = emp->historialPrecios.promedioMovil(dias);
                            cout << "Promedio móvil de " << dias << " días: " << prom << endl;
                        }
                    } else {
                        cout << "Empresa no encontrada.\n";
                    }
                } else if (opcionEmpresa == 5) { 
                    /// Buscar empresas cuyo precio actual está en un rango dado
                    float minPrecio, maxPrecio;
                    cout << "Ingrese el precio mínimo: "; cin >> minPrecio;
                    cout << "Ingrese el precio máximo: "; cin >> maxPrecio;
                    cin.ignore();
                    vector<Empresa*> resultado = arbol.buscarEmpresasPorRangoPrecio(minPrecio, maxPrecio);
                    arbol.imprimirEmpresas(resultado);
                } else if (opcionEmpresa == 6) { 
                    /// Mostrar la empresa con la acción más barata y más cara
                    Empresa* minEmp = arbol.obtenerEmpresaMasBarata();
                    Empresa* maxEmp = arbol.obtenerEmpresaMasCara();
                    cout << "\nEmpresa con acción más barata:\n";
                    arbol.imprimirEmpresa(minEmp);
                    cout << "\nEmpresa con acción más cara:\n";
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
        } else if (opcionPrincipal == 3) {
            /// Opciones relacionadas con simulación y noticias financieras
            int opcionSim;
            do {
                mostrarMenuSimulacion();
                cin >> opcionSim;
                cin.ignore();
                if (opcionSim == 1) {
                    // Insertar noticia manualmente y ajustar precios
                    int impacto;
                    string titulo, descripcion, sector, fecha;
                    cout << "Impacto (1-10): "; cin >> impacto; cin.ignore();
                    cout << "Título: "; getline(cin, titulo);
                    cout << "Descripción: "; getline(cin, descripcion);
                    cout << "Sectores disponibles:\n";
                    for (const auto& s : SECTORES_EMPRESA) {
                        cout << "  - " << s << endl;
                    }
                    cout << "Sector: "; getline(cin, sector);
                    cout << "Fecha (YYYY-MM-DD): "; getline(cin, fecha);
                    colaNoticias.insertar(impacto, titulo, descripcion, sector, fecha);
                    arbol.ajustarPreciosPorNoticia(sector, impacto, fecha);
                    cout << "\nNoticia generada y precios ajustados.\n";
                } else if (opcionSim == 2) {
                    // Generar noticias aleatorias y simular mercado
                    int cantidad;
                    cout << "Cantidad de noticias aleatorias a generar: ";
                    cin >> cantidad;
                    cin.ignore();
                    vector<string> titulos = {
                        "Caída del dólar", "Nuevo impuesto", "Reforma pensional", "Crisis energética",
                        "Inversión extranjera", "Caída de acciones tecnológicas", "Sube el petróleo",
                        "Aumento del salario mínimo", "Devaluación del peso", "Acuerdo comercial firmado"
                    };
                    vector<string> descripciones = {
                        "Los mercados reaccionan ante la noticia.",
                        "Expertos prevén cambios importantes en el comportamiento bursátil.",
                        "Los sectores económicos muestran señales de volatilidad.",
                        "Los analistas recomiendan cautela a los inversionistas.",
                        "Impacto inmediato esperado en el mercado accionario."
                    };
                    cout << "\nNoticias generadas y ajustes aplicados:\n";
                    for (int i = 0; i < cantidad; ++i) {
                        int impacto = rand() % 10 + 1;
                        string titulo = titulos[rand() % titulos.size()];
                        string descripcion = descripciones[rand() % descripciones.size()];
                        string sector = SECTORES_EMPRESA[rand() % SECTORES_EMPRESA.size()];
                        string fecha = generarFecha(i);
                        colaNoticias.insertar(impacto, titulo, descripcion, sector, fecha);
                        arbol.ajustarPreciosPorNoticia(sector, impacto, fecha);
                        cout << "  [" << fecha << "] (Impacto: " << impacto << ") " << titulo << " - " << sector << endl;
                        mostrarAjusteSector(sector, calcularPorcentajeAjuste(impacto));
                    }
                    cout << "Noticias aleatorias generadas y precios ajustados.\n";
                } else if (opcionSim == 3) {
                    // Mostrar noticias (elige orden)
                    int subop;
                    cout << "1. Por prioridad (impacto)\n2. Por fecha\nSeleccione: ";
                    cin >> subop; cin.ignore();
                    if (subop == 1) {
                        colaNoticias.mostrar();
                    } else if (subop == 2) {
                        colaNoticias.ordenarPorFecha();
                        colaNoticias.mostrar();
                    }
                } else if (opcionSim == 4) {
                    // Buscar noticias
                    int subop;
                    cout << "1. Por sector\n2. Por palabra clave\nSeleccione: ";
                    cin >> subop; cin.ignore();
                    if (subop == 1) {
                        string sector;
                        cout << "Sector: "; getline(cin, sector);
                        colaNoticias.buscarPorSector(sector);
                    } else if (subop == 2) {
                        string palabra;
                        cout << "Palabra clave: "; getline(cin, palabra);
                        colaNoticias.buscarPorPalabraClave(palabra);
                    }
                } else if (opcionSim == 5) {
                    // Estadísticas y alertas
                    float promedio = colaNoticias.promedioImpacto();
                    cout << "Impacto promedio de las noticias: " << promedio << endl;
                    if (colaNoticias.hayAlertaDeCrisis()) {
                        cout << "ALERTA: Se detecta posible crisis. Hay múltiples noticias de alto impacto.\n";
                    } else {
                        cout << "No hay señales de crisis por ahora.\n";
                    }
                } else if (opcionSim == 6) {
                    // Mostrar cambios de acciones por noticias (todas las empresas)
                    mostrarImpactoNoticiasEnAcciones(arbol, colaNoticias);
                } else if (opcionSim == 7) {
                    // Mostrar cambios de una empresa por noticias
                    mostrarCambiosPorNoticiasEmpresa(arbol, colaNoticias);
                }
            } while (opcionSim != 0);
        }
    } while (opcionPrincipal != 0);
    cout << "Saliendo...\n";
    return 0;
}
