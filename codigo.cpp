// Código base para un sistema de gestión de acciones y noticias financieras

struct Empresa {
    string ticker;
    string nombre;
    string sector;
    float precioActual;
    MultilistaPrecio* historialPrecios;
    Empresa* izquierda;
    Empresa* derecha;
};

struct NodoPrecio {
    string fecha;
    float precioCierre;
    NodoPrecio* siguiente;
};

struct MultilistaPrecio {
    NodoPrecio* cabeza;
    void agregarPrecio(string fecha, float precio);
    float promedioMovil(int dias);
};

struct Noticia {
    int impacto; // Mayor impacto = mayor prioridad
    string titulo;
    string sectorAfectado;
    Noticia* siguiente;
};

struct AccionComprada {
    string ticker;
    int cantidad;
    float precioCompra;
};

struct Portafolio {
    vector<AccionComprada> acciones;
    void agregar(string ticker, int cantidad, float precio);
    void ordenarPorGanancia();
};

struct AccionComprada {
    string ticker;
    int cantidad;
    float precioCompra;
};

struct Portafolio {
    vector<AccionComprada> acciones;
    void agregar(string ticker, int cantidad, float precio);
    void ordenarPorGanancia();
};

struct NodoGrafo {
    string ticker;
    vector<pair<NodoGrafo*, float>> conexiones; // conexión y peso (correlación)
};

struct Grafo {
    vector<NodoGrafo*> empresas;
    void agregarRelacion(string t1, string t2, float peso);
    vector<string> recomendarAcciones(string ticker);
};

struct Operacion {
    string tipo; // "compra" o "venta"
    string ticker;
    int cantidad;
    float precio;
    Operacion* siguiente;
};

struct PilaOperaciones {
    Operacion* tope;
    void push(string tipo, string ticker, int cantidad, float precio);
    Operacion pop();
};