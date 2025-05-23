#ifndef NOTICIA_H
#define NOTICIA_H

#include <iostream>
#include <string>
using namespace std;

// ======== ESTRUCTURA DE LA NOTICIA ========
struct Noticia {
    int impacto;             // Nivel de impacto de 1 a 10
    string titulo;
    string descripcion;
    string sectorAfectado;
    string fecha;            // NUEVO: fecha en formato "YYYY-MM-DD"
    Noticia* siguiente;

    // Constructor actualizado
    Noticia(int imp, string t, string d, string s, string f) {
        impacto = imp;
        titulo = t;
        descripcion = d;
        sectorAfectado = s;
        fecha = f;
        siguiente = nullptr;
    }
};

// ======== CLASE DE COLA DE PRIORIDAD ========
class ColaPrioridadNoticias {
private:
    Noticia* frente;

public:
    ColaPrioridadNoticias() {
        frente = nullptr;
    }

    bool estaVacia() {
        return frente == nullptr;
    }

    // MÉTODO INSERTAR ACTUALIZADO: incluye fecha
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

    // Muestra las noticias
    void mostrar() {
        Noticia* actual = frente;
        while (actual != nullptr) {
            cout << "[" << actual->fecha << "] "
                 << "(Impacto: " << actual->impacto << ") "
                 << actual->titulo << " - " << actual->sectorAfectado << endl;
            actual = actual->siguiente;
        }
    }

    // Buscar por sector
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

    // Buscar por palabra clave en el título
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

    // Detectar crisis (3 o más noticias de impacto >= 8)
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

    // Calcular promedio del impacto
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

    // Extraer la noticia con mayor prioridad
    Noticia* extraer() {
        if (estaVacia()) return nullptr;

        Noticia* temp = frente;
        frente = frente->siguiente;
        temp->siguiente = nullptr;
        return temp;
    }

    // ======= ORDENAMIENTO POR FECHA (MERGE SORT) =======

    // Divide la lista en dos mitades
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

    // Une dos listas ordenadas por fecha
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

    // Aplica Merge Sort recursivamente
    Noticia* mergeSort(Noticia* cabeza) {
        if (!cabeza || !cabeza->siguiente) return cabeza;

        Noticia* mitad = dividir(cabeza);
        Noticia* izquierda = mergeSort(cabeza);
        Noticia* derecha = mergeSort(mitad);

        return fusionar(izquierda, derecha);
    }

    // Ordena toda la cola cronológicamente
    void ordenarPorFecha() {
        frente = mergeSort(frente);
        cout << "\n📆 Noticias ordenadas por fecha.\n";
    }

    // Destructor para liberar memoria
    ~ColaPrioridadNoticias() {
        while (!estaVacia()) {
            Noticia* temp = extraer();
            delete temp;
        }
    }
};

#endif
