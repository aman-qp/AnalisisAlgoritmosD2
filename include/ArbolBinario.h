#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class ArbolBinario {
private:
    TreeNode* root;
    TreeNode* insert(TreeNode* node, int data);
public:
    ArbolBinario();
    ~ArbolBinario();
    void insert(int data);  // Solo implementamos inserción
};

#endif
