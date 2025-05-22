// TALLER IA 
// TERCER CORTE 
// JESSICA GIL 
// ISABELLA BORDA 

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Nodo para lista de vehículos
// Define un nodo de una lista enlazada simple para almacenar los vehículos estacionados en una zona.

// Struct se usa principalmente para:
// - Agrupar datos relacionados en una sola entidad lógica.
// - Representar objetos simples como coordenadas, fechas, empleados, etc.
// - Organizar mejor el código y hacerlo más legible.
// - En programación orientada a objetos, puede funcionar similar a una clase 

struct Vehiculo {
    string placa;
    Vehiculo* siguiente;
};

// Nodo para la pila de deshacer
// Nodo de una pila (estructura LIFO) para registrar el historial de vehículos agregados, útil para "deshacer" el último registro.
struct NodoPila {
    string placa;
    NodoPila* siguiente;
    // NodoPila >>> el último elemento en entrar es el primero en salir
};

class Pila {
    NodoPila* cima; // Representa la cima de la pila. Se usa para guardar las placas recientemente ingresadas
public:
    // Constructor: pila vacía
    Pila() : cima(nullptr) {}

    // Destructor: libera memoria de todos los nodos
    ~Pila() {
        while (cima) {
            NodoPila* temp = cima;
            cima = cima->siguiente;
            delete temp;
        }
    }

    // Inserta una placa en la parte superior de la pila
    // en otras palabras un nodo con una placa de vehículo en la cima de la pila.
    void push(const string& placa) {
        NodoPila* nuevo = new NodoPila{placa, cima};
        cima = nuevo;
    }
    
    // Devuelve la placa en la cima sin eliminarla
    string top() const {
        return cima ? cima->placa : "";
    }

    // Elimina el nodo en la cima
    void pop() {
        if (!cima) return;
        NodoPila* temp = cima;
        cima = cima->siguiente;
        delete temp;
    }
    
    // Verifica si la pila está vacía.
    bool estaVacia() const {
        return cima == nullptr;
    }
    
    // Imprime el contenido de la pila (de cima hacia abajo)
    void imprimir() const {
        NodoPila* temp = cima;
        while (temp) {
            cout << temp->placa << " ";
            temp = temp->siguiente;
        }
        cout << endl;
    }
};

// Nodo individual de una cola
struct NodoCola {
    string placa;
    NodoCola* siguiente;
    // el primer elemento en entrar es el primero en salir.
};

class Cola {
    NodoCola* frente;  // Primer nodo en la cola
    NodoCola* final;   // Último nodo en la cola
public:

    // Constructor: cola vacía
    Cola() : frente(nullptr), final(nullptr) {}
    
    // Destructor: libera todos los nodos de la cola
    ~Cola() {
        while (frente) {
            NodoCola* temp = frente;
            frente = frente->siguiente;
            delete temp;
        }
        final = nullptr;
    }
    
    // Agrega un vehículo al final de la cola
    void Enqueue(const string& placa) {
        NodoCola* nuevo = new NodoCola{placa, nullptr};
        if (!frente) {
            frente = final = nuevo;  // Si la cola estaba vacía
        } else {
            final->siguiente = nuevo;
            final = nuevo;
        }
    }

    // Elimina y retorna el vehículo al frente de la cola
    string Dequeue() {
        if (!frente) return "";
        NodoCola* temp = frente;
        string placa = temp->placa;
        frente = frente->siguiente;
        if (!frente) final = nullptr;
        delete temp;
        return placa;
    }

    // Verifica si la cola está vacía
    bool estaVacia() const {
        return frente == nullptr;
    }

    // Imprime las placas en orden de atención
    void imprimir() const {
        NodoCola* temp = frente;
        while (temp) {
            cout << temp->placa << " ";
            temp = temp->siguiente;
        }
        cout << endl;
    }
};

    // El orden de los punteros es zona, parqueadero, ciudad; ya que el parqueadero se encuentra
    // dentro de la ciudad, asi como la zona dentro del parqueadero.
    
    // Asi mismo se crean los struct para poder usar las multilistas.
    
struct Zona {
    string nombre;     // Nombre de la zona
    int capacidad;     // Capacidad máxima de vehículos
    int ocupados;      // Número de vehículos actualmente estacionados
    Vehiculo* vehiculos; // Lista de vehículos en esta zona
    Cola cola;         // Cola de vehículos esperando
    Pila pila;         // Pila de vehículos registrados (para deshacer)
    Zona* sigZona;     // Siguiente zona en la lista

    // Constructor
    Zona(const string& nombre_)
        : nombre(nombre_), capacidad(3), ocupados(0),
          vehiculos(nullptr), sigZona(nullptr) {}
};

struct Parqueadero {
    string nombre;               // Nombre del parqueadero
    Zona* zonas;                 // Lista de zonas
    Parqueadero* sigParqueadero; // Siguiente parqueadero

    // Constructor
    Parqueadero(const string& nombre_)
        : nombre(nombre_), zonas(nullptr), sigParqueadero(nullptr) {}
};

struct Ciudad {
    string nombre;             // Nombre de la ciudad
    Parqueadero* parqueaderos; // Lista de parqueaderos
    Ciudad* sigCiudad;         // Siguiente ciudad

    // Constructor
    Ciudad(const string& nombre_)
        : nombre(nombre_), parqueaderos(nullptr), sigCiudad(nullptr) {}
};

// Clase que representa el sistema de gestión de parqueaderos
class Sistema {
private:
    Ciudad* ciudades; // Lista de ciudades en el sistema
    
    // Libera memoria de vehículos
    void liberarVehiculos(Vehiculo* v) {
        while (v) {
            Vehiculo* temp = v;
            v = v->siguiente;
            delete temp;
        }
    }
    
    // Libera memoria de zonas
    void liberarZonas(Zona* z) {
        while (z) {
            Zona* temp = z;
            liberarVehiculos(temp->vehiculos);
            z = z->sigZona;
            delete temp;
        }
    }
    
    // Libera memoria de parqueaderos
    void liberarParqueaderos(Parqueadero* p) {
        while (p) {
            Parqueadero* temp = p;
            liberarZonas(temp->zonas);
            p = p->sigParqueadero;
            delete temp;
        }
    }
    
    // Libera memoria de ciudades
    void liberarCiudades(Ciudad* c) {
        while (c) {
            Ciudad* temp = c;
            liberarParqueaderos(temp->parqueaderos);
            c = c->sigCiudad;
            delete temp;
        }
    }
    
    // Función para intercambiar dos elementos
    // Luego se pueda realizar la implementación del QuickSort
    template <typename T>
    void intercambiar(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }
    
    // Función para particionar la lista en el QuickSort
    template <typename T>
    int particionar(vector<T>& lista, int bajo, int alto, bool (Sistema::*comparar)(T, T)) {
        T pivote = lista[alto];  
        int i = bajo - 1;

        for (int j = bajo; j < alto; ++j) {
            if ((this->*comparar)(lista[j], pivote)) {
                ++i;
                intercambiar(lista[i], lista[j]);
            }
        }
        intercambiar(lista[i + 1], lista[alto]);
        return i + 1;
    }

    // Función que implementa el algoritmo QuickSort
    template <typename T>
    void quickSort(vector<T>& lista, int bajo, int alto, bool (Sistema::*comparar)(T, T)) {
        if (bajo < alto) {
            int particionIndex = particionar(lista, bajo, alto, comparar);
            quickSort(lista, bajo, particionIndex - 1, comparar);
            quickSort(lista, particionIndex + 1, alto, comparar);
        }
    }

    // Función para realizar búsqueda binaria
    // Se usa busqueda binaria para eficencia de espacio y tiempo.
    template <typename T>
    int busquedaBinaria(const vector<T>& arreglo, const string& valor) {
        int bajo = 0;
        int alto = arreglo.size() - 1;
        while (bajo <= alto) {
            int medio = bajo + (alto - bajo) / 2;
            if (arreglo[medio]->nombre == valor) {
                return medio;
            }
            if (arreglo[medio]->nombre < valor) {
                bajo = medio + 1;
            } else {
                alto = medio - 1;
            }
        }
        return -1;
    }
    
    // Funciones de comparación para ordenar elementos por nombre
    bool compararCiudades(Ciudad* a, Ciudad* b) {
        return a->nombre < b->nombre;
    }

    bool compararParqueaderos(Parqueadero* a, Parqueadero* b) {
        return a->nombre < b->nombre;
    }

    bool compararZonas(Zona* a, Zona* b) {
        return a->nombre < b->nombre;
    }
    
    // Obtener listas ordenadas
    vector<Ciudad*> obtenerCiudadesOrdenadas() {
        vector<Ciudad*> lista;
        Ciudad* c = ciudades;
        while (c) {
            lista.push_back(c);
            c = c->sigCiudad;
        }
        if (!lista.empty()) {
            quickSort(lista, 0, lista.size() - 1, &Sistema::compararCiudades);
        }
        return lista;
    }

    // Obtener lista ordenada de parqueaderos
    vector<Parqueadero*> obtenerParqueaderosOrdenados(Parqueadero* parqueaderos) {
        vector<Parqueadero*> lista;
        Parqueadero* p = parqueaderos;
        while (p) {
            lista.push_back(p);
            p = p->sigParqueadero;
        }
        if (!lista.empty()) {
            quickSort(lista, 0, lista.size() - 1, &Sistema::compararParqueaderos);
        }
        return lista;
    }
    
    // Obtener lista ordenada de zonas
    vector<Zona*> obtenerZonasOrdenadas(Zona* zonas) {
        vector<Zona*> lista;
        Zona* z = zonas;
        while (z) {
            lista.push_back(z);
            z = z->sigZona;
        }
        if (!lista.empty()) {
            quickSort(lista, 0, lista.size() - 1, &Sistema::compararZonas);
        }
        return lista;
    }
    
    // Busca una ciudad por nombre
    Ciudad* buscarCiudad(const string& nombreCiudad) {
        vector<Ciudad*> ciudadesOrdenadas = obtenerCiudadesOrdenadas();
        if (!ciudadesOrdenadas.empty()) {
            int idx = busquedaBinaria(ciudadesOrdenadas, nombreCiudad);
            if (idx != -1) {
                return ciudadesOrdenadas[idx];
            }
        }
        return nullptr;
    }
    
    // Busca un parqueadero en una ciudad
    Parqueadero* buscarParqueadero(Ciudad* ciudad, const string& nombreParqueadero) {
        if (!ciudad) return nullptr;
        
        vector<Parqueadero*> parqueaderosOrdenados = obtenerParqueaderosOrdenados(ciudad->parqueaderos);
        if (!parqueaderosOrdenados.empty()) {
            int idx = busquedaBinaria(parqueaderosOrdenados, nombreParqueadero);
            if (idx != -1) {
                return parqueaderosOrdenados[idx];
            }
        }
        return nullptr;
    }
    
    // Busca una zona específica usando búsqueda binaria en cada nivel
    Zona* buscarZona(const string& nombreCiudad, const string& nombreParqueadero, const string& nombreZona) {
        Ciudad* ciudad = buscarCiudad(nombreCiudad);
        if (!ciudad) return nullptr;
        
        Parqueadero* parqueadero = buscarParqueadero(ciudad, nombreParqueadero);
        if (!parqueadero) return nullptr;
        
        vector<Zona*> zonasOrdenadas = obtenerZonasOrdenadas(parqueadero->zonas);
        if (!zonasOrdenadas.empty()) {
            int idx = busquedaBinaria(zonasOrdenadas, nombreZona);
            if (idx != -1) {
                return zonasOrdenadas[idx];
            }
        }
        return nullptr;
    }

    // Verifica si una ciudad existe
    bool existeCiudad(const string& nombre) {
        return buscarCiudad(nombre) != nullptr;
    }

    // Verifica si un parqueadero existe en una ciudad
    bool existeParqueadero(const string& nombreCiudad, const string& nombreParqueadero) {
        Ciudad* ciudad = buscarCiudad(nombreCiudad);
        if (!ciudad) return false;
        
        return buscarParqueadero(ciudad, nombreParqueadero) != nullptr;
    }

    // Verifica si una zona existe en un parqueadero
    bool existeZona(const string& nombreCiudad, const string& nombreParqueadero, const string& nombreZona) {
        return buscarZona(nombreCiudad, nombreParqueadero, nombreZona) != nullptr;
    }
    
    // Valida que el nombre no esté vacío
    bool validarNombre(const string& nombre) {
        return !nombre.empty();
    }

public:
    // Constructor y destructor
    Sistema() : ciudades(nullptr) {}

    ~Sistema() {
        liberarCiudades(ciudades);
    }
    
    // Registra un vehículo en una zona
    bool registrarVehiculo(const string& nombreCiudad, const string& nombreParqueadero, const string& nombreZona, const string& placa, bool desdeAtender = false) {
        // Validar entrada
        if (!validarNombre(nombreCiudad) || !validarNombre(nombreParqueadero) || 
            !validarNombre(nombreZona) || !validarNombre(placa)) {
            cout << "Error: Los nombres no pueden estar vacíos." << endl;
            return false;
        }
        
        Zona* z = buscarZona(nombreCiudad, nombreParqueadero, nombreZona); 
        if (!z) {
            cout << "Error: No se encontró la zona especificada." << endl;
            return false;
        }

        // Verificar si la placa ya existe en la zona
        Vehiculo* actual = z->vehiculos;
        while (actual) {
            if (actual->placa == placa) {
                cout << "Error: Ya existe un vehículo con esa placa en esta zona." << endl;
                return false;
            }
            actual = actual->siguiente;
        }

        if (z->ocupados < z->capacidad) {
            // Hay espacio en la zona
            Vehiculo* nuevo = new Vehiculo{placa, z->vehiculos};
            z->vehiculos = nuevo;
            z->ocupados++;
            
            // Solo agregar a la pila de deshacer si no viene de atenderVehiculo
            if (!desdeAtender) {
                z->pila.push(placa);
            }
            
            cout << "Vehículo " << placa << " registrado exitosamente." << endl;
            return true;
        } else {
            // Zona llena
            if (!desdeAtender) {
                z->cola.Enqueue(placa);
                cout << "Zona llena. Vehículo " << placa << " en cola de espera." << endl;
            } else {
                cout << "Error: No hay espacio disponible para el vehículo." << endl;
            }
            return false;
        }
    }
    
    // Deshace el último registro de vehículo
    void deshacerRegistro(const string& nombreCiudad, const string& nombreParqueadero, const string& nombreZona) {
        // Validar entrada
        if (!validarNombre(nombreCiudad) || !validarNombre(nombreParqueadero) || !validarNombre(nombreZona)) {
            cout << "Error: Los nombres no pueden estar vacíos." << endl;
            return;
        }
        
        Zona* z = buscarZona(nombreCiudad, nombreParqueadero, nombreZona);
        if (!z) {
            cout << "Error: No se encontró la zona especificada." << endl;
            return;
        }
        
        if (z->pila.estaVacia()) {
            cout << "No hay registros para deshacer en esta zona." << endl;
            return;
        }
        
        // Obtener la placa a eliminar de la pila
        string placa = z->pila.top();
        z->pila.pop();
        
        // Buscar y eliminar el vehículo
        Vehiculo* actual = z->vehiculos;
        Vehiculo* anterior = nullptr;

        while (actual) {
            if (actual->placa == placa) {
                if (anterior) anterior->siguiente = actual->siguiente;
                else z->vehiculos = actual->siguiente;
                delete actual;
                z->ocupados--;
                cout << "Se ha deshecho el registro del vehículo " << placa << endl;
                return;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        
        cout << "No se encontró el vehículo con placa " << placa << " en la zona." << endl;
    }

    // Atiende el siguiente vehículo en la cola
    void atenderVehiculo(const string& nombreCiudad, const string& nombreParqueadero, const string& nombreZona) {
        // Validar entrada
        if (!validarNombre(nombreCiudad) || !validarNombre(nombreParqueadero) || !validarNombre(nombreZona)) {
            cout << "Error: Los nombres no pueden estar vacíos." << endl;
            return;
        }
        
        Zona* z = buscarZona(nombreCiudad, nombreParqueadero, nombreZona);
        if (!z) {
            cout << "Error: No se encontró la zona especificada." << endl;
            return;
        }
        
        if (z->cola.estaVacia()) {
            cout << "No hay vehículos en cola para atender." << endl;
            return;
        }

        if (z->ocupados >= z->capacidad) {
            cout << "No hay espacio disponible para atender vehículos en cola." << endl;
            return;
        }

        string placa = z->cola.Dequeue();
        if (registrarVehiculo(nombreCiudad, nombreParqueadero, nombreZona, placa, true)) {
            // Si se registró correctamente, también agregamos a la pila de deshacer
            z->pila.push(placa);
        } else {
            // Si hubo algún problema, devolvemos la placa a la cola
            z->cola.Enqueue(placa);
        }
    }

    // Muestra la estructura completa del sistema
    void mostrarEstructura() {
        if (!ciudades) {
            cout << "El sistema no tiene ciudades registradas." << endl;
            return;
        }

        vector<Ciudad*> ciudadesOrdenadas = obtenerCiudadesOrdenadas();
        
        for (Ciudad* c : ciudadesOrdenadas) {
            cout << "Ciudad: " << c->nombre << endl;
            
            vector<Parqueadero*> parqueaderosOrdenados = obtenerParqueaderosOrdenados(c->parqueaderos);
            
            if (parqueaderosOrdenados.empty()) {
                cout << "  No hay parqueaderos registrados en esta ciudad." << endl;
                continue;
            }
            
            for (Parqueadero* p : parqueaderosOrdenados) {
                cout << "  Parqueadero: " << p->nombre << endl;
                
                vector<Zona*> zonasOrdenadas = obtenerZonasOrdenadas(p->zonas);
                
                if (zonasOrdenadas.empty()) {
                    cout << "    No hay zonas registradas en este parqueadero." << endl;
                    continue;
                }
                
                for (Zona* z : zonasOrdenadas) {
                    cout << "    Zona: " << z->nombre << " (" << z->ocupados << "/" << z->capacidad << ")" << endl;
                    
                    cout << "      Vehículos: ";
                    if (!z->vehiculos) {
                        cout << "Ninguno";
                    } else {
                        Vehiculo* v = z->vehiculos;
                        while (v) {
                            cout << v->placa << " ";
                            v = v->siguiente;
                        }
                    }
                    cout << endl;
                    
                    cout << "      Cola: ";
                    if (z->cola.estaVacia()) {
                        cout << "Vacía" << endl;
                    } else {
                        z->cola.imprimir();
                    }
                    
                    cout << "      Pila: ";
                    if (z->pila.estaVacia()) {
                        cout << "Vacía" << endl;
                    } else {
                        z->pila.imprimir();
                    }
                }
            }
        }
    }

    // Agrega una nueva ciudad
    void agregarCiudad(const string& nombre) {
        // Validar entrada
        if (!validarNombre(nombre)) {
            cout << "Error: El nombre de la ciudad no puede estar vacío." << endl;
            return;
        }
        
        if (existeCiudad(nombre)) {
            cout << "Error: Ya existe una ciudad con ese nombre." << endl;
            return;
        }
        
        Ciudad* nueva = new Ciudad(nombre);
        nueva->sigCiudad = ciudades;
        ciudades = nueva;
        cout << "Ciudad " << nombre << " agregada exitosamente." << endl;
    }

    // Agrega un nuevo parqueadero a una ciudad
    void agregarParqueadero(const string& nombreCiudad, const string& nombreParqueadero) {
        // Validar entrada
        if (!validarNombre(nombreCiudad) || !validarNombre(nombreParqueadero)) {
            cout << "Error: Los nombres no pueden estar vacíos." << endl;
            return;
        }
        
        if (existeParqueadero(nombreCiudad, nombreParqueadero)) {
            cout << "Error: Ya existe un parqueadero con ese nombre en esa ciudad." << endl;
            return;
        }
        
        Ciudad* ciudad = buscarCiudad(nombreCiudad);
        if (!ciudad) {
            cout << "Error: No se encontró la ciudad especificada." << endl;
            return;
        }
        
        Parqueadero* nuevo = new Parqueadero(nombreParqueadero);
        nuevo->sigParqueadero = ciudad->parqueaderos;
        ciudad->parqueaderos = nuevo;
        cout << "Parqueadero " << nombreParqueadero << " agregado exitosamente a " << nombreCiudad << "." << endl;
    }

    // Agrega una nueva zona a un parqueadero
    void agregarZona(const string& nombreCiudad, const string& nombreParqueadero, const string& nombreZona) {
        // Validar entrada
        if (!validarNombre(nombreCiudad) || !validarNombre(nombreParqueadero) || !validarNombre(nombreZona)) {
            cout << "Error: Los nombres no pueden estar vacíos." << endl;
            return;
        }
        
        if (existeZona(nombreCiudad, nombreParqueadero, nombreZona)) {
            cout << "Error: Ya existe una zona con ese nombre en ese parqueadero." << endl;
            return;
        }
        
        Ciudad* ciudad = buscarCiudad(nombreCiudad);
        if (!ciudad) {
            cout << "Error: No se encontró la ciudad especificada." << endl;
            return;
        }
        
        Parqueadero* parqueadero = buscarParqueadero(ciudad, nombreParqueadero);
        if (!parqueadero) {
            cout << "Error: No se encontró el parqueadero especificado." << endl;
            return;
        }
        
        // Crear nueva zona
        Zona* nueva = new Zona(nombreZona);
        
        // Insertar zona y mantener orden
        vector<Zona*> zonasOrdenadas = obtenerZonasOrdenadas(parqueadero->zonas);
        zonasOrdenadas.push_back(nueva);
        quickSort(zonasOrdenadas, 0, zonasOrdenadas.size() - 1, &Sistema::compararZonas);
        
        // Reconstruir la lista enlazada ordenada
        parqueadero->zonas = nullptr;
        for (int i = zonasOrdenadas.size() - 1; i >= 0; --i) {
            zonasOrdenadas[i]->sigZona = parqueadero->zonas;
            parqueadero->zonas = zonasOrdenadas[i];
        }
        
        cout << "Zona " << nombreZona << " agregada exitosamente con capacidad de 3." << endl;
    }
};


int main() {
    Sistema sistema;
    string ciudad, parqueadero, zona, placa, opcion;
    
    // Uso de un DO WHILE para saber que opcion del programa se desea realizar
    do {
        cout << "\n===== SISTEMA DE GESTIÓN DE PARQUEADEROS =====\n";
        cout << "\nMenú:\n";
        cout << "1. Agregar Ciudad, Parqueadero y Zona\n";
        cout << "2. Registrar Vehículo\n";
        cout << "3. Mostrar Estructura\n";
        cout << "4. Deshacer Último Registro\n";
        cout << "5. Atender Vehículo de la Cola\n";
        cout << "6. Salir del Sistema\n";
        cout << "Ingrese una opción: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == "1") {
            cout << "Ingrese nombre de la ciudad: ";
            getline(cin, ciudad);
            sistema.agregarCiudad(ciudad);

            cout << "Ingrese nombre del parqueadero: ";
            getline(cin, parqueadero);
            sistema.agregarParqueadero(ciudad, parqueadero);

            cout << "Ingrese nombre de la zona: ";
            getline(cin, zona);
            sistema.agregarZona(ciudad, parqueadero, zona);
        }
        else if (opcion == "2") {
            cout << "Ingrese nombre de la ciudad: ";
            getline(cin, ciudad);
            cout << "Ingrese nombre del parqueadero: ";
            getline(cin, parqueadero);
            cout << "Ingrese nombre de la zona: ";
            getline(cin, zona);
            cout << "Ingrese placa del vehículo: ";
            getline(cin, placa);
            sistema.registrarVehiculo(ciudad, parqueadero, zona, placa);
        }
        else if (opcion == "3") {
            sistema.mostrarEstructura();
        }
        else if (opcion == "4") {
            cout << "Ingrese nombre de la ciudad: ";
            getline(cin, ciudad);
            cout << "Ingrese nombre del parqueadero: ";
            getline(cin, parqueadero);
            cout << "Ingrese nombre de la zona: ";
            getline(cin, zona);
            sistema.deshacerRegistro(ciudad, parqueadero, zona);
        }
        else if (opcion == "5") {
            cout << "Ingrese nombre de la ciudad: ";
            getline(cin, ciudad);
            cout << "Ingrese nombre del parqueadero: ";
            getline(cin, parqueadero);
            cout << "Ingrese nombre de la zona: ";
            getline(cin, zona);
            sistema.atenderVehiculo(ciudad, parqueadero, zona);
        }
        else if (opcion == "6") {
            cout << "Saliendo del sistema...\n";
        }
        else {
            cout << "Opción no válida. Intente de nuevo.\n";
        }

    } while (opcion != "6");

    return 0;
}