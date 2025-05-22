#ifndef EMPRESA_H
#define EMPRESA_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

/**
 * @brief Nodo para la multilista de precios históricos.
 */
struct NodoPrecio {
    string fecha;              ///< Fecha del precio histórico
    float precioCierre;        ///< Precio de cierre en esa fecha
    NodoPrecio* siguiente;     ///< Puntero al siguiente nodo

    /**
     * @brief Constructor de NodoPrecio.
     * @param f Fecha del precio.
     * @param p Precio de cierre.
     */
    NodoPrecio(string f, float p) : fecha(f), precioCierre(p), siguiente(nullptr) {}
};

/**
 * @brief Multilista para historial de precios de una acción.
 */
class MultilistaPrecio {
public:
    NodoPrecio* cabeza; ///< Puntero al primer nodo del historial

    /**
     * @brief Constructor de MultilistaPrecio.
     */
    MultilistaPrecio() : cabeza(nullptr) {}

    /**
     * @brief Agrega un precio al historial (al inicio).
     * @param fecha Fecha del precio.
     * @param precio Precio de cierre.
     */
    void agregarPrecio(const string& fecha, float precio);

    /**
     * @brief Calcula el promedio móvil de los últimos 'dias' precios.
     * @param dias Número de días a considerar.
     * @return Promedio móvil calculado.
     */
    float promedioMovil(int dias);

    /**
     * @brief Imprime el historial de precios.
     */
    void imprimir();
};

// Implementación de métodos de MultilistaPrecio
inline void MultilistaPrecio::agregarPrecio(const string& fecha, float precio) {
    NodoPrecio* nuevo = new NodoPrecio(fecha, precio);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

inline float MultilistaPrecio::promedioMovil(int dias) {
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

inline void MultilistaPrecio::imprimir() {
    NodoPrecio* actual = cabeza;
    while (actual) {
        cout << actual->fecha << ": " << actual->precioCierre << "  ";
        actual = actual->siguiente;
    }
    cout << endl;
}

/**
 * @brief Nodo de ABB para empresa.
 */
struct Empresa {
    string ticker;                 ///< Ticker de la empresa
    string nombre;                 ///< Nombre de la empresa
    string sector;                 ///< Sector al que pertenece
    float precioActual;            ///< Precio actual de la acción
    MultilistaPrecio historialPrecios; ///< Historial de precios
    Empresa* izquierda;            ///< Hijo izquierdo en el ABB
    Empresa* derecha;              ///< Hijo derecho en el ABB

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
 * @brief Árbol binario de búsqueda para empresas.
 */
class ABBEmpresas {
private:
    Empresa* raiz; ///< Raíz del árbol

    /**
     * @brief Inserta una empresa en el ABB (por ticker).
     * @param nodo Nodo actual.
     * @param nueva Nueva empresa a insertar.
     * @return Puntero al nodo actualizado.
     */
    Empresa* insertar(Empresa* nodo, Empresa* nueva);

    /**
     * @brief Búsqueda binaria por ticker.
     * @param nodo Nodo actual.
     * @param ticker Ticker a buscar.
     * @return Puntero a la empresa encontrada o nullptr.
     */
    Empresa* buscar(Empresa* nodo, const string& ticker);

    /**
     * @brief Recorrido inorden (orden alfabético por ticker).
     * @param nodo Nodo actual.
     * @param lista Vector donde se almacenan las empresas.
     */
    void inorden(Empresa* nodo, vector<Empresa*>& lista);

    /**
     * @brief Libera la memoria del árbol y de los historiales.
     * @param nodo Nodo actual.
     */
    void destruir(Empresa* nodo);

    /**
     * @brief Inicializa automáticamente empresas reales con datos aleatorios.
     */
    void inicializarEmpresas();

public:
    /**
     * @brief Constructor de ABBEmpresas. Inicializa el árbol con empresas reales.
     */
    ABBEmpresas();

    /**
     * @brief Destructor de ABBEmpresas. Libera toda la memoria.
     */
    ~ABBEmpresas();

    /**
     * @brief Inserta una empresa (si no existe).
     * @param ticker Ticker de la empresa.
     * @param nombre Nombre de la empresa.
     * @param sector Sector de la empresa.
     * @param precio Precio actual.
     */
    void insertarEmpresa(const string& ticker, const string& nombre, const string& sector, float precio);

    /**
     * @brief Busca una empresa por ticker.
     * @param ticker Ticker a buscar.
     * @return Puntero a la empresa encontrada o nullptr.
     */
    Empresa* buscarEmpresa(const string& ticker);

    /**
     * @brief Agrega precio histórico a una empresa.
     * @param ticker Ticker de la empresa.
     * @param fecha Fecha del precio.
     * @param precio Precio de cierre.
     */
    void agregarPrecio(const string& ticker, const string& fecha, float precio);

    /**
     * @brief Devuelve lista ordenada de empresas (inorden).
     * @return Vector de punteros a empresas ordenadas.
     */
    vector<Empresa*> obtenerEmpresasOrdenadas();

    /**
     * @brief Imprime todas las empresas y su precio actual.
     */
    void imprimirEmpresas();

    /**
     * @brief Ordena empresas por precio actual usando Merge Sort (de mayor a menor).
     * @param arr Vector de empresas.
     * @param left Índice izquierdo.
     * @param mid Índice medio.
     * @param right Índice derecho.
     */
    static void merge(vector<Empresa*>& arr, int left, int mid, int right);

    /**
     * @brief Merge sort para empresas por precio actual.
     * @param arr Vector de empresas.
     * @param left Índice izquierdo.
     * @param right Índice derecho.
     */
    static void mergeSort(vector<Empresa*>& arr, int left, int right);

    /**
     * @brief Imprime empresas ordenadas por precio actual (de mayor a menor).
     */
    void imprimirPorPrecio();
};

#endif
