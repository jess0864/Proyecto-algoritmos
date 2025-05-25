/**
 * @file empresa.h
 * @brief Definición de estructuras y clases para la gestión de empresas y sus precios históricos.
 *
 * Este archivo contiene la definición de la estructura Empresa, el árbol binario de búsqueda ABBEmpresas,
 * y la multilista para el historial de precios de acciones. Permite gestionar empresas, consultar precios,
 * y ajustar valores según noticias del mercado.
 */

#ifndef EMPRESA_H
#define EMPRESA_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

/// Lista global de sectores consistente para todo el sistema
const vector<string> SECTORES_EMPRESA = {
    "Tecnología", "Finanzas", "Salud", "Consumo", "Energía", "Industrial", "Telecomunicaciones", "Materiales"
};

/**
 * @struct NodoPrecio
 * @brief Nodo para la multilista de precios históricos de una acción.
 *
 * Cada nodo almacena la fecha y el precio de cierre de una acción, así como un puntero al siguiente nodo.
 */
struct NodoPrecio {
    /// Fecha del precio histórico (formato AAAA-MM-DD)
    string fecha;
    /// Precio de cierre en la fecha dada
    float precioCierre;
    /// Puntero al siguiente nodo en la lista
    NodoPrecio* siguiente;

    /**
     * @brief Constructor de NodoPrecio.
     * @param f Fecha del precio.
     * @param p Precio de cierre.
     */
    NodoPrecio(string f, float p) : fecha(f), precioCierre(p), siguiente(nullptr) {}
};

/**
 * @class MultilistaPrecio
 * @brief Multilista para historial de precios de una acción.
 *
 * Permite agregar precios históricos, calcular promedios móviles y mostrar el historial.
 */
class MultilistaPrecio {
public:
    /// Puntero al primer nodo de la lista de precios
    NodoPrecio* cabeza;

    /**
     * @brief Constructor de MultilistaPrecio.
     */
    MultilistaPrecio() : cabeza(nullptr) {}

    /**
     * @brief Agrega un precio al historial (al inicio de la lista).
     * @param fecha Fecha del precio.
     * @param precio Precio de cierre.
     */
    void agregarPrecio(const string& fecha, float precio) {
        NodoPrecio* nuevo = new NodoPrecio(fecha, precio);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }

    /**
     * @brief Calcula el promedio móvil de los últimos 'dias' precios.
     * @param dias Número de días a considerar.
     * @return Promedio móvil calculado.
     */
    float promedioMovil(int dias) {
        float suma = 0;
        int cont = 0;
        NodoPrecio* actual = cabeza;
        while (actual && cont < dias) {
            suma += actual->precioCierre;
            actual = actual->siguiente;
            cont++;
        }
        return (cont > 0) ? suma / cont : 0;
    }

    /**
     * @brief Imprime el historial de precios por consola.
     */
    void imprimir() {
        NodoPrecio* actual = cabeza;
        while (actual) {
            cout << actual->fecha << ": " << actual->precioCierre << "  ";
            actual = actual->siguiente;
        }
        cout << endl;
    }
};

/**
 * @struct Empresa
 * @brief Nodo de ABB que representa una empresa.
 *
 * Contiene información relevante de la empresa y enlaces para el árbol binario de búsqueda.
 */
struct Empresa {
    /// Ticker de la empresa (clave única)
    string ticker;
    /// Nombre de la empresa
    string nombre;
    /// Sector al que pertenece la empresa
    string sector;
    /// Precio actual de la acción
    float precioActual;
    /// Historial de precios de la acción
    MultilistaPrecio historialPrecios;
    /// Puntero al hijo izquierdo en el ABB
    Empresa* izquierda;
    /// Puntero al hijo derecho en el ABB
    Empresa* derecha;

    /**
     * @brief Constructor de Empresa.
     * @param t Ticker.
     * @param n Nombre.
     * @param s Sector.
     * @param p Precio actual.
     */
    Empresa(string t, string n, string s, float p)
        : ticker(t), nombre(n), sector(s), precioActual(p),
          izquierda(nullptr), derecha(nullptr) {}
};

/**
 * @class ABBEmpresas
 * @brief Árbol binario de búsqueda (ABB) para gestionar empresas.
 *
 * Permite insertar, buscar, listar y modificar empresas, así como ajustar precios por noticias.
 */
class ABBEmpresas {
private:
    /// Puntero a la raíz del ABB
    Empresa* raiz;

    /**
     * @brief Inserta una empresa en el ABB (por ticker).
     * @param nodo Nodo actual.
     * @param nueva Nueva empresa a insertar.
     * @return Puntero al nodo actualizado.
     */
    Empresa* insertar(Empresa* nodo, Empresa* nueva) {
        if (!nodo) return nueva;
        if (nueva->ticker < nodo->ticker)
            nodo->izquierda = insertar(nodo->izquierda, nueva);
        else if (nueva->ticker > nodo->ticker)
            nodo->derecha = insertar(nodo->derecha, nueva);
        // Si es igual, no inserta duplicados
        return nodo;
    }

    /**
     * @brief Busca una empresa por ticker en el ABB.
     * @param nodo Nodo actual.
     * @param ticker Ticker a buscar.
     * @return Puntero a la empresa encontrada o nullptr.
     */
    Empresa* buscar(Empresa* nodo, const string& ticker) {
        if (!nodo) return nullptr;
        if (ticker < nodo->ticker)
            return buscar(nodo->izquierda, ticker);
        else if (ticker > nodo->ticker)
            return buscar(nodo->derecha, ticker);
        else
            return nodo;
    }

    /**
     * @brief Recorrido inorden para obtener empresas ordenadas alfabéticamente.
     * @param nodo Nodo actual.
     * @param lista Vector donde se almacenan las empresas.
     */
    void inorden(Empresa* nodo, vector<Empresa*>& lista) {
        if (!nodo) return;
        inorden(nodo->izquierda, lista);
        lista.push_back(nodo);
        inorden(nodo->derecha, lista);
    }

    /**
     * @brief Libera la memoria de todos los nodos del ABB y sus listas de precios.
     * @param nodo Nodo actual.
     */
    void destruir(Empresa* nodo) {
        if (!nodo) return;
        destruir(nodo->izquierda);
        destruir(nodo->derecha);
        // Liberar multilista de precios
        NodoPrecio* p = nodo->historialPrecios.cabeza;
        while (p) {
            NodoPrecio* temp = p;
            p = p->siguiente;
            delete temp;
        }
        delete nodo;
    }

    /**
     * @brief Inicializa automáticamente el ABB con empresas reales y datos aleatorios.
     */
    void inicializarEmpresas() {
        // Arrays de tickers, nombres y sectores reales (ejemplo S&P 500)
        const string tickers[50] = {
            "AAPL","MSFT","GOOGL","AMZN","META","TSLA","NVDA","BRK.B","JPM","V",
            "UNH","HD","PG","MA","LLY","XOM","MRK","ABBV","AVGO","CVX",
            "PEP","KO","COST","WMT","BAC","MCD","DIS","ADBE","CSCO","PFE",
            "TMO","ABT","CRM","ACN","DHR","NKE","LIN","WFC","TXN","NEE",
            "VZ","INTC","CMCSA","HON","ORCL","AMGN","QCOM","MDT","UNP","LOW"
        };
        const string nombres[50] = {
            "Apple","Microsoft","Alphabet","Amazon","Meta Platforms","Tesla","Nvidia","Berkshire Hathaway","JPMorgan Chase","Visa",
            "UnitedHealth","Home Depot","Procter & Gamble","Mastercard","Eli Lilly","Exxon Mobil","Merck","AbbVie","Broadcom","Chevron",
            "PepsiCo","Coca-Cola","Costco","Walmart","Bank of America","McDonald's","Disney","Adobe","Cisco","Pfizer",
            "Thermo Fisher","Abbott","Salesforce","Accenture","Danaher","Nike","Linde","Wells Fargo","Texas Instruments","NextEra Energy",
            "Verizon","Intel","Comcast","Honeywell","Oracle","Amgen","Qualcomm","Medtronic","Union Pacific","Lowe's"
        };

        srand(time(nullptr));
        for (int i = 0; i < 50; ++i) {
            float precio = 50 + rand() % 450 + (rand() % 1000) / 1000.0f; // Precio entre 50 y 500 aprox
            string sector = SECTORES_EMPRESA[rand() % SECTORES_EMPRESA.size()];
            insertarEmpresa(tickers[i], nombres[i], sector, precio);

            // Generar historial de precios desde 2025-01-01 hasta 2025-05-26
            Empresa* emp = buscarEmpresa(tickers[i]);
            int year = 2025, month = 1, day = 1;
            float precioHist = precio;
            while (!(year == 2025 && month == 5 && day == 27)) { // hasta el 26 inclusive
                // Construir la fecha manualmente sin sprintf
                string fecha = "";
                // Año
                fecha += "2025-";
                // Mes
                if (month < 10) fecha += "0";
                fecha += to_string(month) + "-";
                // Día
                if (day < 10) fecha += "0";
                fecha += to_string(day);

                // Variar el precio histórico aleatoriamente
                float variacion = ((rand() % 2001) - 1000) / 100.0f; // -10.00 a +10.00
                precioHist = max(1.0f, precioHist + variacion);
                emp->historialPrecios.agregarPrecio(fecha, precioHist);

                // Avanzar al siguiente día
                day++;
                int diasMes;
                if (month == 2) diasMes = 28;
                else if (month == 4 || month == 6 || month == 9 || month == 11) diasMes = 30;
                else diasMes = 31;
                if (day > diasMes) {
                    day = 1;
                    month++;
                }
                if (month > 12) {
                    month = 1;
                    year++;
                }
                if (year == 2025 && month == 5 && day == 27) break; // detener después del 26
            }
            // Actualizar precio actual al último histórico
            if (emp->historialPrecios.cabeza)
                emp->precioActual = emp->historialPrecios.cabeza->precioCierre;
        }
    }

public:
    /**
     * @brief Constructor de ABBEmpresas. Inicializa el árbol con empresas de ejemplo.
     */
    ABBEmpresas() : raiz(nullptr) {
        inicializarEmpresas();
    }

    /**
     * @brief Destructor de ABBEmpresas. Libera toda la memoria utilizada.
     */
    ~ABBEmpresas() { destruir(raiz); }

    /**
     * @brief Inserta una empresa (si no existe ya en el ABB).
     * @param ticker Ticker de la empresa.
     * @param nombre Nombre de la empresa.
     * @param sector Sector de la empresa.
     * @param precio Precio actual de la acción.
     */
    void insertarEmpresa(const string& ticker, const string& nombre, const string& sector, float precio) {
        if (!buscarEmpresa(ticker)) {
            Empresa* nueva = new Empresa(ticker, nombre, sector, precio);
            raiz = insertar(raiz, nueva);
        }
    }

    /**
     * @brief Busca una empresa por ticker.
     * @param ticker Ticker a buscar.
     * @return Puntero a la empresa encontrada o nullptr.
     */
    Empresa* buscarEmpresa(const string& ticker) {
        return buscar(raiz, ticker);
    }

    /**
     * @brief Agrega un precio histórico a una empresa.
     * @param ticker Ticker de la empresa.
     * @param fecha Fecha del precio.
     * @param precio Precio de cierre.
     */
    void agregarPrecio(const string& ticker, const string& fecha, float precio) {
        Empresa* emp = buscarEmpresa(ticker);
        if (emp) {
            emp->historialPrecios.agregarPrecio(fecha, precio);
            emp->precioActual = precio;
        }
    }

    /**
     * @brief Devuelve una lista ordenada de empresas (inorden).
     * @return Vector de punteros a empresas ordenadas alfabéticamente.
     */
    vector<Empresa*> obtenerEmpresasOrdenadas() {
        vector<Empresa*> lista;
        inorden(raiz, lista);
        return lista;
    }

    /**
     * @brief Imprime todas las empresas y su precio actual por consola.
     */
    void imprimirEmpresas() {
        vector<Empresa*> lista = obtenerEmpresasOrdenadas();
        cout << "---------------------------------------------------------------\n";
        cout << " Ticker   | Empresa                  | Sector         | Precio actual\n";
        cout << "---------------------------------------------------------------\n";
        for (auto e : lista) {
            // Ticker (máx 8)
            cout << " ";
            int t = 0;
            for (; t < 8 && e->ticker[t] != '\0'; ++t) cout << e->ticker[t];
            for (; t < 8; ++t) cout << " ";
            cout << " | ";
            // Nombre (máx 24)
            int n = 0;
            for (; n < 24 && e->nombre[n] != '\0'; ++n) cout << e->nombre[n];
            for (; n < 24; ++n) cout << " ";
            cout << " | ";
            // Sector (máx 14)
            int s = 0;
            for (; s < 14 && e->sector[s] != '\0'; ++s) cout << e->sector[s];
            for (; s < 14; ++s) cout << " ";
            cout << " | " << e->precioActual << endl;
        }
        cout << "---------------------------------------------------------------\n";
    }

    /**
     * @brief Función auxiliar para Merge Sort: combina dos subarreglos.
     * @param arr Vector de empresas.
     * @param left Índice izquierdo.
     * @param mid Índice medio.
     * @param right Índice derecho.
     */
    static void merge(vector<Empresa*>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        vector<Empresa*> L(n1), R(n2);
        for (int i = 0; i < n1; i++) L[i] = arr[left + i];
        for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i]->precioActual > R[j]->precioActual) arr[k++] = L[i++];
            else arr[k++] = R[j++];
        }
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    }

    /**
     * @brief Ordena empresas por precio actual usando Merge Sort (de mayor a menor).
     * @param arr Vector de empresas.
     * @param left Índice izquierdo.
     * @param right Índice derecho.
     */
    static void mergeSort(vector<Empresa*>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    /**
     * @brief Imprime empresas ordenadas por precio actual (de mayor a menor).
     * @param arr Vector de empresas.
     * @param left Índice izquierdo.
     * @param right Índice derecho.
     */
    void imprimirPorPrecio() {
        vector<Empresa*> lista = obtenerEmpresasOrdenadas();
        mergeSort(lista, 0, lista.size() - 1);
        cout << "---------------------------------------------------------------\n";
        cout << " Ticker   | Empresa                  | Sector         | Precio actual\n";
        cout << "---------------------------------------------------------------\n";
        for (auto e : lista) {
            // Ticker (máx 8)
            cout << " ";
            int t = 0;
            for (; t < 8 && e->ticker[t] != '\0'; ++t) cout << e->ticker[t];
            for (; t < 8; ++t) cout << " ";
            cout << " | ";
            // Nombre (máx 24)
            int n = 0;
            for (; n < 24 && e->nombre[n] != '\0'; ++n) cout << e->nombre[n];
            for (; n < 24; ++n) cout << " ";
            cout << " | ";
            // Sector (máx 14)
            int s = 0;
            for (; s < 14 && e->sector[s] != '\0'; ++s) cout << e->sector[s];
            for (; s < 14; ++s) cout << " ";
            cout << " | " << e->precioActual << endl;
        }
        cout << "---------------------------------------------------------------\n";
    }

    /**
     * @brief Imprime todas las empresas de un sector específico.
     * @param sector Nombre del sector a filtrar.
     */
    void imprimirEmpresasPorSector(const string& sector) {
        vector<Empresa*> lista = obtenerEmpresasOrdenadas();
        cout << "---------------------------------------------------------------\n";
        cout << " Ticker   | Empresa                  | Sector         | Precio actual\n";
        cout << "---------------------------------------------------------------\n";
        for (auto e : lista) {
            if (e->sector == sector) {
                // Ticker (máx 8)
                cout << " ";
                int t = 0;
                for (; t < 8 && e->ticker[t] != '\0'; ++t) cout << e->ticker[t];
                for (; t < 8; ++t) cout << " ";
                cout << " | ";
                // Nombre (máx 24)
                int n = 0;
                for (; n < 24 && e->nombre[n] != '\0'; ++n) cout << e->nombre[n];
                for (; n < 24; ++n) cout << " ";
                cout << " | ";
                // Sector (máx 14)
                int s = 0;
                for (; s < 14 && e->sector[s] != '\0'; ++s) cout << e->sector[s];
                for (; s < 14; ++s) cout << " ";
                cout << " | " << e->precioActual << endl;
            }
        }
        cout << "---------------------------------------------------------------\n";
    }

    /**
     * @brief Calcula el promedio del precio actual de las empresas de un sector.
     * @param sector Nombre del sector.
     * @return Promedio del precio actual de las empresas del sector, o 0 si no hay empresas.
     */
    float promedioPrecioPorSector(const string& sector) {
        vector<Empresa*> lista = obtenerEmpresasOrdenadas();
        float suma = 0;
        int cuenta = 0;
        for (auto e : lista) {
            if (e->sector == sector) {
                suma += e->precioActual;
                cuenta++;
            }
        }
        return (cuenta > 0) ? (suma / cuenta) : 0;
    }

    /**
     * @brief Devuelve la empresa con el precio actual más bajo.
     * @return Puntero a la empresa con el precio más bajo, o nullptr si no hay empresas.
     */
    Empresa* obtenerEmpresaMasBarata() {
        vector<Empresa*> lista = obtenerEmpresasOrdenadas();
        if (lista.empty()) return nullptr;
        Empresa* minEmp = lista[0];
        for (size_t i = 1; i < lista.size(); ++i) {
            if (lista[i]->precioActual < minEmp->precioActual)
                minEmp = lista[i];
        }
        return minEmp;
    }

    /**
     * @brief Devuelve la empresa con el precio actual más alto.
     * @return Puntero a la empresa con el precio más alto, o nullptr si no hay empresas.
     */
    Empresa* obtenerEmpresaMasCara() {
        vector<Empresa*> lista = obtenerEmpresasOrdenadas();
        if (lista.empty()) return nullptr;
        Empresa* maxEmp = lista[0];
        for (size_t i = 1; i < lista.size(); ++i) {
            if (lista[i]->precioActual > maxEmp->precioActual)
                maxEmp = lista[i];
        }
        return maxEmp;
    }

    /**
     * @brief Devuelve una lista de empresas cuyo precio actual está en el rango [minPrecio, maxPrecio].
     * @param minPrecio Precio mínimo.
     * @param maxPrecio Precio máximo.
     * @return Vector de punteros a empresas dentro del rango.
     */
    vector<Empresa*> buscarEmpresasPorRangoPrecio(float minPrecio, float maxPrecio) {
        vector<Empresa*> lista = obtenerEmpresasOrdenadas();
        vector<Empresa*> resultado;
        for (auto e : lista) {
            if (e->precioActual >= minPrecio && e->precioActual <= maxPrecio)
                resultado.push_back(e);
        }
        return resultado;
    }

    /**
     * @brief Imprime la información de una empresa en formato de tabla.
     * @param emp Puntero a la empresa a imprimir.
     * Si el puntero es nulo, imprime un mensaje de empresa no encontrada.
     */
    void imprimirEmpresa(const Empresa* emp) {
        if (!emp) {
            cout << "Empresa no encontrada.\n";
            return;
        }
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
    }

    /**
     * @brief Imprime una lista de empresas en formato de tabla.
     * @param empresas Vector de punteros a empresas a imprimir.
     * Si el vector está vacío, muestra un mensaje adecuado.
     */
    void imprimirEmpresas(const vector<Empresa*>& empresas) {
        if (empresas.empty()) {
            cout << "No hay empresas en el rango especificado.\n";
            return;
        }
        cout << "---------------------------------------------------------------\n";
        cout << " Ticker   | Empresa                  | Sector         | Precio actual\n";
        cout << "---------------------------------------------------------------\n";
        for (auto e : empresas) {
            // Ticker (máx 8)
            cout << " ";
            int t = 0;
            for (; t < 8 && e->ticker[t] != '\0'; ++t) cout << e->ticker[t];
            for (; t < 8; ++t) cout << " ";
            cout << " | ";
            // Nombre (máx 24)
            int n = 0;
            for (; n < 24 && e->nombre[n] != '\0'; ++n) cout << e->nombre[n];
            for (; n < 24; ++n) cout << " ";
            cout << " | ";
            // Sector (máx 14)
            int s = 0;
            for (; s < 14 && e->sector[s] != '\0'; ++s) cout << e->sector[s];
            for (; s < 14; ++s) cout << " ";
            cout << " | " << e->precioActual << endl;
        }
        cout << "---------------------------------------------------------------\n";
    }

    /**
     * @brief Ajusta los precios de las empresas de un sector según el impacto de una noticia.
     * @param sector Sector afectado.
     * @param impacto Impacto de la noticia (1-10).
     */
    void ajustarPreciosPorNoticia(const string& sector, int impacto) {
        vector<Empresa*> empresas = obtenerEmpresasOrdenadas();
        float porcentaje = 0.0;
        if (impacto > 5) {
            porcentaje = (impacto - 5) * 0.01;
        } else {
            porcentaje = -(6 - impacto) * 0.01;
        }
        for (auto e : empresas) {
            if (e->sector == sector) {
                e->precioActual += e->precioActual * porcentaje;
                if (e->precioActual < 1.0) e->precioActual = 1.0;
            }
        }
    }

    /**
     * @brief Ajusta los precios de las empresas de un sector según el impacto de una noticia.
     *        Agrega el nuevo precio al historial con la fecha de la noticia y actualiza el precio actual.
     * @param sector Sector afectado.
     * @param impacto Impacto de la noticia (1-10).
     * @param fecha Fecha de la noticia.
     */
    void ajustarPreciosPorNoticia(const string& sector, int impacto, const string& fecha) {
        vector<Empresa*> empresas = obtenerEmpresasOrdenadas();
        float porcentaje = 0.0;
        if (impacto > 5) {
            porcentaje = (impacto - 5) * 0.01;
        } else {
            porcentaje = -(6 - impacto) * 0.01;
        }
        for (auto e : empresas) {
            if (e->sector == sector) {
                float nuevoPrecio = e->precioActual + e->precioActual * porcentaje;
                if (nuevoPrecio < 1.0) nuevoPrecio = 1.0;
                e->precioActual = nuevoPrecio;
                e->historialPrecios.agregarPrecio(fecha, nuevoPrecio);
            }
        }
    }
};

#endif
