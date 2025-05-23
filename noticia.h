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

// ======== GENERADOR DE NOTICIAS ALEATORIAS ========
#ifndef GENERADOR_NOTICIAS_H
#define GENERADOR_NOTICIAS_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>

// Genera un string de fecha con formato "YYYY-MM-DD" a partir de un número
string generarFecha(int diasDesdeInicio = 0) {
    int baseYear = 2025;
    int baseMonth = 5;
    int baseDay = 1 + diasDesdeInicio;

    stringstream ss;
    ss << baseYear << "-";
    ss << setw(2) << setfill('0') << baseMonth << "-";
    ss << setw(2) << setfill('0') << baseDay;
    return ss.str();
}

// Generador aleatorio de noticias con semilla
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

    vector<string> sectores = {
        "Financiero", "Tecnología", "Energía", "Industrial", "Laboral", "Salud", "Consumo"
    };

    for (int i = 0; i < cantidad; ++i) {
        int impacto = rand() % 10 + 1;
        string titulo = titulos[rand() % titulos.size()];
        string descripcion = descripciones[rand() % descripciones.size()];
        string sector = sectores[rand() % sectores.size()];
        string fecha = generarFecha(i);  // Avanza un día por noticia

        cola.insertar(impacto, titulo, descripcion, sector, fecha);
    }
}

#endif

#endif
