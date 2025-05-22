#include <iostream>

template <typename T>
class BST {
private:
    // Estructura de cada nodo del árbol
    struct Node {
        T data;           // Valor almacenado en el nodo
        Node* left;       // Puntero al hijo izquierdo
        Node* right;      // Puntero al hijo derecho

        // Constructor
        Node(T val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root; // Raíz del árbol

    // Función recursiva para insertar sin permitir duplicados
    Node* insert(Node* node, T value) {
        if (!node) return new Node(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        // Si es igual, no se inserta (no se permiten duplicados)

        return node;
    }

    // Función recursiva para eliminar un valor del árbol
    Node* remove(Node* node, T value) {
        if (!node) return nullptr;

        if (value < node->data)
            node->left = remove(node->left, value);
        else if (value > node->data)
            node->right = remove(node->right, value);
        else {
            // Caso 1: sin hijos
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            // Caso 2: un solo hijo
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Caso 3: dos hijos - buscar sucesor
            Node* successor = findMin(node->right);
            T successorValue = successor->data;
            node->right = remove(node->right, successorValue);
            node->data = successorValue;
        }
        return node;
    }

    // Encuentra el nodo con el valor mínimo
    Node* findMin(Node* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    // Búsqueda recursiva de un valor
    bool search(Node* node, T value) const {
        if (!node) return false;
        if (value < node->data)
            return search(node->left, value);
        else if (value > node->data)
            return search(node->right, value);
        else
            return true;
    }

    // Impresión inorden (izquierda, nodo, derecha)
    void printInOrder(Node* node) const {
        if (!node) return;
        printInOrder(node->left);
        std::cout << node->data << " ";
        printInOrder(node->right);
    }

    // Impresión preorden (nodo, izquierda, derecha)
    void printPreOrder(Node* node) const {
        if (!node) return;
        std::cout << node->data << " ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }

    // Impresión postorden (izquierda, derecha, nodo)
    void printPostOrder(Node* node) const {
        if (!node) return;
        printPostOrder(node->left);
        printPostOrder(node->right);
        std::cout << node->data << " ";
    }

    // Liberar memoria
    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    // Constructor
    BST() : root(nullptr) {}

    // Destructor
    ~BST() {
        destroy(root);
    }

    // Inserción pública
    void insert(T value) {
        if (!search(root, value)) {
            root = insert(root, value);
        } else {
            std::cout << "Valor duplicado no permitido: " << value << "\n";
        }
    }

    // Eliminación pública
    void remove(T value) {
        root = remove(root, value);
    }

    // Búsqueda pública
    bool search(T value) const {
        return search(root, value);
    }

    // Impresiones públicas
    void printInOrder() const {
        printInOrder(root);
        std::cout << std::endl;
    }

    void printPreOrder() const {
        printPreOrder(root);
        std::cout << std::endl;
    }

    void printPostOrder() const {
        printPostOrder(root);
        std::cout << std::endl;
    }
};

// Función principal con menú
int main() {
    BST<int> tree;
    int option, value;

    do {
        std::cout << "\n------ MENÚ DE OPCIONES ------\n";
        std::cout << "1. Insertar valor\n";
        std::cout << "2. Buscar valor\n";
        std::cout << "3. Eliminar valor\n";
        std::cout << "4. Imprimir inorden\n";
        std::cout << "5. Imprimir preorden\n";
        std::cout << "6. Imprimir postorden\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> option;

        switch (option) {
            case 1:
                std::cout << "Ingrese el valor a insertar: ";
                std::cin >> value;
                tree.insert(value);
                break;
            case 2:
                std::cout << "Ingrese el valor a buscar: ";
                std::cin >> value;
                if (tree.search(value))
                    std::cout << "Valor encontrado\n";
                else
                    std::cout << "Valor no encontrado\n";
                break;
            case 3:
                std::cout << "Ingrese el valor a eliminar: ";
                std::cin >> value;
                tree.remove(value);
                break;
            case 4:
                std::cout << "Recorrido inorden: ";
                tree.printInOrder();
                break;
            case 5:
                std::cout << "Recorrido preorden: ";
                tree.printPreOrder();
                break;
            case 6:
                std::cout << "Recorrido postorden: ";
                tree.printPostOrder();
                break;
            case 0:
                std::cout << "Saliendo del programa.\n";
                break;
            default:
                std::cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (option != 0);

    return 0;
}