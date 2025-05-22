#include <iostream>
using namespace std;

// TreeNode structure for general trees
struct TreeNode {
    char element;
    TreeNode* firstChild;
    TreeNode* nextSibling;

    TreeNode(char val) : element(val), firstChild(nullptr), nextSibling(nullptr) {}
};

// Pre-order traversal: visit -> children -> siblings
void preOrder(TreeNode* node) {
    if (node == nullptr) return;

    cout << node->element << " ";
    preOrder(node->firstChild);
    preOrder(node->nextSibling);
}

int main() {
    // Creating nodes
    TreeNode* A = new TreeNode('A');
    TreeNode* B = new TreeNode('B');
    TreeNode* C = new TreeNode('C');
    TreeNode* D = new TreeNode('D');
    TreeNode* E = new TreeNode('E');
    TreeNode* F = new TreeNode('F');
    TreeNode* G = new TreeNode('G');

    // Building the tree structure
    A->firstChild = B;             // A has B as first child
    B->nextSibling = C;           // B and C are children of A

    B->firstChild = D;            // B has D as first child
    D->nextSibling = E;           // D and E are children of B

    C->firstChild = F;            // C has F as first child
    F->nextSibling = G;           // F and G are children of C

    // Traversal
    cout << "Pre-order traversal: ";
    preOrder(A);
    cout << endl;

    return 0;
}