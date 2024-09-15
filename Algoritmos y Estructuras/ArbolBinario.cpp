#include "ArbolBinario.h"
#include <iostream>

ArbolBinario::ArbolBinario() : root(nullptr) {}

ArbolBinario::~ArbolBinario() {
    // Aquí podrías implementar un destructor recursivo para eliminar todos los nodos del árbol si fuera necesario.
}

TreeNode* ArbolBinario::insert(TreeNode* node, int data) {
    if (node == nullptr) return new TreeNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);

    return node;
}

void ArbolBinario::insert(int data) {
    root = insert(root, data);
}
