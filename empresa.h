#ifndef EMPRESA_H
#define EMPRESA_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Nodo para la multilista de precios históricos
struct NodoPrecio {
    string fecha;
    float precioCierre;
    NodoPrecio* siguiente;
    NodoPrecio(string f, float p) : fecha(f), precioCierre(p), siguiente(nullptr) {}
};

// Multilista para historial de precios de una acción
class MultilistaPrecio {
public:
    NodoPrecio* cabeza;
    MultilistaPrecio() : cabeza(nullptr) {}

    // Agrega un precio al historial (al inicio)
    void agregarPrecio(const string& fecha, float precio) {
        NodoPrecio* nuevo = new NodoPrecio(fecha, precio);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }

    // Calcula el promedio móvil de los últimos 'dias' precios
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

    // Imprime el historial de precios
    void imprimir() {
        NodoPrecio* actual = cabeza;
        while (actual) {
            cout << actual->fecha << ": " << actual->precioCierre << "  ";
            actual = actual->siguiente;
        }
        cout << endl;
    }
};

// Nodo de ABB para empresa
struct Empresa {
    string ticker;
    string nombre;
    string sector;
    float precioActual;
    MultilistaPrecio historialPrecios;
    Empresa* izquierda;
    Empresa* derecha;

    Empresa(string t, string n, string s, float p)
        : ticker(t), nombre(n), sector(s), precioActual(p),
          izquierda(nullptr), derecha(nullptr) {}
};

// Árbol binario de búsqueda para empresas
class ABBEmpresas {
private:
    Empresa* raiz;

    // Inserta una empresa en el ABB (por ticker)
    Empresa* insertar(Empresa* nodo, Empresa* nueva) {
        if (!nodo) return nueva;
        if (nueva->ticker < nodo->ticker)
            nodo->izquierda = insertar(nodo->izquierda, nueva);
        else if (nueva->ticker > nodo->ticker)
            nodo->derecha = insertar(nodo->derecha, nueva);
        // Si es igual, no inserta duplicados
        return nodo;
    }

    // Búsqueda binaria por ticker
    Empresa* buscar(Empresa* nodo, const string& ticker) {
        if (!nodo) return nullptr;
        if (ticker < nodo->ticker)
            return buscar(nodo->izquierda, ticker);
        else if (ticker > nodo->ticker)
            return buscar(nodo->derecha, ticker);
        else
            return nodo;
    }

    // Recorrido inorden (orden alfabético por ticker)
    void inorden(Empresa* nodo, vector<Empresa*>& lista) {
        if (!nodo) return;
        inorden(nodo->izquierda, lista);
        lista.push_back(nodo);
        inorden(nodo->derecha, lista);
    }

    // Liberar memoria
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

    // Inicializa automáticamente empresas reales con datos aleatorios
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
        const string sectores[8] = {
            "Tecnología","Finanzas","Salud","Consumo","Energía","Industrial","Telecomunicaciones","Materiales"
        };

        srand(time(nullptr));
        for (int i = 0; i < 50; ++i) {
            float precio = 50 + rand() % 450 + (rand() % 1000) / 1000.0f; // Precio entre 50 y 500 aprox
            string sector = sectores[rand() % 8];
            insertarEmpresa(tickers[i], nombres[i], sector, precio);

            // Agregar precios históricos aleatorios (5 a 10 precios)
            Empresa* emp = buscarEmpresa(tickers[i]);
            int nPrecios = 5 + rand() % 6;
            float precioHist = precio;
            for (int j = 0; j < nPrecios; ++j) {
                // Fecha ficticia: "2024-06-(día)"
                string fecha = "2024-06-" + to_string(10 + j);
                // Variar el precio histórico aleatoriamente
                float variacion = ((rand() % 2001) - 1000) / 100.0f; // -10.00 a +10.00
                precioHist = max(1.0f, precioHist + variacion);
                emp->historialPrecios.agregarPrecio(fecha, precioHist);
            }
            // Actualizar precio actual al último histórico
            if (emp->historialPrecios.cabeza)
                emp->precioActual = emp->historialPrecios.cabeza->precioCierre;
        }
    }

public:
    ABBEmpresas() : raiz(nullptr) {
        inicializarEmpresas();
    }

    ~ABBEmpresas() { destruir(raiz); }

    // Inserta una empresa (si no existe)
    void insertarEmpresa(const string& ticker, const string& nombre, const string& sector, float precio) {
        if (!buscarEmpresa(ticker)) {
            Empresa* nueva = new Empresa(ticker, nombre, sector, precio);
            raiz = insertar(raiz, nueva);
        }
    }

    // Busca una empresa por ticker
    Empresa* buscarEmpresa(const string& ticker) {
        return buscar(raiz, ticker);
    }

    // Agrega precio histórico a una empresa
    void agregarPrecio(const string& ticker, const string& fecha, float precio) {
        Empresa* emp = buscarEmpresa(ticker);
        if (emp) {
            emp->historialPrecios.agregarPrecio(fecha, precio);
            emp->precioActual = precio;
        }
    }

    // Devuelve lista ordenada de empresas (inorden)
    vector<Empresa*> obtenerEmpresasOrdenadas() {
        vector<Empresa*> lista;
        inorden(raiz, lista);
        return lista;
    }

    // Imprime todas las empresas y su precio actual
    void imprimirEmpresas() {
        vector<Empresa*> lista = obtenerEmpresasOrdenadas();
        for (auto e : lista) {
            cout << e->ticker << " | " << e->nombre << " | " << e->sector
                 << " | Precio actual: " << e->precioActual << endl;
        }
    }

    // Ordena empresas por precio actual usando Merge Sort (de mayor a menor)
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

    static void mergeSort(vector<Empresa*>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    // Imprime empresas ordenadas por precio actual (de mayor a menor)
    void imprimirPorPrecio() {
        vector<Empresa*> lista = obtenerEmpresasOrdenadas();
        mergeSort(lista, 0, lista.size() - 1);
        for (auto e : lista) {
            cout << e->ticker << " | " << e->nombre << " | " << e->sector
                 << " | Precio actual: " << e->precioActual << endl;
        }
    }
};

#endif
