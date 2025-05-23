#ifndef NOTICIA_H
#define NOTICIA_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "empresa.h"
using namespace std;

/// @brief Estructura que representa una noticia con impacto, título, descripción, sector afectado, fecha y puntero al siguiente nodo.
/**
 * Estructura utilizada para almacenar la información de una noticia en la cola de prioridad.
 */
struct Noticia {
    int impacto;             ///< Nivel de impacto de 1 a 10
    string titulo;           ///< Título de la noticia
    string descripcion;      ///< Descripción de la noticia
    string sectorAfectado;   ///< Sector afectado por la noticia
    string fecha;            ///< Fecha en formato "YYYY-MM-DD"
    Noticia* siguiente;      ///< Puntero a la siguiente noticia en la lista

    /**
     * @brief Constructor de la estructura Noticia.
     * @param imp Nivel de impacto de la noticia.
     * @param t Título de la noticia.
     * @param d Descripción de la noticia.
     * @param s Sector afectado.
     * @param f Fecha de la noticia.
     */
    Noticia(int imp, string t, string d, string s, string f) {
        impacto = imp;
        titulo = t;
        descripcion = d;
        sectorAfectado = s;
        fecha = f;
        siguiente = nullptr;
    }
};

/// @brief Clase que implementa una cola de prioridad para noticias, ordenadas por impacto.
/**
 * Permite insertar, mostrar, buscar, extraer y ordenar noticias, así como calcular estadísticas.
 */
class ColaPrioridadNoticias {
private:
    Noticia* frente; ///< Puntero al primer elemento de la cola

public:
    /// @brief Constructor de la cola de prioridad.
    ColaPrioridadNoticias() {
        frente = nullptr;
    }

    /// @brief Verifica si la cola está vacía.
    /// @return true si la cola está vacía, false en caso contrario.
    bool estaVacia() {
        return frente == nullptr;
    }

    /**
     * @brief Inserta una noticia en la cola de prioridad según su impacto.
     * @param impacto Nivel de impacto de la noticia.
     * @param titulo Título de la noticia.
     * @param descripcion Descripción de la noticia.
     * @param sector Sector afectado.
     * @param fecha Fecha de la noticia.
     */
    void insertar(int impacto, string titulo, string descripcion, string sector, string fecha) {
        Noticia* nueva = new Noticia(impacto, titulo, descripcion, sector, fecha);

        if (frente == nullptr || impacto > frente->impacto) {
            nueva->siguiente = frente;
            frente = nueva;
        } else {
            Noticia* actual = frente;
            while (actual->siguiente != nullptr && actual->siguiente->impacto >= impacto) {
                actual = actual->siguiente;
            }
            nueva->siguiente = actual->siguiente;
            actual->siguiente = nueva;
        }
    }

    /// @brief Muestra todas las noticias en la cola, en orden de prioridad.
    void mostrar() {
        Noticia* actual = frente;
        while (actual != nullptr) {
            cout << "[" << actual->fecha << "] "
                 << "(Impacto: " << actual->impacto << ") "
                 << actual->titulo << " - " << actual->sectorAfectado << endl;
            actual = actual->siguiente;
        }
    }

    /**
     * @brief Busca y muestra noticias que pertenecen a un sector específico.
     * @param sectorClave Nombre del sector a buscar.
     */
    void buscarPorSector(string sectorClave) {
        Noticia* actual = frente;
        cout << "\n🔍 Noticias en el sector '" << sectorClave << "':\n";
        while (actual != nullptr) {
            if (actual->sectorAfectado == sectorClave) {
                cout << "- " << actual->titulo << " (Impacto: " << actual->impacto << ")\n";
            }
            actual = actual->siguiente;
        }
    }

    /**
     * @brief Busca y muestra noticias cuyo título contiene una palabra clave.
     * @param palabra Palabra clave a buscar en los títulos.
     */
    void buscarPorPalabraClave(string palabra) {
        Noticia* actual = frente;
        cout << "\n🔍 Noticias con '" << palabra << "' en el título:\n";
        while (actual != nullptr) {
            if (actual->titulo.find(palabra) != string::npos) {
                cout << "- " << actual->titulo << " (" << actual->sectorAfectado << ")\n";
            }
            actual = actual->siguiente;
        }
    }

    /// @brief Detecta si hay una alerta de crisis (3 o más noticias con impacto >= 8).
    /// @return true si hay alerta de crisis, false en caso contrario.
    bool hayAlertaDeCrisis() {
        Noticia* actual = frente;
        int contador = 0;
        while (actual != nullptr) {
            if (actual->impacto >= 8) {
                contador++;
                if (contador >= 3) return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    /// @brief Calcula el promedio del impacto de todas las noticias en la cola.
    /// @return Promedio del impacto (float).
    float promedioImpacto() {
        if (estaVacia()) return 0;

        Noticia* actual = frente;
        float suma = 0;
        int total = 0;
        while (actual != nullptr) {
            suma += actual->impacto;
            total++;
            actual = actual->siguiente;
        }
        return suma / total;
    }

    /// @brief Extrae y retorna la noticia con mayor prioridad (mayor impacto).
    /// @return Puntero a la noticia extraída, o nullptr si la cola está vacía.
    Noticia* extraer() {
        if (estaVacia()) return nullptr;

        Noticia* temp = frente;
        frente = frente->siguiente;
        temp->siguiente = nullptr;
        return temp;
    }

    /// @brief Llena un vector con punteros a todas las noticias en la cola (en orden actual).
    void obtenerNoticias(vector<Noticia*>& noticias) {
        Noticia* actual = frente;
        while (actual) {
            noticias.push_back(actual);
            actual = actual->siguiente;
        }
    }

    // ======= ORDENAMIENTO POR FECHA (MERGE SORT) =======

    /**
     * @brief Divide la lista enlazada de noticias en dos mitades.
     * @param cabeza Puntero al inicio de la lista.
     * @return Puntero al inicio de la segunda mitad.
     */
    Noticia* dividir(Noticia* cabeza) {
        if (!cabeza || !cabeza->siguiente) return nullptr;

        Noticia* lenta = cabeza;
        Noticia* rapida = cabeza->siguiente;

        while (rapida && rapida->siguiente) {
            lenta = lenta->siguiente;
            rapida = rapida->siguiente->siguiente;
        }

        Noticia* mitad = lenta->siguiente;
        lenta->siguiente = nullptr;
        return mitad;
    }

    /**
     * @brief Fusiona dos listas enlazadas de noticias ordenadas por fecha.
     * @param a Puntero al inicio de la primera lista.
     * @param b Puntero al inicio de la segunda lista.
     * @return Puntero al inicio de la lista fusionada.
     */
    Noticia* fusionar(Noticia* a, Noticia* b) {
        if (!a) return b;
        if (!b) return a;

        if (a->fecha < b->fecha) {
            a->siguiente = fusionar(a->siguiente, b);
            return a;
        } else {
            b->siguiente = fusionar(a, b->siguiente);
            return b;
        }
    }

    /**
     * @brief Aplica el algoritmo Merge Sort recursivamente para ordenar por fecha.
     * @param cabeza Puntero al inicio de la lista a ordenar.
     * @return Puntero al inicio de la lista ordenada.
     */
    Noticia* mergeSort(Noticia* cabeza) {
        if (!cabeza || !cabeza->siguiente) return cabeza;

        Noticia* mitad = dividir(cabeza);
        Noticia* izquierda = mergeSort(cabeza);
        Noticia* derecha = mergeSort(mitad);

        return fusionar(izquierda, derecha);
    }

    /// @brief Ordena toda la cola de noticias cronológicamente por fecha.
    void ordenarPorFecha() {
        frente = mergeSort(frente);
        cout << "\n📆 Noticias ordenadas por fecha.\n";
    }

    /// @brief Destructor. Libera la memoria de todas las noticias en la cola.
    ~ColaPrioridadNoticias() {
        while (!estaVacia()) {
            Noticia* temp = extraer();
            delete temp;
        }
    }
};

// ======== GENERADOR DE NOTICIAS ALEATORIAS ========

/**
 * @brief Genera un string de fecha con formato "YYYY-MM-DD" a partir de un número de días desde el inicio.
 * @param diasDesdeInicio Número de días a sumar al día base (1 de mayo de 2025).
 * @return Fecha en formato "YYYY-MM-DD".
 */
string generarFecha(int diasDesdeInicio = 0) {
    int year = 2025;
    int month = 5;
    int day = 1 + diasDesdeInicio;

    // Ajustar el día y el mes si se pasa del final del mes
    while (true) {
        int diasMes;
        if (month == 2) diasMes = 28;
        else if (month == 4 || month == 6 || month == 9 || month == 11) diasMes = 30;
        else diasMes = 31;
        if (day > diasMes) {
            day -= diasMes;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        } else {
            break;
        }
    }

    string fecha = "";
    fecha += to_string(year) + "-";
    if (month < 10) fecha += "0";
    fecha += to_string(month) + "-";
    if (day < 10) fecha += "0";
    fecha += to_string(day);
    return fecha;
}

/**
 * @brief Genera noticias aleatorias y las inserta en la cola de prioridad.
 * @param cola Referencia a la cola de prioridad de noticias.
 * @param cantidad Número de noticias a generar.
 * @param semilla Semilla para el generador aleatorio (por defecto 1234).
 */
void generarNoticiasAleatorias(ColaPrioridadNoticias& cola, int cantidad, int semilla = 1234) {
    srand(semilla);  // Semilla reproducible

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

    // Usa los sectores globales de empresa.h
    for (int i = 0; i < cantidad; ++i) {
        int impacto = rand() % 10 + 1;
        string titulo = titulos[rand() % titulos.size()];
        string descripcion = descripciones[rand() % descripciones.size()];
        string sector = SECTORES_EMPRESA[rand() % SECTORES_EMPRESA.size()];
        string fecha = generarFecha(i);  // Avanza un día por noticia

        cola.insertar(impacto, titulo, descripcion, sector, fecha);
    }
}

/**
 * @brief Muestra el ajuste aplicado a los precios de un sector.
 * @param sector Sector afectado.
 * @param porcentaje Porcentaje aplicado.
 */
inline void mostrarAjusteSector(const string& sector, float porcentaje) {
    cout << "  > Ajuste aplicado al sector '" << sector << "': ";
    if (porcentaje > 0)
        cout << "+" << porcentaje * 100 << "%\n";
    else if (porcentaje < 0)
        cout << porcentaje * 100 << "%\n";
    else
        cout << "Sin cambio\n";
}

/**
 * @brief Calcula el porcentaje de ajuste según el impacto.
 * @param impacto Impacto de la noticia (1-10).
 * @return Porcentaje como valor decimal.
 */
inline float calcularPorcentajeAjuste(int impacto) {
    if (impacto > 5)
        return (impacto - 5) * 0.01;
    else
        return -(6 - impacto) * 0.01;
}

/**
 * @brief Muestra los cambios de precio de una empresa por cada noticia que la afectó, mostrando el precio antes y después para cada fecha de noticia.
 * @param arbol Árbol de empresas.
 * @param colaNoticias Cola de noticias.
 */
inline void mostrarCambiosPorNoticiasEmpresa(ABBEmpresas& arbol, ColaPrioridadNoticias& colaNoticias) {
    string ticker;
    cout << "Ingrese el ticker de la empresa a consultar: ";
    getline(cin, ticker);
    Empresa* emp = arbol.buscarEmpresa(ticker);
    if (!emp) {
        cout << "Empresa no encontrada.\n";
        return;
    }
    vector<Noticia*> noticias;
    colaNoticias.obtenerNoticias(noticias);
    bool alguna = false;
    cout << "\n================= CAMBIOS DE " << emp->nombre << " (" << emp->ticker << ") POR NOTICIAS =================\n";
    cout << " Fecha       | Título de la noticia                | Precio antes | Precio después | Cambio | Cambio (%)\n";
    cout << "--------------------------------------------------------------------------------------------------------\n";
    for (auto noticia : noticias) {
        if (emp->sector == noticia->sectorAfectado) {
            NodoPrecio* p = emp->historialPrecios.cabeza;
            float precioEnFecha = -1, precioAnterior = -1;
            string fechaAnterior = "";
            while (p) {
                if (p->fecha == noticia->fecha) {
                    precioEnFecha = p->precioCierre;
                } else if (p->fecha < noticia->fecha) {
                    if (fechaAnterior == "" || p->fecha > fechaAnterior) {
                        precioAnterior = p->precioCierre;
                        fechaAnterior = p->fecha;
                    }
                }
                p = p->siguiente;
            }
            if (precioEnFecha >= 0 && precioAnterior >= 0) {
                // Fecha
                cout << noticia->fecha << " | ";
                // Título (máx 32)
                int n = 0;
                for (; n < 32 && noticia->titulo[n] != '\0'; ++n) cout << noticia->titulo[n];
                for (; n < 32; ++n) cout << " ";
                cout << " | ";
                // Precio antes
                cout << precioAnterior << "      | ";
                // Precio después
                cout << precioEnFecha << "        | ";
                // Cambio absoluto
                float cambio = precioEnFecha - precioAnterior;
                float porcentaje = (precioAnterior != 0) ? (cambio / precioAnterior) * 100.0f : 0.0f;
                if (cambio > 0) cout << "+";
                cout << cambio << "    | ";
                if (porcentaje > 0) cout << "+";
                cout << porcentaje << "%\n";
                alguna = true;
            }
        }
    }
    if (!alguna) {
        cout << "No hay noticias que hayan afectado a esta empresa.\n";
    }
    cout << "========================================================================================================\n";
}

/**
 * @brief Muestra el impacto de las noticias en las acciones de las empresas.
 * @param arbol Árbol binario de búsqueda de empresas.
 * @param colaNoticias Cola de prioridad de noticias.
 */
inline void mostrarImpactoNoticiasEnAcciones(ABBEmpresas& arbol, ColaPrioridadNoticias& colaNoticias) {
    vector<Noticia*> noticias;
    colaNoticias.obtenerNoticias(noticias);
    if (noticias.empty()) {
        cout << "No hay noticias registradas.\n";
        return;
    }
    cout << "\n================= IMPACTO DE NOTICIAS EN EMPRESAS =================\n";
    for (auto actual : noticias) {
        cout << "\n---------------------------------------------------------------\n";
        cout << "[" << actual->fecha << "] " << actual->titulo << " (Impacto: " << actual->impacto << ", Sector: " << actual->sectorAfectado << ")\n";
        cout << "---------------------------------------------------------------\n";
        cout << " Ticker   | Precio antes | Precio después | Cambio absoluto | Cambio (%)\n";
        cout << "---------------------------------------------------------------\n";
        vector<Empresa*> empresas = arbol.obtenerEmpresasOrdenadas();
        bool alguna = false;
        for (auto e : empresas) {
            if (e->sector == actual->sectorAfectado) {
                NodoPrecio* p = e->historialPrecios.cabeza;
                float precioEnFecha = -1, precioAnterior = -1;
                string fechaAnterior = "";
                while (p) {
                    if (p->fecha == actual->fecha) {
                        precioEnFecha = p->precioCierre;
                    } else if (p->fecha < actual->fecha) {
                        if (fechaAnterior == "" || p->fecha > fechaAnterior) {
                            precioAnterior = p->precioCierre;
                            fechaAnterior = p->fecha;
                        }
                    }
                    p = p->siguiente;
                }
                if (precioEnFecha >= 0 && precioAnterior >= 0) {
                    float cambio = precioEnFecha - precioAnterior;
                    float porcentaje = (precioAnterior != 0) ? (cambio / precioAnterior) * 100.0f : 0.0f;
                    // Ticker (máx 8)
                    int t = 0;
                    cout << " ";
                    for (; t < 8 && e->ticker[t] != '\0'; ++t) cout << e->ticker[t];
                    for (; t < 8; ++t) cout << " ";
                    cout << " | ";
                    // Precio antes
                    cout << precioAnterior << "      | ";
                    // Precio después
                    cout << precioEnFecha << "        | ";
                    // Cambio absoluto
                    if (cambio > 0) cout << "+";
                    cout << cambio << "         | ";
                    // Cambio porcentual
                    if (porcentaje > 0) cout << "+";
                    cout << porcentaje << "%\n";
                    alguna = true;
                } else if (precioEnFecha >= 0) {
                    int t = 0;
                    cout << " ";
                    for (; t < 8 && e->ticker[t] != '\0'; ++t) cout << e->ticker[t];
                    for (; t < 8; ++t) cout << " ";
                    cout << " | N/A         | " << precioEnFecha << "        | N/A           | N/A\n";
                    alguna = true;
                }
            }
        }
        if (!alguna) cout << "  No hubo empresas afectadas en ese sector.\n";
    }
    cout << "===================================================================\n";
}

#endif
