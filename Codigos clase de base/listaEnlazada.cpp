
// Algoritmos y estructuras de datos - 28/02/2025 //
// Parcial 1 - Jessica Alejandra Gil Tellez //


#include <iostream>
#include <ctime>  // Para srand(time(0))

using namespace std;


/*código para la matriz*/

// Función para crear una matriz dinámica
int** crear_mat(int f, int c) {
    int** m = new int*[f];
    for (int i = 0; i < f; i++) {
        m[i] = new int[c];
        for (int j = 0; j < c; j++) {
            m[i][j] = 0;
        }
    }
    return m;
}

// Función para destruir la matriz
void destruir_mat(int** m, int f) {
    for (int i = 0; i < f; i++) {
        delete[] m[i];
    }
    delete[] m;
}

// Función para imprimir la matriz
void print_mat(int** m, int f, int c) {
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            cout << m[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}


/*código para el arreglo*/

int* crear_arreglo(int n) {
    int* arr = new int[n];  // Crear arreglo dinámico de tamaño n
    for (int i = 0; i < n; i++) {
        arr[i] = 0;  // Inicializar con 0 (o cualquier otro valor que desees)
    }
    return arr;
}

// Función para destruir el arreglo
void destruir_arreglo(int* arr) {
    delete[] arr;  // Liberar la memoria del arreglo dinámico
}

// Función para imprimir el arreglo
void print_arreglo(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\t";
    }
    cout << endl;
}

// Función para llenar el arreglo con valores
void llenar_arreglo(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << "Introduce el valor para el elemento " << i << ": ";
        cin >> arr[i];
    }
}

//  clase Venta - Jessica Alejandra Gil Tellez //

class Venta {
private:
    int cliente;
    int vendedor;
    int producto;
public:
    Venta() {
        cliente = -1; 
        vendedor = -1;
        producto = -1;
    }
    Venta(int c, int v, int p) { // constructor con parametros
        cliente = c;
        vendedor = v;
        producto = p;
    }
    
    // Métodos Getters y Setters - Jessica Alejandra Gil Tellez //
    int getCliente() const { 
        return cliente; 
    }
    void setCliente(int c) { 
        cliente = c; 
    }
    int getVendedor() const { 
        return vendedor; 
    }
    void setVendedor(int v) { 
        vendedor = v; 
    }

    int getProducto() const { 
        return producto; 
    }
    void setProducto(int p) { 
        producto = p; 
    }

    Venta& operator=(const Venta& f) {
        cliente = f.cliente;
        vendedor = f.vendedor;
        producto = f.producto;
        return *this;
    }

    string to_string() const {
        return std::to_string(cliente) + ", " + std::to_string(vendedor) + ", " + std::to_string(producto);
    }

    friend std::ostream& operator<<(std::ostream& os, const Venta& s) {
        return os << s.to_string();
    }
};

// Clase nodo con plantilla - Jessica Alejandra Gil Tellez //

//poner aquí su código de listas con los comentarios realizados en las clases

// Clase Lista simplemente enlazada- Jessica Alejandra Gil Tellez //
// Implementa una lista enlazada con métodos para insertar elementos y mostrar su contenido.

// Definir clase nodo con plantilla - Jessica Alejandra Gil Tellez //
template <typename T> // Usa una plantilla (template<T>), lo que permite usarla con cualquier tipo de dato.
class Nodo{
    private:
        T valor; // Guarda el dato del nodo.
        Nodo<T>* siguiente; // Es un puntero que apunta al próximo nodo en la lista.
    public:
        // constructor 
        // Inicializa el nodo con el valor _valor.
        // siguiente = nullptr significa que el nodo no apunta a otro nodo (por defecto).
        Nodo(T _valor) : valor(_valor), siguiente(nullptr){}

        // Métodos getter y setter - Jessica Alejandra Gil Tellez //
        // Metodo setter para ajustar siguiente
        
        void setSiguiente(Nodo<T>* _siguiente){ // Permite modificar el puntero siguiente para que apunte a otro nodo.
            this -> siguiente = _siguiente; // this es un puntero que apunta al objeto actual de la clase. Se usa para diferenciar atributos y parámetros cuando tienen el mismo nombre.
            // Se usa con -> porque this es un puntero (this->atributo).
        }

        // Metodo setter para ajustar valor - Permite cambiar el valor del nodo.
        void setValor(T _valor){
            this -> valor = _valor;
        }

        // Metodo getter para valor - Devuelve el valor del nodo.
        T getValor(){
            return valor;
        }

        // Metodo getter paar siguiente - Devuelve el puntero al siguiente nodo.
        Nodo<T>* getSiguiente(){
            return siguiente;
        }
};

// Lista enlazada con plantilla - Jessica Alejandra Gil Tellez //
// Usa punteros para enlazar los nodos.
// No tiene un tamaño fijo, crece dinámicamente.
// Implementa inserción y visualización de elementos.

template <typename T>
class ListaEnlazada{
    private:
        Nodo<T>* cabeza; // Puntero al primer nodo de la lista.
        int size; //  Lleva la cuenta del número de elementos en la lista.
    public:
        // constructor
        ListaEnlazada() : cabeza(nullptr){}; //  Inicializa la lista con cabeza = nullptr (lista vacía)

        // destructor- Se encarga de liberar la memoria cuando el objeto se destruye.
        ~ListaEnlazada(){
            Nodo<T>* actual = cabeza;
            Nodo<T>* siguiente = nullptr;
            while(actual != nullptr){ // Usa un bucle while para recorrer y eliminar cada nodo de la lista.
                siguiente = actual -> getSiguiente();
                delete actual;
                actual = siguiente;
            }
        }

        // Metodo para insertar nodos al final de la lista (setter) - Jessica Alejandra Gil Tellez //
        void insertar(const T& _valor){ 
            Nodo<T>* nuevoNodo = new Nodo<T>(_valor); // Crea un nuevo nodo con el valor _valor.
            // new Nodo<T>(_valor) usa el constructor de la clase Nodo para inicializar el nodo.
            if(cabeza == nullptr){
                cabeza = nuevoNodo; //  Si la lista está vacía, el nuevo nodo se convierte en la cabeza.
            }else{
                Nodo<T>* actual = cabeza; // Si la lista no está vacía, crea un puntero actual que apunta a la cabeza de la lista.
                while (actual -> getSiguiente())  //  Recorre la lista hasta el último nodo.
                {
                    actual = actual -> getSiguiente(); // avanza al siguiente nodo hasta encontrar un nodo cuyo siguiente sea nullptr (último nodo).
                }
                actual ->setSiguiente(nuevoNodo); // Conecta el último nodo con el nuevo nodo, agregándolo al final de la lista
            }
            size++; //  Incrementa el tamaño de la lista (size).
        }

        // Metodo para insertar en posicion n - Jessica Alejandra Gil Tellez //
        //  Inserta un nodo en una posición específica de la lista.
        void insertarEnPosicion(int posicion, const T& _valor){ // método que recibe posición en donde se insertara y el valor a insertar
            Nodo<T>* nuevoNodo = new Nodo<T>(_valor); // Crea un nuevo nodo con _valor.
            if(posicion == 0){ // si posicion es 0, significa que el nodo debe insertarse al inicio.
                nuevoNodo -> setSiguiente(cabeza); // El nuevo nodo se enlaza con la antigua cabeza (cabeza).
                cabeza = nuevoNodo; // Luego, la cabeza de la lista ahora es el nuevo nodo.
                return;
            }
            Nodo<T>* actual = cabeza; // Crea actual, un puntero que comienza en la cabeza.
            int contador = 0; // llevará el número de nodos recorridos.
            while (actual != nullptr && contador < (posicion -1) ) // Recorre la lista hasta llegar a la posición anterior a la deseada (posicion - 1).
            {
                actual = actual -> getSiguiente();
                contador++;
            }

            if(actual == nullptr){ // Si actual es nullptr, la posición está fuera del rango y la inserción no es posible.
                cout << "Posicion invalida" << endl;
                delete nuevoNodo; // Se libera la memoria de nuevoNodo y se termina la función.
                return;
            }

            // Insertar el nuevo nodo

            nuevoNodo -> setSiguiente(actual -> getSiguiente()); // nuevoNodo se enlaza con el nodo que sigue después de actual.
            actual -> setSiguiente(nuevoNodo); // actual ahora apunta al nuevoNodo.
        }


        // Metodo para eliminar por valor - Jessica Alejandra Gil Tellez //
        // Busca un nodo que contenga _valor y lo elimina de la lista.
        // Retorna true si lo elimina con éxito y false si el valor no existe.
        bool eliminar(const T& _valor){
            Nodo<T>* actual = cabeza; // Puntero que recorrerá la lista, iniciando en cabeza.
            Nodo<T>* anterior = nullptr; // Puntero que mantiene referencia al nodo previo a actual
            while (actual) // Bucle que recorre la lista hasta que actual sea nullptr (final de la lista).
            {
                if(actual->getValor() == _valor){ // Si el nodo actual tiene el valor buscado, se procede a eliminarlo.
                    if(anterior){ //  Si anterior no es nullptr, significa que actual no es la cabeza.
                        anterior -> setSiguiente(actual -> getSiguiente()); //  Se ajusta el puntero siguiente del nodo anterior para que salte actual.
                    }else{ // i anterior == nullptr, significa que actual es la cabeza de la lista.
                        cabeza = actual -> getSiguiente(); // La nueva cabeza será el siguiente nodo.
                    }
                    delete actual; // Elimina el nodo de la memoria.
                    return true; // Devuelve true porque la eliminación fue exitosa.
                }
                anterior = actual;
                actual = actual -> getSiguiente(); // Si actual no contiene _valor, se avanza al siguiente nodo.
            }
            return false; // Si el bucle termina sin encontrar _valor, retorna false.
        }
        
        // size
        
        int get_size() const{return size;} // Retorna el valor de size, que representa la cantidad de nodos en la lista
				// const indica que este método no modifica la lista.
				
        // Metodo para mostrar lista enlazada - Jessica Alejandra Gil Tellez //
        //  Imprime todos los valores de la lista en la consola.
        void mostrar(){
            Nodo<T>* actual = cabeza; // actual empieza en cabeza.
            while (actual != nullptr) // Bucle while recorre la lista, imprimiendo el valor de cada nodo.
            {
                cout << actual->getValor() << endl;
                actual = actual -> getSiguiente();
            }
            cout << " nullptr " << endl; // Cuando llega al final (nullptr), imprime "nullptr" para indicar el fin de la lista.
        }
        
        Nodo<T>* get(int i) const { // Devuelve un puntero al nodo en la posición i.
        // Si i está fuera de rango, retorna nullptr.
        if (i >= 0 && i < size) { // Si i es válido (0 ≤ i < size), entra al if.
            int j = 0; 
            Nodo<T>* actual = cabeza;
            while (j < i) { // // Se inicia un contador j en 0 y se recorre la lista hasta llegar a la posición i.
                actual = actual->getSiguiente();
                j++;
            }
            return actual; // Se retorna el puntero al nodo en la posición i.
        }
        return nullptr; // Si i está fuera del rango, retorna nullptr.
    }
    
};


// Clase Distribuidora - Jessica Alejandra Gil Tellez //
class Distribuidora {
private:
    ListaEnlazada<Venta> ventas; // creacion de lista enlazada que tiene datos de la clase producto
    int** matriz; // Matriz dinámica que almacena la cantidad de ventas realizados por cada vendedor en cada producto.
    int* arreglo;
    int nc; // Cod. cliente
    int nv; // Cod. vendedor
    int np; // Cod. producto
    int ns; // Cod. ventas total


public:
    Distribuidora(int c = 100, int v = 100, int p = 100, int s = 1000): nc(c), nv(v), np(p), ns(s) {
        matriz = crear_mat(nv, np);
        arreglo = crear_arreglo(nv);
    }
    
    // destructor - Jessica Alejandra Gil Tellez //
    ~Distribuidora() {
        destruir_mat(matriz, nv);
        destruir_arreglo(arreglo);
    }
    
    //crear el método init_lista() - Jessica Alejandra Gil Tellez //

    void init_lista() {
        Venta* t;
        int c,v,p;
        for (int i=0;i<ns;i++){
        // Genera nt productos aleatorias, con clientes, vendedores y productos aleatorias.
            c=rand()% nc;
            v=rand()% nv;
            p=rand()% np;
            t=new Venta(c,v,p); // // Crea una nueva producto con los valores generados
            ventas.insertar(*t); // Inserta cada producto en la lista enlazada.
        }
        cout << "Se han generado "<< ventas.get_size()<<" ventas."<<endl;
        ventas.mostrar(); // Imprime la cantidad de ventas generadas y las muestra.
       
    }

    void print() {
        ventas.mostrar();
    }
    
     void generar_arreglo() {
        Nodo<Venta>* ptr = ventas.get(0);
        while (ptr != nullptr) {
            arreglo[ptr->getValor().getVendedor()]++;  // Incrementar el vendedor correspondiente en el arreglo
            ptr = ptr->getSiguiente();
        }
        cout << "Arreglo de vendedores: " << endl;
        print_arreglo(arreglo, nv);  // Imprimir el arreglo con los vendedores y sus ventas
    }
    
    
    //crear el método calcular matriz - Jessica Alejandra Gil Tellez //
    
     void calcular_matriz(){
        Nodo<Venta>* ptr = ventas.get(0); // // Obtiene el primer nodo de la lista
        for (int i=0;i<ns; i++){ // Recorre la lista de productos y actualiza la matriz, aumentando la cantidad de ventas de un vendedor en una producto.
            matriz[ptr->getValor().getVendedor()][ptr->getValor().getProducto()]++; // Esta línea incrementa en 1 el valor de una posición en la matriz matriz
            // getvendedor() devuelve el número del vendedor que está haciendo el venta en esta producto.
            // getproducto() devuelve el número de la producto en la que está vendiendo el vendedor.
            // En general: 1. Accede a la matriz en la posición [vendedor][producto].
            // 2. Incrementa en 1 el valor en esa posición → Registra un nuevo venta.
            // 3. Se repite para cada nodo en la lista enlazada, recorriendo todas las productos.
            ptr = ptr->getSiguiente(); // // Avanza al siguiente nodo
        }
        cout << "Matriz de vendedores por productos: "<<endl;
        print_mat(matriz, nv, np); // Imprime la matriz resultante.
     }

   //crear el método vendedor_con_mas_ventas_por_producto - Jessica Alejandra Gil Tellez //
   
   int vendedor_con_mas_ventas_por_producto(int p){
        int max =0;
        int vendedor=-1; // inicializa max=0 y vendedor=-1 para almacenar el vendedor con más ventas
        for (int i=0;i<nv;i++){ // recorre todos los vendedores
            if (matriz[i][p]>max){ // si el vendedor  tiene mas ventas que max, actualiza maz
                max=matriz[i][p]; 
                vendedor=i;
            }
        }
        return vendedor;
    }
    
    //crear el método calcular_promedio_ventas - Jessica Alejandra Gil Tellez
    
    void calcular_promedio_ventas() {
        int cont = 0;
        float promedio, suma = 0;
        for (int i = 0; i < nv; i++) {
            suma = suma + arreglo[i];
            cont = cont + 1;
        }
        promedio = suma / cont;
        cout << "El promedio de las ventas es: " << promedio << endl;
    }
    
    
};

// Función principal- Jessica Alejandra Gil Tellez //

int main() {
    srand(time(0));  // Inicialización del generador de números aleatorios con el tiempo actual
    int c = 10;
    int v = 10;
    int p = 10;
    int s = 100;
    Distribuidora dis = Distribuidora(c, v, p, s);
    dis.init_lista();
    cout << endl;
    dis.calcular_matriz();
    for (int i = 0; i < p; i++) {
        cout << "El vendedor con más ventas en el producto " << i << " es: " 
             << dis.vendedor_con_mas_ventas_por_producto(i) << endl;
    }
    cout << "-------------Datos del arreglo-------------" << endl;
    dis.generar_arreglo();
    cout<< "------------- Promedio total de ventas------"<<endl;
    dis.calcular_promedio_ventas();
    return 0;
}