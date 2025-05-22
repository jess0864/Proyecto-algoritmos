int busquedaBinaria(int arreglo[], int n, int valor) {
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
