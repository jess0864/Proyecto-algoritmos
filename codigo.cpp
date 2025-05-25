/**
 * @file codigo.cpp
 * @brief Archivo principal que implementa el menú y la lógica de interacción del sistema de gestión de acciones y noticias financieras.
 */

#include "empresa.h"
#include "noticia.h"
#include "portafolio.h"
#include <set> // Para evitar duplicados en recomendaciones

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
    cout << " 4. Gestión de portafolio\n"; // <-- Agregado
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
 * @brief Muestra el submenú de opciones relacionadas con el portafolio.
 */
void mostrarMenuPortafolio() {
    cout << "\n------ GESTIÓN DE PORTAFOLIO ------\n";
    cout << " 1. Comprar acción\n";
    cout << " 2. Vender acción\n";
    cout << " 3. Ver portafolio\n";
    cout << " 4. Ver recomendaciones de inversión\n";
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
    ColaPrioridadNoticias colaNoticias; ///< Cola de prioridad para noticias financieras

    // Relaciones ejemplo para recomendaciones
    // grafo.agregarRelacion("AAPL", "NVDA");
    // grafo.agregarRelacion("AAPL", "ADBE");
    // grafo.agregarRelacion("GOOG", "AMZN");
    // grafo.agregarRelacion("MSFT", "MSFT_CLOUD_PARTNER");
    // grafo.agregarRelacion("AMZN", "NFLX");
    // grafo.agregarRelacion("NVDA", "TSLA");

    // --- Portafolio interactivo ---
    string nombreUsuario;
    cout << "Ingrese su nombre: ";
    getline(cin, nombreUsuario);
    float presupuesto;
    cout << "Ingrese su presupuesto inicial ($): ";
    cin >> presupuesto;
    cin.ignore();
    Portafolio usuario(nombreUsuario);

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
                    // Normalizar a mayúsculas
                    for (auto& c : ticker) c = toupper(c);
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
        } else if (opcionPrincipal == 4) {
            // --- Menú de portafolio interactivo ---
            int opPort;
            do {
                mostrarMenuPortafolio();
                cin >> opPort;
                cin.ignore();
                if (opPort == 1) {
                    // Comprar acción
                    arbol.imprimirEmpresas();
                    string ticker;
                    cout << "Ingrese el ticker de la empresa a comprar: ";
                    getline(cin, ticker);
                    Empresa* emp = arbol.buscarEmpresa(ticker);
                    if (!emp) {
                        cout << "Empresa no encontrada.\n";
                        continue;
                    }
                    cout << "Precio actual de " << emp->nombre << " (" << emp->ticker << "): $" << emp->precioActual << endl;
                    cout << "¿Cuántas acciones desea comprar?: ";
                    int cantidad;
                    cin >> cantidad;
                    cin.ignore();
                    float total = emp->precioActual * cantidad;
                    if (cantidad <= 0) {
                        cout << "Cantidad inválida.\n";
                    } else if (total > presupuesto) {
                        cout << "No tiene suficiente presupuesto. Total requerido: $" << total << ", disponible: $" << presupuesto << endl;
                    } else {
                        presupuesto -= total;
                        for (int i = 0; i < cantidad; ++i)
                            usuario.agregarActivo(emp->ticker);
                        cout << "Compra realizada. Presupuesto restante: $" << presupuesto << endl;
                    }
                } else if (opPort == 2) {
                    // Vender acción
                    usuario.mostrar();
                    string ticker;
                    cout << "Ingrese el ticker de la acción a vender: ";
                    getline(cin, ticker);
                    Empresa* emp = arbol.buscarEmpresa(ticker);
                    if (!emp) {
                        cout << "Empresa no encontrada.\n";
                        continue;
                    }
                    cout << "¿Cuántas acciones desea vender?: ";
                    int cantidad;
                    cin >> cantidad;
                    cin.ignore();
                    int enPortafolio = 0;
                    vector<string> activos = usuario.obtenerActivos();
                    for (const auto& act : activos)
                        if (act == ticker) enPortafolio++;
                    if (cantidad <= 0 || cantidad > enPortafolio) {
                        cout << "Cantidad inválida. Usted posee " << enPortafolio << " acciones de " << ticker << ".\n";
                    } else {
                        for (int i = 0; i < cantidad; ++i)
                            usuario.eliminarActivo(ticker);
                        float total = emp->precioActual * cantidad;
                        presupuesto += total;
                        cout << "Venta realizada. Presupuesto actual: $" << presupuesto << endl;
                    }
                } else if (opPort == 3) {
                    // Ver portafolio
                    usuario.mostrar();
                    cout << "Presupuesto disponible: $" << presupuesto << endl;
                } else if (opPort == 4) {
                    // Recomendaciones de inversión con opciones avanzadas
                    int subop;
                    cout << "\n=== Recomendaciones de inversión ===\n";
                    cout << " 1. Ver todas las recomendaciones\n";
                    cout << " 2. Ver recomendaciones por sector\n";
                    cout << " 3. Ver recomendación para una acción específica\n";
                    cout << "Seleccione una opción: ";
                    cin >> subop;
                    cin.ignore();

                    vector<Empresa*> todas = arbol.obtenerEmpresasOrdenadas();
                    vector<string> activos = usuario.obtenerActivos();
                    set<string> yaPosee(activos.begin(), activos.end());

                    if (subop == 1) {
                        // Todas las recomendaciones
                        bool alguna = false;
                        for (auto e : todas) {
                            if (yaPosee.find(e->ticker) == yaPosee.end()) {
                                cout << "- " << e->ticker << " (" << e->nombre << ")\n";
                                usuario.recomendarCompra(e->ticker, arbol, colaNoticias);
                                alguna = true;
                            }
                        }
                        if (!alguna) {
                            cout << "(No hay nuevas recomendaciones basadas en el portafolio actual)\n";
                        }
                    } else if (subop == 2) {
                        // Recomendaciones por sector
                        cout << "Sectores disponibles:\n";
                        for (size_t i = 0; i < SECTORES_EMPRESA.size(); ++i) {
                            cout << "  " << (i+1) << ". " << SECTORES_EMPRESA[i] << endl;
                        }
                        cout << "Seleccione el número del sector: ";
                        int idxSector;
                        cin >> idxSector;
                        cin.ignore();
                        if (idxSector < 1 || idxSector > (int)SECTORES_EMPRESA.size()) {
                            cout << "Sector inválido.\n";
                        } else {
                            string sectorSel = SECTORES_EMPRESA[idxSector-1];
                            bool alguna = false;
                            for (auto e : todas) {
                                if (yaPosee.find(e->ticker) == yaPosee.end() && e->sector == sectorSel) {
                                    cout << "- " << e->ticker << " (" << e->nombre << ")\n";
                                    usuario.recomendarCompra(e->ticker, arbol, colaNoticias);
                                    alguna = true;
                                }
                            }
                            if (!alguna) {
                                cout << "(No hay recomendaciones para ese sector o ya posee todas las acciones)\n";
                            }
                        }
                    } else if (subop == 3) {
                        // Recomendación para una acción específica
                        cout << "Ingrese el ticker de la acción a analizar: ";
                        string ticker;
                        getline(cin, ticker);
                        Empresa* emp = arbol.buscarEmpresa(ticker);
                        if (!emp) {
                            cout << "Empresa no encontrada.\n";
                        } else if (yaPosee.find(ticker) != yaPosee.end()) {
                            cout << "Ya posee esta acción en su portafolio.\n";
                        } else {
                            cout << "- " << emp->ticker << " (" << emp->nombre << ")\n";
                            usuario.recomendarCompra(emp->ticker, arbol, colaNoticias);
                        }
                    } else {
                        cout << "Opción inválida.\n";
                    }
                }
            } while (opPort != 0);
        }
    } while (opcionPrincipal != 0);
    cout << "Saliendo...\n";
    return 0;
}
