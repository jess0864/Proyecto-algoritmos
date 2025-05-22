#include <iostream>
#include <stdexcept>
#include <algorithm>

// -------------------- Clase AvlTree --------------------

template <typename T>
class AvlTree {
public:
    // Constructor de la clase, inicializa el árbol vacío
    AvlTree() : root(nullptr) {}

    // Destructor, limpia el árbol llamando a makeEmpty para liberar memoria
    ~AvlTree() { makeEmpty(root); }

    // Función para insertar un valor en el árbol
    void insert(const T &x) { insert(x, root); }

    // Función para eliminar un valor del árbol
    void remove(const T &x) { remove(x, root); }

    // Función para comprobar si un valor existe en el árbol
    bool contains(const T &x) const { return contains(x, root); }

    // Función para verificar si el árbol está vacío
    bool isEmpty() const { return root == nullptr; }

    // Función para encontrar el valor mínimo del árbol
    const T &findMin() const {
        if (isEmpty()) throw std::runtime_error("Árbol vacío");
        return findMinNode(root)->element;
    }

    // Función para encontrar el valor máximo del árbol
    const T &findMax() const {
        if (isEmpty()) throw std::runtime_error("Árbol vacío");
        return findMaxNode(root)->element;
    }

    // Función para imprimir el árbol en recorrido INORDEN
    void printInOrder(std::ostream &out = std::cout) const {
        if (isEmpty()) out << "Árbol vacío\n";
        else printInOrder(root, out);
    }

    // Función para imprimir el árbol en recorrido PREORDEN
    void printPreOrder(std::ostream &out = std::cout) const {
        if (isEmpty()) out << "Árbol vacío\n";
        else printPreOrder(root, out);
    }

    // Función para imprimir el árbol en recorrido POSTORDEN
    void printPostOrder(std::ostream &out = std::cout) const {
        if (isEmpty()) out << "Árbol vacío\n";
        else printPostOrder(root, out);
    }

private:
    // Estructura interna para representar un nodo en el árbol
    struct AvlNode {
        T element;      // Elemento almacenado en el nodo
        AvlNode *left;  // Puntero al subárbol izquierdo
        AvlNode *right; // Puntero al subárbol derecho
        int height;     // Altura del nodo

        // Constructor de un nodo
        AvlNode(const T &e, AvlNode *lt = nullptr, AvlNode *rt = nullptr, int h = 0)
            : element{e}, left{lt}, right{rt}, height{h} {}
    };

    AvlNode *root;  // Puntero a la raíz del árbol

    // Constante para definir el desequilibrio permitido
    static const int ALLOWED_IMBALANCE = 1;

    // Función para obtener la altura de un nodo
    int height(AvlNode *t) const { return t == nullptr ? -1 : t->height; }

    // Función que equilibra el árbol si es necesario
    void balance(AvlNode *&t) {
        if (!t) return; // Si el nodo está vacío, no hace nada

        // Si el árbol está desequilibrado hacia el subárbol izquierdo
        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
            // Si el subárbol izquierdo está desequilibrado hacia la izquierda
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);
            // Si el subárbol izquierdo está desequilibrado hacia la derecha
            else doubleWithLeftChild(t);
        }
        // Si el árbol está desequilibrado hacia el subárbol derecho
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
            // Si el subárbol derecho está desequilibrado hacia la derecha
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t);
            // Si el subárbol derecho está desequilibrado hacia la izquierda
            else doubleWithRightChild(t);
        }

        // Actualiza la altura del nodo
        t->height = std::max(height(t->left), height(t->right)) + 1;
    }

    // Rotación simple hacia la izquierda (para corregir desequilibrio)
    void rotateWithLeftChild(AvlNode *&k2) {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = std::max(height(k2->left), height(k2->right)) + 1;
        k1->height = std::max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    // Rotación simple hacia la derecha (para corregir desequilibrio)
    void rotateWithRightChild(AvlNode *&k2) {
        AvlNode *k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = std::max(height(k2->left), height(k2->right)) + 1;
        k1->height = std::max(height(k1->right), k2->height) + 1;
        k2 = k1;
    }

    // Rotación doble hacia la izquierda (para corregir desequilibrio)
    void doubleWithLeftChild(AvlNode *&k3) {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    // Rotación doble hacia la derecha (para corregir desequilibrio)
    void doubleWithRightChild(AvlNode *&k3) {
        rotateWithLeftChild(k3->right);
        rotateWithRightChild(k3);
    }

    // Función para insertar un valor en el árbol
    void insert(const T &x, AvlNode *&t) {
        if (!t)
            t = new AvlNode{x}; // Si el nodo está vacío, creamos un nuevo nodo
        else if (x < t->element)
            insert(x, t->left); // Si el valor es menor, insertamos en el subárbol izquierdo
        else if (x > t->element)
            insert(x, t->right); // Si el valor es mayor, insertamos en el subárbol derecho
        balance(t); // Balanceamos el árbol después de insertar
    }

    // Función para eliminar un valor del árbol
    void remove(const T &x, AvlNode *&t) {
        if (!t) return; // Si el nodo está vacío, no hacemos nada

        // Si el valor es menor que el nodo actual, lo buscamos en el subárbol izquierdo
        if (x < t->element)
            remove(x, t->left);
        // Si el valor es mayor, lo buscamos en el subárbol derecho
        else if (x > t->element)
            remove(x, t->right);
        // Si el valor es igual, eliminamos el nodo
        else if (t->left && t->right) { // Nodo con dos hijos
            t->element = findMinNode(t->right)->element; // Reemplazamos con el valor más pequeño del subárbol derecho
            remove(t->element, t->right); // Eliminamos ese nodo
        } else { // Nodo con uno o cero hijos
            AvlNode *old = t;
            t = (t->left != nullptr) ? t->left : t->right; // Eliminamos el nodo y lo reemplazamos por su hijo
            delete old;
        }

        balance(t); // Balanceamos el árbol después de eliminar
    }

    // Función para encontrar el nodo con el valor mínimo
    AvlNode *findMinNode(AvlNode *t) const {
        while (t->left) t = t->left; // Nos movemos hacia el nodo más a la izquierda
        return t;
    }

    // Función para encontrar el nodo con el valor máximo
    AvlNode *findMaxNode(AvlNode *t) const {
        while (t->right) t = t->right; // Nos movemos hacia el nodo más a la derecha
        return t;
    }

    // Función para comprobar si un valor existe en el árbol
    bool contains(const T &x, AvlNode *t) const {
        if (!t) return false; // Si el nodo está vacío, el valor no está
        if (x < t->element)
            return contains(x, t->left); // Buscamos en el subárbol izquierdo
        else if (x > t->element)
            return contains(x, t->right); // Buscamos en el subárbol derecho
        else
            return true; // El valor está en el nodo actual
    }

    // Función para imprimir el árbol en recorrido INORDEN
    void printInOrder(AvlNode *t, std::ostream &out) const {
        if (!t) return; // Si el nodo está vacío, no hacemos nada
        printInOrder(t->left, out); // Imprimimos el subárbol izquierdo
        out << t->element << " ";  // Imprimimos el valor del nodo
        printInOrder(t->right, out); // Imprimimos el subárbol derecho
    }

    // Función para imprimir el árbol en recorrido PREORDEN
    void printPreOrder(AvlNode *t, std::ostream &out) const {
        if (!t) return; // Si el nodo está vacío, no hacemos nada
        out << t->element << " ";  // Imprimimos el valor del nodo
        printPreOrder(t->left, out); // Imprimimos el subárbol izquierdo
        printPreOrder(t->right, out); // Imprimimos el subárbol derecho
    }

    // Función para imprimir el árbol en recorrido POSTORDEN
    void printPostOrder(AvlNode *t, std::ostream &out) const {
        if (!t) return; // Si el nodo está vacío, no hacemos nada
        printPostOrder(t->left, out); // Imprimimos el subárbol izquierdo
        printPostOrder(t->right, out); // Imprimimos el subárbol derecho
        out << t->element << " ";  // Imprimimos el valor del nodo
    }

    // Función para liberar la memoria del árbol
    void makeEmpty(AvlNode *&t) {
        if (!t) return; // Si el nodo está vacío, no hacemos nada
        makeEmpty(t->left); // Liberamos el subárbol izquierdo
        makeEmpty(t->right); // Liberamos el subárbol derecho
        delete t; // Liberamos el nodo actual
        t = nullptr; // Ponemos el puntero a null para evitar el uso de memoria no válida
    }
};

// -------------------- Menú principal --------------------

int main() {
    AvlTree<int> tree;  // Creamos un árbol AVL de enteros
    int option, value;

    do {
        // Imprimimos el menú de opciones
        std::cout << "\n------ MENÚ DE OPCIONES ------\n";
        std::cout << "1. Insertar valor\n";
        std::cout << "2. Buscar valor\n";
        std::cout << "3. Eliminar valor\n";
        std::cout << "4. Imprimir INORDEN\n";
        std::cout << "5. Mostrar mínimo\n";
        std::cout << "6. Mostrar máximo\n";
        std::cout << "7. Imprimir PREORDEN\n";
        std::cout << "8. Imprimir POSTORDEN\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> option;

        // Ejecutamos según la opción seleccionada
        switch (option) {
            case 1:
                std::cout << "Ingrese el valor a insertar: ";
                std::cin >> value;
                tree.insert(value);  // Insertamos el valor
                break;
            case 2:
                std::cout << "Ingrese el valor a buscar: ";
                std::cin >> value;
                std::cout << (tree.contains(value) ? "Valor encontrado\n" : "Valor no encontrado\n");
                break;
            case 3:
                std::cout << "Ingrese el valor a eliminar: ";
                std::cin >> value;
                tree.remove(value);  // Eliminamos el valor
                break;
            case 4:
                std::cout << "Recorrido inorden: ";
                tree.printInOrder();  // Imprimimos el recorrido inorden
                std::cout << "\n";
                break;
            case 5:
                try {
                    std::cout << "Valor mínimo: " << tree.findMin() << "\n"; // Mostramos el valor mínimo
                } catch (const std::runtime_error &e) {
                    std::cout << e.what() << "\n";  // Si el árbol está vacío, mostramos un error
                }
                break;
            case 6:
                try {
                    std::cout << "Valor máximo: " << tree.findMax() << "\n"; // Mostramos el valor máximo
                } catch (const std::runtime_error &e) {
                    std::cout << e.what() << "\n";  // Si el árbol está vacío, mostramos un error
                }
                break;
            case 7:
                std::cout << "Recorrido preorden: ";
                tree.printPreOrder();  // Imprimimos el recorrido preorden
                std::cout << "\n";
                break;
            case 8:
                std::cout << "Recorrido postorden: ";
                tree.printPostOrder();  // Imprimimos el recorrido postorden
                std::cout << "\n";
                break;
            case 0:
                std::cout << "Saliendo del programa.\n";
                break;
            default:
                std::cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (option != 0);  // El programa sigue corriendo hasta que se seleccione la opción 0

    return 0;
}