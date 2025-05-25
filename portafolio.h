/**
 * @file portafolio.h
 * @brief Define la clase Portafolio y la estructura de pila para gestionar activos de usuario.
 */

#ifndef PORTAFOLIO_H
#define PORTAFOLIO_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include "empresa.h"
#include "noticia.h"

using namespace std;

/**
 * @brief Nodo simple para la implementación de una pila.
 */
struct Nodo {
    string valor;
    Nodo* siguiente;
};

/**
 * @brief Implementación de una pila LIFO con nodos enlazados.
 */
class Pila {
private:
    Nodo* cima;

public:
    friend class Portafolio;

    /**
     * @brief Constructor que inicializa la pila como vacía.
     */
    Pila() : cima(nullptr) {}

    /**
     * @brief Agrega un nuevo elemento a la cima de la pila.
     * 
     * @param x Elemento a insertar.
     */
    void push(const string& x) {
        Nodo* nuevoNodo = new Nodo;
        nuevoNodo->valor = x;
        nuevoNodo->siguiente = cima;
        cima = nuevoNodo;
    }

    /**
     * @brief Devuelve el elemento en la cima de la pila sin eliminarlo.
     * 
     * @return Elemento en la cima o mensaje de error si está vacía.
     */
    string top() const {
        if (cima == nullptr) {
            cerr << "Error: La pila está vacía.\n";
            return "";
        }
        return cima->valor;
    }

    /**
     * @brief Elimina el elemento en la cima de la pila.
     */
    void pop() {
        if (cima == nullptr) {
            cerr << "Error: No se puede hacer pop en una pila vacía.\n";
            return;
        }
        Nodo* temp = cima;
        cima = cima->siguiente;
        delete temp;
    }

    /**
     * @brief Verifica si la pila está vacía.
     * 
     * @return true si está vacía, false en caso contrario.
     */
    bool isEmpty() const {
        return cima == nullptr;
    }

    /**
     * @brief Muestra el contenido completo de la pila.
     */
    void imprimir() const {
        Nodo* actual = cima;
        while (actual != nullptr) {
            cout << "- " << actual->valor << '\n';
            actual = actual->siguiente;
        }
    }

    /**
     * @brief Elimina la primera aparición de un valor específico.
     * 
     * @param objetivo Valor a eliminar.
     * @return true si se eliminó, false si no se encontró.
     */
    bool eliminar(const string& objetivo) {
        Pila auxiliar;
        bool encontrado = false;

        while (!isEmpty()) {
            if (top() == objetivo) {
                pop();
                encontrado = true;
                break;
            }
            auxiliar.push(top());
            pop();
        }

        while (!auxiliar.isEmpty()) {
            push(auxiliar.top());
            auxiliar.pop();
        }

        return encontrado;
    }

    /**
     * @brief Destructor que libera la memoria de todos los nodos.
     */
    ~Pila() {
        while (cima != nullptr) {
            pop();
        }
    }
};

/**
 * @brief Clase Portafolio que usa una pila para almacenar activos.
 */
class Portafolio {
private:
    string nombreUsuario;
    Pila activos;

public:
    /**
     * @brief Constructor que inicializa el portafolio con un nombre de usuario.
     */
    Portafolio(string nombre) : nombreUsuario(nombre) {}

    /**
     * @brief Agrega un activo al portafolio (al tope de la pila).
     * 
     * @param activo Nombre del activo a agregar.
     */
    void agregarActivo(const string& activo) {
        activos.push(activo);
        cout << "Activo '" << activo << "' agregado." << endl;
    }

    /**
     * @brief Elimina el último activo agregado (pop).
     */
    void eliminarUltimoActivo() {
        if (!activos.isEmpty()) {
            cout << "Activo '" << activos.top() << "' eliminado." << endl;
            activos.pop();
        } else {
            cout << "No hay activos para eliminar." << endl;
        }
    }

    /**
     * @brief Elimina un activo específico del portafolio.
     * 
     * @param activo Nombre del activo a eliminar.
     * @return true si se eliminó, false si no se encontró.
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
     * @brief Muestra el contenido del portafolio.
     */
    void mostrar() const {
        cout << "Portafolio de " << nombreUsuario << ":\n";
        if (activos.isEmpty())
            cout << "(Vacío)\n";
        else
            activos.imprimir();
    }

    /**
     * @brief Ordena los activos del portafolio en orden alfabético ascendente (A-Z).
     *
     * Utiliza una pila auxiliar y manipulación directa de punteros para
     * insertar los elementos en orden sin usar la función push().
     */
    void ordenarActivos() {
        if (activos.isEmpty()) {
            cout << "Nada que ordenar.\n";
            return;
        }

        Pila pilaOrdenada;

        // Proceso de ordenamiento tipo inserción
        while (!activos.isEmpty()) {
            string temp = activos.top();
            activos.pop();

            // Regresar los mayores a la pila original
            while (!pilaOrdenada.isEmpty() && pilaOrdenada.top() > temp) {
                Nodo* mover = new Nodo;
                mover->valor = pilaOrdenada.top();
                mover->siguiente = activos.cima;
                activos.cima = mover;
                pilaOrdenada.pop();
            }

            // Insertar temp ordenadamente sin push
            Nodo* nuevo = new Nodo;
            nuevo->valor = temp;
            nuevo->siguiente = pilaOrdenada.cima;
            pilaOrdenada.cima = nuevo;
        }

        // Restaurar activos desde la pila ordenada
        while (!pilaOrdenada.isEmpty()) {
            Nodo* mover = new Nodo;
            mover->valor = pilaOrdenada.top();
            mover->siguiente = activos.cima;
            activos.cima = mover;
            pilaOrdenada.pop();
        }

        cout << "Activos ordenados alfabéticamente.\n";
    }

    /**
     * @brief Devuelve todos los activos del portafolio como vector sin usar push_back.
     * 
     * @return Vector de strings con los nombres de los activos.
     */
    vector<string> obtenerActivos() const {
        // Contar cuántos nodos hay
        int count = 0;
        Nodo* actual = activos.cima;
        while (actual != nullptr) {
            count++;
            actual = actual->siguiente;
        }
    
        // Crear vector del tamaño exacto
        vector<string> v(count);
    
        // Llenar el vector manualmente
        actual = activos.cima;
        for (int i = 0; i < count; ++i) {
            v[i] = actual->valor;
            actual = actual->siguiente;
        }
    
        return v;
    }


    // Árbol de decisión para recomendar compra de un activo
    // Usa tendencia de precios históricos y noticias del sector
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