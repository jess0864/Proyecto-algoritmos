#include <iostream>
#include <vector>
using namespace std;

void imprimir_vec(vector<int>& v, int size){
    for (int i=0; i<size; i++){
        cout<<v[i]<<"  ";
    }
}

// Métodos de ordenamiento

void bubbleSort(vector<int>& A, int size){
    for (int i=0;i<4;i++){
	    for(int j=i+1;j<5;j++){
		    if(A[i]>=A[j]){
    			int aux=A[i];
    			A[i]=A[j];
    			A[j]=aux;
		    }
	    }
    }
    imprimir_vec(A,size);
}

void ordenamientoInsercion(vector<int>& A, int size){
    for (int i=1;i<size;i++){
        int aux=A[i];
        int k=i-1;
        bool sw=false;
        
        while(k>=0 && sw==false){
            if(aux<A[k]){
                A[k+1]=A[k];
                k=k-1;
            }else{
                sw=true;
            }
        }
        A[k+1]=aux;
    }
    imprimir_vec(A,size);
    
}

void selectionSort(vector<int>& arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
    imprimir_vec(arr,size);
}

void shellSort(vector<int>& L, int n) {
    int S= n / 2; //Calculamos el valor inicial de s
    int i, j, k, aux;
    
    // Mientras S sea maypr que 0
    while (S > 0) {
        // recorremos el arreglo desde el indice S hasta el final
        for (i = S; i < n; i++) {
            j = i -S; // Inicializamos j con la diferencia i - S
            // Realizamos el ciclo de intercambio
            while (j >= 0) {
                k = j + S;
                
                if (L[j] <= L[k]) {
                    j = -1; //Rompemos el ciclo si ya están ordenados
                } else {
                    //Intercambiamos los valores
                    aux = L[j];
                    L[j] = L[k];
                    L[k] = aux;
                }
                // Decrementamos j en función de S
                j = j - S;
            }
        }
        // Reducimos el valor de s
        S = S / 2;
    }
    imprimir_vec(L,n);
}

namespace quicksort_util {
    /**
     *  Función de participación para QuickSort.
     * Reorganiza el arrsy de manera que todos los elementos menores o iguales al pivote
     * queden a su izquierda, y todos los mayores queden a su derecha.
     * 
     * @param arr Vector de enteros a particionar.
     * @param low Indice inicial del subarreglo.
     * @param high Indice final del subarreglo, usado como pivote.
     * @return El índice donde se colloca el pivote.
     */
     int partition(std::vector<int>& arr, int low, int high) {
         int pivot = arr[high]; //El pivote es el último elementos
         int i = low - 1; // Indice del elemento más pequeño
         
         // Recorre el subarreglo aomparando con el pivote
         for (int j = low; j < high; j++) {
             if (arr[j] <= pivot) {
                 i++; // Incrementa el índice del elemento más pequeño
                 std::swap(arr[i], arr[j]); //Intercambia elementos
             }
         }
         // Coloca el pivote en su posición correcta
         std::swap(arr[i + 1], arr[high]);
         return i + 1; // Devuelve la posición final del pivote
     }
}

/**
 *  Función recursiva de QuickSort.
 *  Ordena el vector utilizando el algoritmo QuickSort.
 * 
 * @param arr Vector de enteros a ordenar.
 * @param low Índice incial del subarreglo.
 * @param high Índice final del subarreglo.
 */
 void quickSort(std::vector<int>& arr, int low, int high) {
     if (low < high) {
         // Realiza la partición y obtione el índice de pívote
         int pivotIndex = quicksort_util::partition(arr, low, high);
         // Ordena los elementos a la izquierda del pívote 
         quickSort(arr, low, pivotIndex - 1);
         // Ordena los elementos a la derecha del pívote
         quickSort(arr, pivotIndex + 1, high);
     }
 }
 
 void merge(vector<int>& arr, int left, int mid, int right) {
    // Calcula el tamaño de los dos subarreglos a combinar
    int n1 = mid - left + 1;    // Tamaño del subarreglo izquierdo
    int n2 = right - mid;       // Tamaño del subarreglo derecho
    
    // Crear arreglos temporales para almacenar los dos subarreglos
    vector<int> L(n1);          // Vector temporal para el subarreglo izquierdo
    vector<int> R(n2);          // Vector temporal para el subarreglo derecho
    
    // Copiar los datos a los arreglos temporales
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];   // Copia elementos al subarreglo izquierdo
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j]; // Copia elementos al subarreglo derecho
    
    // Combinar los arreglos temporales de vuelta en arr[left...right]
    int i = 0;      // Índice para recorrer el subarreglo izquierdo
    int j = 0;      // Índice para recorrer el subarreglo derecho
    int k = left;   // Índice para colocar elementos en el arreglo combinado
    
    // Mientras haya elementos en ambos subarreglos
    while (i < n1 && j < n2) {
        // Comparar elementos de ambos subarreglos
        if (L[i] <= R[j]) {
            arr[k] = L[i];      // Si el elemento izquierdo es menor o igual, se coloca primero
            i++;                // Avanza al siguiente elemento del subarreglo izquierdo
        }
        else {
            arr[k] = R[j];      // Si el elemento derecho es menor, se coloca primero
            j++;                // Avanza al siguiente elemento del subarreglo derecho
        }
        k++;                    // Avanza a la siguiente posición en el arreglo combinado
    }
    
    // Si quedan elementos en el subarreglo izquierdo, copiarlos al arreglo combinado
    while (i < n1) {
        arr[k] = L[i];          // Copia el elemento actual del subarreglo izquierdo
        i++;                    // Avanza al siguiente elemento del subarreglo izquierdo
        k++;                    // Avanza a la siguiente posición en el arreglo combinado
    }
    
    // Si quedan elementos en el subarreglo derecho, copiarlos al arreglo combinado
    while (j < n2) {
        arr[k] = R[j];          // Copia el elemento actual del subarreglo derecho
        j++;                    // Avanza al siguiente elemento del subarreglo derecho
        k++;                    // Avanza a la siguiente posición en el arreglo combinado
    }
}

/**
 * Función principal de MergeSort que ordena arr[left...right] usando recursión
 * @param arr: Vector a ordenar
 * @param left: Índice inicial del subarreglo a ordenar
 * @param right: Índice final del subarreglo a ordenar
 */
void mergeSort(vector<int>& arr, int left, int right) {
    // Caso base: si left >= right, el subarreglo tiene 0 o 1 elemento (ya está ordenado)
    if (left < right) {
        // Encontrar el punto medio para dividir el arreglo en dos partes
        int mid = left + (right - left) / 2;  // Equivalente a (left+right)/2 pero evita desbordamiento
        
        // Llamadas recursivas para ordenar las dos mitades
        mergeSort(arr, left, mid);            // Ordena la primera mitad
        mergeSort(arr, mid + 1, right);       // Ordena la segunda mitad
        
        // Combina las dos mitades ordenadas
        merge(arr, left, mid, right);
    }
}
 
 
 // Métodos de búsqueda
 
 // Función para realizar una búsqueda secuencial
int busquedaSecuencial(vector<int>& arreglo, int n, int valor) {
    // Recorrer el arreglo buscando el valor
    for (int i = 0; i < n; i++) {
        if (arreglo[i] == valor) {
            return i; // Retorna la posición donde se encontró el valor
        }
    }
    return -1; // Retorna -1 si no se encuentra el valor
}

int busquedaBinaria(vector<int>& arreglo, int n, int valor) {
    int bajo = 0;
    int alto = n - 1;
    while (bajo <= alto) {
        int medio = bajo + (alto - bajo) / 2;  // Calcula el índice medio

       if (arreglo[medio] == valor) {
            return medio;  // Retorna la posición donde se encontró el valor
        }        
      if (arreglo[medio] < valor) {
            bajo = medio + 1;
        }
      else {
            alto = medio - 1;
        }
    }    
    return -1;  // Retorna -1 si no se encuentra el valor
}

// Creación indice para busqueda Indexada
vector<int> crearIndice(const vector<int>& lista, int bloque) {
    vector<int> indice;
    int n = lista.size();

    // Crear el índice tomando el primer elemento de cada bloque
    for (int i = 0; i < n; i += bloque) {
        indice.push_back(lista[i]);  
    }

    return indice;
}


int busquedaIndexada(const std::vector<int>& lista, const std::vector<int>& indice, int elementoBuscado) {
    int tamanoIndice = indice.size();
    int tamanoLista = lista.size();
    int bloque = tamanoLista / tamanoIndice; // Calculate block size based on index
    
    // Recorrer el índice
    for (int i = 0; i < tamanoIndice; ++i) {
        // Si el elemento está en el índice
        if (indice[i] == elementoBuscado) {
            return i * bloque; // Elemento encontrado en el índice
        }        
        // Si el valor en el índice es mayor que el elemento buscado
        if (indice[i] > elementoBuscado) {
            // Solo buscar en bloques después del primero (i > 0)
            if (i > 0) {
                int inicio = (i - 1) * bloque;  // Determinamos el rango de inicio
                int fin = i * bloque;           // Determinamos el rango de fin
                // Buscar el elemento en el rango de la lista
                for (int j = inicio; j < fin && j < tamanoLista; ++j) {
                    if (lista[j] == elementoBuscado) {
                        return j; // Elemento encontrado en la lista
                    }
                }
            }
            break; // Si el elemento no está en el rango, no está en la lista
        }
    }
    
    // Verificar en el último bloque si no encontramos el elemento antes
    int ultimoBloque = (tamanoIndice - 1) * bloque;
    for (int j = ultimoBloque; j < tamanoLista; ++j) {
        if (lista[j] == elementoBuscado) {
            return j; // Elemento encontrado en el último bloque
        }
    }
    
    return -1; // Elemento no encontrado
}



void leer_v(vector<int>& v, int size){
    int i,r=0;
    for (i=0;i<size;i++){
        r=rand()%100;
        v[i]=r;
        cout<<v[i]<<"  ";
    }    
}



int main()
{
    int size;
    cout << "Ingrese el tamaño del arreglo: ";
    cin >> size;

    vector<int> v(size);
    int metodo, opcion;
    cout<<"Arreglo original"<<endl;
    leer_v(v, size);
    cout<<endl;
    cout<<"Que desea hacer:\n1. Ordenar el arreglo\n2. Buscar un dato en el arreglo\nEscriba 1 o 2"<<endl;
    cin>>opcion;
    if (opcion==1){
        cout<<"Con que método desea ordenar el arreglo:\n1. Bubble Sort \n2. Insert Sort\n3. Selection Sort \n4. Shell Sort\n5. Quick Sort\n6. Merge Sort\nEscriba 1, 2, 3, 4, 5 o 6 dependiendo del método"<<endl;
        cin>>metodo;
        if (metodo==1){
            cout<<"Arreglo ordenado por Bubble Sort:"<<endl;
            bubbleSort(v,size);
        }
        else if(metodo==2){
            cout<<"Arreglo ordenado por Insert Sort:"<<endl;
            ordenamientoInsercion(v,size);
        }
        else if(metodo==3){
            cout<<"Arreglo ordenado por Selection Sort:"<<endl;
            selectionSort(v,size);
        }
        else if(metodo==4){
            cout<<"Arreglo ordenado por ShellSort Sort:"<<endl;
            shellSort(v,size);
        }
        else if(metodo==5){
            cout<<"Arreglo ordenado por Quick Sort:"<<endl;
            quickSort(v,0,size-1);
            imprimir_vec(v,size);
        }
        else if(metodo==6){
            cout<<"Arreglo ordenado por merge sort"<<endl;
            mergeSort(v,0,size-1);
            imprimir_vec(v,size);
        }
        else{
            cout<<"Método de ordenamiento no identificado"<<endl;
        }
    }
    else if(opcion==2){
        cout<<"Con que método desea buscar en el arreglo\n1. Búsqueda Secuencial\n2. Búsqueda Binaria\n3. Búsqueda Indexada\nEscriba 1,2 o 3"<<endl;
        cin>>metodo;
        cout<<"Que elemento desea buscar: ";
        int elemento;
        cin>>elemento;
        if (metodo==1){
            cout<<"El elemento que busca se encuentra en la posición: "<<busquedaSecuencial(v, size, elemento)<<endl;
        }
        else if(metodo==2){
            quickSort(v,0,size-1);
            cout<<"Arreglo ordenado para hacer la busqueda binaria"<<endl;
            imprimir_vec(v,size);
            cout<<endl;
            cout<<"El elemento que busca se encuentra en la posición: "<<busquedaBinaria(v, size, elemento)<<endl;
        }
        else if(metodo==3){
            quickSort(v,0,size-1);
            vector<int> indice = crearIndice(v, size);
            cout<<"Arreglo ordenado para hacer la busqueda Indexada"<<endl;
            imprimir_vec(v,size);
            cout<<endl;
            cout<<"El elemento que busca se encuentra en la posición: "<<busquedaIndexada(v, indice, elemento)<<endl;
        }
        else{
            cout<<"Método de busqueda no valido"<<endl;
        }
    }
    else{
        cout<<"Opción no valida"<<endl;
    }
    
    return 0;
}
