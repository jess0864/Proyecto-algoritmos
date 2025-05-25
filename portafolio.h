/**
 * @file portafolio.h
 * @brief Definición de la clase Portafolio y del vector dinámico personalizado MiVector.
 *
 * Este archivo contiene la implementación de la clase Portafolio, que permite gestionar
 * activos de un usuario, así como la clase plantilla MiVector para manejo de arreglos dinámicos.
 * Incluye lógica para recomendaciones de compra de activos basada en tendencias y noticias.
 */

#ifndef PORTAFOLIO_H
#define PORTAFOLIO_H

#include <iostream>
#include <string>
#include <cmath> ///< Para usar sqrt en cálculos estadísticos
#include "empresa.h"
#include "noticia.h"
using namespace std;

// ===============================
// Clase MiVector integrada
// ===============================

/**
 * @class MiVector
 * @brief Clase plantilla que implementa un vector dinámico personalizado.
 * 
 * Permite agregar, eliminar, ordenar y acceder a elementos de forma similar a std::vector,
 * pero con implementación propia para entender el funcionamiento interno de estructuras dinámicas.
 * 
 * @tparam T Tipo de dato de los elementos almacenados.
 */
template <typename T>
class MiVector {
private:
    T* datos;          ///< Puntero al arreglo dinámico que almacena los elementos.
    int capacidad;     ///< Capacidad máxima actual del arreglo.
    int cantidad;      ///< Número actual de elementos en el arreglo.

public:
    /**
     * @brief Constructor por defecto.
     * 
     * Inicializa el vector con una capacidad inicial de 2.
     */
    MiVector() {
        capacidad = 2;
        cantidad = 0;
        datos = new T[capacidad];
    }

    /**
     * @brief Destructor.
     * 
     * Libera la memoria asignada dinámicamente al vector.
     */
    ~MiVector() {
        delete[] datos;
    }
    
    /**
     * @brief Inserta un elemento al final del vector.
     * 
     * Si el vector ha alcanzado su capacidad máxima, se duplica su tamaño.
     * 
     * @param valor Elemento a insertar.
     */
    void miPush(const T& valor) {
        if (cantidad == capacidad) {
            capacidad *= 2;
            T* nuevo = new T[capacidad];
            for (int i = 0; i < cantidad; ++i)
                nuevo[i] = datos[i];
            delete[] datos;
            datos = nuevo;
        }
        datos[cantidad++] = valor;
    }

    /**
     * @brief Elimina el último elemento del vector.
     * 
     * Si el vector está vacío, muestra un mensaje de error.
     */
    void miPop() {
        if (cantidad > 0)
            cantidad--;
        else
            cout << "Error: vector vacío.\n";
    }

    /**
     * @brief Elimina la primera aparición de un valor en el vector.
     * 
     * Reorganiza los elementos restantes para llenar el hueco.
     * 
     * @param valor Elemento a eliminar.
     * @return true si se eliminó exitosamente, false si no se encontró.
     */
    bool eliminar(const T& valor) {
        for (int i = 0; i < cantidad; ++i) {
            if (datos[i] == valor) {
                for (int j = i; j < cantidad - 1; ++j)
                    datos[j] = datos[j + 1];
                cantidad--;
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Ordena los elementos del vector en orden ascendente.
     * 
     * Utiliza el algoritmo de burbuja (Bubble Sort).
     */
    void ordenar() {
        for (int i = 0; i < cantidad - 1; ++i)
            for (int j = 0; j < cantidad - i - 1; ++j)
                if (datos[j] > datos[j + 1])
                    swap(datos[j], datos[j + 1]);
    }

    /**
     * @brief Obtiene el número actual de elementos en el vector.
     * 
     * @return Cantidad de elementos almacenados.
     */
    int size() const { return cantidad; }

    /**
     * @brief Verifica si el vector está vacío.
     * 
     * @return true si no hay elementos, false en caso contrario.
     */
    bool empty() const { return cantidad == 0; }

    /**
     * @brief Acceso por índice con posibilidad de modificación.
     * 
     * @param index Índice del elemento a acceder.
     * @return Referencia al elemento solicitado.
     */
    T& operator[](int index) { return datos[index]; }

    /**
     * @brief Acceso por índice para lectura (constante).
     * 
     * @param index Índice del elemento a acceder.
     * @return Referencia constante al elemento solicitado.
     */
    const T& operator[](int index) const { return datos[index]; }
};

// ===============================
// Clase Portafolio usando MiVector
// ===============================

/**
 * @class Portafolio
 * @brief Clase que representa el portafolio de un usuario, permitiendo gestionar activos.
 * 
 * Utiliza la clase MiVector para almacenar los activos del usuario y provee métodos para
 * agregar, eliminar, mostrar y ordenar activos, así como recomendaciones de compra.
 */
class Portafolio {
private:
    string nombreUsuario;           ///< Nombre del usuario propietario del portafolio.
    MiVector<string> activos;       ///< Vector personalizado de activos (por ejemplo, tickers).

public:
    /**
     * @brief Constructor que inicializa el portafolio con el nombre del usuario.
     * @param nombre Nombre del usuario.
     */
    Portafolio(string nombre) : nombreUsuario(nombre) {}

    /**
     * @brief Agrega un activo al portafolio.
     * @param activo Nombre o ticker del activo a agregar.
     */
    void agregarActivo(const string& activo) {
        activos.miPush(activo);
        cout << "Activo '" << activo << "' agregado." << endl;
    }

    /**
     * @brief Verifica si el portafolio contiene un activo específico.
     * @param activo Nombre o ticker del activo a buscar.
     * @return true si el activo está presente, false en caso contrario.
     */
    bool tieneActivo(const string& activo) const {
        for (int i = 0; i < activos.size(); ++i)
            if (activos[i] == activo) return true;
        return false;
    }

    /**
     * @brief Muestra todos los activos del portafolio por consola.
     */
    void mostrar() const {
        cout << "Portafolio de " << nombreUsuario << ":\n";
        if (activos.empty()) cout << "(Vacío)\n";
        else
            for (int i = 0; i < activos.size(); ++i)
                cout << "- " << activos[i] << '\n';
    }

    /**
     * @brief Elimina un activo del portafolio.
     * @param activo Nombre o ticker del activo a eliminar.
     * @return true si se eliminó exitosamente, false si no se encontró.
     */
    bool eliminarActivo(const string& activo) {
        if (activos.eliminar(activo)) {
            cout << "Activo '" << activo << "' eliminado." << endl;
            return true;
        }
        cout << "Activo '" << activo << "' no encontrado." << endl;
        return false;
    }

    /**
     * @brief Ordena los activos del portafolio en orden ascendente.
     */
    void ordenarActivos() {
        if (activos.empty()) cout << "Nada que ordenar.\n";
        else {
            activos.ordenar();
            cout << "Activos ordenados.\n";
        }
    }

    /**
     * @brief Obtiene los activos del portafolio como un std::vector<string>.
     * @return Vector de strings con los activos.
     */
    vector<string> obtenerActivos() const {
        vector<string> v;
        for (int i = 0; i < activos.size(); ++i)
            v.push_back(activos[i]);
        return v;
    }

    /**
     * @brief Árbol de decisión para recomendar la compra de un activo.
     * 
     * Analiza la tendencia de precios históricos y noticias del sector para dar una recomendación.
     * 
     * @param ticker Ticker del activo a analizar.
     * @param arbol Referencia al árbol binario de búsqueda de empresas.
     * @param colaNoticias Referencia a la cola de prioridad de noticias.
     */
    void recomendarCompra(const string& ticker, ABBEmpresas& arbol, ColaPrioridadNoticias& colaNoticias) {
        Empresa* emp = arbol.buscarEmpresa(ticker);
        if (!emp) {
            cout << "No se encontró la empresa para el ticker '" << ticker << "'.\n";
            return;
        }
        // 1. ¿Tendencia positiva? (precio actual > promedio últimos 5 días)
        float prom5 = emp->historialPrecios.promedioMovil(5);
        bool tendenciaPositiva = emp->precioActual > prom5;
        cout << "Tendencia positiva (precio actual $" << emp->precioActual << " > promedio 5 días $" << prom5 << "): ";
        cout << (tendenciaPositiva ? "Sí" : "No") << endl;

        if (tendenciaPositiva) {
            // 2. ¿Noticias positivas? (noticias recientes con impacto positivo y esPositiva)
            bool noticiaPositiva = false;
            vector<Noticia*> noticias;
            colaNoticias.obtenerNoticias(noticias);
            for (auto n : noticias) {
                if (n->sectorAfectado == emp->sector && n->impacto >= 6 && n->esPositiva) {
                    noticiaPositiva = true;
                    break;
                }
            }
            cout << "¿Noticias positivas recientes en el sector? " << (noticiaPositiva ? "Sí" : "No") << endl;
            if (noticiaPositiva) {
                cout << "→ Recomendación: COMPRAR\n";
            } else {
                cout << "→ Recomendación: ESPERAR\n";
            }
        } else {
            // 3. ¿Volatilidad baja? (desviación estándar últimos 5 días < 3%)
            float precios[5];
            int count = 0;
            NodoPrecio* p = emp->historialPrecios.cabeza;
            while (p && count < 5) {
                precios[count++] = p->precioCierre;
                p = p->siguiente;
            }
            float media = 0;
            for (int i = 0; i < count; ++i) media += precios[i];
            if (count > 0) media /= count;
            float var = 0;
            for (int i = 0; i < count; ++i) var += (precios[i] - media) * (precios[i] - media);
            float desv = (count > 0) ? sqrt(var / count) : 0;
            float desvPorc = (media > 0) ? (desv / media) * 100.0f : 0;
            bool volatilidadBaja = desvPorc < 3.0f;
            cout << "Volatilidad últimos 5 días: " << desvPorc << "% (" << (volatilidadBaja ? "Baja" : "Alta") << ")\n";
            if (volatilidadBaja) {
                cout << "→ Recomendación: COMPRAR\n";
            } else {
                cout << "→ Recomendación: NO COMPRAR\n";
            }
        }
    }
};

#endif